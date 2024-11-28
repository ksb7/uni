INCLUDE Irvine32.inc
.data
mes1 byte "Valoarea generata pentru X este:",0
mes2 byte "Valoarea generata pentru Y este:",0
mes3 byte "Rezultatul este:",0
vrx dword 0
vry dword 0
rez dd 0

.code
main PROC
    ; Generare valoare random pentru X
    call RandomRange
    mov vrx, eax
    mov edx, OFFSET mes1
    call WriteString
    mov eax, vrx
    call WriteInt
    call Crlf

    ; Generare valoare random pentru Y
    call RandomRange
    mov vry, eax 
    mov edx, OFFSET mes2
    call WriteString
    mov eax, vry
    call WriteInt
    call Crlf

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
	xor edx, edx ; Resetam registrul edx pentru a nu avea overflow
    div ebx ; (Y - 2X) / 5
    add eax, 150
    mov rez, eax

ex:
    ; Afisare rezultat
    mov edx, OFFSET mes3
    call WriteString
    mov eax, rez
    call WriteInt ; Afisare rezultat
    call Crlf ; Caractere de sfarsit de linie

    exit
main ENDP
END main
