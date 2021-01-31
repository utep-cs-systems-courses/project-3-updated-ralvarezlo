
/** brief program based on the button demo
 *  will play a different sound and turn on a LED w/ each button
 */

#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include <p2switches.h>
#include "buzzer.h"

void button_machine()
{
    u_int switches = p2sw_read(), i;
    char str[5];
    char ledFlag = 0;

    P1OUT &= 0xBE;
    switch(switches & 0x0F) {
    case 14: buzzer_set_period(500); break;
    case 13: buzzer_set_period(750); break;
    case 11: buzzer_set_period(1000); break;
    case 7: buzzer_set_period(1200); break;
    default: buzzer_set_period(0); ledFlag = 1;
    }
    
    for (i = 0; i < 4; i++)
      str[i] = (switches & (1<<i)) ? '-' : '0'+i;
    str[4] = 0;
    drawString5x7(20,20, str, COLOR_GREEN, COLOR_BLUE);

    P1OUT |= ledFlag? 0x40 : 0x01;
}


/** Initializes everything, clears the screen, draws "hello" and the circle */
void main()
{
  configureClocks();
  lcd_init();
  p2sw_init(15);
  buzzer_init();
  buzzer_set_period(0);
  P1DIR |= 0x41;
  or_sr(0x8);			/* GIE (enable interrupts) */
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLUE);

  drawString5x7(10,10, "switches:", COLOR_GREEN, COLOR_BLUE);
  while (1) button_machine();
}
