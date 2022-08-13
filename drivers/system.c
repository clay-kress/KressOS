#include "AH.h"


/**********************************************************************/
void reboot(void) {
      
      // This makes the entire system reboot
      sendControllerCommand(0xFE);                                      // note: The sendControllerCommand is in the keyboard driver
                                                                        //          (because the hardware is actually layed out this way)
      
}
/**********************************************************************/
void memCopy(char* source, char* dest, int NumBytes) {
      
      for (int offset=0; offset<NumBytes; offset++) {                   // Loops through the selected bytes
            *(dest + offset)= *(source + offset);                       // Destination bytes = Source bytes
            *(source + offset)= 0;                                      // Overwrites the old bytes
      }
      
      return;
}
/**********************************************************************/
void memSet(char* low, char* high, char byteVal) {

      for (char* i= low; i< high; i++) {
            *i= byteVal;
      }
      
}
/**********************************************************************/

// IO read functions:
// 1: returns one byte from the IO-port in 'port'
// 2: returns two bytes (a word) from the IO-port in 'port'
/**********************************************************************/
unsigned char byteREAD(unsigned short port) /*8 bits*/ {
      
      unsigned char result;
      
      // GCC uses GAS assembly (instead of NASM assembly)
      // Syntax: __asm__("command" : outputs : inputs);
      __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
      // "port" is the IO-port that we want to read from
      // "result" is the value in IO-port dx
      
      return result;
}
/**********************************************************************/
unsigned short wordREAD(unsigned short port) /*16 bits*/ {
      
      unsigned short result;
      
      // GCC uses GAS assembly (instead of NASM assembly)
      // Syntax: __asm__("command" : outputs : inputs);
      __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
      // "port" is the IO-port that we want to read from
      // "result" is the value in IO-port dx
      
      return result;
}
/**********************************************************************/


// IO write functions:
// 1: writes one byte to the IO-port in 'port'
// 2: writes two bytes (a word) to the IO-port in 'port'
/**********************************************************************/
void byteWRITE(unsigned short port, unsigned char data) /*8 bits*/ {
      
      // GCC uses GAS assembly (instead of NASM assembly)
      // Syntax: __asm__("command" : outputs : inputs);
      __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
      // "port" is the IO-port that we want to move the data to
      // "data" is the data that we want to move into IO-port dx
      
}
/**********************************************************************/
void wordWRITE(unsigned short port, unsigned short data) /*16 bits*/ {
      
      // GCC uses GAS assembly (instead of NASM assembly)
      // Syntax: __asm__("command" : outputs : inputs);
      __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
      // "port" is the IO-port that we want to move the data to
      // "data" is the data that we want to move into IO-port dx
      
}
/**********************************************************************/
