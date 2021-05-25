/* On and off all the leds by sequence with the period of 1s,
   on state: 500ms, with buzzer sounds on,
   off state: 500ms, with buzzer sounds off */

#include <reg51.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char

uchar ledState;
sbit fm = P2 ^ 3;

void delay(uint);

void main()
{
  ledState = 0xfe;
  while (1) {
    P1 = ledState;
    fm = 0;
    delay(500);
    P1 = 0xff;
    fm = 1;
    delay(500);
    ledState = _crol_(ledState, 1);
  }
}

void delay(uint x)
{
  uint i, j;
  for (i = x; i > 0; i--) {
    for (j = 110; j > 0; j--);
  }
}