/*
 *  sernaBot.cpp
 *  bot
 *
 *  Created by Sergio Bromberg Dimaté on 6/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "sernaBot.h"

#ifndef MODE_H
#define MODE_H
#include "mode.h"
#endif

# define TUIO // no lo he usado todavía
void SernaBot::setup(){
	
	cout << "SernaBot: inicializando..." << endl;
	
	// Setup de la clase padre ??
	//( (Bot*)this)->Bot();
	
	// ***COSAS DE LA CLASE PADRE QUE PEGUÉ AQUÍ...


	vision = "camara";
	cout << "Visión :: " << vision << endl;
		// No está perdido en principio.
	isLost = false;


		// MODOS Y VAINAS
		modo = "inicial"; // Tengo que poner esto momentáneamente... creo
		chooseMode(); // Para elegir inicialmente un modo.
		firstTimeInMode = true;
		tiempoDeBebida = 5000; // En milisegundos... medio charro...
		tiempoDePausa = 10000;


		//      LUGARES:
		bebedero.set(0.8, 0.8);
		cargadero1.set(0.8, 0.3);

		//**** AQUI CIERRAN



	int port = 9001;
	cout << "tratando de conectar al puerto " << port << endl;
	( (Bot* )this)->setListeningPort(9001);
	
	// Track size
	( (Bot* )this)->setTrackSize(30);
	
	
	// Tipo de bot
	botType = "sernaBot";
	
	//Setear wiringPI
		
	wiringPiSetup();
	
	//intento i2c......................................................................
	//fd = wiringPiI2CSetup(0x21);
	
	pinMode(1, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);

	//SERIAL
	fdS  = serialOpen("/dev/ttyAMA0", 38400);
	
	cout << "Se ha conectado al puerto serial número: " << fdS << endl;

	
	// Medir inicialmente el valor de los sensores.
	// YA ES INUTIL
	sensorHumedad = 0;
	sensorLuz = 0;
	necesidadCal = 1; // Primero necesita calibrarse
	
	//modo = "calibracion";
    modos.push_back( Mode( "relajado" , 0.5 ) );
	modos.push_back( Mode( "sediento" , 0.6) );
	modos.push_back( Mode( "calibracion" , 0.5) );
	
	
	// BEbedero y otras suciedades
	
	//bebedero.set(0.9, 0.9);
	cout << "EL bebedero está en ==================="  << bebedero << endl;
	elTimer.start();
	tiempoDeAvance = 400;
	
	// Calibracion
	firstTimeCal = true;

	// ************
	//  MOVIMIENTO
	// ************

	linear = 0 ;
	rotation = 1; // Poner como defines
	// defined rotation

	movementStatus = linear; // ¿Cómo inicializar?

	movementThreshold = 0.1;
	isStatic = false; // Seguro????
	timeAngleCalFactor = /*1*/0.6 * 1000 / ( 1.42 * 180/PI ) ; //segundos por radián [cronometrado suciamente cuando tenía adaptador]


	anguloDeEvasion = 180;

	// inicializar la distancia grande, por si jode...
	distancia = 100;

	// COLOR DEL BLOB !!!
	// No sé si sea correcto setearlos así inicialmente...
	h = 0;
	s = 0;
	v = 0; 

}
void SernaBot::update(){

	// Antes de recibir OSC, borre el registro de los obstáculos que tiene. Un día hacemos tracking, para que sepa donde estaban ayer...
	obstaculos.clear();
	((Bot* )this)->update(); // Aquí adentro están los recibidores de osc.
	
	// Encontrar el máximo de las necesidades
	float necesidades [modos.size()];//= new float[  ]; 
	for( int i = 0 ; i < modos.size() ; i++){
		necesidades[i] = modos.at(i).sensorValue;

		if( showNecesidades == true ){
			cout << "necesidad "  << modos.at(i).mode << "   ... " << modos.at(i).sensorValue << endl; 
		}
	}
	// **************
	//    SERIAL    *
	//***************

	while ( serialDataAvail (fdS) > 0)
    { //cout << "available: " << serialDataAvail(fdS) << endl;
      //cout << serialGetchar (fdS) << endl;
      char c = serialGetchar(fdS);
      //cout << "recibí ..." << c.c_str() << endl;

      // Conversion a string luego a float:
      serialData += c;
      if(c == '\n'){ // String complete
        stringComplete = true;

      }

      // Conversión de prueba
      if( stringComplete){
        //cout << "en el string complete con :: " << serialData << endl;
        //cout << "Brújula mirando hacia :: " << serialData << endl;
        //cout << ".... Te gané brújula malparida !!!!!!!!!!!" << endl;
        
        vector <string> losStrings = ofSplitString(serialData, " ");

        //cout << "tamaño de los strings" << losStrings.size() << endl;

        //cout << "Los strings son : " << endl;

        /*for(int i = 0 ; i < losStrings.size() ; i++){
        	cout << i << ":: "<< losStrings.at(i) << endl;
        }*/
        if( losStrings.size() == 2){ // interpretable

        	if(losStrings.at(0) == "brujula"){

        		angle = ofToFloat(losStrings.at(1));
        		cout << "Angulo [RAW]" << angle << endl;
        		angle = angle - 230.0f; //Le resto el cero.
        		cout << "Angulo brujula [DEG]" << angle << endl; 
        		angle = ofDegToRad(angle);

        		if( ofRandom(1) < 0.1 ){ cout << "Angulo brujula [RAD]" << angle << endl; }
        	}
        	if( losStrings.at(0) == "distancia"){
        		distancia = ofToFloat( losStrings.at(1) );
        		//cout << "Distancia " << distancia << endl;

        	}

        }
        // Reset de las cositas para recibir
        serialData = "";
        stringComplete = false;
      }

    }

    /*string s("0.001");
    float a = atof(s.c_str());
    cout << "El float de prueba es : " << a << endl;
    */
    ofSleepMillis(10);

    
	
	
	//------------------
	// ESTA ES LA PARTE JUGOSA!!!

	//if( ofRandom(1) < 0.1 ){ cout << "A ver los modos pues... MODO = " << modo << endl; }
	//-----------------	

    if(controlledMotion == false){
    	if(modo == "sediento"){

    		cout << "TimerSediento "  <<  timerSediento.getTime() << endl;

    		if(firstTimeInMode){
    			cout << "En el modo de beber" << endl;
    			timerSediento.start();
    			goTo(bebedero.x, bebedero.y);
    			firstTimeInMode = false;
    		}
    		else if( timerSediento.getTime() > 5000){
    			chooseMode();
			//timerSediento.stop();
    		}

    	}
    	if( modo == "parar"){
		//chooseMode();
    		cout << "Parado, como un miembro ..." << endl;
		//timerParado.start();
    		cout << "Timer pàradp " << timerParado.getTime() << endl;

    		if( firstTimeInMode ){
    			stop();
    			isStatic = true;
    			timerParado.start();
    			firstTimeInMode = false;
    		}
    		else if( timerParado.getTime() > 5000) {
    			cout << "ME voy a salir de PARADO" << endl;
    			chooseMode();
    			isStatic = false;
    			timerParado.stop();
    		}
    	}
    	else if( modo == "cargar"){

    		cout << "TimerCarga "  <<  timerCarga.getTime() << endl;

    		if(firstTimeInMode){
    			cout << "En el modo de cargar" << endl;
    			timerCarga.start();
    			goTo( cargadero1.x, cargadero1.y);
    			firstTimeInMode = false;
    		}
    		else if( timerCarga.getTime() > 5000){
    			chooseMode();
    			timerCarga.stop();
		}// MODS
		if( pos.distance( cargadero1 ) < 0.1 ){

			cout << "YA LLEGUE" << endl;
			//exit();
			ofSleepMillis(3000);
		}
	}
	else if(modo == "cangri"){

		cout << "TimerCangri "  <<  timerCangri.getTime() << endl;

		if(firstTimeInMode){
			cout << "En el modo de Cangri " << endl;
			timerCangri.start();
			//goTo( cargadero1.x, cargadero1.y);
			firstTimeInMode = false;
		}

		else if( timerCangri.getTime() > 5000){
			chooseMode();
			//timerCangri.stop();
		}// MODS

		if( timerCangri.getTime() < 2000){
			rotateL();
			ofSleepMillis(110);
			rotateR();
			ofSleepMillis(110);
		}

	}
	
	
	//mover.updateAngle();

	
}
	
	
	updateMovement();
}
void SernaBot::updateMovement(){


	if( reportObstacles == true){
		cout << "______________________" << endl;
		cout << "Número de obstáculos = " << obstaculos.size() << endl;

		for(int i = 0 ; i < obstaculos.size() ; i++){
			cout << "Obs " << i << ": posX = " << obstaculos.at(i).x <<  ", posY = " << obstaculos.at(i).y << endl;

		}
		cout << "______________________" << endl;

	}
	// -------------------------
	//	PRIMER MODO DE MOVIMIENTO: LÍNEAS RECTAS...
	//________________________

	// FACTOR DE CALIBRACIÓN: (HABRÍA QUE HACER QUE FUERA DINÁMICO...):
	// 4.4s por vuelta entera = 1.42 rad / s

	// HAY QUE PONERLE UN MODO ** LOST ** !!!!

	if( isStatic == false ){ // Si no es estático

		// CALCULO DE LOS ÁNGULOS DE DESTINO
		// Calcular antes que nada la diferencia angular entre uno y el destino
				// Primero el vector que nos une con el destino
		ofVec2f deltaPos = destino - pos; 
		//cout << "Delta destino" << endl;

		float anguloGrados = angle*(180.0/PI);
		float anguloDeltaPos = - deltaPos.angle( ofVec2f(1,0)); // el ángulo entre este vector y el eje x.
		// cout << "mi Pos " << pos << endl;
		// cout << "mi Angulo en grados " <<  anguloGrados << endl;
		// cout << "destino " << destino << endl;
		// cout << "delta pos " << deltaPos << endl;
 	// 	cout << "El ángulo del delta Pos" << anguloDeltaPos; // en grados

 	// 	cout << "angulo restado " <<  anguloDeltaPos - anguloGrados << endl;
 		float angleDifference = ofAngleDifferenceDegrees(anguloDeltaPos, anguloGrados ); // ESte es el ángulo que tengo que rotar! ( o una constante por este ángulo)
		
		// OBSTACULOS:
 		bool colisionInminente = false;
 		for( int i = 0 ; i < obstaculos.size() ; i++){

 			float d =  pos.distance( obstaculos.at(i) );
 			cout << "Distancia con obstaculo " << d << endl;
 			
 			if( d < collisionDistance && colisionInminente == false){
 				cout << "Colision inminente " << endl;
 				colisionInminente = true; // Dejo esto por si voy a colisionar con más de una persona

 				// Detectar angulo con obstaculo
 				ofVec2f deltaPosObstaculo = obstaculos.at(i) - pos; // OJO con el signo!
 				float anguloDeltaPosObstaculo =  -deltaPosObstaculo.angle( ofVec2f(1,0) ); // Aqui le cambié el signo para que rote correctamente. 
 				float angleToObstacle = - ofAngleDifferenceDegrees( anguloDeltaPosObstaculo , anguloGrados );
 				cout << "Angulo con el obstáculo " << angleToObstacle << endl;

 				if( angleToObstacle > 0){ // Lo desvía brutalmente. Hay que notar que este ángulo de evasión no es real, sino que está ponderado por un factor (abgle2TimeFactor, o algo así)
 					angleDifference = anguloDeEvasion;
 				}
 				else {
 					angleDifference = -anguloDeEvasion;

 				}
 			}


 		}
 		
 		if(isLost == true && controlledMotion == false ){ //  Por si está perdido, rote si se va a estrellar.
 			cout << "navegando en modo perdido" << endl;
			cout<<"Distancia: "<<distancia<<" cm" <<endl;
 			float umbralDistancia = 40;
 			if( distancia < umbralDistancia){
 				// Aquí hay que navegarlo!!!
 				rotateL();
 				ofSleepMillis(3000);
 			}
 			else{
 				advance();
 			}

 		}
 		
 		// cout << "angulo con calculo OF" << angleDifference << endl;
 		// cout << "voy a rotar "<< angle2Time(angleDifference) << "segundos" << endl;
		
		if( movementStatus == linear && controlledMotion == false ){

			

			if( movementTimer.getTime() >  1000 ){ // definir T!
				stop(); // O tal vez cambiarlo de modo...
				cout << "Paré en el linear movement" << endl;
				movementStatus = rotation;
				movementTimer.restart();

				cout << "mi Pos " << pos << endl;
				cout << "mi Angulo en grados " <<  anguloGrados << endl;
				cout << "destino " << destino << endl;
				cout << "delta pos " << deltaPos << endl;
 				cout << "El ángulo del delta Pos" << anguloDeltaPos; // en grados

		 		cout << "angulo restado " <<  anguloDeltaPos - anguloGrados << endl;
 		
 				cout << "angulo con calculo OF" << angleDifference << endl;
 				cout << "voy a rotar "<< angle2Time(angleDifference) << "segundos" << endl;

				// Calcular el ángulo [En versión no TUIO]
				/*
				ofVec2f deltaPos = pos - lastStopPos; // la posición actual, menos la pos en la última parada
				float elAngulo = deltaPos.angle( ofVec2f(1,0) ); 
				ofxOscMessage m;
				m.setAddress( "/measuredAngle");
				m.addFloatArg( elAngulo );
				oscSender.sendMessage(m);
				*/

				if( angleDifference > 0){
					rotateL();
				}
				else {
					rotateR();
				}
			}
		} else if(movementStatus == rotation && controlledMotion == false ){
			if( movementTimer.getTime() > abs( angle2Time( angleDifference ) ) ){ // definir T! // ojo con el signo! tiene que ser positivo!
				stop();
				movementStatus = linear;
				movementTimer.restart();
				advance();
				lastStopPos.set(pos); // La posición justo antes de empezar a andar
			}


		}
		
	}

}
float SernaBot::angle2Time(float angle){
	return( angle * timeAngleCalFactor );

}
/*float SernaBot::rotateTo(float angle){


}*/

