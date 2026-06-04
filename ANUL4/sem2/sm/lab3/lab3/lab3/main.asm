.include "m32def.inc"

.def tmpL    = r16
.def tmpH    = r17
.def dispIdx = r18
.def segCode = r19

.cseg
.org 0x0000
    rjmp RESET
.org OC1Aaddr
    rjmp TIMER1_ISR

MSG:
    .db 0x66, 0xFC  ; 4, 0
    .db 0x01, 0x3E  ; ., b
    .db 0xEE, 0x1C  ; A, L

TIMER1_ISR:
    push tmpL
    in   tmpL, SREG
    push tmpL
    push tmpH
    push segCode
    push ZL
    push ZH

    ; turn off all digits
    ldi tmpL, 0xFF
    out PORTB, tmpL

	; get first position from message
    ldi ZH, HIGH(MSG << 1)
    ldi ZL, LOW(MSG << 1)
    clr tmpH
    add ZL, dispIdx ; access the character at position dispIdx
    adc ZH, tmpH
    lpm segCode, Z

    ; load segment code in PORTD
    out PORTD, segCode

    ; Activate current digit (start from bit5, shift right)
    ldi tmpL, 0x20
    mov tmpH, dispIdx
    tst tmpH
    breq DO_ACTIVATE
SHIFT_LOOP:
    lsr tmpL
    dec tmpH
    brne SHIFT_LOOP
DO_ACTIVATE:
    ldi tmpH, 0xFF
    eor tmpH, tmpL
    out PORTB, tmpH

    ; increment dispIdx and check for overflow
    inc dispIdx
    cpi dispIdx, 6
    brne ISR_DONE
    clr dispIdx

ISR_DONE:
    pop ZH
    pop ZL
    pop segCode
    pop tmpH
    pop tmpL
    out SREG, tmpL
    pop tmpL
    reti

RESET:
    ; Initialize stack
    ldi tmpL, Low(RAMEND)
    out SPL, tmpL
    ldi tmpL, High(RAMEND)
    out SPH, tmpL

    ; Set PORTB and PORTD to output
    ldi tmpL, 0xFF
    out DDRB, tmpL
    out DDRD, tmpL

    ; set all digits OFF, all segments OFF
    ldi tmpL, 0xFF
    out PORTB, tmpL
    ldi tmpL, 0x00
    out PORTD, tmpL

    ; init display index 
	clr dispIdx

    ; Timer1 CTC, prescaler 8
    ldi tmpL, 0x00
    out OCR1AH, tmpL
    ldi tmpL, 250
    out OCR1AL, tmpL

    ; CTC mode (WGM12=1), prescaler 8 (CS11=1)
    ldi tmpL, (1<<WGM12)|(1<<CS11)
    out TCCR1B, tmpL
    ldi tmpL, 0x00
    out TCCR1A, tmpL

    ; Enable Timer1 Compare Match A interrupt
    ldi tmpL, (1<<OCIE1A)
    out TIMSK, tmpL

    sei

MAIN:
    rjmp MAIN