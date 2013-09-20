/*
 *  leg.h
 *  bot
 *
 *  Created by Sergio Bromberg Dimaté on 20/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */
#include "SSC32.h"
#include "ofMain.h"

class Leg{

public:
	Leg(){}
	void setServocontroller( SSC32 * _servoControllerFromParent ){
		servocontroller = _servoControllerFromParent;
	}
	
	void setSize( float _lBrazo, float _lAntebrazo, float _lMun){
		lBrazo = _lBrazo;
		lAntebrazo = _lAntebrazo;
		lMun = _lMun;
	}

	void setOffset(ofVec3f _offset){
	  offset.set(_offset);
	}
	
	void calcularAngulos(float x, float y, float z, float w);
	void moveTo(float x, float y, float z, float w);
	

	// zero offset
	ofVec3f offset; 
	
	// Lengths of arm
	float lBrazo;
	float lAntebrazo;
	float lMun;
	
	// Angulo 
	float angBrazo;
	float angAntebrazo;
	float angMun;
	float angGiro;
	
	//float cabeceo;
	
	SSC32 *servocontroller;
	
	

};

