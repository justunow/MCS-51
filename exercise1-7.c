/* On and off all the leds by sequence */

#include <reg51.h>
#include <intrins.h>
#define uint unsigned int

void delay(uint);

void main()
{
  P1 = 0xfe;
  delay(1000);
  while (1) {
    P1 = _crol_(P1, 1);
    delay(1000);
  }
}

void delay(uint x)
{
  uint i, j;
  for (i = x; i > 0; i--) {
    for (j = 110; j > 0; j--);
  }
}