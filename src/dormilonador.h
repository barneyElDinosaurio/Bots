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

#ifndef LEG_H
#define LEG_H
#include "leg.h"
#endif

#include "SSC32.h"


class Dormilonador: public Bot{

public:
	void setup();
	void meterEnVaso();
	void update();
	SSC32 servocontroller;
	
	Leg brazo;
	
};