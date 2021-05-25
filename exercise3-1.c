/* Using timer 0 to output a square wave
  from P1 ^ 0 with period of 1s, the
  crystal oscillator frequency is 12MHz */
/* In 8051,
  1 instruction cycle = 1, 2 or 4 machine cycle
  1 machine cycle = 12 clock cycle
  e.g. fosc = 12MHz, "INC A" takes 1 instruction
  cycle, so fina = fmc = 1Hz, tina = 1us */

#include <reg51.h>
#define uchar unsigned char

sbit led = P1 ^ 0;
uchar count;

void initTimer0();

void main()
{
  initTimer0();
  while (1);
}

void initTimer0()
{
  /* timer/counter 0 and 1 modes, non-bit addressable */
  TMOD = 0x01;
  /* timer 0 high byte and low byte registers */
  // set 50ms to overflow
  TH0 = (65535 - 50000) / 256;
  TL0 = (65535 - 50000) % 256;
  /* IE.7
    EA = 0, disables all interrupts,
    no interrupt will be acknowledged.
    EA = 1, each interrupt source is individually enabled
    or disabled by setting or cleaning its enable bit */
  EA = 1;
  /* IE.1, timer 0 overflow interrupt enable bit */
  ET0 = 1;
  /* TCON.4
    clear to turn off timer/ counter 0,
    set to turn on timer/ counter 0 */
  TR0 = 1;
}

/* interrupt priority level,
  1 - IE0, 2 - TF0, 3 - IE1, 4 - TF1, 5 - RI + TI,
  6 - TF2 + EXF2 */
/* IP.1, timer 0 interrupt priority bit */
void timer0() interrupt 1
{
  TH0 = (65535 - 50000) / 256;
  TL0 = (65535 - 50000) % 256;
  count++;
  if (count == 10) {
    count = 0;
    led = ~led;
  }
}