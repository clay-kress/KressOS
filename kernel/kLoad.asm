[bits 32]
[extern kernel]


jmp start

daySavTime db 0

start:
      pop ax
      mov [daySavTime], ax
      
      ; call the kernel with args
      movzx ax, byte [daySavTime]
      push ax                                                           ; Daylight savings time argument
      
      call kernel                                                       ; Call kernel in C
      
jmp $

