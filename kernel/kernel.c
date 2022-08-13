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

