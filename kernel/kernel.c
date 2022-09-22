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

// Driver Functions
#include "../drivers/interrupt.h"
#include "../drivers/keyboard.h"
#include "../drivers/timer.h"
#include "../drivers/cmosRTC.h"

#include "../drivers/numUtil.h"
#include "../drivers/screen.h"
#include "../drivers/system.h"

// PIT frequency must not be set higher than 1,193,182 or lower than 19
// RTC frequency must not be set higher than 8,192 or lower than 2

// Main (the arguments come from BIOS commands that we can't run in 32 bit mode)
void kernel(char daySavTime) {
      
      
      // OS Init
      clearScreen();
      initPIT(0,3,2,1000);
      initRTC(32, daySavTime);
      
      // Interrupt Init
      initIDT(32);
      clearMask(TimerIRQ);
      clearMask(KeyboardIRQ);
      clearMask(ClockIRQ);
      
      
      
      printI(-31415, DefaultColor);
      printS("\n", DefaultColor);
      printF(-31415.3456, DefaultColor);
      printS("\n", DefaultColor);
}

