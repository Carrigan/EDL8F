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

#include "EDL8F.h"

void setup()
{	
	// Set up pin 11 as a push/pull output.
	gpio_pinMode(P11, OUTPUT_PUSHPULL);
	
	// Set up the Wake-Up Timer to interrupt every 500ms.
	setupWktTimer(500);
}

void onWkt()
{
	// Toggle the pin
	gpio_togglePin(P11);
}

void processor()
{

}
