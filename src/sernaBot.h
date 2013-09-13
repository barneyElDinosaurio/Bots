/*
 *  sernaBot.h
 *  bot
 *
 *  Created by Sergio Bromberg Dimaté on 6/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "bot.h"
#include "wiringPi.h"
#include "wiringSerial.h"

class sernaBot : public Bot{

public:
	void setup();
	void advance(float speed, float rotAngle);
	void advance();
	void rotateR();
	void rotateL();
	void recoil();
	void stop();

};
