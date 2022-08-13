#include "AH.h"


/**********************************************************************/
int secondSinceBoot=0;                                                  // Counts the seconde since boot
int milliSecSinceBoot=0;                                                // Counts the milliseconds since boot
int milliSecSinceLastSec=0;                                             // Counts the milliseconds since the last second
/**********************************************************************/
void initPIT(int channel, int accessMode, int timerMode, int hertz) {
      
      // Perform Checking on hertz
      if (hertz < 19) {
            hertz= 19;                                                  // Minimum value
      }
      if (hertz > 1193182) {
            hertz= 1193182;                                             // Maximum Value
      }
      
      short reloadFrequency= 1193182/hertz;                             // The oscilator runs at 1,193,182 Htz, the chip divides that by reloadFrequency to get the output frequency
      char reloadFrequencyLOW= (reloadFrequency & 0x00FF);              // Low byte of the reload frequency
      char reloadFrequencyHIGH= (reloadFrequency >> 8);                 // High byte of the reload frequency
      
      // Command byte: {7,6 bits= channel; 5,4 bits= accessMode; 3,2,1 bits= timerMode; 0 bits= BCD/Binary}
      char commandByte= (channel << 6) + (accessMode << 4) + (timerMode << 1) + 0;
      
      byteWRITE(0x43, commandByte);
      // Uses the correct commands for the access mode set above
      if (accessMode== 3) {                                             // If the accessMode= 3: loByte, hiByte
            byteWRITE(0x40, reloadFrequencyLOW);
            byteWRITE(0x40, reloadFrequencyHIGH);
      } else if(accessMode== 2) {                                       // If the accessMode= 2: hiByte
            byteWRITE(0x40, reloadFrequencyHIGH);
      } else if(accessMode== 1) {                                       // If the accessMode= 1: loByte
            byteWRITE(0x40, reloadFrequencyLOW);
      }
      
      return;
}
/**********************************************************************/
void timerHandler(void) {
      
      milliSecSinceBoot++;                                              // Increment the milliseconds since boot
      milliSecSinceLastSec++;                                           // Increment the milliseconds since the last second
      
      int cursorOffset= getCursorOffset();                              // Store the cursor offset for later use
      
      // If a second has past
      if (milliSecSinceLastSec >= 1000) {
            
            milliSecSinceLastSec= 0;                                    // If a second has past then the milliseconds since the last sec must be zero
            secondSinceBoot++;                                          // Increment the number of seconds since boot
            
            setCursorOffset(0x02);
            printN(secondSinceBoot, 0x04);
      }
      
      setCursorOffset(cursorOffset);
      
      return;
}
/**********************************************************************/
void wait(int Msecs) {
      
      int startMsecs= milliSecSinceBoot;
      
      // Waits until the difference between 'milliSecSinceBoot' and 'startMsecs' is greater than the specified number of millisecs
      while (milliSecSinceBoot-startMsecs < Msecs) {
            continue;                                                   // This is a busy wait, it just loops until done
      }
      
      return;
}
/**********************************************************************/
