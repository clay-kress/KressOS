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
int lastCommand= 0x00;                                                  // This variable keeps track of the last command so the ACK handler knows what to do
int ledStatus= 0x00;                                                    // This variable keeps track of all LED status so we can reference it across interrupts
int shiftPressed= 0x00;                                                 // This variable keeps track of whether either shift is pressed
int ctrlPressed= 0x00;                                                  // This variable keeps track of whether either control is pressed
int altPressed= 0x00;                                                   // This variable keeps track of whether either alt is pressed

char lowerCaseLetterArray[]= {                                          // This is the array of characters that correspond to lower case scan codes
      '~', '~', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-',  //                               (The '~'s signify special characters like Return or Delete)
      '=', '~', '~', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
      '[', ']', '~', '~', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
      ';', '\'', '`', '~', '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',',
      '.', '/', '~', '~', '~', ' ', '~'
};
char upperCaseLetterArray[]= {                                          // This is the array of characters that correspond to upper case scan codes
      '`', '`', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_',  //                               (The '`'s signify special characters like Return or Delete)
      '+', '`', '`', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
      '{', '}', '`', '`', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
      ':', '"', '~', '`', '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<',
      '>', '?', '`', '`', '`', ' ', '`'
};
/**********************************************************************/
void keyboardHandler(void) {
      
      // Make sure port 0x60 is full before reading from it
      while (byteREAD(ControllerStatusPort) & 0x01 != 1) {              // If bit 0 of the status port is set, then port 0x60 is ready to be read
            continue;
      }
      int scanCode= byteREAD(EncoderDataPort);                          // This reads the scanCode to tell exactly what key was pressed
      
      
      
      // These statements return if we don't care about the scan codes
      if (scanCode == ESC_UP || scanCode == DEL_UP || scanCode == TAB_UP || scanCode == RET_UP) {
            return;
      }
      // These statements return if we don't care about the scan codes
      if (scanCode == CAPLK_UP || scanCode == NUMLK_UP || scanCode == SCRLK_UP) {
            return;
      }
      
      
      
      switch(scanCode) {
            
            /*  These conditions deal with commanding the keyboard (LEDs, Errors) */
            case ACK:
                  
                  if (lastCommand == 0xED) {                            // If the command being acknowledged is the 0xED command then:
                        lastCommand= ledStatus;                         // Send the LED status as a command to the keyboard
                        sendKeyboardCommand(lastCommand);               // Send the command
                  }
                  break;
                  
            case RESND:
                  
                  // Sometimes the keyboard fails to read a command, at this point we notify the user of the failure and the last command (the one that made it fail)
                  printS("Keyboard failure:\n", 0x00);
                  printS("\tLast Command= ", 0x00);
                  printN(lastCommand, 0x00);
                  break;
            /**********************************************************/
            
            /*  These conditions are special keys on the keyboard (Escape, Delete, Tab, Return) */
            case ESC:
                  
                  // The escape key should make the system escape the current program
                  break;
                  
            case DEL:
                  
                  // The delete key deletes the previous character
                  if (getCursorOffset() > getCoordsOffset(1,4)) {       // If the cursor is below the reserved lines at the top of the screen
                        setCursorOffset(getCursorOffset()-2);           // Send the cursor back one space
                        printChar(' ', 0x00);                           // Replace the previous letter with a blank space
                        setCursorOffset(getCursorOffset()-2);           // Then send the sursor back to that space (undo where printChar sent us)
                  }
                  break;
                  
            case TAB:
                  
                  // This creates a 4 space Tab
                  setCursorOffset(getCursorOffset()+8);
                  break;
                  
            case RET:
                  
                  // Simple carridge return
                  carridgeReturn(1);
                  break;
            /**********************************************************/
            
            /*  These conditions deal with the shift keys (whether letters should be capitalized) */
            case LSHIFT:
                  
                  // Record that a shift key is pressed
                  shiftPressed= 1;
                  break;
                  
            case LSHIFT_UP:
                  
                  // Record that a shift key has been unpressed
                  shiftPressed= 0;
                  break;
                  
            case RSHIFT:
                  
                  // Record that a shift key is pressed
                  shiftPressed= 1;
                  break;
                  
            case RSHIFT_UP:
                  
                  // Record that a shift key has been unpressed
                  shiftPressed= 0;
                  break;
            /**********************************************************/
            
            /*  These conditions deal with the control and alt keys */
            case CTL:
                  
                  // Record that the Control key has been pressed
                  ctrlPressed= 1;
                  break;
                  
            case CTL_UP:
                  
                  // Record that the Control key has been un-pressed
                  ctrlPressed= 0;
                  break;
                  
            case ALT:
                  
                  // Record that the Alt key has been pressed
                  altPressed= 1;
                  break;
                  
            case ALT_UP:
                  
                  // Record that the Alt key has been un-pressed
                  altPressed= 0;
                  break;
            /**********************************************************/
            
            /*  These conditions deal with the caps num and scroll lock LEDs */
            case CAPLK:
                  
                  ledStatus= ledStatus ^ 0x04;                          // Toggle the Caps LED
                  lastCommand= 0xED;                                    // Sets the last command variable so the ACK handler knows what to do
                  sendKeyboardCommand(lastCommand);                     // Send the command to set the keyboard LEDs
                  break;                                                // Leave, the keyboard will interrupt again when its ready for the next command
                  
            case NUMLK:
                  
                  ledStatus= ledStatus ^ 0x02;                          // Toggle the Num LED
                  lastCommand= 0xED;                                    // Sets the last command variable so the ACK handler knows what to do
                  sendKeyboardCommand(lastCommand);                     // Send the command to set the keyboard LEDs
                  break;                                                // Leave, the keyboard will interrupt again when its ready for the next command
                  
            case SCRLK:
                  
                  ledStatus= ledStatus ^ 0x01;                          // Toggle the Scroll LED
                  lastCommand= 0xED;                                    // Sets the last command variable so the ACK handler knows what to do
                  sendKeyboardCommand(lastCommand);                     // Send the command to set the keyboard LEDs
                  break;                                                // Leave, the keyboard will interrupt again when its ready for the next command
            /**********************************************************/
            // This is the default condition when any standard letter is pressed
            default:
                  
                  // All the relevant characters are below 0x3a
                  if (scanCode > 0x3a) {
                        return;
                  }
                  
                  if (ctrlPressed == 1) {
                        
                        switch(lowerCaseLetterArray[scanCode]) {
                              
                              case 'c':
                                    
                                    clearScreen();
                                    break;
                                    
                              case 'r':
                                    
                                    reboot();
                                    break;
                                    
                              default:
                                    break;
                              
                        }
                        
                  } else if (altPressed == 1) {
                        
                        switch(lowerCaseLetterArray[scanCode]) {
                              
                              default:
                                    break;
                              
                        }
                        
                  } else {
                        
                        if ((ledStatus & 0x04) > 0 | shiftPressed == 1) {
                              printChar(upperCaseLetterArray[scanCode], 0x00);// If the CAPS Lock is on or shift is pressed, then print upper case
                        } else {
                              printChar(lowerCaseLetterArray[scanCode], 0x00);// otherwise, print lower case
                        }
                  }
                  break;
            
      }
      
      return;
}
/**********************************************************************/
void sendKeyboardCommand(int command) {
      
      // Loop until the keyboard is ready for a command
      while (byteREAD(ControllerStatusPort) & 0x02 != 0) {              // Bit 1 of the Controller Status Port signifies wheather the keyboard input buffer is full
            continue;
      }
      
      // Send the command to the keyboard
      byteWRITE(EncoderCommandPort, command);
      
      return;
}
/**********************************************************************/
void sendControllerCommand(int command) {
      
      // Loop until the keyboard is ready for a command
      while (byteREAD(ControllerStatusPort) & 0x02 != 0) {              // Bit 1 of the Controller Status Port signifies wheather the keyboard input buffer is full
            continue;
      }
      
      // Send the command to the keyboard controller
      byteWRITE(ControllerCommandPort, command);
      
      return;
}
/**********************************************************************/
