/* On and off the first led with the off period of 200ms */

#include <reg51.h>
#define uint unsigned int

sbit led = P1 ^ 0;

void delay(uint);

void main()
{
  while (1) {
    led = ~led;
    delay(200);
  }
}

void delay(uint x)
{
  uint i, j;
  for (i = x; i > 0; i--) {
    for (j = 110; j > 0; j--);
  }
}