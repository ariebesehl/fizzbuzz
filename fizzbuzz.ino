#include <util/delay.h>
#define EINE_ZAHL 255
static const unsigned char* gConst[3] = {(const unsigned char*)"Fizzbuzz!\n", (const unsigned char*)"Fizz!\n", (const unsigned char*)"Buzz!\n"};
static unsigned char gBuffer[5] = {'\0', '\0', '\0', '\n', '\0'};
void gSerialInit(void) {UBRR0H = 0x0; UBRR0L = 0x0; UCSR0A = 0x0; UCSR0B = 0x8; UCSR0C = 0x6;} // 1M baud-rate, RX only 
void gSerialPrint(const unsigned char* iText) {unsigned char lChar; while ((lChar = *(iText)++)) {while (!(UCSR0A & 0x20)); UDR0 = lChar;}}
int main(void) {
  gSerialInit();
  unsigned char lCounter = 0, lState;
  while (0x1) {
    ++lCounter;
    if ((lState = (lCounter % 3 ? 0x2 : 0x0) | (lCounter % 5 ? 0x1 : 0x0)) != 0x3) {
      gSerialPrint(gConst[lState]);
    } else {
      unsigned char lCache = lCounter, i = 3;
      do {gBuffer[--i] = 0x30 + (lCache % 10);} while (lCache /= 10);
      gSerialPrint(&gBuffer[i]);
    }
    lCounter %= EINE_ZAHL;
    _delay_ms(100);
  }
  return 0;
}
