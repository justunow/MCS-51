/* Use 7-segment display shows number from
  000 to 999 with rate of 10ms set by timer,
  when tap down an individual key, the number
  stops, continues to run after letting go */

#include <reg51.h>
#define uint unsigned int
#define uchar unsigned char

sbit dula = P2 ^ 6;
sbit wela = P2 ^ 7;
sbit key1 = P3 ^ 4;

uchar code segmentNum[] = {
  0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
  0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71
};
uchar code segmentSelect[] = {
  0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf
};
uchar numDigit[] = {0, 0, 0};
uint num;

void initTimer0();
void display();
void keyScan();
void delay(uint);

void main()
{
  initTimer0();
  while (1) {
    display();
    keyScan();
  }
}

void initTimer0()
{
  TMOD = 0x01;
  // set 10ms to overflow
  TH0 = (65535 - 10000) / 256;
  TL0 = (65535 - 10000) % 256;
  EA = 1;
  ET0 = 1;
  TR0 = 1;
}

void display()
{
  uchar i;
  for (i = 0; i < 3; i++) {
    dula = 1;
    P0 = segmentNum[numDigit[i]];
    dula = 0;
    P0 = 0xff;
    wela = 1;
    P0 = segmentSelect[i];
    wela = 0;
    delay(1);
  }
}

void keyScan()
{
  while (!key1) {
    delay(5);
    while (!key1) {
      TR0 = 0;
      display();
    }
    delay(5);
    if (key1) {
      TR0  = 1;
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

void timer0() interrupt 1
{
  TH0 = (65535 - 10000) / 256;
  TL0 = (65535 - 10000) % 256;
  num++;
  numDigit[0] = num / 100;
  numDigit[1] = num / 10 % 10;
  numDigit[2] = num % 10;
  if (num == 999) {
    num = 0;
  }
}