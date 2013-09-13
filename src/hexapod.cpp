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


hexapod::hexapod(){
	//startSerial();
}
void hexapod::setup(){
	servocontroller.begin(9600);
}
void hexapod:: advance( float speed, float rotAngle){

}
void hexapod::mandarUnDato(){
	servocontroller.mandarUnDato();
}

void hexapod:: rotate( float angle ){

}

void hexapod:: advance(){

}

void hexapod:: stop(){

}