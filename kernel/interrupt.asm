;=======================================================================
;
;     KressOS by Clay Kress
;     Org: January 1st, 2019       (or something like that...)
;
; Copyright (c) 2022 Clay Kress
;
; This file is part of KressOS.
; KressOS is free software: you can redistribute it and/or modify it
; under the terms of the GNU General Public License as published by
; the Free Software Foundation, either version 3 of the License, or
; (at your option) any later version.
;
; KressOS is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty
; of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
;
; See the GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with KressOS. If not, see <https://www.gnu.org/licenses/>.
;
;=======================================================================

[bits 32]

[extern printS]
[extern printN]
[extern clearTop]
[extern carridgeReturn]
[extern setCursorOffset]
[extern getCursorOffset]


[global loadIDT]
[global enableInt]
[global disableInt]


; Exception handlers
[global isr0]
[global isr1]
[global isr2]
[global isr3]
[global isr4]
[global isr5]
[global isr6]
[global isr7]
[global isr8]
[global isr9]
[global isr10]
[global isr11]
[global isr12]
[global isr13]
[global isr14]
[global isr15]
[global isr16]
[global isr17]
[global isr18]
[global isr19]
[global isr20]
[global isr21]
[global isr22]
[global isr23]
[global isr24]
[global isr25]
[global isr26]
[global isr27]
[global isr28]
[global isr29]
[global isr30]
[global isr31]


; C call funcs
[global int0x00]
[global int0x01]
[global int0x02]
[global int0x03]
[global int0x04]
[global int0x05]
[global int0x06]
[global int0x07]
[global int0x08]
[global int0x09]
[global int0x0a]
[global int0x0b]
[global int0x0c]
[global int0x0d]
[global int0x0e]
[global int0x0f]
[global int0x10]
[global int0x11]
[global int0x12]
[global int0x13]
[global int0x14]
[global int0x15]
[global int0x16]
[global int0x17]
[global int0x18]
[global int0x19]
[global int0x1a]
[global int0x1b]
[global int0x1c]
[global int0x1d]
[global int0x1e]
[global int0x1f]


; PIC Handlers
[global timer]
[extern timerHandler]

[global keyboard]
[extern keyboardHandler]

[global realTimeClock]
[extern rtcHandler]



loadIDT:
      mov eax, [esp+4]
      lidt [eax]
      ret

enableInt:
      sti
      ret

disableInt:
      cli
      ret



int0x00:
      int 0x00
      ret
      
int0x01:
      int 0x01
      ret
      
int0x02:
      int 0x02
      ret
      
int0x03:
      int 0x03
      ret
      
int0x04:
      int 0x04
      ret
      
int0x05:
      int 0x05
      ret
      
int0x06:
      int 0x06
      ret
      
int0x07:
      int 0x07
      ret
      
int0x08:
      int 0x08
      ret
      
int0x09:
      int 0x09
      ret
      
int0x0a:
      int 0x0a
      ret
      
int0x0b:
      int 0x0b
      ret
      
int0x0c:
      int 0x0c
      ret
      
int0x0d:
      int 0x0d
      ret
      
int0x0e:
      int 0x0e
      ret
      
int0x0f:
      int 0x0f
      ret
      
int0x10:
      int 0x10
      ret
      
int0x11:
      int 0x11
      ret
      
int0x12:
      int 0x12
      ret
      
int0x13:
      int 0x13
      ret
      
int0x14:
      int 0x14
      ret
      
int0x15:
      int 0x15
      ret
      
int0x16:
      int 0x16
      ret
      
int0x17:
      int 0x17
      ret
      
int0x18:
      int 0x18
      ret
      
int0x19:
      int 0x19
      ret
      
int0x1a:
      int 0x1a
      ret
      
int0x1b:
      int 0x1b
      ret
      
int0x1c:
      int 0x1c
      ret
      
int0x1d:
      int 0x1d
      ret
      
int0x1e:
      int 0x1e
      ret
      
int0x1f:
      int 0x1f
      ret
      







