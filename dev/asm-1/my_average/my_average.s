    global my_average

section     .text
my_average:
    ; Additionner tous les chiffres
    add rdi, rsi
    add rdi, rdx
    add rdi, rcx

    ; Diviser par 4
    mov rax, rdi
    mov rsi, 4
    xor rdx, rdx
    div rsi         ; voir https://www.felixcloutier.com/x86/fdiv:fdivp:fidiv
                    ; pour division flottante
    ; Retourne la valeur 
    ret
