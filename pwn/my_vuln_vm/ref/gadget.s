section .text
___:
    db 0xb8
; for classical function
    pop rdi
    ret
    db 0xca,0xca,0xb9
    pop rsi
    ret
    db 0xca,0xcb,0xba
    pop rdx
    ret
    db 0xca,0xcc,0xbb
    pop rcx
    ret
    db 0xca,0xcd,0xbc
    pop r8
    ret
    db 0xce,0xbd
    pop r9
    ret
; for syscall
    db 0xcf,0xbe
    pop rax
    ret
    db 0xca,0xcb,0xbf
    pop rax
    syscall
    ret
; very usefull
    db 0xcc,0xb8
    shr rdi, 4
    jmp 5
    db 0xb9
    ret
    db 0xca, 0xcb, 0xcc, 0xba
    shl rdi, 4
    jmp 5
    db 0xbb
    ret
    db 0xbc
    xor dil, 0xff
    ret
