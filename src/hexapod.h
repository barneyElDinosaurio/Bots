/*
 *  hexapod.h
 *  bot
 *
 *  Created by Sergio Bromberg Dimaté on 6/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef BOT_H
#define BOT_H
#include "bot.h"
#endif



#include "SSC32.h"

// Should this be in ssc32 ?
//#include "wiringPi.h"
//#include "wiringSerial.h"



class Hexapod : public Bot{

public:	
	Hexapod();
	void advance( float speed, float rotAngle);
	void rotate(float angle);
	void rotateR();
	void rotateL();
	void advance();
	void recoil();
	void stop();
	void setup();
	void mandarUnDato();
	
	// Serial:
void startSerial();
	
	SSC32 servocontroller;

};