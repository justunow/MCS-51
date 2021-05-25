/* Display stable 654321 on 7-segment display */

#include <reg51.h>

#define uchar unsigned char
#define uint unsigned int

sbit dula = P2 ^ 6;
sbit wela = P2 ^ 7;

uchar code segmentNum[] = {
  0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
  0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71
};
uchar code segmentSelect[] = {
  0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf
};

void display();
void delay(uint);

void main()
{
  display();
}

void display()
{
  uchar i;
  while (1) {
    for (i = 0; i < 6; i++) {
      dula = 1;
      P0 = segmentNum[6 - i];
      dula = 0;
      P0 = 0xff;
      wela = 1;
      P0 = segmentSelect[i];
      wela = 0;
      delay(1);
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