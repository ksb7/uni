.include "m32def.inc"

.equ BitRate = 287     ; 2400 baud @ 11.0592 MHz

.def flags = r2
.def tempL = r16
.def tempH = r17
.def dataL = r18
.def dataH = r19
.def adc3L = r20
.def adc3H = r21
.def icnt  = r22

.dseg
VideoBuff:  .byte 4
ADCResults: .byte 4

.cseg

.org 0x0000
    rjmp RESET
.org	UDREaddr	; adresa vect de intrer ce se va apela atita timp cit in emitator va mai fi spatiu
	rjmp TRANSMIT

.org	UTXCaddr	; USART Transmit Complete Interrupt Vector Address
	reti

.org	ADCCaddr	; adr de intr la sfirsit conv de la adc
	rjmp End_Conversion


;====================================================
; ADC INTERRUPT (MANUAL SEQUENCE)
;====================================================
End_Conversion:
    in flags, SREG

    in tempL, ADCL
    in tempH, ADCH

    in r16, ADMUX
    andi r16, 0x01

    cpi r16, 0x01
    breq SAVE_ADC3

;---------------- ADC1 ----------------
SAVE_ADC1:
    sts ADCResults, tempL
    sts ADCResults+1, tempH

    ldi tempL, (1<<REFS0)|0x03   ; select ADC3
    out ADMUX, tempL

    sbi ADCSRA, ADSC            ; start next conversion
    rjmp ADC_DONE

;---------------- ADC3 ----------------
SAVE_ADC3:
    sts ADCResults+2, tempL
    sts ADCResults+3, tempH

    ldi tempL, (1<<REFS0)|0x01   ; select ADC1
    out ADMUX, tempL

    sbi ADCSRA, ADSC            ; start next conversion

ADC_DONE:
    out SREG, flags
    reti

;====================================================
; UART TX ISR
;====================================================
TRANSMIT:
    in flags, SREG

    ld tempL, Y+
    out UDR, tempL

    dec icnt
    brne TX_END

    cbi UCSRB, UDRIE

TX_END:
    out SREG, flags
    reti

;====================================================
; RESET
;====================================================
RESET:
    ; stack
    ldi tempL, low(RAMEND)
    out SPL, tempL
    ldi tempL, high(RAMEND)
    out SPH, tempL

    clr tempL
    out DDRA, tempL

    ;---------------- ADC (NO FREE RUN!) ----------------
    ldi tempL, (1<<REFS0)|0x01
    out ADMUX, tempL

    ldi tempL, (1<<ADEN)|(1<<ADIE)|(1<<ADPS2)
    out ADCSRA, tempL

    sbi ADCSRA, ADSC      ; start first conversion

    ;---------------- UART ----------------
    ldi tempL, high(BitRate)
    out UBRRH, tempL
    ldi tempL, low(BitRate)
    out UBRRL, tempL

    clr tempL
    out UCSRA, tempL

    ldi tempL, (1<<TXEN)
    out UCSRB, tempL

    ldi tempL, (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0)
    out UCSRC, tempL

    sei

;====================================================
; MAIN
;====================================================
MAIN:
    cli
    lds dataL, ADCResults
    lds dataH, ADCResults+1

    lds adc3L, ADCResults+2
    lds adc3H, ADCResults+3
    sei

    ; 2 * ADC1
    lsl dataL
    rol dataH

    ; + ADC3
    add dataL, adc3L
    adc dataH, adc3H

    ; FRAME: # BH BL LF
    ldi ZL, low(VideoBuff)
    ldi ZH, high(VideoBuff)

    ldi tempL, '#'
    st Z+, tempL

    mov tempL, dataH
    st Z+, tempL

    mov tempL, dataL
    st Z+, tempL

    ldi tempL, 0x0A
    st Z, tempL

    ; UART SEND
    ldi icnt, 4
    ldi YL, low(VideoBuff)
    ldi YH, high(VideoBuff)

    ld tempL, Y+
    out UDR, tempL
    dec icnt

    in tempL, UCSRB
    ori tempL, (1<<UDRIE)
    out UCSRB, tempL

WAIT_TX:
    sbic UCSRB, UDRIE
    rjmp WAIT_TX

    rjmp MAIN