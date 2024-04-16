section     .text
global my_fillstruct

my_fillstruct:
    ; rdi = struct _my_struct*  => 8 octets (QWORD)
    ; rsi = int64t              => 8 octets
    ;  ?  = double              => 8 octets

    mov [rdi], rsi              ; struct { .int64_t = rsi }
    
    fld qword [rbp + 8]         ; Charger le double dans st0
    movsd [rdi + 8], xmm0       ; st0 -> [rdi + 8]

    ret
