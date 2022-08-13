#include "AH.h"


/**********************************************************************/
void FloatToString(char* result, float value) {
      
      char* ptr1= result;                                               // 'ptr1' does most of the work, moving up the array writing letters
      char* ptr2= result;                                               // 'ptr2' is used in the end to invert the array
      char storedChar;                                                  // This variable stores characters while the array is being inverted
      int storedVal= value;                                             // This variable is used as a reference to the original value
      int base= 10;                                                     // This variable keeps track of our base
      
      int ipart= (int) value;                                           // Isolate the Integer part of the number
      float fpart= (float) value - (int) value;                         // Isolate the Float part of the number
      
      
      // Takes the float digits and puts them into an integer
      while ((float) fpart != (int) fpart) {
            fpart *= base;
      }
      
      
      // This is done backwards because we can not know the size of the array, it is inverted later
      // Writes all the characters right of the decimal to the array
      do {
            *ptr1= "9876543210123456789"[9+ (int) fpart%base];          // Picks the character from an array of characters, then puts it into the output array
                                                                        //   (This puts the digit of lowest significance into the first segment of the array)
                                                                        //     We need to mirror this array because we don't know the sign of the number
            ptr1++;                                                     // Points to the next segment of the array
            fpart= fpart/base;                                          // Divides the value by the base to shift the decimal to the left one place
      } while ((int) fpart != 0);                                       // Does this while the value is not equal to 0
      
      
      *ptr1= '.';
      ptr1++;
      
      
      // This is done backwards because we can not know the size of the array, it is inverted later
      // Writes all the characters left of the decimal to the array
      do {
            *ptr1= "9876543210123456789"[9+ ipart%base];                // Picks the character from an array of characters, then puts it into the output array
                                                                        //   (This puts the digit of lowest significance into the first segment of the array)
                                                                        //     We need to mirror this array because we don't know the sign of the number
            ptr1++;                                                     // Points to the next segment of the array
            ipart= ipart/base;                                          // Divides the value by the base to shift the decimal to the left one place
      } while (ipart != 0);                                             // Does this while the value is not equal to 0
      ipart= (int) value;
      
      
      // Add a negative sign if value is less than 0, otherwise, add a plus sign
      if (value < 0) {
            *ptr1= '-';                                                 // Adds the minus sign if negative
      } else {
            *ptr1= '+';                                                 // Adds the plus sign if positive
      }
      ptr1++;                                                           // Points to the next segment of the array
      
      
      // Add the termination byte to the end of the array
      *ptr1= 0x00;                                                      // This is still done last because its the one char we don't reverse
      ptr1--;                                                           // This is done so we don't end up reversing this char
      
      
      // Reverse the array to make it readable from left to right
      while(ptr1 > ptr2) {
            storedChar = *ptr1;                                         // Pointer one points to the high char of the array
            *ptr1= *ptr2;                                               // pointer two points to the low char of the array
            *ptr2= storedChar;                                          // This switches the chars from pointer1 to pointer2 and from pointer2 to pointer1
                                                                        //   essentially *ptr1= *ptr2;  and *ptr2= *ptr1;
            // Moves the high pointer and the low pointer closer together
            ptr1--;                                                     // Moves the high pointer down one
            ptr2++;                                                     // Moves the low pointer up one
      }
      
      return;
}
/**********************************************************************/
void NumToString(char* result, int value, int base) {
      
      char* ptr1= result;                                               // 'ptr1' does most of the work, moving up the array writing letters
      char* ptr2= result;                                               // 'ptr2' is used in the end to invert the array
      char storedChar;                                                  // This variable stores characters while the array is being inverted
      int storedVal= value;                                             // This variable is used as a reference to the original value
      
      // Make sure base is within our constraints
      if (base < 2 || base > 16) {
            *result= '\0';
            return;
      }
      
      
      // This is done backwards because we can not know the size of the array, it is inverted later
      // Writes all the characters to the array
      do {
            *ptr1= "FEDCBA9876543210123456789ABCDEF"[15+ value%base];   // Picks the character from an array of characters, then puts it into the output array
                                                                        //   (This puts the digit of lowest significance into the first segment of the array)
                                                                        //     We need to mirror this array because we don't know the sign of the number
            ptr1++;                                                     // Points to the next segment of the array
            value= value/base;                                          // Divides the value by the base to shift the decimal to the left one place
      } while (value != 0);                                             // Does this while the value is not equal to 0
      value= storedVal;
      
      
      if (base == 16) {
            // Add an 'x0' to the end of the array after the numbers (imagine the array being constructed backwards and than being inverted)
            *ptr1= 'x';                                                 // Adds 'x' to the string (array)
            ptr1++;                                                     // Points to the next segment of the array
            *ptr1 = '0';                                                // Adds '0' to the string (array)
            ptr1++;                                                     // Points to the next segment of the array
      }
      
      
      // Add a negative sign if value is less than 0, otherwise, add a plus sign
      if (value < 0) {
            *ptr1= '-';                                                 // Adds the minus sign if negative
            ptr1++;                                                     // Points to the next segment of the array
      } else {
            ;                                                           // We only want to add a sign if its negative. This is essentially an empty else condition
      }
      
      
      // Add the termination byte to the end of the array
      *ptr1= 0x00;                                                      // This is still done last because its the one char we don't reverse
      ptr1--;                                                           // This is done so we don't end up reversing this char
      
      
      // Reverse the array to make it readable from left to right
      while(ptr1 > ptr2) {
            storedChar = *ptr1;                                         // Pointer one points to the high char of the array
            *ptr1= *ptr2;                                               // pointer two points to the low char of the array
            *ptr2= storedChar;                                          // This switches the chars from pointer1 to pointer2 and from pointer2 to pointer1
                                                                        //   essentially *ptr1= *ptr2;  and *ptr2= *ptr1;
            // Moves the high pointer and the low pointer closer together
            ptr1--;                                                     // Moves the high pointer down one
            ptr2++;                                                     // Moves the low pointer up one
      }
      
      return;
}
/**********************************************************************/
void printF(float number, char color) {
      
      char* message;                                                    // Creates a pointer to an array that we can put the message into
      FloatToString(message, number);                                   // Converts number into a string and then outputs it into message
      
      printS(message, color);                                           // Prints the message
      return;
}
/**********************************************************************/
void printN(int number, char color) {
      
      char* message;                                                    // Creates a pointer to an array that we can put the message into
      NumToString(message, number, 16);                                 // Converts number into a string and then outputs it into message
      
      printS(message, color);                                           // Prints the message
      return;
}
/**********************************************************************/
void printI(int number, char color) {
      
      char* message;                                                    // Creates a pointer to an array that we can put the message into
      NumToString(message, number, 10);                                 // Converts number into a string and then outputs it into message
      
      printS(message, color);                                           // Prints the message
      return;
}
/**********************************************************************/
void printS(char* message, char color) {
      
      // Loops through message until message[i] = 0x00
      int i=0;
      while (message[i] != 0x00) {                                      // 0x00 signifies a termination byte, meant to tell the function that the string is over
            printChar(message[i], color);                               // Prints the next char in message
            i++;                                                        // Sets i to the next char in message
      }
      
      return;
}
/**********************************************************************/
void printChar(char character, char color) {
      
      char* MemPos= (char*) VideoMemory;
      short offset;
      
      // Sets offset to the current cursor offset
      offset= getCursorOffset();
      
      if (color == 0x00) {
            color= DefaultColor;
      }
      
      // This includes different speciel characters that the compiler may want to use (you can add more)
      switch(character) {
            
            case '\n':
                  
                  // This makes a new line
                  carridgeReturn(1);
                  break;
            
            case '\t':
                  
                  // This makes a 4 space tab
                  setCursorOffset(getCursorOffset()+8);
                  break;
            
            default:
                  
                  MemPos[offset]= character;                            // Sets the first byte of the letter segment to the character
                  offset++;                                             // Makes offset point to the color byte of the letter segment
                  MemPos[offset]= color;                                // Sets the color byte to the defaut screen color
                  
                  offset += 2;                                          // Sets the offset to point to the next letter segment
                  setCursorOffset(offset);                              // Sets the cursor to the next letter segment
                  break;
            
      }
      
      // Possible scrolling
      if (getCursorOffset() > getCoordsOffset(MaxCols,MaxRows)) {
            scroll();                                                   // Only scrolls if the cursor is past the bottom of the screen
      }
      
      return;
}
/**********************************************************************/





