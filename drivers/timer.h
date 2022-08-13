void initPIT(int channel, int accessMode, int timerMode, int hertz);    // Initialize timer
void timerHandler(void);                                                // Called everytime the timer fires an interrupt

// Functions so the kernel can communicate with the time system
void wait(int Msecs);                                                   // Waits the specified number of milliseconds

