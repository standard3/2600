section     .text
global  my_factorial

my_factorial:
    ; rdi = long int n
    mov rax, 1

    cmp rdi, 2
    jl ok

factorial:
    imul rax, rdi       ; multiplication signée
    dec rdi
    cmp rdi, 1
    jg factorial

ok:
    ret