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


char binary= 0;
char twentyFourHour= 0;
char dayLtSav= 0;
/**********************************************************************/
void initRTC(int frequency, int dayLtSavInput) {
      
      char CMOSDataMask;
      
      // Allows the user choose the interrupt frequency
      char rate= log2((float) 32768/ (float) frequency) + 1;            // Finds the rate to send to the clock (derived from the equation: frequency= 32768 >> (rate-1) )
      
      
      // If the NMI is left enabed while programming the RTC it could interrupt the CPU, leaving the RTC in an undefined state,
      // This is a problem because CMOS (and the RTC) runs on a battery and will maintain that undefined state even after the computer has shutdown
      byteWRITE(CmosControlPort, 0x8A);                                 // Select CMOS register A, and disable NMI (Non-Maskable-Interrupt) with bit 7
      CMOSDataMask= byteREAD(CmosDataPort);                             // Read the current value of register A
      
      byteWRITE(CmosControlPort, 0x8A);                                 // Set the control register again (reading data will reset the control register)
      byteWRITE(CmosDataPort, (CMOSDataMask & 0xF0) | (rate & 0x0F));   // Clears the low 4 bits of 'dataStored' and the high 4 bits of 'rate', then combines them and sends them to 0x71
      // Note that the rate is only the lower 4 bits
      
      
      // Determines the settings of the RTC
      byteWRITE(CmosControlPort, 0x8A);                                 // Select CMOS register A, and disable NMI
      CMOSDataMask= byteREAD(CmosDataPort);                             // Read the current value of register A
      
      if ((CMOSDataMask & 0x02) > 0x00) {                               // The 0x02 byte tells us if the RTC is in 24 hr mode
            twentyFourHour= 1;                                          //  If the bit is set, set the 24 hr mode variable to true (1)
      }
      if ((CMOSDataMask & 0x04) > 0x00) {                               // The 0x04 byte tells us if the RTC is in binary mode as opposed to BCD mode
            binary= 0;                                                  //  If the bit is set, set the binary mode variable to true (1)
      }
      
      dayLtSav= dayLtSavInput;
      
      
      // Enable interrupts from the RTC chip
      byteWRITE(CmosControlPort, 0x8B);                                 // Select CMOS register B, and disable NMI
      CMOSDataMask= byteREAD(CmosDataPort);                             // Read the current value of register B
      
      byteWRITE(CmosControlPort, 0x8B);                                 // Set the control register again (reading data will reset the control register)
      byteWRITE(CmosDataPort, CMOSDataMask | 0x40);                     // This turns on bit 6 of register B
      
      
      // Read register C so that IRQ 8 can happen again
      // If this is not done, IRQ 8 will never happen again
      byteWRITE(CmosControlPort, 0x0C);                                 // select register C (and enable the NMI)
      int trash= byteREAD(CmosDataPort);                                // just throw away contents
      
      byteWRITE(CmosControlPort, byteREAD(CmosControlPort) & 0x7F);     // Re-enable NMI
      return;
}
/**********************************************************************/
void rtcHandler(void) {
      
      int cursorOffset= getCursorOffset();
      
      
udip:
      // Wait until update flag is clear
      while (updateInProgress() > 0x00) {
            continue;
      }
      
      // Read Seconds
      byteWRITE(CmosControlPort, 0x00);                                 // Set port 0x71 to the seconds port
      char seconds= byteREAD(CmosDataPort);
      
      // Read Minutes
      byteWRITE(CmosControlPort, 0x02);                                 // Set port 0x71 to the minutes port
      char minutes= byteREAD(CmosDataPort);
      
      // Read hours
      byteWRITE(CmosControlPort, 0x04);                                 // Set port 0x71 to the hours port
      char hours= byteREAD(CmosDataPort);
      
      // Makes sure an update did not occur when reading the time
      if (updateInProgress() > 0x00) {
            goto udip;                                                  // If update is in progress, goto the udip label
      }
      
      
      // If the RTC uses BCD, then convert it to binary
      if (binary == 0) {
            // Convert from BCD to binary
            hours= ((hours/16) * 10) + (hours & 0x0F);                  // Converts BCD format to Binary
            minutes= ((minutes/16) * 10) + (minutes & 0x0F);            // Converts BCD format to Binary
            seconds= ((seconds/16) * 10) + (seconds & 0x0F);            // Converts BCD format to Binary
      }
      hours= (hours+17)%24;                                             // Must do this, I think to align hours with our time zone (MST)
      if (dayLtSav == 0) {
            hours= (hours+1)%24;                                        // Does this during daylight savings
      }
      
      
      setCursorOffset(0x30);
      
      printS("Time: ", 0x05);
      printI(hours, 0x04);
      printS(":", 0x04);
      printI(minutes, 0x04);
      printS(":", 0x04);
      printI(seconds, 0x04);
      printS("  ", 0x04);
      
      setCursorOffset(cursorOffset);
      
      // Register C needs to be read or the interrupt will not happen again
      byteWRITE(CmosControlPort, 0x0C);                                 // select register C
      int trash= byteREAD(CmosDataPort);                                // just throw away contents
      
      return;
}
/**********************************************************************/
char updateInProgress(void) {
      
      byteWRITE(CmosControlPort, 0x0A);                                 // Selects register A
      char inProgress= byteREAD(CmosDataPort) & 0x80;                   // Masks the 'update in progress' bit of register A
      
      return inProgress;
}
/**********************************************************************/
