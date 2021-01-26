section .data

section .text
		global _ft_strlen
;ft_strlen(str = rdi)
_ft_strlen:		mov rax, 0 ; rax is a return value, and the count, i = 0
				jmp loop

loop:			cmp	byte[rdi + rax], 0 ; compare value with '\0'
				je	return			   ; if it's equal jump to return
				inc rax				   ; i++
				jne loop			   ; if it's not equal jump to loop

return:			ret
