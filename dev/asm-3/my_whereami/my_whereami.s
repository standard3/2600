section      .text
global my_whereami

my_whereami:
  push rbp
  mov rbp, rsp ;

  mov rax, end - my_whereami ; Taille = addr_where - addr_stack

  lea rsi, [rel my_whereami]
  mov [rdi], rsi

  leave
  ret

end: