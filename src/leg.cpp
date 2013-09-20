/*
 *  leg.cpp
 *  bot
 *
 *  Created by Sergio Bromberg Dimaté on 20/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "leg.h"

void Leg::calcularAngulos(float x, float y, float z, float w){
        float xPrima = sqrt( x*x + y*y);
        float yPrima = z;
	
	float cabeceo = w * PI/180;
	
	float afx = cos(cabeceo) * lMun;
	float afy = sin(cabeceo) * lMun;
	
	float ladoX  = xPrima - afx;
	float ladoY  = yPrima - afy - offset.x ;
	
	float hipotenusa  = sqrt( ladoX*ladoX + ladoY*ladoY );
	
	//  println("HIPOTENUSA " + hipotenusa);
	float alfa    = atan2   (ladoY, ladoX);
	float beta    = acos    ( ( lBrazo*lBrazo - lAntebrazo*lAntebrazo + hipotenusa*hipotenusa ) / ( 2 * lBrazo * hipotenusa) );
	float gama    = acos    ( ( lBrazo*lBrazo + lAntebrazo*lAntebrazo - hipotenusa*hipotenusa ) / ( 2 * lBrazo * lAntebrazo) );
	
	cout << "alfa "<< alfa << endl;
	cout << "beta " << beta << endl;
	cout << "game " << gama << endl;
	//angulos en grados
	
	angBrazo    = (alfa + beta);
	angAntebrazo   = (-( PI - gama));
	angMun    = cabeceo - angBrazo - angAntebrazo;
	angGiro     = atan2(y, x);
}

void Leg::moveTo(float x, float y, float z, float w){
	calcularAngulos(x, y, z, w);
	
	// CALIBRACION SUCIA 
	// Angulos en radianes, hay que convertir a milisegundos
	// Vamos a suponer por ahora que la mínima es 1000, y la máxima, 2000, ver http://www.servodatabase.com/servo/hitec/hs-5745mg
	// angulos en radiantes
	
	//Brazo
	cout << " 1 " << endl;
	float pulseWidth1 = angBrazo/PI*1000 + 1000;
	cout << " 2 " << endl;
	servocontroller->servoMove(1, 1500 );
	cout << " 3 " << endl;
	//Antebrazo
	float pulseWidth2 = angAntebrazo/PI*1000 + 1500;
	servocontroller->servoMove(2, 1500 );
	
	//Muñeca
	float pulseWidth3 = angMun/PI*1000 + 1500;
	servocontroller->servoMove(3, 1500);
}

