; nasm -felf64 hello.asm
; ld hello.o && ./a.out

    global _start

section     .text
_start:
    mov rax,1       ; system call for write
    mov rdi,1       ; file handle 1 is stdout
    mov rsi,msg     ; address of string to output
    mov rdx,13      ; number of bytes
    syscall         ; call kernel

    mov rax, 60     ; system call for exit
    xor rdi, rdi    ; exit code 0
    syscall         ; call kernel

section     .data

    msg db "Hello, World", 0xa