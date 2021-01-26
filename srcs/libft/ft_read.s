section .data

section .text
        extern ___error
        global _ft_read

; ft_read(fd = rdi, str = rsi, buff_size = rdx)
_ft_read:       mov rax, 0x2000003 ; in rax system write
                syscall            ; system call write from rax, if doesn't work cf = 1
                jc  error          ; ckeck carry flag and if true jump to error
                jmp return

error:          push	rax        ; save rax(pointer on error) on stack
	            call	___error   ; call error
	            pop		rdx        ; save rax from stack in rdx
	            mov		[rax], rdx ; save error value to pointer
            	mov		rax, -1
	            ret

return:         ret