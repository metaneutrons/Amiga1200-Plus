#include <atmel_start.h>
#include <util/delay.h>
#include <port.h>
#include <key_scan.h>
#include <amigakb.h>


int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	_delay_ms(100);

	//boot from DF0:
	__BootFromDF0___set_level(true);
	//boot from DF1:
	//__BootFromDF0___set_level(false);

	//keep keyboard reset line low for another 400ms
	CapsLockLed_set_level(false);
	KB_RESET_set_level(false);
	_delay_ms(800);
	
	keyscan_init();
	amikb_init();

	KB_RESET_set_level(true); //release keyboard reset
	CapsLockLed_set_level(true);
	
	bool capslockState = false;
	
	while (1)
	{
		uint8_t curkey = scankeys();
		if (curkey == 0x62)
		{
			continue;
		}
		if (curkey == (0x62 | 0x80))
		{
			capslockState = !capslockState;
			CapsLockLed_set_level(!capslockState);
		}
		
		if(getResetState())
		{
			//CapsLockLed_set_level(false);
			KB_RESET_set_level(false);
			CapsLockLed_set_level(false);
			_delay_ms(1000);
			CapsLockLed_set_level(true);
		}
		else
		{
			KB_RESET_set_level(true); //release keyboard reset
			//CapsLockLed_set_level(true);
		}
		amikb_sendkey(curkey);
	}
}
