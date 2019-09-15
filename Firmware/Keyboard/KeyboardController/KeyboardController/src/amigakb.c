#include <stdio.h>
#include <avr/io.h>
#include <port.h>
#include <atmel_start.h>
#include <util/delay.h>
#include "amigakb.h"

#define TIMEOUT_uSEC	14300

static void resync(void);

static unsigned char prev_keycode = 0xff;
static unsigned char capslk;

void amikb_init()
{
    //leave data and clock line floating
	KB_DATA_set_dir(PORT_DIR_IN);
	KB_CLOCK_set_dir(PORT_DIR_IN);
}

void amikb_sendkey(unsigned char keycode)
{
    bool press = (keycode >> 7);
	keycode = keycode & 0x7F;
	int i;

	if(keycode == 0x62) {
		/* caps lock doesn't get a key release event when the key is released
		 * but rather when the caps lock is toggled off again
		 */
		if(!press) return;

		capslk = ~capslk;
		press = capslk;
	}

	/* keycode bit transfer order: 6 5 4 3 2 1 0 7 (7 is pressed flag) */
	keycode = (keycode << 1) | (~press & 1);
	if(keycode == prev_keycode) return;
	prev_keycode = keycode;

	for(i=0; i<8; i++) {
		/* data line is inverted */
		if(keycode & 0x80) {
			KB_DATA_set_dir(PORT_DIR_OUT);
		} else {
			KB_DATA_set_dir(PORT_DIR_IN);
		}
		keycode <<= 1;
		_delay_us(20);
		/* pulse the clock */
		KB_CLOCK_set_dir(PORT_DIR_OUT);
		_delay_us(20);
		KB_CLOCK_set_dir(PORT_DIR_IN);
		_delay_us(20);
	}

	/* similarly tristate first, then drop the pullups */
	KB_DATA_set_dir(PORT_DIR_IN);

	/* wait for ack */
	int timeout = 0;
	while(KB_DATA_IN_get_level()) 
	{
		if(timeout >= TIMEOUT_uSEC) 
		{
			resync();
			break;
		}
		_delay_us(10);
		timeout++;
	}
}


static void resync(void)
{
	//PORTD |= ACLK_BIT | ADATA_BIT;
	//printf("lost sync\r\n");
//
	//for(;;) {
		//cli();
		//DDRD |= ACLK_BIT | ADATA_BIT;
//
		//PORTD &= ~ACLK_BIT;
		//EIFR |= (1 << INTF1);	/* clear interrupt raised by the previous line */
		//sei();
		//_delay_us(20);
		//PORTD |= ACLK_BIT;
//
		//DDRD &= ~(ACLK_BIT | ADATA_BIT);
//
		//reset_timer();
		//while(get_msec() < TIMEOUT_MSEC) {
			//if(!(PIND & ADATA_BIT)) {
				//return;
			//}
		//}
	//}
}

