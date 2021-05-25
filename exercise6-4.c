/* Use ADC to sample the analog signals with frequency
  of 1Hz, then send the digital signals to the computer
  at 1200bps */

#include <reg51.h>
#include <intrins.h>
#define uint unsigned int

sbit wr = P3 ^ 6;
sbit rd = P2 ^ 7;

void initSerial();
void adcStart();
void adcRead();
void delay(uint);

void main()
{
  // set CSAD pin of ADC0804 to 0;
  P0 = 0x7f;
  initSerial();
  while (1) {
    adcStart();
    adcRead();
    SBUF = P1;
    while (!TI);
    TI = 0;
  }
}

void initSerial()
{
  TMOD = 0x20;
  // set baud rate to 1200
  TH1 = 0xe8;
  TL1 = 0xe8;
  TR1 = 1;
  SM0 = 0;
  SM1 = 1;
}

void adcStart()
{
  wr = 1;
  _nop_();
  wr = 0;
  _nop_();
  wr = 1;
}

void adcRead()
{
  delay(500);
  rd = 0;
  _nop_();
  rd = 1;
  delay(500);
}

void delay(uint x)
{
  uint i, j;
  for (i = x; i > 0; i--) {
    for (j = 110; j > 0; j--);
  }
}