isrstr00: db "Int#: 00 Divide-by-Zero", 0x00
isr0:       ; Divide-by-Zero
      cli
      pushad
      
      call getCursorOffset    ; Gets and stores the cursor offset to restore later
      push eax                ; Makes sure the data doesnt get overwritten by the C functions
      
      call clearTop
      
      mov eax, 80             ; This is the desired offset of the interrupt text
      push eax                ; push the offset
      call setCursorOffset    ; Set the offset so the interrupt text is in the right place
      pop eax                 ; Remove the data from the stack
      
      mov eax, isrstr00       ; Send the string to print to eax
      push 0x4f               ; Thi is the color of the text we want to print
      push eax                ; push the pointer to the string to the C function
      call printS             ; call the C func
      pop eax                 ; Remove the data from the stack
      pop eax                 ; Remove the data from the stack
      
      call setCursorOffset    ; The 'getCursorOffset' data is still at the top of the stack
      pop eax                 ; Remove the data from the stack
      
      popad
      sti
      iret





isrstr01: db "Int#: 01 Debug", 0x00
isr1:       ; Debug
      cli
      pushad
      
      call getCursorOffset
      push eax
      
      call clearTop
      
      mov eax, 80
      push eax
      call setCursorOffset
      pop eax
      
      mov eax, isrstr01
      push 0x4f
      push eax
      call printS
      pop eax
      pop eax
      
      call setCursorOffset
      pop eax
      
      popad
      sti
      iret





isrstr02: db "Int#: 02 Non-Maskable Interrupt", 0x00
isr2:       ; Non-Maskable Interrupt
      cli
      pushad
      
      call getCursorOffset
      push eax
      
      call clearTop
      
      mov eax, 80
      push eax
      call setCursorOffset
      pop eax
      
      mov eax, isrstr02
      push 0x4f
      push eax
      call printS
      pop eax
      pop eax
      
      call setCursorOffset
      pop eax
      
      popad
      sti
      iret





isrstr03: db "Int#: 03 Breakpoint", 0x00
isr3:       ; Breakpoint
      cli
      pushad
      
      call getCursorOffset
      push eax
      
      call clearTop
      
      mov eax, 80
      push eax
      call setCursorOffset
      pop eax
      
      mov eax, isrstr03
      push 0x4f
      push eax
      call printS
      pop eax
      pop eax
      
      call setCursorOffset
      pop eax
      
      popad
      sti
      iret





isrstr04: db "Int#: 04 Overflow", 0x00
isr4:       ; Overflow
      cli
      pushad
      
      call getCursorOffset
      push eax
      
      call clearTop
      
      mov eax, 80
      push eax
      call setCursorOffset
      pop eax
      
      mov eax, isrstr04
      push 0x4f
      push eax
      call printS
      pop eax
      pop eax
      
      call setCursorOffset
      pop eax
      
      popad
      sti
      iret





isrstr05: db "Int#: 05 Bound Range Exceeded", 0x00
isr5:       ; Bound Range Exceeded
      cli
      pushad
      
      call getCursorOffset
      push eax
      
      call clearTop
      
      mov eax, 80
      push eax
      call setCursorOffset
      pop eax
      
      mov eax, isrstr05
      push 0x4f
      push eax
      call printS
      pop eax
      pop eax
      
      call setCursorOffset
      pop eax
      
      popad
      sti
      iret





isrstr06: db "Int#: 06 Invalid Opcode", 0x00
isr6:       ; Invalid Opcode
      cli
      pushad
      
      call getCursorOffset
      push eax
      
      call clearTop
      
      mov eax, 80
      push eax
      call setCursorOffset
      pop eax
      
      mov eax, isrstr06
      push 0x4f
      push eax
      call printS
      pop eax
      pop eax
      
      call setCursorOffset
      pop eax
      
      popad
      sti
      iret





isrstr07: db "Int#: 07 Device Not Available", 0x00
isr7:       ; Device Not Available
      cli
      pushad
      
      call getCursorOffset
      push eax
      
      call clearTop
      
      mov eax, 80
      push eax
      call setCursorOffset
      pop eax
      
      mov eax, isrstr07
      push 0x4f
      push eax
      call printS
      pop eax
      pop eax
      
      call setCursorOffset
      pop eax
      
      popad
      sti
      iret





