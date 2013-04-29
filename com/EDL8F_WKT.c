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

void wkt_setup()
{
	// Set bit 9 in the SYSAHBCLKCTRL register to enable the clock
	LPC_SYSCON -> SYSAHBCLKCTRL |= (1ul << 9);
	
	// Clear the WKT reset in PRESETCTRL
	LPC_SYSCON->PRESETCTRL &= ~(1ul << 9);
	LPC_SYSCON->PRESETCTRL |= (1ul << 9);
	
	// Enable low power oscillator in the PMU
	LPC_PMU -> DPDCTRL |= 1ul << 2;
	
	// Set up the WKT Timer, but do not start it.
	LPC_WKT->CTRL = 0x00000005;
}

void wkt_begin(unsigned int pPeriodInTicks)
{
	LPC_WKT->COUNT = pPeriodInTicks;
}

void wkt_stop()
{
	LPC_WKT->CTRL |= 0x00000004;
}
