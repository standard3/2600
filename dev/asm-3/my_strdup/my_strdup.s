section     .text
global my_strdup
my_strdup:
    ; rdi = char* s

    call my_strlen      ; Récupère le taille de la chaîne
    add rax, 1          ; Ajoute 1 pour le '\0'
    mov rdx, rax        ; Stocke strlen(s) dans rdx

    push rdi            ; Sauvegarde de char* s avant allocation mémoire

    ; Allocation mémoire avec taille = strlen(s) + 1
    call my_malloc      ; Retour de l'adresse dans rax

    pop rdi             ; Restauration de l'adresse de char* s

    xor r8, r8          ; Incrément sur la chaîne parcourue => 0
    mov r12, rax        ; r12 = Adresse de char* new
    jmp duplicate_loop  ; Boucle sur chaque caractère

next:
    ; Append \0 à la fin de chaîne
    mov byte [r12 + r8], 0
    ret

duplicate_loop:
    ; rdi = Adresse de char* s
    ; r12 = Adresse de char* new
    ; r8  = Incrément sur la chaîne parcourue
    ; al  = s[i]
    ; rdx = strlen(s)

    mov al, byte [rdi + r8] ; al = s[i]
    mov byte [r12 + r8], al ; new[i] = al
    inc r8                  ; i++

    ; Vérifie si al (le caractère copié) est nul pour sortir de la boucle
    cmp al, 0
    jnz duplicate_loop

    jmp next

my_malloc:
    mov rax, 9      ; sys_mmap
    xor rdi, rdi    ; addr = NULL
    mov rsi, rdx    ; len = rdx
    mov rdx, 7      ; prot = PROT_READ|PROT_WRITE|PROT_EXEC
    mov r10, 34     ; flags = MAP_PRIVATE|MAP_ANONYMOUS
    mov r8, -1      ; fd = -1
    xor r9, r9      ; offset = 0
    syscall

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