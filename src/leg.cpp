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

