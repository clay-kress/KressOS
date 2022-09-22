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

