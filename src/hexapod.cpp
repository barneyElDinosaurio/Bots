/*
 *  hexapod.cpp
 *  bot
 *
 *  Created by Sergio Bromberg Dimaté on 6/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "hexapod.h"

/*
 void advance( float speed, float rotAngle);
 void rotate(float angle);
 void advance();
 void stop();

*/

#ifndef BOT_H
#define BOT_H
#include "bot.h"
#endif
Hexapod::Hexapod(){
	//startSerial();
}
// PONER EL UPDATE DE ESTE MAN.
void Hexapod::setup(){
	servocontroller.begin(9600);
	((Bot*)this)->setListeningPort(9000);
	botType = "hexapod";
}
void Hexapod:: advance( float speed, float rotAngle){

}
void Hexapod::mandarUnDato(){
	servocontroller.mandarUnDato();
}

void Hexapod:: rotate( float angle ){

}

void Hexapod:: rotateR(){

}

void Hexapod:: rotateL(){


}

void Hexapod:: advance(){

}

void Hexapod:: recoil(){

}
void Hexapod:: stop(){

}