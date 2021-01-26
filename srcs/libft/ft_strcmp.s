section .data

section .text
        global _ft_strcmp
; ft_strcmp(str1 = rdi, str2 = rsi)
_ft_strcmp:     mov rax, 0          ; define rax
                jmp comparation

comparation:    mov al, byte[rdi]   ; al(8 bit register) to rdi (str1)
                mov bl, byte[rsi]   ; bl(8 bit register) to rsi (str2)
                cmp al, 0           ; if !*str1 return
                je  return
                cmp bl, 0           ; if !*str2 return
                je  return
                cmp al, bl          ; if *str1 != *str2 return
                jne return
                inc rdi             ; str1++
                inc rsi             ; str2++
                jmp comparation

return:         movzx rax, al       ; copy al to rax, rax > al that is why movzx make free bits equal to 0
                movzx rbx, bl       ; copy bl to rax, rbx > bl that is why movzx make free bits equal to 0
                sub rax, rbx
                ret