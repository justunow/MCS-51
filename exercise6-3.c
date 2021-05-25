/* Send a number between 0 ~ 65536 to MCU, after MCU
  receives this number, displays it on the 7-segment
  display */

#include <reg51.h>
#define uint unsigned int
#define uchar unsigned char

sbit dula = P2 ^ 6;
sbit wela = P2 ^ 7;

uchar code segmentNum[] = {
  0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
  0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71
};
uchar code segmentSelect[] = {
  0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf
};
uchar numDigit[] = {0, 0, 0, 0, 0};
uchar count, flag;
uint num;

void initSerial();
void display();
void delay(uint);

void main()
{
  initSerial();
  while (1) {
    if (flag) {
      flag = 0;
      display();
    }
  }
}

void initSerial()
{
  TMOD = 0x20;
  // set baud rate to 9600
  TH1 = 0xfd;
  TL1 = 0xfd;
  TR1 = 1;
  SM0 = 0;
  SM1 = 1;
  REN = 1;
  EA = 1;
  ES = 1;
}

void display()
{
  uchar i;
  for (i = 0; i < 5; i++) {
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

void delay(uint x)
{
  uint i, j;
  for (i = x; i > 0; i--) {
    for (j = 110; j > 0; j--);
  }
}

void serial() interrupt 4
{
  RI = 0;
  count++;
  if (count == 1) {
    num = SBUF;
    num = num << 8;
  }
  if (count == 2) {
    num += SBUF;
    numDigit[0] = num / 10000;
    numDigit[1] = num / 1000 % 10;
    numDigit[2] = num / 100 % 10;
    numDigit[3] = num / 10 % 10;
    numDigit[4] = num % 10;
    count = 0;
    flag = 1;
  }
}