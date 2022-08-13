void reboot(void);

// ex: memCopy(0x7c00, 0x7e00, 50);
// This moves 50 bytes from 7c00 to 7e00 (overwriting nessesary bytes in the process)
void memCopy(char* source, char* dest, int NumBytes);
void memSet(char* low, char* high, char byteVal);

unsigned char byteREAD(unsigned short port);
unsigned short wordREAD(unsigned short port);

void byteWRITE(unsigned short port, unsigned char data);
void wordWRITE(unsigned short port, unsigned short data);

