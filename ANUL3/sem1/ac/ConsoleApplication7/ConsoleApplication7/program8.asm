INCLUDE Irvine32.inc

.data
asc_tbl db '0123456789ABCDEF' ;Tabelul ASCII
numar dw 7C3Fh ;Numarul de referinta
masti dw 0E000h, 1F00h, 00F0h, 000Eh, 1h ;Mastile pentru fiecare grup
deplasari db 13, 8, 4, 1, 0 ;pozitia de shiftat 
num_grupuri db 5
newline db 13, 10, '$'

.code
start:
    movzx cx, num_grupuri ;Incarcam toate valorile definite in registri
    mov esi, offset masti
    mov edi, offset deplasari

procesare_grupuri:
    mov ax, numar ;Numarul original 
    mov dx, ax 
    mov ax, [esi] ;Masca curenta
    and dx, ax ;Se aplica masca
    mov cl, [edi] ;Se incarca numarul cu care se va face shift
    shr dx, cl ;Se executa shift pentru a selecta doar bitii necesari
	mov al, dl ;Salveaza valoarea
    call ConversieSiAfisare

    mov dl, ' ' ;Afisam spatiu
    call WriteChar

    add esi, 2 ;Trecem la urmatoarea masca
    add edi, 1 ;Trecem la urmatoarea pozitie de shiftat
    loop procesare_grupuri ;Repetam pana se termina grupurile

    mov edx, offset newline
    call WriteString

    exit

ConversieSiAfisare PROC
	lea si, asc_tbl ;Adresa efectiva a sirului ascii
	movzx ax, dl ;mutam valoarea obtinuta in ax pentru a o putea folosi
	xlatb ;Convertim valoarea din ax in ascii
	mov dl, al ;WriteChar foloseste registrul dl
    call WriteChar
    ret
ConversieSiAfisare ENDP

end start