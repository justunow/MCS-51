/* 8 leds show the accumulation process of 8bit binary numbers */

#include <reg51.h>
#define uint unsigned int
#define uchar unsigned char

void delay(uint);

void main()
{
  uchar num;
  while (1) {
    num = 0;
    while (num != 0xff) {
      num++;
      P1 = ~num;
      delay(100);
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