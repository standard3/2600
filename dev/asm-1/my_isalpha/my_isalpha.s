    global my_isalpha

section     .text
my_isalpha:
    ; Retourne à l'appelant si le caractère passé en 
    ; paramètre est alphabétique ou non

    ; param par rdi
    ; retour par rax avec :
    ; 1 -> succès, 0 -> échec

    ; si la valeur est comprise dans le tableau ascii [A-Z]
    mov rax, rdi
    cmp rax, 41h
    jb not_alpha
    cmp rax, 5Bh
    jb is_alpha

    ; si la valeur est comprise dans le tableau ascii [a-z]
    cmp rax, 61h 
    jb not_alpha
    cmp rax, 7Bh
    jb is_alpha

    xor rax, rax
    ret

is_alpha:
    mov rax, 1
    ret
    