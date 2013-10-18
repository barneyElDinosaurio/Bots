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

#ifndef MOVER_H
#define MOVER_H
#include "mover.h"
#endif


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
	void updateMovement();
	
	
	float sensorHumedad; // Tenemos que cambiarles factores de escala para hacerlos comparables.
	float sensorLuz;
	float necesidadCal;
	
	Timer elTimer;

	// MOVIMIENTO
	Timer movementTimer;
	ofVec2f destino; // ojo con la inicialización.
	
	// Calibracion
	Timer timerCal;
	bool firstTimeCal;
	
	float tiempoDeAvance;
	// Cosillas sucioas
	
	ofVec2f bebedero; // En la clase general??? Es decir, en BOt?
	
	//int serialNumber;

	Mover mover;
//	float 

};
