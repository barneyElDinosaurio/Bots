/*
 *  sernaBot.h
 *  bot
 *
 *  Created by Sergio Bromberg Dimaté on 6/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */


#include "wiringPi.h"
#include "wiringSerial.h"

#ifndef BOT_H
#define BOT_H
#include "bot.h"
#endif

#include "timer.h"

//class Bot;

class SernaBot : public Bot{

public:
	void setup();
	void advance(float speed, float rotAngle);
	void update();
	void advance();
	void rotateR();
	void rotateL();
	void recoil();
	void stop();
	void goTo( float x, float y);
	void advanceTime(float time);
	void calibrate();
	
	
	// Sensores y modos
	
	string modo;
	vector <string> modos;
	
	
	float sensorHumedad; // Tenemos que cambiarles factores de escala para hacerlos comparables.
	float sensorLuz;
	float necesidadCal;
	
	Timer elTimer;
	
	// Calibracion
	Timer timerCal;
	bool firstTimeCal;
	
	float tiempoDeAvance;
	// Cosillas sucioas
	
	ofVec2f bebedero; // En la clase general??? Es decir, en BOt?
	
	
//	float 

};
