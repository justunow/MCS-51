/* The led 1, 3, 5, 7 light up by sequence,
  then led 2, 4, 6, 8 light up by sequence,
  both with period of 300ms for 3 times,
  then light up the first led to the last led
  for 3 times,
  then light up the first and the last leds and
  and then the ones next to them till the middle
  for 3 times,
  then all the leds blink for 3 times,
  turn off all the leds */

#include <reg51.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char

void delay(uint);

void main()
{
  uchar count, ledState, left, right;
  for (count = 3; count > 0; count--) {
    ledState = 1;
    while ((ledState & 0x40) != 0x40) {
      P1 = ~ledState;
      delay(300);
      ledState = _crol_(ledState, 2);
    }
    delay(300);
    P1 = ~ledState;
    ledState = 2;
    while ((ledState & 0x80) != 0x80) {
      P1 = ~ledState;
      delay(300);
      ledState = _crol_(ledState, 2);
    }
    delay(300);
    P1 = ~ledState;
  }

  ledState = 1;
  for (count = 24; count > 0; count--) {
    P1 = ~ledState;
    delay(300);
    ledState = _crol_(ledState, 1);
  }

  left = 0x80;
  right = 0x01;
  for (count = 24; count > 0; count--) {
    P1 = (~left) & (~right);
    delay(300);
    left = _cror_(left, 1);
    right = _crol_(right, 1);
  }

  P1 = 0xff;
  for (count = 6; count > 0; count--) {
    P1 = ~P1;
    delay(300);
  }

  P1 = 0xff;
  while (1);
}

void delay(uint x)
{
  uint i, j;
  for (i = x; i > 0; i--) {
    for (j = 110; j > 0; j--);
  }
}