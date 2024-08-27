#ifndef __AVR__ // LINUX, WINDOWS, POSIX(?), OTHER(?)
#include <stdio.h>
#define gPrint(iTEXT) printf(iTEXT)
#define gLoop(iCOUNT, iRANGE, iDELAY) if (!((iCOUNT) % (iRANGE))) {break;}
#define gInit() 
#else // ARDUINO IDE, AVR-GCC
#include <avr/io.h>
#include <util/delay.h>
void gPrint(const unsigned char* iText) {unsigned char lChar; while ((lChar = *(iText)++)) {while (!(UCSR0A & 0x20)); UDR0 = lChar;}}
#define gLoop(iCOUNT, iRANGE, iDELAY) iCOUNT %= (iRANGE); _delay_ms(iDELAY)
#define gInit() UBRR0H = 0x0; UBRR0L = 0x0; UCSR0A = 0x0; UCSR0B = 0x8; UCSR0C = 0x6 // 1M baud, AVR is TX only
#endif

#define RANGE 255
#define DELAY 100

static const unsigned char* gConst[3] = {(const unsigned char*)"Fizzbuzz!\n", (const unsigned char*)"Fizz!\n", (const unsigned char*)"Buzz!\n"};

static unsigned char gBuffer[] = {
#if defined(__WIN32) || defined(_WIN32) || defined(WIN32) || defined(__WIN64) || defined(_WIN64) || defined(WIN64) // WINDOWS
	'\0', '\0', '\0', '\r', '\n', '\0'
#else // POSIX
	'\0', '\0', '\0', '\n', '\0'
#endif
};

int main(void) {
  gInit();
  unsigned char lCounter = 0, lState;
  while (0x1) {
    ++lCounter;
    if ((lState = (lCounter % 3 ? 0x2 : 0x0) | (lCounter % 5 ? 0x1 : 0x0)) != 0x3) {
      gPrint(gConst[lState]);
    } else {
      unsigned char lCache = lCounter, i = 3;
      do {gBuffer[--i] = 0x30 + (lCache % 10);} while (lCache /= 10);
      gPrint(&gBuffer[i]);
    }
    gLoop(lCounter, RANGE, DELAY);
  }
  return 0;
}