/**********************************************************************/
/**********************************************************************/
//                These below functions are for utility purposes
//                For managing cursor position, clearing screen, etc.
/**********************************************************************/
/**********************************************************************/





/**********************************************************************/
void clearScreen(void) {
      
      // MemPos know points to the start of memory
      char* MemPos= VideoMemory;
      
      // This function doesn't clear the top of the screen because that is reserved for interrupts and timer
      // Outline the top two lines of the screen for information
      for (short offset= 160; offset<240; offset++) {
            setCursorOffset(offset);                                    // Sets the cursor offset to each character
            MemPos[offset]= 0xcd;                                       // Set each char to '='
            offset++;                                                   // Now MemPos[offset] points to the color byte instead of the char byte
            MemPos[offset]= 0x01;                                       // Set the color to white
      }
      
      // Sets every segment of the screen to black
      for (short offset=240; offset<2000; offset++) {
            MemPos[offset]= 0x0000;                                     // Clears that character
      }
      
      setCursorOffset(getCoordsOffset(1,4));                            // Set the cursor back to the beginning of the user accesible screen
      
      return;
}
/**********************************************************************/
void clearTop(void) {
      
      char* MemPos= (char*) VideoMemory;
      
      // Clears the interrupt line, not the timer line though (this clears the second line)
      for (int offset= 80; offset<160; offset++) {
            MemPos[offset]= 0x0000;
      }
      
      return;
}
/**********************************************************************/
void carridgeReturn(int times) {
      
      int offset;
      
      // Loop as many times as we want to return
      for (int i=0; i<times; i++) {
            offset= getCursorOffset();                                  // Get the current cursor so we can edit it
            offset= offset-(offset%80);                                 // sets offset back to column 0
            offset= offset+80;                                          // Adds one row to offset
            setCursorOffset(offset);                                    // Set cursor one row down
            
            // Possible scrolling
            if (getCursorOffset() > getCoordsOffset(MaxCols,MaxRows)) {
                  scroll();                                             // Only scrolls if the cursor is past the bottom of the screen
            }
      }
      
      return;
}
/**********************************************************************/
void scroll(void) {
      
      // Copies all lines to the next line up (skips the first three because they are reserved for the system)
      memCopy((char*) 0xb8140, (char*) 0xb80F0, 1680);                  // Copies 1680 letters from b8140 to b80F0
      setCursorOffset(getCoordsOffset(1,25));                           // Sets cursor to 1,25...
      
      return;
}
/**********************************************************************/
int getCoordsOffset(int x, int y) {
      
      x -=1;                                                            // Makes x=1 the first X position
      y -=1;                                                            // Makes y=1 the first Y position
      
      int offset;
      offset= 2*(x + y*40);                                             // There are 40 cols and each space takes two bytes
      
      return offset;
}
/**********************************************************************/
void setCursorOffset(int offset) {
      
      int Hbyte,Lbyte;                                                  // These must be 'int' because 'char << 8' truncates
      
      // Accounts for the fact that a single cursor space is represented by two bytes in RAM
      offset /= 2;                                                      // Divides by two to get the acctual number of spaces
      
      // We split offset into its high byte and its low byte
      Lbyte= (offset & 0xff);                                           // Masks off the lower byte of offset by ANDing with 0x00FF
      Hbyte= (offset >> 8);                                             // Finds the high byte of offset by shifting right 8 bits
      
      // Put 14 in the CTRL register to acces the high byte of the DATA register
      byteWRITE(RegisterCTRL, 14);                                      // Writes 14 to the CTRL register
      byteWRITE(RegisterDATA, Hbyte);                                   // Writes the High byte of offset to the DATA register
      
      // Put 15 in the CTRL register to acces the low byte of the DATA register
      byteWRITE(RegisterCTRL, 15);                                      // Writes 15 to the CTRL register
      byteWRITE(RegisterDATA, Lbyte);                                   // Writes the Low byte of offset to the DATA register
      
      return;
}
/**********************************************************************/
int getCursorOffset(void) {
      
      int Hbyte,Lbyte;                                                  // These must be 'int' because 'char << 8' truncates
      int offset;
      
      // Write 14 to the CTRL register in order to read from the high byte
      byteWRITE(RegisterCTRL, 14);                                      // Writes 14 to the CTRL register
      Hbyte= byteREAD(RegisterDATA);                                    // Reads a byte from DATA register to Hbyte
      
      // Write 15 to the CTRL register in order to read from the low byte
      byteWRITE(RegisterCTRL, 15);                                      // Writes 15 to the CTRL register
      Lbyte= byteREAD(RegisterDATA);                                    // Reads a byte from DATA register to Lbyte
      
      // Combine the Hbyte and the Lbyte to make the offset variable to return
      offset= (Hbyte << 8);                                             // Shift Hbyte over to its original position in offset
      offset= (offset + Lbyte);                                         // Simply add the low byte to offset
      
      // Accounts for the fact that a single cursor space is represented by two bytes in RAM
      offset *= 2;                                                      // Multiply by two to get the actual position in RAM
      
      return offset;
}
/**********************************************************************/