isrstr08: db "Int#: 08 Double Fault-> Err: ", 0x00
isr8:       ; Double Fault
      cli
      pushad
      
      call getCursorOffset
      push eax
      
      call clearTop
      
      mov eax, 80
      push eax
      call setCursorOffset
      pop eax
      
      mov eax, isrstr08
      push 0x4f
      push eax
      call printS
      pop eax
      pop eax
      
      mov eax, [esp+36]       ; This is the location on the stack of the interrupt Err code
      push 0x4f               ; This is the color of the Err code
      push eax
      call printN             ; C function for printNumber
      pop eax
      pop eax
      
      call setCursorOffset
      pop eax
      
      popad
      sti
      iret





isrstr09: db "Int#: 09 Coprocessor Segment Overrun", 0x00
isr9:       ; Coprocessor Segment Overrun (Obsolete)
      cli
      pushad
      
      call getCursorOffset
      push eax
      
      call clearTop
      
      mov eax, 80
      push eax
      call setCursorOffset
      pop eax
      
      mov eax, isrstr09
      push 0x4f
      push eax
      call printS
      pop eax
      pop eax
      
      call setCursorOffset
      pop eax
      
      popad
      sti
      iret





isrstr10: db "Int#: 10 Invalid TSS-> Err: ", 0x00
isr10:      ; Invalid TSS
      cli
      pushad
      
      call getCursorOffset
      push eax
      
      call clearTop
      
      mov eax, 80
      push eax
      call setCursorOffset
      pop eax
      
      mov eax, isrstr10
      push 0x4f
      push eax
      call printS
      pop eax
      pop eax
      
      mov eax, [esp+36]
      push 0x4f
      push eax
      call printN
      pop eax
      pop eax
      
      call setCursorOffset
      pop eax
      
      popad
      sti
      iret





isrstr11: db "Int#: 11 Seg not Present-> Err: ", 0x00
isr11:      ; Segment not present
      cli
      pushad
      
      call getCursorOffset
      push eax
      
      call clearTop
      
      mov eax, 80
      push eax
      call setCursorOffset
      pop eax
      
      mov eax, isrstr11
      push 0x4f
      push eax
      call printS
      pop eax
      pop eax
      
      mov eax, [esp+36]
      push 0x4f
      push eax
      call printN
      pop eax
      pop eax
      
      call setCursorOffset
      pop eax
      
      popad
      sti
      iret





isrstr12: db "Int#: 12 SSF-> Err: ", 0x00
isr12:      ; Stack-Segment Fault
      cli
      pushad
      
      call getCursorOffset
      push eax
      
      call clearTop
      
      mov eax, 80
      push eax
      call setCursorOffset
      pop eax
      
      mov eax, isrstr12
      push 0x4f
      push eax
      call printS
      pop eax
      pop eax
      
      mov eax, [esp+36]
      push 0x4f
      push eax
      call printN
      pop eax
      pop eax
      
      call setCursorOffset
      pop eax
      
      popad
      sti
      iret





isrstr13: db "Int#: 13 GPF-> Err: ", 0x00
isr13:      ; General Protection Fault
      cli
      pushad
      
      call getCursorOffset
      push eax
      
      call clearTop
      
      mov eax, 80
      push eax
      call setCursorOffset
      pop eax
      
      mov eax, isrstr13
      push 0x4f
      push eax
      call printS
      pop eax
      pop eax
      
      mov eax, [esp+36]
      push 0x4f
      push eax
      call printN
      pop eax
      pop eax
      
      call setCursorOffset
      pop eax
      
      popad
      sti
      iret





isrstr14: db "Int#: 14 Page Fault-> Err: ", 0x00
isr14:      ; Page Fault
      cli
      pushad
      
      call getCursorOffset
      push eax
      
      call clearTop
      
      mov eax, 80
      push eax
      call setCursorOffset
      pop eax
      
      mov eax, isrstr14
      push 0x4f
      push eax
      call printS
      pop eax
      pop eax
      
      mov eax, [esp+36]
      push 0x4f
      push eax
      call printN
      pop eax
      pop eax
      
      call setCursorOffset
      pop eax
      
      popad
      sti
      iret





isrstr15: db "Int#: 15 Reserved (you have a problem)", 0x00
isr15:      ; Reserved
      cli
      pushad
      
      call getCursorOffset
      push eax
      
      call clearTop
      
      mov eax, 80
      push eax
      call setCursorOffset
      pop eax
      
      mov eax, isrstr15
      push 0x4f
      push eax
      call printS
      pop eax
      pop eax
      
      call setCursorOffset
      pop eax
      
      popad
      sti
      iret





