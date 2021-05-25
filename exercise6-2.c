/* Send 1 byte to MCU, after MCU receives this byte,
  send it with a serial number in a front back to the
  computer, reset the serial number when it counts over
  255, set the baud rate to 2400 */

#include <reg51.h>
#define uchar unsigned char

uchar num0, num1, flag;

void initSerial();

void main()
{
  initSerial();
  while (1) {
    if (flag) {
      flag = 0;
      ES = 0;
      SBUF = num0;
      while (!TI);
      TI = 0;
      SBUF = num1;
      while (!TI);
      TI = 0;
      ES = 1;
    }
  }
}

void initSerial()
{
  TMOD = 0x20;
  // set baud rate to 2400
  TH1 = 0xf4;
  TL1 = 0xf4;
  TR1 = 1;
  SM0 = 0;
  SM1 = 1;
  REN = 1;
  EA = 1;
  ES = 1;
}

void serial() interrupt 4
{
  RI = 0;
  if (num0 == 255) {
    num0 = 0;
  }
  num0++;
  num1 = SBUF;
  flag = 1;
}