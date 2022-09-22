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
; Foobar is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty
; of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
;
; See the GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with Foobar. If not, see <https://www.gnu.org/licenses/>.
;
;=======================================================================

; GDT structure section:
;
; low 16 bits of limit        (16 bit)
; low 16 bits of base         (16 bit)
; mid 8 bits of base          (08 bit)
; byte of flags               (08 bit)
;     bit 8       : "Segment is present in RAM"
;     bit 7-6     : Privilage level of code in the segment
;     bit 5       : 1 for code/data, 0 is for traps
;     bit 4       : 1 for code, 0 for data
;     bit 3       : 0= protected, 1= open
;     bit 2       : Readable (1)
;     bit 1       : Accessed, always 0
; nybble of flags             (04 bit)
;     bit 4       : Granularity, if 1, limit is multiplied by 16*16*16
;     bit 3       : bit number, 1 for 32 bit, 0 for 16
;     bit 2       : 64 bit, unused on 32 bit system 
;     bit 1       : dont use (0)
; last nybble of limit        (04 bit)
; high 8 bits of base         (08 bit)

; GDT for protected mode goes here--------------------------------------
      GDTD:
        dw gdtEnd - gdtStart - 1    ; Size of GDT
        dd gdtStart                 ; Address of start
      
      gdtStart:
        
        null:
          dd 0x0000
          dd 0x0000
        
        codeSeg: ; Starts at 0x0000, Ends at 0xffff0000
          dw 0xffff     ; Limit
          dw 0x0000     ; Base
          db 0x00       ; Base
          db 10011010b  ; Flags
          db 11000000b  ; Flags, last nibble: Limit
          db 0x00       ; Base
        
        dataSeg: ; Starts at 0x0000, Ends at 0xffff0000
          dw 0xffff     ; Limit
          dw 0x0000     ; Base
          db 0x00       ; Base
          db 10010010b  ; Flags
          db 11000000b  ; Flags, last nibble: Limit
          db 0x00       ; Base
        
        stakSeg: ; Starts at 0x0000, Ends at 0xffff0000
          dw 0xffff     ; Limit
          dw 0x0000     ; Base
          db 0x00       ; Base
          db 10010010b  ; Flags
          db 11000000b  ; Flags, last nibble: Limit
          db 0x00       ; Base
        
      gdtEnd:
      
      ; Constants to set the segment registers to
      cSegOffset equ codeSeg - gdtStart ; offset of cSeg= 0x08
      dSegOffset equ dataSeg - gdtStart ; offset of dSeg= 0x10
      sSegOffset equ stakSeg - gdtStart ; offset of sSeg= 0x18
; GDT for protected mode goes here--------------------------------------
