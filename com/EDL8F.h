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

#ifndef EDL8F_H
#define EDL8F_H

///////////////////////////////////////////////////////////////////////////////
//								  	Includes  								 //
///////////////////////////////////////////////////////////////////////////////
#include "LPC8xx.h"
#include "EDL8F_types.h"
#include "EDL8F_pindefs.h"
#include "EDL8F_GPIO.h"
#include "SystemManager.h"

///////////////////////////////////////////////////////////////////////////////
//								  User Defined  							 //
///////////////////////////////////////////////////////////////////////////////
void setup(void);
void onWkt(void);
void processor(void);


#endif
