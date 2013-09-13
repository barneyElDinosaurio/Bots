/*
 *  sernaBot.cpp
 *  bot
 *
 *  Created by Sergio Bromberg Dimaté on 6/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "sernaBot.h"

void setup::setup(){
	
	//Setear wiringPI
	wiringPiSetup();
	int serialFlag  = serialOpen("/dev/ttyAMA0",9600);
	
	cout << "Se ha conectado al puerto serial número: " << endl;
}
void sernaBot::advance(float speed, float rotAngle){

}

void sernaBot::advance(){

}

void sernaBot::rotate(float rotAngle){

}
