    global my_sum

section     .text
; tester enter et leave
; voir https://stackoverflow.com/questions/29790175/assembly-x86-leave-instruction
my_sum:
    push rbp        ; sauvegarde valeur origin de rbp
    mov rbp, rsp    ; rbp = rsp

    ; 7 paramètres long int = 8 octets chacun
    mov rax, rdi
    add rax, rsi
    add rax, rdx
    add rax, rcx
    add rax, r8
    add rax, r9
    add rax, [rbp + 16]

    mov rsp, rbp    ; actualisation de rsp
    pop rbp         ; restauration de la valeur de rbp
    ret             