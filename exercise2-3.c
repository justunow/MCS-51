/* Light up all the leds back and forth,
   on state: 200ms,
   buzzer sounds during switching */

#include <reg51.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char

uchar ledState;
sbit fm = P2 ^ 3;

void beep(uint);
void delay(uint);

void main()
{
  ledState = 0xfe;
  while (1) {
    while (ledState != 0x7f) {
      P1 = ledState;
      delay(100);
      beep(2);
      ledState = _crol_(ledState, 1);
    }
    P1 = ledState;
    delay(100);
    beep(2);
    ledState = _cror_(ledState, 1);
    while (ledState != 0xfe) {
      P1 = ledState;
      delay(100);
      beep(2);
      ledState = _cror_(ledState, 1);
    }
    P1 = ledState;
    delay(100);
    beep(2);
    ledState = _crol_(ledState, 1);
  }
}

void beep(uint x)
{
  for (x; x > 0; x--) {
    fm = ~fm;
    delay(10);
  }
}

void delay(uint x)
{
  uint i, j;
  for (i = x; i > 0; i--) {
    for (j = 110; j > 0; j--);
  }
}