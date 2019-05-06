;MYPROG
code SEGMENT
 ASSUME cs:code
	begin:	push ebp
	mov	ebp, esp
	xor	eax, eax
	mov	esp, ebp
	pop	ebp

	mov ax, 4c00h
	int 21h
code ENDS
	end begin

