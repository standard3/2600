    global my_max

section     .text
my_max:
    mov     rax, rdi        
    cmp     rax, rsi     ; voir https://0xinfection.github.io/reversing/pages/part-37-asm-program-6-cmov-instructions.html
    cmovng  rax, rsi     ; rax -> rsi, si rsi < rax
    cmp     rax, rdx        
    cmovng  rax, rdx     ; rax -> rdx, si rdx < rax
    ret