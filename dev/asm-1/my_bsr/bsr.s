    global my_bsr

section     .text
my_bsr:
    ; Appeler BSR => récupérer bit le plus significatif de rdi
    ; stocker retour dans rax
    bsr rax, rdi
    ret