/**
*	@file SSC32.h
*	@brief Control Lynxmotion's SSC-32 with Arduino.
*	@author Martin Peris (http://www.martinperis.com)
*	@date 5/2/2011
*
*	@change 27.10.2011 by Marco Schwarz <marco.schwarz@cioppino.net>
*/

/*
  SSC32.cpp - Control Lynxmotion's SSC-32 V2 with Arduino
  Copyright (c) 2011 Martin Peris (http://www.martinperis.com).
  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/*
* @author Marco Schwarz
* @descr for Arduino >= 1.0rc2 
*/ 
#if defined(ARDUINO) && ARDUINO >= 100
//#include "Arduino.h"	// for digitalRead, digitalWrite, etc
#else
//#include "WProgram.h"
#endif

#include "SSC32.h"

#include "wiringPi.h"
#include "wiringSerial.h"

//using namespace std;


/**
*	Create an SSC32 object and initialize SoftwareSerial.
*/
SSC32::SSC32() 
{
	_ttcm = -1;
	_commandType = SSC32_CMDGRP_TYPE_NONE;
	
	// ********** Init wiringPi stuff:
}

/**
*	Begin the serial port communications. Should be called inside the setup() function of the Arduino.
*	@param bauds	The speed in bauds for the serial port
*/


void SSC32::begin(int bauds)
{

	wiringPiSetup();
	
	serialNumber  = serialOpen("/dev/ttyAMA0",bauds);
	
	//std::cout << "Se ha conectado al puerto serial número: " << endl;
	serialPutchar( serialNumber, 'c' );
	
	
	
	int k = 5;
	
	
}

void SSC32:: mandarUnDato(){

	serialPutchar(serialNumber, 'c');
}
/**
*	Start a new group of commands
*	@param type	The type of group command. Should be one of the following : SSC32_CMDGRP_TYPE_SERVO_MOVEMENT, SSC32_CMDGRP_TYPE_PULSE_OFFSET, SSC32_CMDGRP_TYPE_DISCRETE_OUTPUT
*	@return It will return false if a previous call to beginGroupCommand has not been finished yet by calling endGroupCommand. True otherwise.
*/

