section     .text
global my_mul_arrays

my_mul_arrays:
    ; rdi = int a[4]
    ; rsi = int b[4]

    xor rax, rax
    xor r8, r8
    jmp array_loop

inc_r8:
    add r8, 4           ; 32 bits = 4 octets

array_loop:
    mov edx,  dword [rdi + r8]    ; a[i]
    imul edx, dword [rsi + r8]    ; b[i]
    add rax, rdx        ; additionne le résultat dans rax

    cmp r8, 16          ; 4*4 = 16
    jne inc_r8

done:
    ret