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
	
	cout << "Se ha conectado al puerto serial número: " << serialNumber << endl;
	
	// Código de prueba
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

bool SSC32::beginGroupCommand(int type)
{
	
	if (type < SSC32_CMDGRP_TYPE_NONE || type > SSC32_CMDGRP_TYPE_DISCRETE_OUTPUT)
	{
		//The command type is not valid
		return false;
	}
	
	
	if ( _commandType != SSC32_CMDGRP_TYPE_NONE)
	{
		//Can not start another command group while in the middle of another command group
		return false;
	}
	
	_commandType = type;
	return true;
	
}

/**
 *	Abort a group of commands
 *	@return It will return false if a group command has not been started by calling beginGroupCommand. True otherwise.
 */
bool SSC32::abortGroupCommand()
{
	
	if (_commandType == SSC32_CMDGRP_TYPE_NONE)
	{
		//Can not abort, we are not in a group of commands
		return false;
	}
	
	//According to the manual I should write the ascii character for <esc>
	// ************ ARDUINO *********
	
	//Serial.write(27);
	
	// *********** RASPI (WiringPi) ******
	
	serialPutchar( serialNumber, 27);
	
	
	_commandType = SSC32_CMDGRP_TYPE_NONE;
	_ttcm = -1;
	
	return true;
}

/**
 *	End a group of commands
 *	@return It will return false if a group command has not been started by calling beginGroupCommand or it has been aborted by abortGroupCommand. True otherwise.
 */
bool SSC32::endGroupCommand()
{
	
	if (_commandType == SSC32_CMDGRP_TYPE_NONE)
	{
		//Can not end, we are not in a group of commands
		return false;
	}
	
	if (_ttcm != -1)
	{
		//Set the time to complete movement
		// **** ARDUINO ****
//		Serial.print(" T");
//		Serial.print(_ttcm);
		
		// **** RASPI ****
		
		string mes(" T");
		serialPuts( serialNumber, (char*) mes.c_str() ); // With wiringpi
		serialPuts( serialNumber, (char*)_ttcm ); // With wiringpi // NO estoy seguro

	}
	
	string mes("/n/r"); // **** REvisar orden
	serialPuts( serialNumber, (char*) mes.c_str() );
	
	
	_commandType = SSC32_CMDGRP_TYPE_NONE;
	_ttcm = -1;
	return true;
	
}

/**
 *	Move the servo at #channel to "position".
 *	If this function is called from outside a pair of beginGroupCommand/endGroupCommand	then the servo will move right away.
 *
 *	But if this function is called inside a gruop of commands, then the servo will not move	until you call endGroupCommand
 *	@param	channel	The servo to move
 *	@param	position	The position where to move the servo
 *	@return False if the channel or position is not valid or if this function is called while inside a command group other than SSC32_CMDGRP_TYPE_SERVO_MOVEMENT. True otherwise.
 */
bool SSC32::servoMove(int channel, int position)
{
	if (channel < SSC32_MIN_CH || channel > SSC32_MAX_CH)
	{
		//Channel not valid
		return false;
	}
	
	if (position < SSC32_MIN_PW || position > SSC32_MAX_PW)
	{
		//Position not valid
		return false;
	}
	
	if (_commandType != SSC32_CMDGRP_TYPE_NONE && _commandType != SSC32_CMDGRP_TYPE_SERVO_MOVEMENT)
	{
		//This can only be called as a single command or inside a group of 
		//commands of type SSC32_CMDGRP_TYPE_SERVO_MOVEMENT
		return false;	
	}
	
	//We are good to go
	
	// **** ARDUINO ****
	/*
	Serial.print("#");
	Serial.print(channel);
	Serial.print(" P");
	Serial.print(position);
	Serial.print(" ");
	*/
		
	// **** RASPI *****
	
	
	stringstream ss;
	ss << "#" << int2str(channel) << " P" << int2str(position) << " ";
	const string s = ss.str(); // Careful with this, see  See http://stackoverflow.com/questions/1374468/c-stringstream-string-and-char-conversion-confusion
	//cout << "SS___ " << ss;  
	
	
	
	//const char * c = appendChannelPos( channel , position );
	serialPuts(serialNumber,  (char *) s.c_str() );
	
	//serialPuts( serialNumber, (char*) ss.str().c_str() );
	//serialPuts( serialNumber, (char*) mes.c_str() ); // With wiringpi
	
	//string mes2("\n+\r");
     	//serialPuts(serialNumber, (char*) mes2.c_str());
	
	if (_commandType == SSC32_CMDGRP_TYPE_NONE)
	{
		//This is a single command so execute it
		
		// **** ARDUINO ****
		//Serial.println();
		
		// **** RASPI ****
		string mes("\n\r");
		serialPuts(serialNumber, (char*) mes.c_str());
		
	}
	
	cout << "En el movedor de servos" << endl;
	return true;
	
}



/**
 *	Move the servo at #channel to "position" with speed "speed".
 *	If this function is called from outside a pair of beginGroupCommand/endGroupCommand	then the servo will move right away.
 *
 *	But if this function is called inside a gruop of commands, then the servo will not move	until you call endGroupCommand.
 *	@param channel The servo to move
 *	@param position	The position where to move the servo
 *	@param speed	The speed for the movement
 *	@return False if the channel or position or speed is invalid or if this function is called while inside a command group other than SSC32_CMDGRP_TYPE_SERVO_MOVEMENT. True otherwise.
 */