void SernaBot::startLinearMovement(){
// Timer restart?
// Static = false?

}
void SernaBot::goTo(float x, float y){
	cout << " Enviado a " << x << " " << y << endl;
	if(destino.distance( ofVec2f(x,y) ) > 0.1){
		isStatic = false;
		destino = ofVec2f( x , y );
		movementStatus = linear;
		movementTimer.restart();
		advance();
		cout << "nuevo destino " << x << " " << y << endl;
	}
}
void SernaBot::setDestino(float x , float y){

	destino = ofVec2f( x, y);
}
void SernaBot::calibrate(){
	// OJO: tendría que tener primero mi posición
	
	Bot* papa = (Bot*)this;
	//papa->update();
	
	
	if( firstTimeCal ){
		timerCal.start();
		advance();
		firstTimeCal = false;
		cout << "EMPEXANDO CALIBRACION ******************************* "<< endl;
	}
	
	cout << "EN CA CALIBRACION ******************************* "<< endl;
	cout << "**** 0 " << endl;
	ofVec2f posicionInicial;
	ofVec2f posicionFinal;
	if(timerCal.getTime() > 1000){
		
		// Agarrar primera posición no nula, y última posición.
		
		//ofVec2f trackedPos = lastPos.at(0);
		/*	while( trackedPos == ofVec2f( 0, 0)  ){
		  i++;			
		  trackedPos = lastPos.at(29);
		  posicionInicial.set(trackedPos);
		       
		  }*/

		  for(int i = 0 ; i < lastPos.size() ; i++){
		  	ofVec2f trackedPos = lastPos.at(i);
		  	cout << "En el chequeador de no nulos*********************** CON I = " << i << endl;
		  	if( trackedPos != ofVec2f(0, 0) ){
		  		posicionInicial.set(trackedPos);
	    // posicionFinal.set(lastPos.back());
		  		cout << "La posición inicil ************************** " << posicionInicial << endl;

		  		break;
		  	}

		  }		
		  cout << "**** 1 " << endl;
	stop(); // Parar el man

	//salir de modo calibracion 
	timerCal.stop();
	if( lastPos.size() > 0){
		posicionFinal = lastPos.back(); // Tambien podría sacarla con papa->getPos
		ofVec2f deltaPos = posicionFinal - posicionInicial;
	float elAngulo = deltaPos.angle( ofVec2f(1,0) ); // Angulo con respecto al eje x.
	papa->setAngle( elAngulo );
	cout << "Datos calibracion delta pos " << deltaPos << endl;
	cout << "CALIBRACION TERMINADA ------------  POSINIT: "<< posicionInicial << " POSFINAL: " << posicionFinal << "  ANGULO: " << elAngulo << endl;	
	cout << "SALIENDO GNRS" << endl;
	
	// Poner en 0 la necesidad de calibración
	necesidadCal = 0;
	int modoCal = 2;
	modos.at(modoCal).sensorValue = 0; // Esta muy sucio, cambiarlo por map.
	cout  << "Ya calibré, con modo: "  << modos.at( modoCal ).mode << endl;
	lastStopPos = posicionFinal;



	// Aquí debería poner que el destino sea la posición actual.
	// destino = posicionFinal;

}
	else{
		cout << " *********** IMPOSIBLE CALIBRAR *********** REINICIANDO CALIBRACION" << endl;
		cout << "[NO HAY REGISTRO DE UNA POSICIÓN ANTERIOR]" << endl;
		necesidadCal = 1;
		firstTimeCal = true;
	}
	
	
	//	exit();	
}







}
void SernaBot::advance(){
	
	cout << " SERNAPODO: En la funcion de avanzar " << endl;
	digitalWrite(1, HIGH);
	digitalWrite(4, LOW);
	digitalWrite(5, HIGH);
	digitalWrite(6, LOW);
	
	
}

void SernaBot::recoil(){

	cout << "retrocediendo wiring pi" << endl;
	digitalWrite(1, LOW);
	digitalWrite(4, HIGH);
	digitalWrite(5, LOW);
	digitalWrite(6, HIGH);
	
}

void SernaBot::rotateR(){
	
	cout << "rotateR wiring pi" << endl;

	digitalWrite(1, LOW);
	digitalWrite(4, HIGH);
	digitalWrite(5, HIGH);
	digitalWrite(6, LOW);
	
}
void SernaBot::rotateL(){
	
	digitalWrite(1, HIGH);
	digitalWrite(4, LOW);
	digitalWrite(5, LOW);
	digitalWrite(6, HIGH);
	
	cout << "rotateL wiring pi" << endl;
}

void SernaBot::stop(){
	digitalWrite(1, LOW);
	digitalWrite(4, LOW);
	digitalWrite(5, LOW);
	digitalWrite(6, LOW);
		
	cout << "stop wiring pi" << endl;
}
