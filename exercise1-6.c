/* On and off the first led */

#include <reg51.h>
#define uint unsigned int

void delay(uint);

void main()
{
  while (1) {
    P1 = 0xfe;
    delay(1000);
    P1 = 0xff;
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