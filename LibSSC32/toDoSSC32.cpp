
/**
 *	The servo channel will be offset by the amount indicated in the offset value
 *	@param channel The servo to move
 *	@param offset	The offset to apply
 *	@return False if the channel or offset is invalid or if this function is called while inside a command group other than SSC32_CMDGRP_TYPE_PULSE_OFFSET. True otherwise.
 */

bool SSC32::pulseOffset(int channel, int offset)
{
	
	if (channel < SSC32_MIN_CH || channel > SSC32_MAX_CH)
	{
		//Channel not valid
		return false;
	}
	
	if (offset < SSC32_MIN_OFFSET || offset > SSC32_MAX_OFFSET)
	{
		//Offset not valid
		return false;
	}
	
	if (_commandType != SSC32_CMDGRP_TYPE_NONE && _commandType != SSC32_CMDGRP_TYPE_PULSE_OFFSET)
	{
		//This can only be called as a single command or inside a group of 
		//commands of type SSC32_CMDGRP_TYPE_PULSE_OFFSET
		return false;	
	}
	
	//We are good to go
	Serial.print("#");
	Serial.print(channel);
	Serial.print(" PO");
	Serial.print(offset);
	Serial.print(" ");
	
	if (_commandType == SSC32_CMDGRP_TYPE_NONE)
	{
		//This is a single command so execute it
		Serial.println();
	}
	
	return true;
	
}

/**
 *	The channel will go to the indicated level
 *	@param channel The output channel
 *	@param level	The level to write (HIGH or LOW)
 *	@return	It will return false if channel is invalid or if this function is called while inside a command group other than SSC32_CMDGRP_TYPE_DISCRETE_OUTPUT. True otherwise.
 */
bool SSC32::discreteOutput(int channel, bool level)
{
	if (channel < SSC32_MIN_CH || channel > SSC32_MAX_CH)
	{
		//Channel not valid
		return false;
	}
	
	if (_commandType != SSC32_CMDGRP_TYPE_NONE && _commandType != SSC32_CMDGRP_TYPE_DISCRETE_OUTPUT)
	{
		//This can only be called as a single command or inside a group of 
		//commands of type SSC32_CMDGRP_TYPE_PULSE_OFFSET
		return false;	
	}
	
	//We are good to go
	Serial.print("#");
	Serial.print(channel);
	
	if (level == HIGH)
		Serial.print("H");
	else
		Serial.print("L");
	
	if (_commandType == SSC32_CMDGRP_TYPE_NONE)
	{
		//This is a single command so execute it
		Serial.println();
	}
	
	return true;
}

/**
 *	This command allows 8 bits of binary data to be written at once.
 *	@param bank The output bank of bits. Value should be one of these : SSC32_BANK_0, SSC32_BANK_1, SSC32_BANK_2, SSC32_BANK_3
 *	@param value The value to write. Should be between 0 and 255.
 *	@return It will return false if the bank or the value is not valid. True otherwise.  
 */
bool SSC32::byteOutput(int bank, int value)
{
	
	if (bank < SSC32_BANK_0 || bank > SSC32_BANK_3)
	{
		//Bank is not valid
		return false;
	}
	
	if (value < 0 || value > 255)
	{
		//Value is not valid
		return false;
	}
	
	//We are good to go
	Serial.print("#");
	Serial.print(bank);
	Serial.print(":");
	Serial.print(value);
	Serial.println();
	
	
	return true;
}

/**
 *	Check whether there is a movement in progress or not.
 *	@return This will return false if the previous movement is complete and true if it is still in progress.
 */
bool SSC32::isMoving()
{
	char c = '.';
	Serial.println("Q");
	Serial.println();
	
	//delay(50);
	if (Serial.available())
	{
		
		c = Serial.read();
		
	}
	
	
	if ( c == '+' )
		return true;
	
	return false;
	
}

/**
 *	This will return a value indicating the pulse width of the selected servo with a resolution	of 10uS. For example, if the pulse width is 1500uS, the returned value would be 150.
 *	@param channel The channel to query
 *	@return Will return -1 if the channel is not valid or the function is called inside a group of commands. Will return the pusle width of the desired channel otherwise.
 */
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
	
	char c;
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
	}
}

/**
 *	This function reads the digital inputs A, B, C, D, AL, BL, CL and DL according to the SSC-32 user manual
 *	@param input The digital input to read. Should be one of these : SSC32_DIGITAL_INPUT_A, SSC32_DIGITAL_INPUT_B, SSC32_DIGITAL_INPUT_C, SSC32_DIGITAL_INPUT_D, SSC32_DIGITAL_INPUT_AL, SSC32_DIGITAL_INPUT_BL, SSC32_DIGITAL_INPUT_CL, SSC32_DIGITAL_INPUT_DL
 *	@return It will return the state of the desired input (0 or 1). Or -1 if any error happens.  
 */
int SSC32::readDigitalInput(int input)
{
	
	if (_commandType != SSC32_CMDGRP_TYPE_NONE)
	{
		//This can only be executed from outside a group of commands. That is, as a single command.
		return -1;
	}
	
	switch(input)
	{
		case SSC32_DIGITAL_INPUT_A:
			//Read digital input A
			Serial.print("A");
			break;
		case SSC32_DIGITAL_INPUT_B:
			//Read digital input B
			Serial.print("B");
			break;
		case SSC32_DIGITAL_INPUT_C:
			//Read digital input C
			Serial.print("C");
			break;
		case SSC32_DIGITAL_INPUT_D:
			//Read digital input D
			Serial.print("D");
			break;
		case SSC32_DIGITAL_INPUT_AL:
			//Read digital input AL
			Serial.print("AL");
			break;
		case SSC32_DIGITAL_INPUT_BL:
			//Read digital input BL
			Serial.print("BL");
			break;
		case SSC32_DIGITAL_INPUT_CL:
			//Read digital input CL
			Serial.print("CL");
			break;
		case SSC32_DIGITAL_INPUT_DL:
			//Read digital input DL
			Serial.print("DL");
			break;
		default:
			//Input not valid
			return -1;
	}
	
	char c;
	delay(50);
	if (Serial.available())
	{
		c = Serial.read();
		return int(c);
	}else{
		return -1;
	}
	
}

/**
 *	This function reads the analog inputs VA, VB, VC, VD according to the SSC-32 user manual
 *	@param input The analog input to read. Should be one of these : SSC32_DIGITAL_INPUT_VA, SSC32_DIGITAL_INPUT_VB, SSC32_DIGITAL_INPUT_VC, SSC32_DIGITAL_INPUT_VD
 *	@return It will return the state of the desired input (Between 0 and 255). Or -1 if any error happens.  
 */
int SSC32::readAnalogInput(int input)
{
	
	if (_commandType != SSC32_CMDGRP_TYPE_NONE)
	{
		//This can only be executed from outside a group of commands. That is, as a single command.
		return -1;
	}
	
	switch(input)
	{
		case SSC32_ANALOG_INPUT_VA:
			//Read digital input A
			Serial.print("VA");
			break;
		case SSC32_ANALOG_INPUT_VB:
			//Read digital input B
			Serial.print("VB");
			break;
		case SSC32_ANALOG_INPUT_VC:
			//Read digital input C
			Serial.print("VC");
			break;
		case SSC32_ANALOG_INPUT_VD:
			//Read digital input D
			Serial.print("D");
			break;
			
		default:
			//Input not valid
			return -1;
	}
	
	char c;
	delay(50);
	if (Serial.available())
	{
		c = Serial.read();
		return int(c);
	}else{
		return -1;
	}
	
	
}
