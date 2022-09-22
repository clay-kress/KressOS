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

; The boot sector is located in RAM from 0x7c00 to 0x7e00

[org 0x7c00]
[bits 16]

jmp 0x0000:start              ; Set cs (code segment) to zero

%include "boot/startGDT.asm"
bootDrive db 0
daySavTime db 0

start:
      
      ; Inits all relevant registers------------------------------------------
      xor di, di
      xor si, si
      
      
      xor ax, ax
      mov ss, ax              ; Set ss (stack segment) to zero
      mov ds, ax              ; Set ds (data segment) to zero
      mov es, ax
      mov fs, ax
      mov gs, ax
      
      
      mov ax, 0x7c00
      mov bp, ax              ; Set bp (base pointer) for our stack
      mov sp, ax              ; Set sp (stack pointer) equal to the bp
      ; Inits all relevant registers------------------------------------------
      
      mov [bootDrive], dl     ; Stores the drive # in bootDrive
      
      
      ; Boot code goes here---------------------------------------------------
      mov ax, 0x0000          ; int 10/ah= 0x00 -> set video mode (clear screen)
      int 0x10
      
      
      ; Loads the Kernel into RAM at 0x7e00
      mov dl, [bootDrive]     ; Drive to load from
      mov bx, 0x7e00          ; Mem address to load into
      mov al, 0x30            ; Number of sectors to load
      mov cl, 0x02            ; Sector to start at (1st is 1)
      mov dh, 0x00            ; Head to start at (0 for flash mem)
      mov ch, 0x00            ; Cylinder to start at (0 for flash mem)
      mov ah, 0x02            ; ah=0x02 tells int 0x13 to read from a disk
      call readDisk
      
      
      ; Return:
      ;     CH = hour
      ;     CL = minutes
      ;     DH = seconds
      ;     DL = daylight savings flag (00h standard time, 01h daylight time)
      mov ah, 0x02
      int 0x1A
      mov [daySavTime], dl
      
      call enableA20
      
      ; Switches the CPU mode from 16-bit (real) to 32-bit (protected)
      lgdt [GDTD]             ; Tell the CPU about the GDT included in this file
      cli                     ; Clears Interrupts, telling the CPU not to accept them
      mov eax, cr0            ; cr0 is a CPU control register
      or eax, 0x1             ; Switch the lowest bit in cr0 to 1
      mov cr0, eax            ; mov the updated bits into cr0
      
      ; This jump keeps the CPU from executing 32-bit code in 16-bit mode
      jmp cSegOffset:startPM  ; 'Far jump' to our 32-bit init code
      ; Boot code goes here---------------------------------------------------
jmp $                         ; Incase something goes wrong, continuously loop here



printStr:               ; Routine: print the string pointed to by si
      pusha
      mov ah, 0x0E                                                      ; ah= 0x0E: teletype output
                                                                        ; AL = Character, BH = Page Number, BL = Color (only in graphic mode)
      
      .loopStr:
        lodsb                                                           ; load the byte in [si] into al
        cmp al, 0x00                                                    ; If it is zero, then terminate the string
        je .doneStr
        int 0x10                                                        ; else: print character
      jmp .loopStr
      
      .doneStr:
        popa
        ret



printHex:               ; Routine: print value in (dx) as hexadecimal
      pusha
      mov cx, 0x4
      
      mov bx, outputHex                                                 ; Sets bx to the address of outputHex
      add bx, 0x2                                                       ; Keeps the '0x' the same
      add bx, 0x3                                                       ; Sets the address to the last char
      
      .loopHex:
        dec cx
        
        mov ax, dx
        shr dx, 0x4                                                     ; Cuts successive hex chars off of dx
        and ax, 0x000f                                                  ; Masks successive hex chars in to ax
        
        cmp al, 0xa
        jge .letter                                                     ; If its a letter
        jl  .number                                                     ; If its a number
        
        .letter:
          sub al, 0x9                                                   ; Since hex letters start at 10, we subtract 10 and add 1
          or al, 0x60                                                   ; The first nibble of a lowercase letter is always 0110
          jmp .setChar
          
        .number:
          sub al, 0x0                                                   ; Numbers start at 0 so we dont need to unbias them
          or al, 0x30                                                   ; The first nibble of a number is always 0011
          jmp .setChar
        
        .setChar:
          mov [bx], al                                                  ; Write our char to the output var
          sub bx, 0x1                                                   ; bx should now point to the previous char
          
      cmp cx, 0x0
      jne .loopHex
      
      .doneHex:
        mov si, outputHex
        call printStr
        
        popa
        ret
      
      outputHex db "0x0000", 10, 13, 0x00



readDisk:               ; Routine: read disk, output message and freeze if error occurs
      pusha
      
      int 0x13                                                          ; The interrupt that we use
      jc .DiskError                                                     ; CF is set on error
      jmp .diskDone                                                     ; If no error, then skip error msg
      
      .DiskError:
        mov si, diskErrorStr                                            ; Prints "Warning; Fatal Disk Error"
        call printStr
        
        mov si, diskErrorNum                                            ; Prints "Error code (AX): "
        call printStr
        
        mov dx, ax                                                      ; Prints AX
        call printHex
        
        jmp $
      
      .diskDone:
        popa
        ret
        
      diskErrorStr db "Warning; Fatal Disk Error", 10, 13, 0x00
      diskErrorNum db "Error code (AX): ", 0x00



enableA20:
      pusha
      
      mov ax, 0x2401
      int 0x15
      jc .A20Error
      jmp .A20Done
      
      .A20Error:
        mov si, A20ErrorStr
        call printStr
        
        mov si, A20Status
        call printStr
        
        ; Prints status: (01=keyboard controller is in secure mode, 0x86=function not supported)
        mov al, 0
        mov dx, ax
        call printHex
        
        jmp $
      
      .A20Done:
        popa
        ret
      
      A20ErrorStr db "Error while enabling A20", 10, 13, 0x00
      A20Status db "Status (AH): ", 0x00


startPM:
      ; 32-bit protected mode Init--------------------------------------------
      [bits 32]
      
      mov ax, dSegOffset
      mov ds, ax
      mov es, ax
      mov fs, ax
      mov gs, ax
      
      mov ax, sSegOffset
      mov ss, ax
      
      xor eax, eax
      mov esi, eax
      mov edi, eax
      
      mov eax, 0x7c00
      mov esp, eax
      mov ebp, eax
      
      ; Values to send to the C code
      movzx ax, byte [daySavTime]
      push ax
      
      jmp 0x7e00
      ; 32-bit protected mode Init--------------------------------------------
jmp $                         ; Incase something goes wrong, continuously loop here



; Define a partition table:
times 440-($-$$) db 0x00

dw 0xD15C
dw 0xB001
dw 0x0000

; 0x80 = bootable : else 0x00
dw 0x0080
dw 0x0000

; Partition type
dw 0x0083
dw 0x0000

; First sector of partition
dw 0x0800         ; Secnd Word
dw 0x0000         ; First Word

; Number of Sectors
dw 0x0000         ; Secnd Word
dw 0x0060         ; First Word

times 510-($-$$) db 0x00
dw 0xaa55                     ; This number tells the BIOS that the disk is bootable

