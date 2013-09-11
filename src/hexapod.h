/*
 *  hexapod.h
 *  bot
 *
 *  Created by Sergio Bromberg Dimaté on 6/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "bot.h"

class hexapod : public Bot{

public:	
	hexapod();
	void advance( float speed, float rotAngle);
	void rotate(float angle);
	void advance();
	void stop();
	
};