.model small
.stack 100h
.data
.code
start: 
    mov ax, @data
    mov ds, ax

    mov ah, 00h ;Setam modul grafic 12h
    mov al, 12h 
    int 10h

    mov ah, 0Ch ;functia pentru afisarea unui pixel
    mov bh, 0 ;pagina de baza - pagina 0
    mov al, 01h ;setam culoarea albastru
    mov cx, 0 ;coordonata x initiala (coloana)
    mov dx, 0 ;coordonata y initiala (linie)

m1: int 10h ;afisam un pixel la coordonataele cx, dx
    inc cx ;trecem la urmatoarea coloana
    cmp cx, 213 ;verificam daca am desenat pana la marginea benzii
    jne m1 ;continuam daca nu am ajuns la margine

    inc dx ;trecem la urmatoarea linie
    xor cx, cx	;resetam coloana la 0
    cmp dx, 480 ;verificam daca am ajuns la marginea ecranului
    jne m1 ;continuam daca mai sunt linii

	;configurarea benzii galben
    mov ah, 0Ch
    mov al, 0Eh
    mov cx, 213
    mov dx, 0

m2: int 10h
    inc cx
    cmp cx, 426
    jne m2

    inc dx
    mov cx, 213
    cmp dx, 480
    jne m2

	;configurarea benzii rosii
    mov ah, 0Ch
    mov al, 04h
    mov cx, 426
    mov dx, 0

m3: int 10h
    inc cx
    cmp cx, 640
    jne m3
    inc dx
    mov cx, 426
    cmp dx, 480
    jne m3

	;asteptam apasarea unei taste
    mov ah, 1
    int 21h

	;revenim la modul text
    mov ax, 03h
    int 10h

	;iesim din program
    mov ax, 4C00h
    int 21h

end start