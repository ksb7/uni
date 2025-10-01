INCLUDE Irvine32.inc

; Sa se calculeze ((a*3+b*b*5)/(a*a+2*a*b))-a-b

	.data 
	  	a dw 1
		b db 8
		interm dw ?
		rez db ?

	.code 
	 main proc
		; Calculam numaratorul
		mov ax, a ;ax = 1
		imul ax, 3 ;ax*3
		mov cx, ax ;salvam valoarea obtinuta in cx

		movzx ax, b ;ax =8
		imul ax, ax ;ax*ax
		imul ax, 5 ;ax*5
		add ax, cx ;ax + cx (valoarea salvata anterior)
		mov interm, ax ;salvam valoarea numaratorului

		; Calculam numitorul
		mov ax, a ;ax = a
		imul ax, a ;ax * a
		mov cx, ax ; salvam valoarea obtinuta in cx

		movzx dx, b ;dx = b
		imul dx, 2 ;dx * 2
		imul ax, dx ;ax * dx
		add ax, cx ;ax + cx (valoarea salvata anterior)
		mov cx, ax ; Salvam valuarea obtinuta in cx

		mov ax, interm ;Restabilim numaratorul
		cwd ;Extindem valoarea numaratorului pentru a putea imparti
		idiv cx ;Impartim valoarea extinsa la cx si salvam in ax

		sub ax, a ;Rezultatul obtinut la impartire - a
		movzx dx, b ;dx = b (pe 16 biti)
		sub ax, dx ;Rezultatul precedent - dx

		mov rez, al ;Salvam rezultatul final in rez
exit
main ENDP
END main