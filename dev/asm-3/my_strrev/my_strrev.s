section     .text
global my_strrev


my_strrev:
    xor rsi, rsi        ; reset taille
    xor rcx, rcx        ; reset index
count_loop:
    mov  al, byte [rdi + rcx]
    test al, al
    jz reverse

    inc rsi
    inc rcx
    jmp count_loop

reverse:
    xor rcx, rcx
    dec rcx             ; vers dernier char de la string

reverse_loop:
    ; swap chars
    mov al, byte [rdi + rcx]
    mov dl, byte [rdi + rsi]
    mov [rdi + rcx], dl
    mov [rdi + rsi], al

    inc rcx             ; incr l'index depuis la gauche
    dec rsi             ; decr l'index depuis la droite
    cmp rcx, rsi
    jl reverse_loop

    mov rax, rdi

    ret