/* Use 7-segment display shows from 765432
  to 765398 with rate of 100ms set by timer 1,
  at the same time, leds light up by sequence
  with period of 500ms, when the number 765398
  is reached, all the leds starts blinking and
  turning off after 3 seconds set by timer 0,
  displays "Hello" on 7-segment display */

#include <reg51.h>
#include <intrins.h>

#define uint unsigned int
#define uchar unsigned char

sbit dula = P2 ^ 6;
sbit wela = P2 ^ 7;

uchar flag0, flag1;
uchar code segmentNum[] = {
  0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
  0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x80 /*dp*/
};
uchar code segmentSelect[] = {
  0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf
};
uchar code letterHello[] = {
  0x76, 0x79, 0x38, 0x38, 0x3f
};
uint initNum, endNum, count0, count1;
uint countNum[] = {0, 0, 0};

void display();
void delay(uint);
void initTimers();

void main()
{
  flag0 = 1;
  flag1 = 1;
  initNum = 432;
  endNum = 398;
  P1 = 0xfe;
  initTimers();
  display();
}

void display()
{
  uchar i;
  while (flag0) {
    for (i = 0; i < 3; i++) {
      dula = 1;
      P0 = segmentNum[7 - i];
      dula = 0;
      P0 = 0xff;
      wela = 1;
      P0 = segmentSelect[i];
      wela = 0;
      delay(1);
    }
    for (i = 0; i < 3; i++) {
      dula = 1;
      P0 = segmentNum[countNum[i]];
      dula = 0;
      P0 = 0xff;
      wela = 1;
      P0 = segmentSelect[i + 3];
      wela = 0;
      delay(1);
    }
  }
  while (1) {
    for (i = 0; i < 5; i++) {
      dula = 1;
      P0 = letterHello[i];
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

void initTimers()
{
  TMOD = 0x11;
  // set 50ms to overflow
  TH0 = (65535 - 50000) / 256;
  TL0 = (65535 - 50000) % 256;
  TH1 = (65535 - 50000) / 256;
  TL1 = (65535 - 50000) % 256;
  EA = 1;
  ET0 = 1;
  ET1 = 1;
  TR0 = 1;
  TR1 = 1;
}

void timer0() interrupt 1
{
  TH0 = (65535 - 50000) / 256;
  TL0 = (65535 - 50000) % 256;
  count0++;
  if (flag1) {
    if (count0 == 10) {
      count0 = 0;
      P1 = _crol_(P1, 1);
    }
  }
  else {
    P1 = 0xff;
    delay(1);
    P1 = 0;
    if (count0 == 60) {
      P1 = 0xff;
      flag0 = 0;
      TR0 = 0;
    }
  }
}

void timer1() interrupt 3
{
  TH1 = (65535 - 50000) / 256;
  TL1 = (65535 - 50000) % 256;
  count1++;
  if (count1 == 2) {
    count1 = 0;
    initNum--;
    countNum[0] = initNum / 100;
    countNum[1] = initNum / 10 % 10;
    countNum[2] = initNum % 10;
    if (initNum == endNum) {
      flag1 = 0;
      TR1 = 0;
    }
  }
}