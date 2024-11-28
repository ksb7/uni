INCLUDE Irvine32.inc
.DATA
    bcd1 DB 22h,41h,75h,32h
    bcd2 DB 31h,27h,53h,62h
    result DB 8 DUP(0)
    asciiStr DB 9 DUP(0), '$'
    n EQU sizeof bcd1

    msg1 DB "Suma BCD in ASCII: ", 0

.CODE
main PROC
    lea esi, bcd1 ;Adresa primului sir
    lea edi, bcd2 ;Adresa celui de al doilea sir
    mov ecx, n ;numarul de octeti
    clc

bucla: 
	mov al, [esi]	;ultimul octet din primul sir
    adc al, [edi]	;adunat cu ultimul octet din al doilea
    daa				;ajustare pentru formatul bcd
    mov [edi], al	;salveaza valoarea in bcd2
    inc esi			;urmatorul octet a bcd1
    inc edi			;urmatorul octet a bcd2
    loop bucla

    lea esi, bcd2	;preia adresa valorii calculate
    lea edi, result ;preia adresa unde va fi scris rezultatul
    mov ecx, n		;numarul de iteratii (octeti)

unpack_loop:
    mov al, [esi]	;ultimul octet din bcd2
    inc esi			;urmatorul octet

    mov ah, al
    shr ah, 4		;preia partea superioara de nibble
    mov [edi], ah	;scrie in rezultat
    inc edi

    and al, 0Fh		;preia partea inferioara de nibble
    mov [edi], al	;scrie in urmatorul byte din rezultat
    inc edi
    loop unpack_loop

    lea esi, result	;preia adresa rezultatului
    lea edi, asciiStr ;adresa unde va scrie sirul in ascii
    mov ecx, 8		;numarul de iteratii

ascii_conversion:
    mov al, [esi]	
    add al, 30h		;conversia in ascii (adunarea cu caracterul 0)
    mov [edi], al
    inc esi
    inc edi
    loop ascii_conversion

    lea edx, msg1
    call WriteString

    lea edx, asciiStr
    call WriteString

    exit
main ENDP
END main