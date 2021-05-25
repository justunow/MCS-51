/* Display the square number of 1 to 16
  based on the key tapped on the keyboard */

#include <reg51.h>
#define uint unsigned int
#define uchar unsigned char

sbit dula = P2 ^ 6;
sbit wela = P2 ^ 7;

uchar key;
uchar code segmentNum[] = {
  0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
  0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71
};
uchar code segmentSelect[] = {
  0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf
};
uchar numDigit[] = {0, 0, 0};
uint num;

void display();
void keyboardScan();
void numberSquare();
void delay(uint);

void main()
{
  while (1) {
    display();
    keyboardScan();
    numberSquare();
  }
}

void display()
{
  uchar i;
  for (i = 0; i < 3; i++) {
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

void keyboardScan()
{
  P3 = 0xfe;
  key = P3 & 0xf0;
  while (key != 0xf0)
  {
    delay(5);
    key = P3 & 0xf0;
    while (key != 0xf0) {
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
  }
  P3 = 0xfd;
  key = P3 & 0xf0;
  while (key != 0xf0)
  {
    delay(5);
    key = P3 & 0xf0;
    while (key != 0xf0) {
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
  }
  P3 = 0xfb;
  key = P3 & 0xf0;
  while (key != 0xf0)
  {
    delay(5);
    key = P3 & 0xf0;
    while (key != 0xf0) {
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
  }
  P3 = 0xf7;
  key = P3 & 0xf0;
  while (key != 0xf0)
  {
    delay(5);
    key = P3 & 0xf0;
    while (key != 0xf0) {
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
  }
}

void numberSquare() {
  numDigit[0] = num * num / 100;
  numDigit[1] = num * num / 10 % 10;
  numDigit[2] = num * num % 10;
}

void delay(uint x)
{
  uint i, j;
  for (i = x; i > 0; i--) {
    for (j = 110; j > 0; j--);
  }
}
