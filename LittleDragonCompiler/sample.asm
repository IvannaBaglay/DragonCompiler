M
PROC
push ebp 
mov ebp, esp
[ebp+8];A
	cmp [ebp+8]
jmp ?ELSE1
?THEN:1
?ELSE:1
	cmp [ebp+8]
jmp ?ELSE2
?THEN:2
?ELSE:2
	cmp [ebp+8]
jmp ?ELSE3
?THEN:3
?ELSE:3
ret
M
endp 