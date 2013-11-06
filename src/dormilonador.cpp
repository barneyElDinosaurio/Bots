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
	botType = "dormilonador";
	
	((Bot*)this)->setListeningPort(9001);
	servocontroller.begin(9600);
	
	// LEG // MEDIR CORRECTAMENTE !!!
	brazo.setServocontroller(&servocontroller);
	brazo.setSize(6, 12.5, 16, 8);
	//especificando que el angMun es inverso....
	brazo.setInv(3,true);
	brazo.setOffset( ofVec3f( 0, 0, 6) );

	cout << "EN EL SETUP DEL DORM" << endl;
	
}
void Dormilonador::meterEnVaso(){
	servocontroller.servoMove(2, 1500);
}
void Dormilonador::update(){
	((Bot*)this)->update();
}
