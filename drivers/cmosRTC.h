#define CmosControlPort 0x70
#define CmosDataPort 0x71

void initRTC(int frequency, int dayLtSavInput);
void rtcHandler(void);

// Utillity Functions
char updateInProgress(void);                                            // If theres an update in progress, it returns a value >0, else return 0

