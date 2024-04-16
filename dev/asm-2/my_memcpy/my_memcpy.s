section     .text
global  my_memcpy

; The memcpy() function copies n bytes from memory area src 
; to memory area dest.  The memory areas must not overlap.  
; Use memmove(3) if the memory areas do overlap.

; https://stackoverflow.com/questions/17591624/understanding-the-source-code-of-memcpy

my_memcpy:
    ; rdi = void* dst
    ; rsi = void* src
    ; rdx = unsigned int n

    xor rax, rax

    ; si (source + n) < destination
    add rax, [rsi + rdx]
    cmp rdi, rax
    jge mcopy

    ; si source > (destination + n)
    mov rax, rdi
    add rax, [rsi + rdx]
    cmp rdi, rax
    jge mcopy

mcopy:
    mov rcx, rdx

scopy:
    mov rax, [rsi]
    mov [rdi], al
    inc rdi
    inc rsi
    loop scopy
    ret