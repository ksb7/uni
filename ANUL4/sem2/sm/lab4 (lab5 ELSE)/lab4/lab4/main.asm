.include "m32def.inc"

.def flags = r2
.def cnt   = r3
.def temp  = r16
.def RezL  = r17
.def RezH  = r18
.def pos   = r19
.def tmpL  = r20
.def tmpH  = r21

.dseg
    Display: .byte 4

.cseg
.org 0x0000
    rjmp RESET

.org INT0addr
    reti
.org INT1addr
    reti
.org INT2addr
    reti
.org OC2addr
    reti
.org OVF2addr
    reti
.org ICP1addr
    reti
.org OC1Aaddr
    rjmp TIMER1_ISR     
.org OC1Baddr
    reti
.org OVF1addr
    reti
.org OC0addr
    rjmp Display_Next  
.org OVF0addr
    reti
.org SPIaddr
    reti
.org URXCaddr
    reti
.org UDREaddr
    reti
.org UTXCaddr
    reti
.org ADCCaddr
    rjmp End_Conversion
.org ERDYaddr
    reti
.org ACIaddr
    reti
.org TWIaddr
    reti
.org SPMRaddr
    reti

RESET:
    ldi temp, Low(RAMEND)
    out SPL, temp
    ldi temp, High(RAMEND)
    out SPH, temp

    clr temp
    out DDRA, temp
    ldi temp, 0x0F
    out DDRB, temp
    ser temp
    out DDRD, temp

    ; Initialize Display buffer with '0'
    ldi XL, Low(Display)
    ldi XH, High(Display)
    ldi temp, 0x3F
    st X+, temp
    st X+, temp
    st X+, temp
    st X+, temp

    ; Reset X and pos
    ldi XL, Low(Display)
    ldi XH, High(Display)
    ldi pos, ~(1<<3)

    clr RezL
    clr RezH
    clr tmpL
    clr tmpH

    ; Timer0 for display
    ldi temp, 156
    out OCR0, temp
    ldi temp, (1<<WGM01)|(1<<CS02)|(1<<CS00)
    out TCCR0, temp

    ; Timer1 for 1kHz
    ldi temp, High(1249)
    out OCR1AH, temp
    ldi temp, Low(1249)
    out OCR1AL, temp
    ldi temp, (1<<WGM12)|(1<<CS11)
    out TCCR1B, temp
    clr temp
    out TCCR1A, temp

    ldi temp, (1<<OCIE0)|(1<<OCIE1A)
    out TIMSK, temp

    ; ADC - start first conversion manually with ADSC
    ldi temp, (1<<REFS0)|0x01
    out ADMUX, temp
    ldi temp, (1<<ADEN)|(1<<ADIE)|(1<<ADSC)|(1<<ADPS2)|(1<<ADPS1)
    out ADCSRA, temp

    sei

MAIN:
    rjmp MAIN

TIMER1_ISR:
    in flags, SREG
    push temp

    ; Select ADC1 and start conversion
    ldi temp, (1<<REFS0)|0x01
    out ADMUX, temp
    ldi temp, (1<<ADEN)|(1<<ADIE)|(1<<ADSC)|(1<<ADPS2)|(1<<ADPS1)
    out ADCSRA, temp

    pop temp
    out SREG, flags
    reti

Display_Next:
    in flags, SREG
    push temp

    ; Turn off all digits
    ldi temp, 0x0F
    out PORTB, temp

    ; Output segment code for current digit
    ld temp, X+
    out PORTD, temp

    ; Activate current digit
    out PORTB, pos

    ; Advance digit position
    asr pos
    brcs end_display

    ; Reset to first digit
    ldi pos, ~(1<<3)
    ldi XL, Low(Display)
    ldi XH, High(Display)

end_display:
    pop temp
    out SREG, flags
    reti

End_Conversion:
    in flags, SREG
    push temp

    ; Check which channel finished
    in temp, ADMUX
    andi temp, 0x1F
    cpi temp, 0x01          ; check if ADC1
    brne Channel2

    ; ADC1 done — save, switch to ADC2
    in tmpL, ADCL
    in tmpH, ADCH

    ldi temp, (1<<REFS0)|0x02       ; switch to ADC2
    out ADMUX, temp
    ldi temp, (1<<ADEN)|(1<<ADIE)|(1<<ADSC)|(1<<ADPS2)|(1<<ADPS1)
    out ADCSRA, temp

    pop temp
    out SREG, flags
    reti

Channel2:
    ; ADC2 done — compute ADC1 minus ADC2
    in RezL, ADCL
    in RezH, ADCH

    ; ADC1 - ADC2
    sub tmpL, RezL
    sbc tmpH, RezH

    ; Clamp to 0 if negative
    brpl store_result
    clr tmpL
    clr tmpH

store_result:
    mov RezL, tmpL
    mov RezH, tmpH

    ; Convert to decimal and store in Display[]
    rcall Convert

    pop temp
    out SREG, flags
    reti

Convert:
    push tmpL
    push tmpH

    ; Thousands
    clr cnt
    ldi tmpL, Low(1000)
    ldi tmpH, High(1000)
Mie:
    cp RezL, tmpL
    cpc RezH, tmpH
    brlo end_Mie
    sub RezL, tmpL
    sbc RezH, tmpH
    inc cnt
    rjmp Mie
end_Mie:
    ldi ZL, Low(CodeTable*2)
    ldi ZH, High(CodeTable*2)
    add ZL, cnt
    clr cnt
    adc ZH, cnt
    lpm tmpL, Z
    sts Display+3, tmpL

    ; Hundreds
    clr cnt
    ldi tmpL, Low(100)
    ldi tmpH, High(100)
Sute:
    cp RezL, tmpL
    cpc RezH, tmpH
    brlo end_Sute
    sub RezL, tmpL
    sbc RezH, tmpH
    inc cnt
    rjmp Sute
end_Sute:
    ldi ZL, Low(CodeTable*2)
    ldi ZH, High(CodeTable*2)
    add ZL, cnt
    clr cnt
    adc ZH, cnt
    lpm tmpL, Z
    sts Display+2, tmpL

    ; Tens
    clr cnt
    ldi tmpL, Low(10)
    ldi tmpH, High(10)
Zeci:
    cp RezL, tmpL
    cpc RezH, tmpH
    brlo end_Zeci
    sub RezL, tmpL
    sbc RezH, tmpH
    inc cnt
    rjmp Zeci
end_Zeci:
    ldi ZL, Low(CodeTable*2)
    ldi ZH, High(CodeTable*2)
    add ZL, cnt
    clr cnt
    adc ZH, cnt
    lpm tmpL, Z
    sts Display+1, tmpL

    ; === Units ===
    ldi ZL, Low(CodeTable*2)
    ldi ZH, High(CodeTable*2)
    add ZL, RezL
    adc ZH, RezH
    lpm tmpL, Z
    sts Display, tmpL

    pop tmpH
    pop tmpL
    ret

; 7-segment codes 0-9 (Common Cathode)
CodeTable:
    .db 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F