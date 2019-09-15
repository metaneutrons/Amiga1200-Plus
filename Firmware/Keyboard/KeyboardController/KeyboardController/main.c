#include <atmel_start.h>
#include <util/delay.h>
#include <port.h>
#include <key_scan.h>
#include <amigakb.h>

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	

	//boot from DF0:
	__BootFromDF0___set_level(true);
	//boot from DF1:
	//__BootFromDF0___set_level(false);

	//keep keyboard reset line low for another 400ms
	CapsLockLed_set_level(false);
	KB_RESET_set_level(false);
	_delay_ms(600);
	
	keyscan_init();
	amikb_init();

	KB_RESET_set_level(true); //release keyboard reset
	CapsLockLed_set_level(true);

	while (1) 
	{
	  //_delay_ms(500);
	 // CapsLockLed_toggle_level();
	 // X2_set_dir(PORT_DIR_IN);
	 uint8_t curkey = scankeys();
	 amikb_sendkey(curkey);
	 if (curkey == 0x04)
	 {
		CapsLockLed_set_level(false);
	 }
	 if (curkey == (0x04 | 0x80))
	 {
		 CapsLockLed_set_level(true);
	 }
	 
	}
}
