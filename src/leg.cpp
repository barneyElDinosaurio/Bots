/*
 *  leg.cpp
 *  bot
 */
 
#include "leg.h"
/*
Leg::Leg()
{

	grad = 180/PI;
	rad = PI/180;
	inv = false;
	ruido = false;

}*/

void Leg::calcularAngulos(float x, float y, float z, float w){


	if ((posFin.x != x) || (posFin.y != y) || (posFin.z != z)) {

		posFin.set(x,y,z);

	    float xPrima = sqrt( x*x + y*y);
	    float yPrima = z;

		bool menos = false;
	    bool mas = false;
    	int repeat=0;

        while ( (menos == true) || (mas == true) || (repeat == 0)) {

			float cabeceo = w * rad;


			float afx = cos(cabeceo) * lMun;
			float afy = sin(cabeceo) * lMun;

			float ladoX  = xPrima - afx;
			float ladoY  = yPrima - afy - offset.x ;

			float hipotenusa  = sqrt( ladoX*ladoX + ladoY*ladoY );

			//  println("HIPOTENUSA " + hipotenusa);
			float alfa    = atan2   (ladoY, ladoX);
			float beta    = acos    ( ( lBrazo*lBrazo - lAntebrazo*lAntebrazo + hipotenusa*hipotenusa ) / ( 2 * lBrazo * hipotenusa) );
			float gama    = acos    ( ( lBrazo*lBrazo + lAntebrazo*lAntebrazo - hipotenusa*hipotenusa ) / ( 2 * lBrazo * lAntebrazo) );

			// cout << "alfa "<< alfa << endl;
			// cout << "beta " << beta << endl;
			// cout << "game " << gama << endl;
			//angulos en grados

			angBrazo    = (alfa + beta);
			angAntebrazo   = (-( PI - gama));
			angMun    = cabeceo - angBrazo - angAntebrazo;
			angGiro     = atan2(y, x);

	        if (inv) {
	          angGiro = - angGiro;
	        }

	        repeat +=1;

	        if  ( angMun*grad < -90 ) {
	          menos = true;
	          mas = false;
	          cabeceo=cabeceo * grad + 1;
	        }
	        else if (angMun*grad > 90) {
	          mas = true;
	          menos=false;
	          cabeceo=cabeceo * grad - 1;
	        }
	        else {
	          mas = false;
	          menos=false;
	        }
        }
	}
/*	falta crear el saveAng	**************************************************/
	saveAng();
}

//no se   que suceda con los Strings!!!**********************************
void Leg::saveAng() {


	//ASI NO SE LLENA UN STRING EN C++
		/*string strGiro = "" + angGiro;
		string strBrazo = "" + angBrazo;
		string strAntebrazo = "" + angAntebr;
		string strMun = "" + angMun;*/



	if ((angGiro != angGiro) || (angBrazo != angBrazo) || (angAntebrazo != angAntebrazo) || (angGiro != angGiro))
	{
		cout << "triplehpta" << endl;
	}
	else {
		angulos[0] = angGiro;
	  	angulos[1] = angBrazo;
		angulos[2] = angAntebrazo;
	  	angulos[3] = angMun;
	}
}

float Leg::rad2Pulse(float x){

	x = (x * grad) + 90.0;

	float maxPulse = 1800;
	float minPulse = 640;

	float maxAng = 140;
	float minAng = 40;


	float m = (maxPulse - minPulse) / ( maxAng - minAng) ;
	float b = minPulse - (m * minAng);
	float y = (m*x)+b;

	return(y);
}

void Leg::moveTo(float x, float y, float z, float w){
	calcularAngulos(x, y, z, w);

	// CALIBRACION SUCIA
	// Angulos en radianes, hay que convertir a milisegundos
	// Vamos a suponer por ahora que la mínima es 1000, y la máxima, 2000, ver http://www.servodatabase.com/servo/hitec/hs-5745mg
	// angulos en radiantes

	//Brazo
	
	//servocontroller->servoMove( , rad2Pulse() );
	servocontroller->servoMove( 0, rad2Pulse( angGiro ) );
	servocontroller->servoMove( 1, rad2Pulse( angBrazo ) );
	servocontroller->servoMove( 2, rad2Pulse( angAntebrazo) );
	servocontroller->servoMove( 3, rad2Pulse( angMun ) );


	/*********** escrito por sergio*********//*
		
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
	*/
}