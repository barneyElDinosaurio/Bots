/*
 *  sernaBot.h
 *  bot
 *
 *  Created by Sergio Bromberg Dimaté on 6/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */



//intento de i2c
#include <wiringPiI2C.h>


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
	void startLinearMovement();
	void setDestino(float x, float y);
	float angle2Time(float angle);
	
	
	float sensorHumedad; // Tenemos que cambiarles factores de escala para hacerlos comparables.
	float sensorLuz;
	float necesidadCal;
	
	Timer elTimer;

	//***************
	// MOVIMIENTO
	//***************

	Timer movementTimer;
	ofVec2f destino; // ojo con la inicialización.
	ofVec2f lastStopPos;

	//bool isStatic; // Lo mandé a BOT

	int movementStatus;
	int linear; // Poner como defines
	int rotation; // Poner como defines


	float beforeAngle; 
	float timeAngleCalFactor; // Conversión radianes -> tiempo de rotación

	float anguloDeEvasion;


	//***************
	// OTRAS COSAS
	//***************
	// Calibracion

	Timer timerCal;
	bool firstTimeCal;
	
	float tiempoDeAvance;
	// Cosillas sucioas
	
	ofVec2f bebedero; // En la clase general??? Es decir, en BOt?
	
	
	// SERIAL

	int fdS; // device identifier
	bool stringComplete; // Para saber si ya terminó la línea
	string serialData;

	//intento i2c...........................................................PENDIENTE
	int fd;
	int byte1;
	int byte2;
	int angulo;

    // distancia medida por el sensor de prox (en cm)
    float distancia;
};