bool SSC32::servoMoveSpeed(int channel, int position, int speed)
{
	if (channel < SSC32_MIN_CH || channel > SSC32_MAX_CH)
	{
		//Channel not valid
		return false;
	}
	
	if (position < SSC32_MIN_PW || position > SSC32_MAX_PW)
	{
		//Position not valid
		return false;
	}
	
	if (speed < 0)
	{
		//Speed not valid
		return false;
	}
	
	if (_commandType != SSC32_CMDGRP_TYPE_NONE && _commandType != SSC32_CMDGRP_TYPE_SERVO_MOVEMENT)
	{
		//This can only be called as a single command or inside a group of 
		//commands of type SSC32_CMDGRP_TYPE_SERVO_MOVEMENT
		return false;	
	}
	
	//**** ARDUINO ****
	/*
	//We are good to go
	Serial.print("#");
	Serial.print(channel);
	Serial.print(" P");
	Serial.print(position);
	Serial.print(" S");
	Serial.print(speed);
	Serial.print(" ");
	*/
	
	//**** RASPI ****
	
	stringstream ss;
	ss <<"#"<<int2str(channel) << " P"<< int2str(position) << " S" << int2str(speed) << " ";
	const string s = ss.str();
	
	serialPuts(serialNumber, (char*) s.c_str());

	
	if (_commandType == SSC32_CMDGRP_TYPE_NONE)
	{
		//This is a single command so execute it
		
		//**** ARDUINO ****
		//Serial.println();
		
		//**** RASPI ****
		string mes("\n\r");
		serialPuts(serialNumber, (char*) mes.c_str());
		
	}
	
	return true;
	
}
/**
 *	Move the servo at #channel to "position" taking "time" milliseconds.
 *	If this function is called from outside a pair of beginGroupCommand/endGroupCommand	then the servo will move right away.
 *
 *	But if this function is called inside a gruop of commands, then the servo will not move	until you call endGroupCommand
 *	@param channel The servo to move
 *	@param position	The position where to move the servo
 *	@param ttcm	Time to complete the movement
 *	@return False if the channel or position or time is invalid or if this function is called while inside a command group other than SSC32_CMDGRP_TYPE_SERVO_MOVEMENT. True otherwise.
 */
bool SSC32::servoMoveTime(int channel, int position, int ttcm)
{
	if (channel < SSC32_MIN_CH || channel > SSC32_MAX_CH)
	{
		//Channel not valid
		return false;
	}
	
	if (position < SSC32_MIN_PW || position > SSC32_MAX_PW)
	{
		//Position not valid
		return false;
	}
	
	if (ttcm < SSC32_MIN_TIME || ttcm > SSC32_MAX_TIME )
	{
		//time not valid
		return false;
	}
	
	if (_commandType != SSC32_CMDGRP_TYPE_NONE && _commandType != SSC32_CMDGRP_TYPE_SERVO_MOVEMENT)
	{
		//This can only be called as a single command or inside a group of 
		//commands of type SSC32_CMDGRP_TYPE_SERVO_MOVEMENT
		return false;	
	}
	
	//We are good to go
	//**** ARDUINO ****
	/*
	Serial.print("#");
	Serial.print(channel);
	Serial.print(" P");
	Serial.print(position);
	*/
	
	//**** RASPI ****
	
	stringstream ss;
	ss <<"#"<<int2str(channel) << " P"<< int2str(position);
	const string s = ss.str();
	serialPuts(serialNumber, (char*) s.c_str());
	
	if (_commandType == SSC32_CMDGRP_TYPE_NONE)
	{
		//This is a single command so execute it
		// **** ARDUINO ****
		/*
		Serial.print(" T");
		Serial.print(ttcm);
		Serial.print(" ");
		Serial.println();
		 */
		
		// **** RASPI *****
		
		stringstream ss;
		ss << " T" << int2str( ttcm ) << " \n\r";
		const string s = ss.str();
		serialPuts( serialNumber, (char*) s.c_str() );
	}else{
		//This is a command group. Store the "time to complete movement" for later
		_ttcm = ttcm;
	}
	
	return true;
	
}
int SSC32::queryPulseWidth(int channel)
{

	if (channel < SSC32_MIN_CH || channel > SSC32_MAX_CH)
	{
		//Channel not valid
		return -1;
	}

	if (_commandType != SSC32_CMDGRP_TYPE_NONE)
	{
		//This can only be executed from outside a group of commands. That is, as a single command.
		return -1;
	}

	stringstream ss;
	ss << "QP " << int2str(channel) << "\n\r";
	cout<< "Enviando datos al servo controlador: " 	<< ss;
	const string s = ss.str();
	serialPuts( serialNumber, (char*) s.c_str() );


cout << "antes del delay" << endl;
	delay(100);

	cout << "despues del delay" << endl;
	cout << "SERIAL dATA av.: " << serialDataAvail(serialNumber) << endl;

	if( serialDataAvail(serialNumber) > 0){
		char c = serialGetchar( serialNumber );
		cout << "El pulso del servo " << channel <<" es " << c << endl;
		return c;
	}
	else{
		return -1;
	}

	/*char c;
	Serial.print("QP");
	Serial.print(channel);
	Serial.println();

	delay(50);
	if (Serial.available())
	{	
		c = Serial.read();
		return int(c);
	}else{
		return -1;
	}*/

}


// AUXILIARY FUNCTIONS

string SSC32::int2str(int number){// por revisar
	stringstream ss;
	ss << number;
	return(ss.str());
}
const char* SSC32::appendChannelPos( int channel , int position){ // Append stuff into char*
	
	string mes = "#";
	string channelString = int2str(channel);
	mes.append(channelString);
	mes.append(" P");
	
	string positionString = int2str(position);
	mes.append(positionString);
	mes.append(" "); // unnecesary
	
	// c_str() deallocates after usage, using temp variable . See http://stackoverflow.com/questions/1374468/c-stringstream-string-and-char-conversion-confusion

	
	return( mes.c_str() );

}




