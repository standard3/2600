section     .text
global  my_swap

my_swap:
    mov rax, [rdi] 
    mov r8, [rsi]  
    mov [rdi], r8
    mov [rsi], rax
    ret

