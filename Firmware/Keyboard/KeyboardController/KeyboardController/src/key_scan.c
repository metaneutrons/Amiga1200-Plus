/*
* key_scan.c
*
* Created: 14/09/2019 16:03:36
*  Author: Jeroen Vandezande
*/
#include <port.h>
#include <atmel_start.h>
#include <util/delay.h>

void (*XDDRArray[6]) (const enum port_dir dir);
bool (*YInputArray[15]) ();
uint8_t keycodes[6][15];
bool prevkeystates[6][15];
int currentX;

void keyscan_init()
{
	XDDRArray[0] = X2_set_dir;
	XDDRArray[1] = X3_set_dir;
	XDDRArray[2] = X4_set_dir;
	XDDRArray[3] = X5_set_dir;
	XDDRArray[4] = X6_set_dir;
	XDDRArray[5] = X7_set_dir;
	
	YInputArray[0] = Y0_get_level;
	YInputArray[1] = Y1_get_level;
	YInputArray[2] = Y2_get_level;
	YInputArray[3] = Y3_get_level;
	YInputArray[4] = Y4_get_level;
	YInputArray[5] = Y5_get_level;
	YInputArray[6] = Y6_get_level;
	YInputArray[7] = Y7_get_level;
	YInputArray[8] = Y8_get_level;
	YInputArray[9] = Y9_get_level;
	YInputArray[10] = Y10_get_level;
	YInputArray[11] = Y11_get_level;
	YInputArray[12] = Y12_get_level;
	YInputArray[13] = Y13_get_level;
	YInputArray[14] = Y14_get_level;

	keycodes[0][0] = 0x5F; //HELP
	keycodes[0][1] = 0x59; //F10
	keycodes[0][2] = 0x58; //F9
	keycodes[0][3] = 0x57; //F8
	keycodes[0][4] = 0x56; //F7
	keycodes[0][5] = 0x5C; // /
	keycodes[0][6] = 0x55; //F6
	keycodes[0][7] = 0x5B; // )
	keycodes[0][8] = 0x54; //F5
	keycodes[0][9] = 0x53; //F4
	keycodes[0][10] = 0x52; //F3
	keycodes[0][11] = 0x51; //F2
	keycodes[0][12] = 0x50; //F1
	keycodes[0][13] = 0x5A; // (
	keycodes[0][14] = 0x45; //ESC

	keycodes[1][0] = 0x4C; //CURS UP
	keycodes[1][1] = 0x0D; // |
	keycodes[1][2] = 0x0C; // +=
	keycodes[1][3] = 0x0B; // _-
	keycodes[1][4] = 0x0A; // 0
	keycodes[1][5] = 0x09; // 9
	keycodes[1][6] = 0x08; // 8
	keycodes[1][7] = 0x07; // 7
	keycodes[1][8] = 0x06; // 6
	keycodes[1][9] = 0x05; // 5
	keycodes[1][10] = 0x04; // 4
	keycodes[1][11] = 0x03; // 3
	keycodes[1][12] = 0x02; // 2
	keycodes[1][13] = 0x01; // 1
	keycodes[1][14] = 0x00; // ~

	for (int x = 0; x < 6; x++)
	{
		for (int y = 0; y < 15; y++)
		{
			prevkeystates[x][y] = false;
		}
	}

	currentX = 0;

}

int scankeys()
{
	while (1)
	{
	   _delay_us(166);
	   for (int y = 0; y < 15; y++)
	   {
	        bool temp = !YInputArray[y]();
			if (temp != prevkeystates[currentX][y])
			{
				prevkeystates[currentX][y] = temp;
				uint8_t tempscancode = keycodes[currentX][y];
				if (temp)
				{
				  tempscancode |= 0x80; //set bit 7 to one , indicating key pressed
				}
				return tempscancode;
			}
	   }
	   XDDRArray[currentX](PORT_DIR_IN);
	   currentX++;
	   if (currentX > 5)
	   {
			currentX = 0;
	   }		
	   XDDRArray[currentX](PORT_DIR_OUT);
	}
}