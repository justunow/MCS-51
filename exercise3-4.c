/* Display hexadecimal numbers on 7-segment
  display by sequence with period of 500ms
  set by timer */

#include <reg51.h>
#define uchar unsigned char

sbit dula = P2 ^ 6;
sbit wela = P2 ^ 7;

uchar num, count;
uchar code segmentNum[] = {
  0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
  0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71
};

void initTimer0();
void display();

void main()
{
  initTimer0();
  while (1) {
    display();
  }
}

void initTimer0()
{
  TMOD = 0x01;
  // set 50ms to overflow
  TH0 = (65535 - 50000) / 256;
  TL0 = (65535 - 50000) % 256;
  EA = 1;
  ET0 = 1;
  TR0 = 1;
}

void display()
{
  dula = 1;
  P0 = segmentNum[num];
  dula = 0;
  P0 = 0xff;
  wela = 1;
  P0 = 0xc0;
  wela = 0;
}

void timer0() interrupt 1
{
  TH0 = (65535 - 50000) / 256;
  TL0 = (65535 - 50000) % 256;
  count++;
  if (count == 10) {
    count = 0;
    num++;
    if (num == 16) {
      num = 0;
    }
  }
}