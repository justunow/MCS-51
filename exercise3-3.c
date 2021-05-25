/* Use two timers to control the buzzer,
  timer 0 control the frequency, timer 1
  sets 300ms for every time period of
  different frequencies, outputs 1, 10, 50,
  100, 200, 400, 800, 1kHz square waves by
  sequence */

#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int

uchar fmState;
uint num, count0, count1, fsw;
uint frequencies[] = {1, 10, 50, 100, 200, 400, 800, 1000};
sbit fm = P2 ^ 3;

void initTimers();

void main()
{
  fsw = frequencies[0];
  initTimers();
  while (1);
}

void initTimers()
{
  TMOD = 0x11;
  // set 1ms to overflow
  TH0 = (65535 - 1000) / 256;
  TL0 = (65535 - 1000) % 256;
  // set 60ms to overflow
  TH1 = (65535 - 60000) / 256;
  TL1 = (65535 - 60000) % 256;
  EA = 1;
  ET0 = 1;
  ET1 = 1;
  TR0 = 1;
  TR1 = 1;
}

void timer0() interrupt 1
{
  TH0 = (65535 - 500) / 256;
  TL0 = (65535 - 500) % 256;
  count0++;
  if (count0 == 1000 / fsw /*1/fsw*1/2*2000*/ ) {
    count0 = 0;
    fmState = ~fmState;
    fm = fmState;
  }
}

void timer1() interrupt 3
{
  TH1 = (65535 - 60000) / 256;
  TL1 = (65535 - 60000) % 256;
  count1++;
  if (count1 == 5) {
    count1 = 0;
    fsw = frequencies[num];
    num++;
    if (num == 8) {
      num = 0;
    }
  }
}