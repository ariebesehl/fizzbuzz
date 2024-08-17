#include <util/delay.h>
#define EINE_ZAHL 255
static const unsigned char* gConst[3] = {(const unsigned char*)"Fizzbuzz!\n", (const unsigned char*)"Fizz!\n", (const unsigned char*)"Buzz!\n"};
void gSerialInit(void) {UBRR0H = 0x0; UBRR0L = 0x0; UCSR0A = 0x0; UCSR0B = 0x8; UCSR0C = 0x6;} // 1M baud-rate, TX only 
void gSerialPrint(const unsigned char* iText) {unsigned char lChar; while ((lChar = *(iText)++)) {while (!(UCSR0A & 0x20)); UDR0 = lChar;}}
int main(void) {
  gSerialInit();
  unsigned char lBuffer[5] = {'\0', '\0', '\0', '\n', '\0'}, lCounter = 0, lState;
  while (0x1) {
    ++lCounter;
    if ((lState = (lCounter % 3 ? 0x2 : 0x0) | (lCounter % 5 ? 0x1 : 0x0)) != 0x3) {
      gSerialPrint(gConst[lState]);
    } else {
      unsigned char i = 3;
      unsigned char lCache = lCounter;
      do {lBuffer[--i] = 0x30 + (lCache % 10); lCache /= 10;} while (i);
      gSerialPrint(lBuffer);
    }
    if (!(lCounter % EINE_ZAHL)) {lCounter = 0;};
    _delay_ms(100);
  }
  return 0;
}
