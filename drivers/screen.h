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

/*
 * 0F: White
 * 0E: Yellow
 * 0D: Magenta
 * 0C: Orange
 * 0B: Light Blue
 * 0A: Light Green
 * 09: Blue
 * 08: Grey
 * 07: Light Grey
 * 06: Brown
 * 05: Purple
 * 04: Red
 * 03: Dark Cyan
 * 02: Dark Green
 * 01: Dark Blue
 * 00: Black
 */

#define MaxRows 25
#define MaxCols 40

#define DefaultColor 0x0A
#define VideoMemory 0xb8000

#define RegisterCTRL 0x3D4
#define RegisterDATA 0x3D5

/*    Screen Functions:
 *      - The first three lines are not supposed to be accessible by the user (although they can be accesed using the setCursorOffset() and getCoordsOffset() functions)
 *      - The first line is used by the timer to print the number of seconds since boot
 *      - The second is used by the CPU exception interrupts to notify the user of any CPU exceptions
 *      - You can make them accessible by changing the clearScreen, clearTop, and scroll functions to copy characters to and from that region
 *      - printN prints in Hex format, you can change this by editing the HexToString function (and hopefully renaming it)
 * --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */


// Printing Functions
void FloatToString(char* result, float value);                          // Converts an float to a string in base 10
void NumToString(char* result, int value, int base);                    // Converts an int to a string in hexadecimal format

void printF(float number, char color);                                  // Prints a number to the screen (floating point)
void printN(int number, char color);                                    // Prints a number to the screen (in hexadecimal format)
void printI(int number, char color);                                    // Prints a number to the screen (in decimal format)
void printS(char* message, char color);                                 // Prints the input message to the screen
void printChar(char character, char color);                             // Prints a single char to the screen


// Utility Functions
void clearScreen(void);                                                 // Really an initScreen function: sets up the screen for general usage
void clearTop(void);                                                    // Only used by interrupts to keep them from overlaping text on the screen
void carridgeReturn(int times);                                         // Returns as many times as is specified
void scroll(void);                                                      // Copies the letters on the screen up one line

int getCoordsOffset(int x, int y);                                      // Simply performs a mathematical function, calculates the offset of two x,y coordinates
void setCursorOffset(int offset);                                       // Sets the screen cursor to the specified offset
int getCursorOffset(void);                                              // Gets the cursor offset from the screen port

