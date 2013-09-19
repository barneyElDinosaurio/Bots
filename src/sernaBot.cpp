/*
 *  sernaBot.cpp
 *  bot
 *
 *  Created by Sergio Bromberg Dimaté on 6/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "sernaBot.h"

void SernaBot::setup(){
	cout << "SernaBot: inicializando..." << endl;
	// Setup de la clase padre ??
	//(Bot*) setup();
	( (Bot* )this)->setListeningPort(9000);
	
	// Tipo de bot
	botType = "sernaBot";
	
	
	//Setear wiringPI
	wiringPiSetup();
	pinMode(15, OUTPUT);
	pinMode(16, OUTPUT);
	pinMode(1, OUTPUT);
	pinMode(4, OUTPUT);
	
}
void SernaBot::update(){
	((Bot* )this)->update(); // Aquí adentro están los recibidores de osc.
}
void SernaBot::advance(){
	cout << " SERNAPODO: En la funcion de avanzar " << endl;
	digitalWrite(15, HIGH);
	digitalWrite(16, LOW);
	digitalWrite(1, HIGH);
	digitalWrite(4, LOW);
	
	
}

void SernaBot:: recoil(){
	
	digitalWrite(15, LOW);
	digitalWrite(16, HIGH);
	digitalWrite(1, LOW);
	digitalWrite(4, HIGH);
	
}

void SernaBot::rotateR(){
	
	digitalWrite(15, LOW);
	digitalWrite(16, HIGH);
	digitalWrite(1, HIGH);
	digitalWrite(4, LOW);
	
}
void SernaBot::rotateL(){

	digitalWrite(15, HIGH);
	digitalWrite(16, LOW);
	digitalWrite(1, LOW);
	digitalWrite(4, HIGH);
}

void SernaBot::stop(){
	digitalWrite(15, LOW);
	digitalWrite(16, LOW);
	digitalWrite(1, LOW);
	digitalWrite(4, LOW);
	
}
