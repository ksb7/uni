INCLUDE Irvine16.inc
.DATA
Promt DB 'Doresti sa devii programator?(da/nu)-[y/n]$'
Dad DB 13,10,'Vei deveni!',13,10,'$'
Nud DB 13,10,'Vei deveni filosof!',13,10,'$'
.CODE
main PROC
mov ax,@data
mov ds,ax
mov dx,OFFSET Promt
mov ah,9
Int 21h
mov ah,1
Int 21h
cmp al,'y'
jz IsDad
cmp al,'n'
jz IsNud
IsDad: mov dx,OFFSET Dad
Jmp SHORT Disp
IsNud: mov dx,OFFSET Nud
Disp: mov ah,9
Int 21h
mov ah,1
Int 21h
Exit
main ENDP
END main