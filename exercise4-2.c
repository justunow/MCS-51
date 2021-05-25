/* Use timer 1 to set the time period
  to 10ms, 7-segment display shows the
  current time */

#include <reg51.h>

#define uint unsigned int
#define uchar unsigned char

sbit dula = P2 ^ 6;
sbit wela = P2 ^ 7;

uchar code segmentNum[] = {
  0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
  0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x80 /* dp */
};
uchar code segmentSelect[] = {
  0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf
};
uint timeNum[] = {0, 0, 0, 0, 0, 0};
uint currentTime;

void display();
void delay(uint);
void initTimer1();

void main()
{
  initTimer1();
  display();
}

void display()
{
  uchar i;
  while (1) {
    for (i = 0; i < 6; i++) {
      dula = 1;
      P0 = segmentNum[timeNum[i]];
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

void initTimer1()
{
  TMOD = 0x10;
  // set 10ms to overflow
  TH1 = (65535 - 10000) / 256;
  TL1 = (65535 - 10000) % 256;
  EA = 1;
  ET1 = 1;
  TR1 = 1;
}

void timer1() interrupt 3
{
  TH1 = (65535 - 10000) / 256;
  TL1 = (65535 - 10000) % 256;
  currentTime++;
  timeNum[0] = currentTime / 10000;
  timeNum[1] = currentTime / 1000 % 10;
  timeNum[2] = currentTime / 100 % 10;
  timeNum[3] = 16;
  timeNum[4] = currentTime / 10 % 10;
  timeNum[5] = currentTime % 10;
  if (currentTime == 65535) {
    currentTime = 0;
  }
}