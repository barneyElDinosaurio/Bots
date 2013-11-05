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


	if ((posFin.x != x) || (posFin.y != y) || (posFin.z != z)|| (cabeceo != (w * rad) ) ) {

		posFin.set(x,y,z);
		cabeceo = w * rad;
	
	    float xPrima = sqrt( x*x + y*y);
	    float yPrima = z;

		bool menos = false;
	    bool mas = false;
    	int repeat=0;

        while ( (menos == true) || (mas == true) || (repeat == 0)) {

		//	float cabeceo = w * rad;


			float afx = cos(cabeceo) * lMun;
			float afy = sin(cabeceo) * lMun;

			float ladoX  = xPrima - afx;
			float ladoY  = yPrima - afy - lAltura ;

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
	          cabeceo = cabeceo + (1 * rad);
	        }
	        else if (angMun*grad > 90) {
	          mas = true;
	          menos=false;
	          cabeceo = cabeceo - (1 * rad);
	        }
	        else {
	          mas = false;
	          menos=false;
	        }
        }
	}
/*	falta crear el savePulse	**************************************************/
	savePulse();
}

//no se   que suceda con los Strings!!!**********************************
void Leg::savePulse() {


	//ASI NO SE LLENA UN STRING EN C++
		/*string strGiro = "" + angGiro;
		string strBrazo = "" + angBrazo;
		string strAntebrazo = "" + angAntebr;
		string strMun = "" + angMun;*/



	if ((angGiro != angGiro) || (angBrazo != angBrazo) || (angAntebrazo != angAntebrazo) || (angMun != angMun))
	{
		cout << "no alcanza llegar al destino " << endl;
	}
	else {
	cout << "empezando a guardar pulsos " << endl;
		pulsos[0] = rad2Pulse ( angGiro 	);
	  	pulsos[1] = rad2Pulse ( angBrazo 	);
		pulsos[2] = rad2Pulse ( angAntebrazo);
	  	pulsos[3] = rad2Pulse ( angMun 		);
	}
}

int Leg::rad2Pulse(float x){


//quizas deberia no colocar este mas 90.0.... debug aqui PENDIENTE...
	x = (x * grad) + 90.0;

	float maxPulse = 1800;
	float minPulse = 640;

	float maxAng = 140;
	float minAng = 40;


	float m = (maxPulse - minPulse) / ( maxAng - minAng) ;
	float b = minPulse - (m * minAng);
	int y =(int)((m*x)+b);

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

	servocontroller->servoMove( 0, pulsos[0] );
	servocontroller->servoMove( 1, pulsos[1] );
	servocontroller->servoMove( 2, pulsos[2] );
	servocontroller->servoMove( 3, pulsos[3] );
}

void Leg::moveTimeTo(float x, float y, float z, float w, int tiempo){
cout << "entrando a moveTimeTo()..." << endl;
	calcularAngulos(x, y, z, w);
cout << "calculo de angulos aprobado.... "<<  endl;


// por motivos de tiempo y para tirar sucioas esto queda descartado hasta nueva orden
//cout << "los argumentos " << pulsos[0] << " tiempo " << tiempo << endl:
//		cout << "brebebrebr" << endl;
//	  servocontroller->servoMoveTime( 0, pulsos[0], tiempo );
	//servocontroller->servoMoveTime( 1, pulsos[1], tiempo );
	//servocontroller->servoMoveTime( 2, pulsos[2], tiempo );
	//servocontroller->servoMoveTime( 3, pulsos[3], tiempo );
}


float Leg::printPulse (int in){
	return ( pulsos[in] );
}