isrstr16: db "Int#: 16 Floating-Point Exception", 0x00
isr16:      ; x87 Floating-Point Exception
      cli
      pushad
      
      call getCursorOffset
      push eax
      
      call clearTop
      
      mov eax, 80
      push eax
      call setCursorOffset
      pop eax
      
      mov eax, isrstr16
      push 0x4f
      push eax
      call printS
      pop eax
      pop eax
      
      call setCursorOffset
      pop eax
      
      popad
      sti
      iret





isrstr17: db "Int#: 17 Alignment Check-> Err: ", 0x00
isr17:      ; Alignment Check
      cli
      pushad
      
      call getCursorOffset
      push eax
      
      call clearTop
      
      mov eax, 80
      push eax
      call setCursorOffset
      pop eax
      
      mov eax, isrstr17
      push 0x4f
      push eax
      call printS
      pop eax
      pop eax
      
      mov eax, [esp+36]
      push 0x4f
      push eax
      call printN
      pop eax
      pop eax
      
      call setCursorOffset
      pop eax
      
      popad
      sti
      iret





isrstr18: db "Int#: 18 Machine Check", 0x00
isr18:      ; Machine Check
      cli
      pushad
      
      call getCursorOffset
      push eax
      
      call clearTop
      
      mov eax, 80
      push eax
      call setCursorOffset
      pop eax
      
      mov eax, isrstr18
      push 0x4f
      push eax
      call printS
      pop eax
      pop eax
      
      call setCursorOffset
      pop eax
      
      popad
      sti
      iret





isrstr19: db "Int#: 19 SIMD Floating-Point", 0x00
isr19:      ; SIMD Floating-Point Exception
      cli
      pushad
      
      call getCursorOffset
      push eax
      
      call clearTop
      
      mov eax, 80
      push eax
      call setCursorOffset
      pop eax
      
      mov eax, isrstr19
      push 0x4f
      push eax
      call printS
      pop eax
      pop eax
      
      call setCursorOffset
      pop eax
      
      popad
      sti
      iret





isrstr20: db "Int#: 20 Virtualization Exception", 0x00
isr20:      ; Virtualization Exception
      cli
      pushad
      
      call getCursorOffset
      push eax
      
      call clearTop
      
      mov eax, 80
      push eax
      call setCursorOffset
      pop eax
      
      mov eax, isrstr20
      push 0x4f
      push eax
      call printS
      pop eax
      pop eax
      
      call setCursorOffset
      pop eax
      
      popad
      sti
      iret





isrstr21: db "Int#: 21 Reserved (you have a problem)", 0x00
isr21:      ; Reserved
      cli
      pushad
      
      call getCursorOffset
      push eax
      
      call clearTop
      
      mov eax, 80
      push eax
      call setCursorOffset
      pop eax
      
      mov eax, isrstr21
      push 0x4f
      push eax
      call printS
      pop eax
      pop eax
      
      call setCursorOffset
      pop eax
      
      popad
      sti
      iret





isrstr22: db "Int#: 22 Reserved (you have a problem)", 0x00
isr22:      ; Reserved
      cli
      pushad
      
      call getCursorOffset
      push eax
      
      call clearTop
      
      mov eax, 80
      push eax
      call setCursorOffset
      pop eax
      
      mov eax, isrstr22
      push 0x4f
      push eax
      call printS
      pop eax
      pop eax
      
      call setCursorOffset
      pop eax
      
      popad
      sti
      iret





isrstr23: db "Int#: 23 Reserved (you have a problem)", 0x00
isr23:      ; Reserved
      cli
      pushad
      
      call getCursorOffset
      push eax
      
      call clearTop
      
      mov eax, 80
      push eax
      call setCursorOffset
      pop eax
      
      mov eax, isrstr23
      push 0x4f
      push eax
      call printS
      pop eax
      pop eax
      
      call setCursorOffset
      pop eax
      
      popad
      sti
      iret





isrstr24: db "Int#: 24 Reserved (you have a problem)", 0x00
isr24:      ; Reserved
      cli
      pushad
      
      call getCursorOffset
      push eax
      
      call clearTop
      
      mov eax, 80
      push eax
      call setCursorOffset
      pop eax
      
      mov eax, isrstr24
      push 0x4f
      push eax
      call printS
      pop eax
      pop eax
      
      call setCursorOffset
      pop eax
      
      popad
      sti
      iret





