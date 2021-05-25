/* Light up leds by sequence, every led
  has the frequency of 10Hz, use timer 1
  to set the time period */

#include <reg51.h>
#include <intrins.h>
#define uchar unsigned char

uchar count;

void initTimer1();

void main()
{
  P1 = 0xfe;
  initTimer1();
  while (1);
}

void initTimer1()
{
  /* timer/counter 0 and 1 modes, non-bit addressable */
  TMOD = 0x10;
  /* timer 1 high byte and low byte registers */
  // set 50ms to overflow
  TH1 = (65535 - 50000) / 256;
  TL1 = (65535 - 50000) % 256;
  /* IE.7
    EA = 0, disables all interrupts,
    no interrupt will be acknowledged.
    EA = 1, each interrupt source is individually enabled
    or disabled by setting or cleaning its enable bit */
  EA = 1;
  /* IE.3, timer 1 overflow interrupt enable bit */
  ET1 = 1;
  /* TCON.6
    clear to turn off timer/ counter 1,
    set to turn on timer/ counter 1 */
  TR1 = 1;
}

/* interrupt priority level,
  1 - IE0, 2 - TF0, 3 - IE1, 4 - TF1, 5 - RI + TI,
  6 - TF2 + EXF2 */
/* IP.3, timer 1 interrupt priority bit */
void timer1() interrupt 3
{
  TH1 = (65535 - 50000) / 256;
  TL1 = (65535 - 50000) % 256;
  count++;
  if (count == 2) {
    count = 0;
    P1 = _crol_(P1, 1);
  }
}