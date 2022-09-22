/***********************************************************************/
/* Copyright (c) 2022 Clay Kress                                       */
/*                                                                     */
/* This file is part of KressOS.                                       */
/* KressOS is free software: you can redistribute it and/or modify it  */
/* under the terms of the GNU General Public License as published by   */
/* the Free Software Foundation, either version 3 of the License, or   */
/* (at your option) any later version.                                 */
/*                                                                     */
/* KressOS is distributed in the hope that it will be useful,          */
/* but WITHOUT ANY WARRANTY; without even the implied warranty         */
/* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.             */
/*                                                                     */
/* See the GNU General Public License for more details.                */
/*                                                                     */
/* You should have received a copy of the GNU General Public License   */
/* along with KressOS. If not, see <https://www.gnu.org/licenses/>.    */
/*                                                                     */
/***********************************************************************/

/*** PIC Defs *********************************************************/
#define PIC1Command 0x20
#define PIC1Data 0x21

#define PIC2Command 0xA0
#define PIC2Data 0xA1

#define TimerIRQ 0
#define KeyboardIRQ 1
#define CascadeIRQ 2
#define Serial2IRQ 3
#define Serial1IRQ 4
#define ParallelIRQ 5
#define FloppyIRQ 6
#define PrinterIRQ 7
#define ClockIRQ 8
#define ACPIIRQ 9
#define SCSIIRQ 10
#define NICIRQ 11
#define MouseIRQ 12
#define FPUIRQ 13
#define SATA1IRQ 14
#define SATA2IRQ 15
/**********************************************************************/

/*** Interrupt Defs ***************************************************/
typedef unsigned char u08bit;
typedef unsigned short u16bit;
typedef unsigned int u32bit;
typedef unsigned long long u64bit;

/* Flags:
 *    
 *    Byte 1:     Present: Set to 0 for unused interrupts
 *    Byte 2,3:   Privilage Level: Minimum Privilage level of the calling function
 *    Byte 4:     Storage Segment: Set to 0 for interrupt and trap gates
 *    Byte 5,8:   Type:
 *                      0x5 for 32-bit task gate
 *                      0x6 for 16-bit interrupt gate
 *                      0x7 for 16-bit trap gate
 *                      0xE for 32-bit interrupt gate
 *                      0xF for 32-bit trap gate
 */
 
// 64 bit (8 byte) struct
typedef struct {
      u16bit offsetLow;                                                 // Offset represents the address of the entry point of the ISR (Low 16 bits)
      u16bit segSelector;                                               // Code Segment Selector
      u08bit zero;                                                      // A byte of zeros for whatever reason
      u08bit flags;                                                     // Flags: (see lengthy comment above)
      u16bit offsetHigh;                                                // Offset represents the address of the entry point of the ISR (High 16 bits)
} __attribute__((packed)) idtSegment;

// 48 bit (6 byte) struct
typedef struct {
      u16bit length;                                                    // Length of the IDT
      u32bit base;                                                      // Start adress of the IDT
} __attribute__((packed)) idtDiscriptor;
/**********************************************************************/


/*** Assembly Handlers ************************************************/
// The assembly functions for handling internal CPU errors (mainly used to reference the address of the interrupt handlers while setting the IDT)
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

// PIC handlers
extern void timer();
extern void keyboard();
extern void realTimeClock();
/**********************************************************************/


// Links to generate the actual interrupts from C  (command int 0x1, int 0x2, etc.)
extern void int0x00();                                                  // int 0x00
extern void int0x01();                                                  // int 0x01
extern void int0x02();                                                  // int 0x02
extern void int0x03();                                                  // int 0x03
extern void int0x04();                                                  // int 0x04
extern void int0x05();                                                  // int 0x05
extern void int0x06();                                                  // int 0x06
extern void int0x07();                                                  // int 0x07
extern void int0x08();                                                  // int 0x08
extern void int0x09();                                                  // int 0x09
extern void int0x0A();                                                  // int 0x0A
extern void int0x0B();                                                  // int 0x0B
extern void int0x0C();                                                  // int 0x0C
extern void int0x0D();                                                  // int 0x0D
extern void int0x0E();                                                  // int 0x0E
extern void int0x0F();                                                  // int 0x0F
extern void int0x10();                                                  // int 0x10
extern void int0x11();                                                  // int 0x11
extern void int0x12();                                                  // int 0x12
extern void int0x13();                                                  // int 0x13
extern void int0x14();                                                  // int 0x14
extern void int0x15();                                                  // int 0x15
extern void int0x16();                                                  // int 0x16
extern void int0x17();                                                  // int 0x17
extern void int0x18();                                                  // int 0x18
extern void int0x19();                                                  // int 0x19
extern void int0x1A();                                                  // int 0x1A
extern void int0x1B();                                                  // int 0x1B
extern void int0x1C();                                                  // int 0x1C
extern void int0x1D();                                                  // int 0x1D
extern void int0x1E();                                                  // int 0x1E
extern void int0x1F();                                                  // int 0x1F


// External Functions
extern void loadIDT(u32bit);                                            // lidt assembly command
extern void enableInt();                                                // sti assembly command
extern void disableInt();                                               // cli assenbly command

// Utility Functions
void initIDT(char PICOffset);                                           // Makes and loads the IDT
void setGate(u08bit num, u32bit base, u16bit codeSeg, u08bit flagByte); // Defines a specific gate in the IDT

void initPIC(int offset);                                               // Initializes the PIC's
void setMask(char IRQline);                                             // Disable a specific PIC line
void clearMask(char IRQline);                                           // Enable a specific PIC line

