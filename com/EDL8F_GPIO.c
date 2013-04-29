/*
  	Author: Brian Carrigan
  	Date: 4/29/2013
  	Email: brian.c.carrigan@gmail.com
 
	This file is part of the EDL8F Framework.

    The EDL8F Framework is free software: you can redistribute it and/or 
	modify it under the terms of the GNU General Public License as published 
	by the Free Software Foundation, either version 3 of the License, or 
	(at your option) any later version.

    The EDL8F Framework is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of 
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
	Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the EDL8F Framework.  If not, see <http://www.gnu.org/licenses/>
 */

#include "LPC8xx.h"
#include "EDL8F_GPIO.h"

void gpio_setup()
{
	// Turn on clock
	LPC_SYSCON -> SYSAHBCLKCTRL |= (1ul << 6);
}

void gpio_pinMode(Pin_t pPin, PinMode_t pMode)
{
	unsigned int iocon;
	
	// IOCON Set
	if(pPin == P10 || pPin == P11)
	{
		iocon = 0x00000080;
	} else {
		switch(pMode)
		{
			case INPUT_FLOATING:
				iocon = 0x00000080;
				break;
			case INPUT_PULLDOWN:
				iocon = 0x00000088;
				break;
			case OUTPUT_PUSHPULL:
				iocon = 0x00000080;
				break;
			case OUTPUT_OPENDRAIN:
				iocon = 0x00000480;
				break;
			default:
				iocon = 0x00000090;
				break;
		}
	}
	
	switch(pPin)
	{
		case P1:
			LPC_IOCON -> PIO0_17 = iocon;
			break;
		case P2:
			LPC_IOCON -> PIO0_13 = iocon;
			break;
		case P3:
			LPC_IOCON -> PIO0_12 = iocon;
			break;
		case P4:
			LPC_SWM -> PINENABLE0 |= 0x40;
			LPC_IOCON -> PIO0_5 = iocon;
			break;
		case P5:
			LPC_IOCON -> PIO0_4 = iocon;
			break;
		case P6:
			LPC_SWM -> PINENABLE0 |= 0x4;
			LPC_IOCON -> PIO0_3 = iocon;
			break;
		case P7:
			LPC_SWM -> PINENABLE0 |= 0x8;
			LPC_IOCON -> PIO0_2 = iocon;
			break;
		case P8:
			LPC_IOCON -> PIO0_11 = iocon;
			break;
		case P9:
			LPC_IOCON -> PIO0_10 = iocon;
			break;
		case P10:
			LPC_IOCON -> PIO0_16 = iocon;
			break;
		case P11:
			LPC_IOCON -> PIO0_15 = iocon;
			break;
		case P12:
			LPC_SWM -> PINENABLE0 |= 0x82;
			LPC_IOCON -> PIO0_1 = iocon;
			break;
		case P13:
			LPC_SWM -> PINENABLE0 |= 0x20;
			LPC_IOCON -> PIO0_9 = iocon;
			break;
		case P14:
			LPC_SWM -> PINENABLE0 |= 0x10;
			LPC_IOCON -> PIO0_8 = iocon;
			break;
		case P17:
			LPC_IOCON -> PIO0_7 = iocon;
			break;
		case P18:
			LPC_SWM -> PINENABLE0 |= 0x100;
			LPC_IOCON -> PIO0_6 = iocon;
			break;
		case P19:
			LPC_SWM -> PINENABLE0 |= 0x1;
			LPC_IOCON -> PIO0_0 = iocon;
			break;
		case P20:
			LPC_IOCON -> PIO0_14 = iocon;
			break;
	}

	// Set Direction
	if(pMode == INPUT_FLOATING || pMode == INPUT_PULLDOWN || pMode == INPUT_PULLUP)
	{
		LPC_GPIO_PORT -> DIR0 &= ~(1ul << (unsigned int)pPin);
	} else {
		LPC_GPIO_PORT -> DIR0 |= (1ul << (unsigned int)pPin);
	}

}

unsigned int gpio_read(unsigned int pMask)
{
	unsigned int read;
	LPC_GPIO_PORT -> MASK0 = pMask;
	read = LPC_GPIO_PORT -> PIN0;
	LPC_GPIO_PORT -> MASK0 = 0x00000000;
	return read;
}

unsigned int gpio_readPin(Pin_t pPin)
{
	if(LPC_GPIO_PORT -> PIN0 & (1ul << (unsigned char)pPin))
	{
		return 1;
	}
		
	return 0;
}

// Digital Writes
void gpio_write(unsigned int pMask, unsigned int pValue)
{
	LPC_GPIO_PORT -> MASK0 = pMask;
	LPC_GPIO_PORT -> PIN0 = pValue;
	LPC_GPIO_PORT -> MASK0 = 0x00000000;
}

void gpio_setPin(Pin_t pPin)
{
	LPC_GPIO_PORT -> SET0 = (1ul << (unsigned int)pPin);
}

void gpio_clearPin(Pin_t pPin)
{
	LPC_GPIO_PORT -> CLR0 = (1ul << (unsigned int)pPin);
}

void gpio_togglePin(Pin_t pPin)
{
	LPC_GPIO_PORT -> NOT0 = (1ul << (unsigned int)pPin);
}

