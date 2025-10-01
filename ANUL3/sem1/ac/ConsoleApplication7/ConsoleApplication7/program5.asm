INCLUDE Irvine32.inc
.data
mes1 byte "Introduceti valoarea X:",0
mes2 byte "Introduceti valoarea Y:",0
mes3 byte "Rezultatul este:",0
vrx dword 0
vry dword 0
rez dd 0

.code
main PROC
    ; Afisare mesaj pentru X
    mov edx, OFFSET mes1
    call WriteString
    call ReadDec
    mov vrx, eax ; Salvare valoare X

    ; Afisare mesaj pentru Y
    mov edx, OFFSET mes2
    call WriteString
    call ReadDec
    mov vry, eax ; Salvare valoare Y

    ; Calculam X > Y / 2
    mov eax, vrx
    mov ebx, vry
    shr ebx, 1 ; Y / 2
    cmp eax, ebx
    jg con1 ; Daca X > Y / 2, mergem la con1 

    ; Daca X <= Y / 2, calculam Z = 2X - 64 + Y
    mov eax, vrx
    shl eax, 1 ; 2X
    add eax, vry
    sub eax, 64
    mov rez, eax
    jmp ex ; Sarim la afisare rezultat

con1:
    ; Daca X > Y / 2, calculam Z = (Y - 2X) / 5 + 150
    mov eax, vrx
	mov ebx, vry
    shl ebx, 1 ; 2Y
    sub eax, ebx
    mov ebx, 5
	xor edx, edx ;Resetam registrul edx pentru a nu avea overflow
    div ebx ; (Y - 2X) / 5
    add eax, 150
    mov rez, eax

ex:
    ; Afisare rezultat
    mov edx, OFFSET mes3
    call WriteString
    call WriteInt ; Afisare rezultat
    call Crlf ; Caractere de sfarsit de linie

    exit
main ENDP
END main