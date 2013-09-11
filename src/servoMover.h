/*
 *  servoMover.h
 *  bot
 *
 *  Created by Sergio Bromberg Dimaté on 6/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofMain.h"
class servoMover{
	
public:
	void moveServo(int numServo, float angle, float time);
	void initSerial( string terminal , int baudRate);
};