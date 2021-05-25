/* Light up the first led */

#include <reg51.h>

sbit diola = P2 ^ 5; // reset value of P2 is 0xff

void main()
{
  diola = 1; // not necessary
  P1 = 0xfe;
}