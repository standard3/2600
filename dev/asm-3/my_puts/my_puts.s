section .data
    newline db 10 ; Caractère de retour à la ligne ('\n')

section     .text
global  my_puts

my_puts:
    ; rdi = const char *s
    ; man 3 puts
    ; man 2 write
    ; -> ssize_t write(int fd, const void buf[.count], size_t count);

    call my_strlen

    ; Print la chaine
    mov rsi, rdi    ; buf = s
    mov rdi, 1      ; fd = 1 (stdout)
    mov rdx, r8     ; count = strlen(buf)
    mov	rax, 1		; system call number (sys_write)
    syscall 		; call kernel

    mov rdi, 1       ; fd = 1 (stdout)
    mov rsi, newline ; adresse de '\n'
    mov rdx, 1       ; longueur : 1 caractère ('\n')
    mov	rax, 1		 ; system call number (sys_write)
    syscall          ; call kernel

    ret

my_strlen:
    ; Arguments :
    ; rdi : pointeur vers la chaîne de caractères
    xor r8, r8

.loop:
    cmp byte [rdi + r8], 0
    je .end
    inc r8
    jmp .loop

.end:
    ret