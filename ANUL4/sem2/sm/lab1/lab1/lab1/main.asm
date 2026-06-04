.include "m32def.inc"

; Registers
.def tmpH   = r16
.def tmpL   = r17
.def aL     = r18
.def aH     = r19
.def flags  = r2

.dseg
.org 0x72
myvar: .byte 1

.cseg
.org 0x0000
    rjmp Reset

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
    reti
.org OC1Baddr
    reti
.org OVF1addr
    reti
.org OC0addr
    reti
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
RESET:
    ; Initialize stack
    ldi tmpL, Low(RAMEND)
    out SPL, tmpL
    ldi tmpH, High(RAMEND)
    out SPH, tmpH

    ; Set PORTA as input
    clr tmpL
    out DDRA, tmpL

    ; Set PORTC, PORTD as output
    ldi tmpL, 0xFF
    out DDRC, tmpL
    out DDRD, tmpL

MAIN:
    ; Read PinA
    in tmpL, PINA
    clr tmpH

    clr aH
    mov aL, tmpL

    lsl aL
    rol aH              ; PA * 2
    lsl aL
    rol aH              ; PA * 4

    add aL, tmpL
    adc aH, tmpH        ; PA * 5

    inc aH              ; +256

    ; result / 4 
    lsr aH
    ror aL
    lsr aH
    ror aL

    ; + 3000
    ldi tmpL, 0xB8
    ldi tmpH, 0x0B
    add aL, tmpL
    adc aH, tmpH

    out PORTC, aH       ; MSB
    out PORTD, aL       ; LSB

    rcall delay
    rjmp MAIN

delay:
    ldi tmpL, 150
extloop:
    ldi tmpH, 200
intloop:
    nop
    dec tmpH
    brne intloop
    dec tmpL
    brne extloop
    ret