section     .text
global my_countv

my_countv:
    ; rdi = adresse du tableau de caractères (s)
    ; rsi = taille du tableau (size)
    ; rdx = adresse du tableau d'entiers (v)

    mov dword [rdx]     , 0 ; v[0] (a) => 61h
    mov dword [rdx + 4] , 0 ; v[1] (e) => 65h
    mov dword [rdx + 8] , 0 ; v[2] (i) => 69h
    mov dword [rdx + 12], 0 ; v[3] (o) => 6Fh
    mov dword [rdx + 16], 0 ; v[4] (u) => 75h
    mov dword [rdx + 20], 0 ; v[5] (y) => 79h

    mov rcx, rsi       ; n iterations
    xor rax, rax
    mov rsi, rdi

count_loop:
    lodsb ; https://www.gladir.com/LEXIQUE/ASM/lodsb.htm

    ; Check a
    cmp al, 61h
    je count_a

    ; Check e
    cmp al, 65h
    je count_e

    ; Check i
    cmp al, 69h
    je count_i

    ; Check o
    cmp al, 6Fh
    je count_o

    ; Check u
    cmp al, 75h
    je count_u

    ; Check y
    cmp al, 79h
    je count_y    

    jmp end

count_a:
    inc dword [rdx]
    jmp end
    
count_e:
    inc dword [rdx + 4]
    jmp end

count_i:
    inc dword [rdx + 8]
    jmp end

count_o:
    inc dword [rdx + 12]
    jmp end
    
count_u:
    inc dword [rdx + 16]
    jmp end
    
count_y:
    inc dword [rdx + 20]
    jmp end

end:
    loop count_loop     ; decrements rcx and jumps to label if not 0
    ret