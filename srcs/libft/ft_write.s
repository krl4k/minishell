section .data

section .text
        extern ___error
        global _ft_write
; ft_write(fd = rdi, str = rsi, buff_size = rdx)
_ft_write:      mov rax, 0x2000004 ; in rax system write
                syscall            ; system call write from rax
                jc  error          ; ckeck carry flag and if true jump to error
                jmp return

error:          push	rax
	            call	___error
	            pop		rdx
	            mov		[rax], rdx
            	mov		rax, -1
	            ret

return:         ret