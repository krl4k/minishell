section .data

        section .text
        global _ft_strdup
extern _ft_strlen
extern _ft_strcpy
extern _malloc
extern ___error

; ft_strdup(str = rdi)
_ft_strdup:     call _ft_strlen        ; call ft_strlen for malloc
        add  rax, 1            ; increment rax for '\0'
push rdi               ; save arg[0] on stack
mov  rdi, rax          ; set len for malloc for first arg;
call _malloc           ; call malloc(rdi) ret in rax
        test rax, rax          ; test allocate memory with bit &
jz   error             ; if not allocated make error
pop  rsi               ; get arg[0] saved on stack make src
        mov  rdi, rax          ; dst for strcpy
        call _ft_strcpy        ; ft_strcpy( dst = rdi, src = rsi)
ret

        error:          push	rax            ; save NULL pntr on stack
        call	___error       ; take pntr for error
        pop		rdx            ; rdx = NULL
mov     dl, 12         ; error num 12, allocated memory error
        mov		qword[rax], 12 ; write error num in pntr
        mov		rax, rdx       ; ret NULL pntr
        ret
