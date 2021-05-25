/* When send 1 to MCU, buzzer sounds with period
  of 400ms, 200ms when receives 2, 100ms when
  receives 3, turns off the buzzer when receives 4 */

#include <reg51.h>
#define uint unsigned int
#define uchar unsigned char

sbit fm = P2 ^ 3;
uint period;
uchar numReceive, flag;

void initSerial();
void delay(uint);

void main()
{
  initSerial();
  while (1) {
    if (flag) {
      flag = 0;
      switch (numReceive) {
        case 1: period = 400;
          break;
        case 2: period = 200;
          break;
        case 3: period = 100;
          break;
      }
      if (numReceive == 4) {
        fm = 1;
      }
      else {
        fm = ~fm;
        delay(period);
      }
    }
  }
}

void initSerial()
{
  /* timer/counter 0 and 1 modes, non-bit addressable */
  // set to mode 2: 8-bit auto-reload timer/ counter (TL1)
  // reloaded from TH1 at overflow
  TMOD = 0x20;
  /* PCON is not set, smod1 is 0, when fosc is 11.0592MHz, baud rate is 9600 */
  TH1 = 0xfd;
  TL1 = 0xfd;
  TR1 = 1;
  /* SCON.7, SCON.6
    serial port mode bit 0 and 1 */
  // 8-bit UART, baud rate is variable
  SM0 = 0;
  SM1 = 1;
  /* SCON.4
    clear to disable serial reception
    set to enable serial reception */
  REN = 1;
  EA = 1;
  /* IE.4, serial port interrupt enable bit */
  ES = 1;
}

/* IP.4, serial port interrupt priority bit */
void serial() interrupt 4
{
  /* SCON.0
    clear to acknowledge interrupt
    set by hardware at the end of the 8th bit time in mode 0 or
    halfway through the stop bit time in the other modes */
  RI = 0;
  /* SBUF, serial buffer register for UART */
  numReceive = SBUF;
  flag = 1;
}

void delay(uint x)
{
  uint i, j;
  for (i = x; i > 0; i--) {
    for (j = 110; j > 0; j--);
  }
}