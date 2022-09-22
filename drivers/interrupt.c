/***********************************************************************/
/* Copyright (c) 2022 Clay Kress                                       */
/*                                                                     */
/* This file is part of KressOS.                                       */
/* KressOS is free software: you can redistribute it and/or modify it  */
/* under the terms of the GNU General Public License as published by   */
/* the Free Software Foundation, either version 3 of the License, or   */
/* (at your option) any later version.                                 */
/*                                                                     */
/* Foobar is distributed in the hope that it will be useful,           */
/* but WITHOUT ANY WARRANTY; without even the implied warranty         */
/* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.             */
/*                                                                     */
/* See the GNU General Public License for more details.                */
/*                                                                     */
/* You should have received a copy of the GNU General Public License   */
/* along with Foobar. If not, see <https://www.gnu.org/licenses/>.     */
/*                                                                     */
/***********************************************************************/

#include "AH.h"


/**********************************************************************/
idtSegment intSeg[256];
idtDiscriptor IDTD;
/**********************************************************************/
void initIDT(char PICOffset) {
      
      // Sets the IDT Descriptor
      IDTD.length= sizeof(idtSegment)*256 -1;                           // Set the length to the size of the segments times the number of segments
      IDTD.base= (u32bit) &intSeg;                                      // Sets the start of the IDT to the adress of the segments
      
      // Sets all segments to NULL so the CPU doesnt triple-fault when it encounters an int that hasn't been defined
      memSet(&intSeg, &intSeg[255], 0x00);
      
      // Sets the CPU Exception handlers (handlerNum, handlerAdress, codeSegment, Flags) -- Learn what flags mean in 'interrupt.h'
      setGate(0, (u32bit)isr0, 0x08, 0x8E);
      setGate(1, (u32bit)isr1, 0x08, 0x8E);
      setGate(2, (u32bit)isr2, 0x08, 0x8E);
      setGate(3, (u32bit)isr3, 0x08, 0x8E);
      setGate(4, (u32bit)isr4, 0x08, 0x8E);
      setGate(5, (u32bit)isr5, 0x08, 0x8E);
      setGate(6, (u32bit)isr6, 0x08, 0x8E);
      setGate(7, (u32bit)isr7, 0x08, 0x8E);
      setGate(8, (u32bit)isr8, 0x08, 0x8E);
      setGate(9, (u32bit)isr9, 0x08, 0x8E);
      setGate(10, (u32bit)isr10, 0x08, 0x8E);
      setGate(11, (u32bit)isr11, 0x08, 0x8E);
      setGate(12, (u32bit)isr12, 0x08, 0x8E);
      setGate(13, (u32bit)isr13, 0x08, 0x8E);
      setGate(14, (u32bit)isr14, 0x08, 0x8E);
      setGate(15, (u32bit)isr15, 0x08, 0x8E);
      setGate(16, (u32bit)isr16, 0x08, 0x8E);
      setGate(17, (u32bit)isr17, 0x08, 0x8E);
      setGate(18, (u32bit)isr18, 0x08, 0x8E);
      setGate(19, (u32bit)isr19, 0x08, 0x8E);
      setGate(20, (u32bit)isr20, 0x08, 0x8E);
      setGate(21, (u32bit)isr21, 0x08, 0x8E);
      setGate(22, (u32bit)isr22, 0x08, 0x8E);
      setGate(23, (u32bit)isr23, 0x08, 0x8E);
      setGate(24, (u32bit)isr24, 0x08, 0x8E);
      setGate(25, (u32bit)isr25, 0x08, 0x8E);
      setGate(26, (u32bit)isr26, 0x08, 0x8E);
      setGate(27, (u32bit)isr27, 0x08, 0x8E);
      setGate(28, (u32bit)isr28, 0x08, 0x8E);
      setGate(29, (u32bit)isr29, 0x08, 0x8E);
      setGate(30, (u32bit)isr30, 0x08, 0x8E);
      setGate(31, (u32bit)isr31, 0x08, 0x8E);
      
      // Set PIC Handlers
      setGate(PICOffset+ TimerIRQ, (u32bit)timer, 0x08, 0x8E);
      setGate(PICOffset+ KeyboardIRQ, (u32bit)keyboard, 0x08, 0x8E);
      setGate(PICOffset+ ClockIRQ, (u32bit)realTimeClock, 0x08, 0x8E);
      
      // lidt [&IDTD]         (Assembly Function)
      loadIDT((u32bit)&IDTD);
      
      // Set up PIC
      initPIC(PICOffset);
      
      setMask(TimerIRQ);
      setMask(KeyboardIRQ);
      setMask(CascadeIRQ);
      setMask(Serial2IRQ);
      setMask(Serial1IRQ);
      setMask(ParallelIRQ);
      setMask(FloppyIRQ);
      setMask(PrinterIRQ);
      setMask(ClockIRQ);
      setMask(ACPIIRQ);
      setMask(SCSIIRQ);
      setMask(NICIRQ);
      setMask(MouseIRQ);
      setMask(FPUIRQ);
      setMask(SATA1IRQ);
      setMask(SATA2IRQ);
      
      // sti                  (Assembly Function)
      enableInt();
      
      return;
}
/**********************************************************************/
void setGate(u08bit num, u32bit base, u16bit codeSeg, u08bit flagByte) {
      
      intSeg[num].offsetLow= base & 0xFFFF;                             // Masks the low 16 bits of base
      intSeg[num].offsetHigh= (base >> 16);                             // Shifts the value of base right 16 bits effectively masking the high part of base
      
      intSeg[num].segSelector= codeSeg;                                 // Sets the segment selector in the interrupt segment
      intSeg[num].zero= 0x00;                                           // Sets the zeros byte in the interrupt segment
      
      intSeg[num].flags= flagByte;                                      // Set flags to the input flag byte
      
      return;
}
/**********************************************************************/
void setMask(char IRQline) {
      
      short port;
      char mask;
      
      if (IRQline < 8) {                                                // If the line is less than 8, than use PIC1
            port= PIC1Data;
      } else {                                                          // If the line in greater than 8, than use PIC2
            port= PIC2Data;
            IRQline -= 8;                                               // Subtract 8 from the line to use it as an offset for the chip
      }
      
      mask= byteREAD(port) | (1 << IRQline);                            // Take the data from the port and switch the line from 0 to 1
      byteWRITE(port, mask);                                            // Write the mask back to the port
      
      return;
}
/**********************************************************************/
void clearMask(char IRQline) {
      
      short port;
      char mask;
      
      if (IRQline < 8) {                                                // If the line is less than 8, than use PIC1
            port= PIC1Data;
      } else {                                                          // If the line in greater than 8, than use PIC2
            port= PIC2Data;
            IRQline -= 8;                                               // Subtract 8 from the line to use it as an offset for the chip
      }
      
      mask= byteREAD(port) & ~(1 << IRQline);                           // Take the data from the port and switch the line from 1 to 0
      byteWRITE(port, mask);                                            // Write the mask back to the port
      
      return;
}
/**********************************************************************/
void initPIC(int offset) {
      
      char mask1= byteREAD(PIC1Data);                                   // Stores the masks for the PIC1 chip so we can overwrite it and reset later
      char mask2= byteREAD(PIC2Data);                                   // Stores the masks for the PIC2 chip so we can overwrite it and reset later
      
      // Init number
      byteWRITE(PIC1Command, 0x11);                                     // Tell the PIC1 to initialize
      byteWRITE(PIC2Command, 0x11);                                     // Tell the PIC2 to initialize
      
      // Send Offsets
      byteWRITE(PIC1Data, offset);                                      // Tell the PIC1 chip its offset
      byteWRITE(PIC2Data, offset+8);                                    // Tell the PIC2 chip its offset
      
      // Tell The chips their orientation with respect to eachother (master, slave, etc.)
      byteWRITE(PIC1Data, 0x04);                                        // Tell the master where the slave is connected (IRQ2)
      byteWRITE(PIC2Data, 0x02);                                        // Tell the slave PIC where to cascade to (IRQ2)
      
      
      // Reload the masks into the PICs
      byteWRITE(PIC1Data, mask1);                                       // Reload the masks into PIC1
      byteWRITE(PIC2Data, mask2);                                       // Reload the masks into PIC2
      
      return;
}
/**********************************************************************/
