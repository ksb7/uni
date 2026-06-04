.include "m32def.inc"

; Register definitions
.def flags  = r2
.def tmpL   = r16
.def tmpH   = r17
.def perL   = r18       ; period result LOW byte
.def perH   = r19       ; period result HIGH byte
.def ovfCnt = r20       ; Timer0 overflow counter

.cseg
.org 0x0000
    rjmp RESET

.org INT0addr           ; INT0 - interrupt input
    rjmp INT0_ISR

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
    reti

.org OC1Baddr
    reti

.org OVF1addr
    reti

.org OC0addr
    reti

.org OVF0addr           ; Timer0 overflow 
    rjmp OVF0_ISR

.org SPIaddr
    reti

.org URXCaddr
    reti

.org UDREaddr
    reti

.org UTXCaddr
    reti

.org ADCCaddr
    reti

.org ERDYaddr
    reti

.org ACIaddr
    reti

.org TWIaddr
    reti

.org SPMRaddr
    reti

;---------------------------------------------------------------
; Timer0 Overflow ISR
; Called every 256 Timer0 ticks — counts overflows for period
;---------------------------------------------------------------
OVF0_ISR:
    in  flags, SREG
    inc ovfCnt          ; count each overflow
    out SREG, flags
    reti

;---------------------------------------------------------------
; INT0 ISR - triggered on RISING edge
; First pulse:  reset Timer0 + overflow counter ? start measuring
; Second pulse: read Timer0 + overflow counter  ? period captured
;---------------------------------------------------------------
INT0_ISR:
    in  flags, SREG

    sbrs tmpH, 0        ; check first edge flag
    rjmp FIRST_EDGE

; fallback from INT0_ISR
SECOND_EDGE:
    in  perL, TCNT0     ; timer in low byte
    mov perH, ovfCnt    ; overflow count in high byte

    ; stop Timer0
    ldi tmpL, 0x00
    out TCCR0, tmpL

    cbr tmpH, (1<<0)	; clear first edge flag for next interrupt

    rjmp INT0_DONE

FIRST_EDGE:
    ; Reset and start Timer0
    ldi tmpL, 0x00
    out TCNT0, tmpL     ; reset counter
    clr ovfCnt          ; reset overflow count

    ; Start Timer0 with prescaler 256
    ; At 10MHz: each tick = 25.6us, overflow = 6.5ms
    ldi tmpL, (1<<CS02) ; prescaler = 256
    out TCCR0, tmpL

    sbr tmpH, (1<<0)	; set first edge flag needed for the second edge

; fallback from FIRST_EDGE
INT0_DONE:
    out SREG, flags		; reset the status register
    reti

RESET:
    ; initialize the stack
    ldi tmpL, Low(RAMEND)
    out SPL, tmpL
    ldi tmpL, High(RAMEND)
    out SPH, tmpL

    clr tmpL
    out DDRD, tmpL      ; PORTD = input (INT0 on PD2)

    ldi tmpL, 0xFF
    out DDRB, tmpL      ; PORTB = output (period LOW)
    out DDRC, tmpL      ; PORTC = output (period HIGH / overflows)

    ; initial value to Timer0
    ldi tmpL, 0x00
    out TCCR0, tmpL
    out TCNT0, tmpL

    ; enable Timer0 overflow interrupt
    ldi tmpL, (1<<TOIE0)
    out TIMSK, tmpL

    ; INT0: trigger on RISING edge
    ldi tmpL, (1<<ISC01)|(1<<ISC00)
    out MCUCR, tmpL

    ; Enable INT0
    ldi tmpL, (1<<INT0)
    out GICR, tmpL

    ; Init flags and result registers
    clr tmpH            ; bit0 = first edge flag
    clr perL
    clr perH
    clr ovfCnt

    sei                 ; enable global interrupts

MAIN:
    out PORTB, perL     ; LOW byte of period
    out PORTC, perH     ; HIGH byte (overflows)

    rjmp MAIN