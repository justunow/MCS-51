/* Send 1, 2, 4, 4 at 1200bps when tap the first
  line of the keys, 5, 6, 7, 8 at 2400bps on thesecond
  line, so on, 9, 10, 11, 12 at 4800bps on the third line,
  13, 14, 15, 16 at 9600bps on the last line */

#include <reg51.h>
#define uint unsigned int
#define uchar unsigned char

uchar code segmentNum[] = {
  0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
  0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71
};
uchar code segmentSelect[] = {
  0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf
};
uchar num, key, flag;

void initSerial();
void keyboardScan();
void delay(uint);

void main()
{
  initSerial();
  while (1) {
    keyboardScan();
    if (flag) {
      flag = 0;
      SBUF = num;
      while (!TI);
      TI = 0;
    }
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

void keyboardScan()
{
  P3 = 0xfe;
  key = P3 & 0xf0;
  while (key != 0xf0)
  {
    delay(5);
    key = P3 & 0xf0;
    while (key != 0xf0) {
      // set baudrate to 1200
      TH1 = 0xe8;
      TL1 = 0xe8;
      switch (key) {
        case 0xe0: num = 1;
          break;
        case 0xd0: num = 2;
          break;
        case 0xb0: num = 3;
          break;
        case 0x70: num = 4;
          break;
      }
      delay(5);
      key = P3 & 0xf0;
    }
    delay(5);
    key = P3 & 0xf0;
    flag = 1;
  }
  P3 = 0xfd;
  key = P3 & 0xf0;
  while (key != 0xf0)
  {
    delay(5);
    key = P3 & 0xf0;
    while (key != 0xf0) {
      // set baudrate to 2400
      TH1 = 0xf4;
      TL1 = 0xf4;
      switch (key) {
        case 0xe0: num = 5;
          break;
        case 0xd0: num = 6;
          break;
        case 0xb0: num = 7;
          break;
        case 0x70: num = 8;
          break;
      }
      delay(5);
      key = P3 & 0xf0;
    }
    delay(5);
    key = P3 & 0xf0;
    flag = 1;
  }
  P3 = 0xfb;
  key = P3 & 0xf0;
  while (key != 0xf0)
  {
    delay(5);
    key = P3 & 0xf0;
    while (key != 0xf0) {
      // set baudrate to 4800
      TH1 = 0xfa;
      TL1 = 0xfa;
      switch (key) {
        case 0xe0: num = 9;
          break;
        case 0xd0: num = 10;
          break;
        case 0xb0: num = 11;
          break;
        case 0x70: num = 12;
          break;
      }
      delay(5);
      key = P3 & 0xf0;
    }
    delay(5);
    key = P3 & 0xf0;
    flag = 1;
  }
  P3 = 0xf7;
  key = P3 & 0xf0;
  while (key != 0xf0)
  {
    delay(5);
    key = P3 & 0xf0;
    while (key != 0xf0) {
      // set baudrate to 9600
      TH1 = 0xfd;
      TL1 = 0xfd;
      switch (key) {
        case 0xe0: num = 13;
          break;
        case 0xd0: num = 14;
          break;
        case 0xb0: num = 15;
          break;
        case 0x70: num = 16;
          break;
      }
      delay(5);
      key = P3 & 0xf0;
    }
    delay(5);
    key = P3 & 0xf0;
    flag = 1;
  }
}

void delay(uint x)
{
  uint i, j;
  for (i = x; i > 0; i--) {
    for (j = 110; j > 0; j--);
  }
}