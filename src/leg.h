/*
 *  leg.h
 *  bot
 */

#include "SSC32.h"
#include "ofMain.h"

class Leg{

public:
	Leg(){
		grad = 180/PI;
        rad = PI/180;
        inv = false;
        ruido = false;
        //esto creo q va a llorar
        pulsos[4];
	}

	void setServocontroller( SSC32 * _servoControllerFromParent ){
		servocontroller = _servoControllerFromParent;
		servocontroller->_commandType = SSC32_CMDGRP_TYPE_NONE;
		servocontroller->_ttcm = -1;
	}

	void setSize(float _lAltura, float _lBrazo, float _lAntebrazo, float _lMun){
		lAltura = _lAltura;
		lBrazo = _lBrazo;
		lAntebrazo = _lAntebrazo;
		lMun = _lMun;
	}

	void setOffset(ofVec3f _offset){
	  offset.set(_offset);
	}



void calcularAngulos(float x, float y, float z, float w);
void moveTo(float x, float y, float z, float w); // un toque modificada....

//NUEVOS METODOS
void moveTimeTo(float x, float y, float z, float w, int tiempo);



void setInv(bool invertir){
    inv = invertir;
}
void setInv(){
    inv = !inv;
}
void savePulse();

int rad2Pulse(float x);

// funcion de float!! si retorna el flotante??
float* printPulse() {
    return(pulsos);
  }
float  printPulse (int in);

// zero offset
	ofVec3f offset;

//Variables de conversion
	float rad;
	float grad;

// Lengths of arm
	float lAltura;
	float lBrazo;
	float lAntebrazo;
	float lMun;
	float cabeceo;
// Angulo
	float angBrazo;
	float angAntebrazo;
	float angMun;
	float angGiro;

	//ALgunos booleanos nuevos
	bool inv ;
	bool ruido ;

	//un pequeño array q quizas joda bastante
	float pulsos[];

	ofVec3f posFin;

	//float cabeceo;

	SSC32 *servocontroller;
};
