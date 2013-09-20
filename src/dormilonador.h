/*
 *  dormilonador.h
 *  bot
 *
 *  Created by Sergio Bromberg Dimaté on 19/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

//#include 
#ifndef BOT_H
#define BOT_H
#include "bot.h"
#endif

#include "SSC32.h"

class Dormilonador: public Bot{

	
	void setup();
	void meterEnVaso();
	SSC32 servocontroller;
	
};