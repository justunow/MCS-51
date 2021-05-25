/* The first led lights up back and forth
  with period of 300ms, then the first two,
  then the first three and so on until all the
  leds light up */

#include <reg51.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char

void delay(uint);

void main()
{
  uchar ledState;
  while (1) {
    ledState = 1;
    while (ledState != 0xff) {
      while ((ledState & 0x80) != 0x80) {
        P1 = ~ledState;
        delay(300);
        ledState = _crol_(ledState, 1);
      }
      P1 = ~ledState;
      delay(300);
      ledState = _cror_(ledState, 1);
      while ((ledState & 0x01) != 0x01) {
        P1 = ~ledState;
        delay(300);
        ledState = _cror_(ledState, 1);
      }
      P1 = ~ledState;
      delay(300);
      ledState = (ledState << 1) + 1;
    }
    P1 = 0;
  }
}

void delay(uint x)
{
  uint i, j;
  for (i = x; i > 0; i--) {
    for (j = 110; j > 0; j--);
  }
}