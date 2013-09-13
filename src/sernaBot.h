/*
 *  sernaBot.h
 *  bot
 *
 *  Created by Sergio Bromberg Dimaté on 6/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */


#include "wiringPi.h"
#include "wiringSerial.h"

#ifndef BOT_H
#define BOT_H
#include "bot.h"
#endif

//
//class Bot;

class SernaBot : public Bot{

public:
	void setup();
	void advance(float speed, float rotAngle);
	void advance();
	void rotateR();
	void rotateL();
	void recoil();
	void stop();

};
