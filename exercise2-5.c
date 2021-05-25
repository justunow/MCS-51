/* 8 leds light up back and forth
  for twice with period of 200ms,
  then turn off, and then light up
  all the leds with period of 300ms */

#include <reg51.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char

void delay(uint);

void main()
{
  uchar count;
  while (1) {
    P1 = 0xfe;
    for (count = 2; count > 0; count--) {
      while (P1 != 0x7f) {
        delay(200);
        P1 = _crol_(P1, 1);
      }
      delay(200);
      P1 = _cror_(P1, 1);
      while (P1 != 0xfe) {
        P1 = P1;
        delay(200);
        P1 = _cror_(P1, 1);
      }
      delay(200);
      P1 = _crol_(P1, 1);
    }
    P1 = 0xff;
    for (count = 10; count > 0; count--) {
      P1 = ~P1;
      delay(300);
    }
  }
}

void delay(uint x)
{
  uint i, j;
  for (i = x; i > 0; i--) {
    for (j = 110; j > 0; j--);
  }
}