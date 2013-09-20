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
	// zero offset
	ofVec2f offset; 
	
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
	
	
	void setSize( float _lBrazo, float _lAntebrazo, float _lMun){
		lBrazo = _lBrazo;
		lAntebrazo = _lAntebrazo;
		lMun = _lMun;
	};
	
	void calcularAngulos(float x, float y, float z, float w);
	
	
	
	
	

};

