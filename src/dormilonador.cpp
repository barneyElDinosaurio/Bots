/*
 *  dormilonador.cpp
 *  bot
 *
 *  Created by Sergio Bromberg Dimaté on 19/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef DORMILONADOR_H
#define DORMILONADOR_H
#include "dormilonador.h"
#endif


void Dormilonador::setup(){
	
	// Setup de la clase padre?
	//((Bot* )this )->setup();
	
	((Bot*)this)->setListeningPort(9000);
	servocontroller.begin(9600);
	
}
void Dormilonador::meterEnVaso(){
	servocontroller.servoMove(2, 1500);
}