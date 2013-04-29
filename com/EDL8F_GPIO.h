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

#ifndef EDL8F_GPIO_H
#define EDL8F_GPIO_H

#include "EDL8F_types.h"
#include "EDL8F_pindefs.h"

// Setup Stuff
void gpio_setup(void);
void gpio_pinMode(Pin_t pPin, PinMode_t pMode);

// Digital Reads
unsigned int gpio_read(unsigned int pMask);
unsigned int gpio_readPin(Pin_t pPin);

// Digital Writes
void gpio_write(unsigned int pMask, unsigned int pValue);
void gpio_setPin(Pin_t pPin);
void gpio_clearPin(Pin_t pPin);
void gpio_togglePin(Pin_t pPin);

#endif
