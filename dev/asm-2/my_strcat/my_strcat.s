section     .text
global  my_strcat

my_strcat:
    ; This function catenates the string pointed to by src, 
    ; after the string pointed to by dst (overwriting its 
    ; terminating null byte).  The programmer is responsible 
    ; for allocating a destination buffer large enough,  
    ; that is, strlen(dst) + strlen(src) + 1

    ; rdi = char* restrict dst
    ; rsi = const char* restrict src

    ; r8 = dst + strlen(dst)
    call my_strlen
    add rdi, rax
    mov r8, rdi

    ; rdx = strlen(src)
    mov rdi, rsi
    call my_strlen
    mov rdx, rax

    ; memcpy
    mov rdi, r8     ; dst + strlen(dst)
    call my_memcpy

    ret

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

my_strlen:
    xor rax, rax            ; loop counter

strloop:
    mov dl, byte [rdi + rax]
    inc rax

    cmp dl, 0h              ; null byte
    jne strloop

    dec rax
    ret