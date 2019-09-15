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

//see http://amigadev.elowar.com/read/ADCD_2.1/Hardware_Manual_guide/node017A.html
const uint8_t keycodes[6][15] =
{
	{0x5F, 0x59, 0x58, 0x57, 0x56, 0x5C, 0x55, 0x5B, 0x54, 0x53, 0x52, 0x51, 0x50, 0x5A, 0x45},
	{0x4C, 0x0D, 0x0C, 0x0B, 0x0A, 0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00},
	{0x4F, 0x44, 0x1B, 0x1A, 0x19, 0x18, 0x17, 0x16, 0x15, 0x14, 0X13, 0x12, 0x11, 0x10, 0x42},
	{0x4E, 0x46, 0x2B, 0x2A, 0x29, 0x28, 0x27, 0x26, 0x25, 0X24, 0x23, 0x22, 0x21, 0x20, 0x62},
	{0x4D, 0x41, 0x40, 0x3B, 0x3A, 0x39, 0x38, 0x37, 0x36, 0x35, 0X34, 0x33, 0x32, 0x31, 0x30},
	{0x4A, 0x0F, 0x1D, 0x2D, 0x3D, 0x43, 0x1E, 0x2E, 0x3E, 0x3C, 0x1F, 0x2F, 0x3F, 0x5E, 0x5D}
};

uint8_t prevkeystates[6][15];
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

	for (int x = 0; x < 6; x++)
	{
		for (int y = 0; y < 15; y++)
		{
			prevkeystates[x][y] = false;
		}
	}
	currentX = 0;
}

static inline bool isStable(uint8_t switchData)
{
	if (switchData == 255) return true;
	if (switchData == 0) return true;
	return false;
}

int scankeys()
{
	while (1)
	{
		XDDRArray[currentX](PORT_DIR_IN);
		currentX++;
		if (currentX > 5)
		{
			currentX = 0;
		}
		XDDRArray[currentX](PORT_DIR_OUT);
		_delay_us(25);
		for (int y = 0; y < 15; y++)
		{
			bool temp = !YInputArray[y]();
			if (isStable(prevkeystates[currentX][y]))
			{
				if (temp != prevkeystates[currentX][y])
				{
					prevkeystates[currentX][y] = 170; // 10101010
					uint8_t tempscancode = keycodes[currentX][y];
					if (temp)
					{
						tempscancode |= 0x80; //set bit 7 to one , indicating key pressed
					}
					return tempscancode;
				}
			}
			else
			{
			  if (temp)
			  {
				prevkeystates[currentX][y] = (prevkeystates[currentX][y] << 1) | 1;
			  }
			  else
			  {
			    prevkeystates[currentX][y] = (prevkeystates[currentX][y] << 1);
			  }
			  
			}
		}
	}
}