isrstr25: db "Int#: 25 Reserved (you have a problem)", 0x00
isr25:      ; Reserved
      cli
      pushad
      
      call getCursorOffset
      push eax
      
      call clearTop
      
      mov eax, 80
      push eax
      call setCursorOffset
      pop eax
      
      mov eax, isrstr25
      push 0x4f
      push eax
      call printS
      pop eax
      pop eax
      
      call setCursorOffset
      pop eax
      
      popad
      sti
      iret





isrstr26: db "Int#: 26 Reserved (you have a problem)", 0x00
isr26:      ; Reserved
      cli
      pushad
      
      call getCursorOffset
      push eax
      
      call clearTop
      
      mov eax, 80
      push eax
      call setCursorOffset
      pop eax
      
      mov eax, isrstr26
      push 0x4f
      push eax
      call printS
      pop eax
      pop eax
      
      call setCursorOffset
      pop eax
      
      popad
      sti
      iret





isrstr27: db "Int#: 27 Reserved (you have a problem)", 0x00
isr27:      ; Reserved
      cli
      pushad
      
      call getCursorOffset
      push eax
      
      call clearTop
      
      mov eax, 80
      push eax
      call setCursorOffset
      pop eax
      
      mov eax, isrstr27
      push 0x4f
      push eax
      call printS
      pop eax
      pop eax
      
      call setCursorOffset
      pop eax
      
      popad
      sti
      iret





isrstr28: db "Int#: 28 Reserved (you have a problem)", 0x00
isr28:      ; Reserved
      cli
      pushad
      
      call getCursorOffset
      push eax
      
      call clearTop
      
      mov eax, 80
      push eax
      call setCursorOffset
      pop eax
      
      mov eax, isrstr28
      push 0x4f
      push eax
      call printS
      pop eax
      pop eax
      
      call setCursorOffset
      pop eax
      
      popad
      sti
      iret





isrstr29: db "Int#: 29 Reserved (you have a problem)", 0x00
isr29:      ; Reserved
      cli
      pushad
      
      call getCursorOffset
      push eax
      
      call clearTop
      
      mov eax, 80
      push eax
      call setCursorOffset
      pop eax
      
      mov eax, isrstr29
      push 0x4f
      push eax
      call printS
      pop eax
      pop eax
      
      call setCursorOffset
      pop eax
      
      popad
      sti
      iret





isrstr30: db "Int#: 30 Security Exception-> Err: ", 0x00
isr30:      ; Security Exception
      cli
      pushad
      
      call getCursorOffset
      push eax
      
      call clearTop
      
      mov eax, 80
      push eax
      call setCursorOffset
      pop eax
      
      mov eax, isrstr30
      push 0x4f
      push eax
      call printS
      pop eax
      pop eax
      
      mov eax, [esp+36]
      push 0x4f
      push eax
      call printN
      pop eax
      pop eax
      
      call setCursorOffset
      pop eax
      
      popad
      sti
      iret





isrstr31: db "Int#: 31 Reserved (you have a problem)", 0x00
isr31:      ; Reserved
      cli
      pushad
      
      call getCursorOffset
      push eax
      
      call clearTop
      
      mov eax, 80
      push eax
      call setCursorOffset
      pop eax
      
      mov eax, isrstr31
      push 0x4f
      push eax
      call printS
      pop eax
      pop eax
      
      call setCursorOffset
      pop eax
      
      popad
      sti
      iret

      



; PIC handlers

; Timer
timer:
      cli
      pushad
      
      call timerHandler
      
      .done:
        mov ax, 0x20
        mov dx, 0x20
        out dx, ax
        popad
        sti
        iret



; Keyboard
keyboard:
      cli
      pushad
      
      call keyboardHandler
      
      .done:
        mov ax, 0x20
        mov dx, 0x20
        out dx, ax
        popad
        sti
        iret



realTimeClock:
      cli
      pushad
      
      call rtcHandler
      
      .done:
        mov ax, 0x20
        mov dx, 0x20
        out dx, ax
        popad
        sti
        iret
