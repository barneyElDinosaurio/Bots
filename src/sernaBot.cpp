/*
 *  sernaBot.cpp
 *  bot
 *
 *  Created by Sergio Bromberg Dimaté on 6/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "sernaBot.h"

void SernaBot::setup(){
	
	cout << "SernaBot: inicializando..." << endl;
	
	// Setup de la clase padre ??
	//(Bot*) setup();
	
	int port = 9001;
	cout << "tratando de conectar al puerto " << port << endl;
	( (Bot* )this)->setListeningPort(9001);
	
	// Track size
	( (Bot* )this)->setTrackSize(30);
	
	
	// Tipo de bot
	botType = "sernaBot";
	
	//Setear wiringPI
	wiringPiSetup();
	pinMode(15, OUTPUT);
	pinMode(16, OUTPUT);
	pinMode(1, OUTPUT);
	pinMode(4, OUTPUT);
	
	// Medir inicialmente el valor de los sensores.
	sensorHumedad = 0;
	sensorLuz = 0;
	necesidadCal = 1; // Primero necesita calibrarse
	
	//modo = "calibracion";
	modos.push_back("relajado");
	modos.push_back("sediento");
	modos.push_back("calibracion");
	
	
	// BEbedero y otras suciedades
	
	bebedero.set(0.3, 0.3);
	elTimer.start();
	tiempoDeAvance = 400;
	
	// Calibracion
	firstTimeCal = true;
}
void SernaBot::update(){
	((Bot* )this)->update(); // Aquí adentro están los recibidores de osc.
	
	// Encontrar el máximo de las necesidades
	
	float necesidades [] = {sensorHumedad, sensorLuz, necesidadCal }; // Es importante que estén en el mismo orden en modos!!!
	
	// Brujería para encontrar el máximo de las necesidades
	const int N = sizeof(necesidades) / sizeof(float);
	
	float  maxIndex = distance( necesidades, max_element(necesidades, necesidades + N));
	
	modo = modos.at(maxIndex);
	
	cout << "Estoy en modo --- > " << modo << endl;
	
	if( modo == "relajado"){
		//cout << "estoy relajado" << endl;
	}
	else if(modo == "sediento"){
		goTo( bebedero.x, bebedero.y );
	}
	else if(modo == "calibracion"){
		calibrate();
	}
	
	
	
	
	
	
}

void SernaBot::goTo(float x, float y){
	if(elTimer.getTime() > tiempoDeAvance ){
		ofVec2f pos = ((Bot * )this)->getPos();
		
		float deltaAngulo = pos.angle( bebedero );
		cout << "angulo Diff" << endl;
		
		
		elTimer.restart();
	}
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
	  cout << "En el chequeador de no nulos***********************" << endl;
	  if( trackedPos != ofVec2f(0, 0) ){
	    posicionInicial.set(trackedPos);
	    posicionFinal.set(lastPos.back());
	    cout << "La posición inicil ************************** " << posicionInicial << endl;

	    break;
}

}		
	stop(); // Parar el man
		necesidadCal = 0; //salir de modo calibracion 
		timerCal.stop();
		posicionFinal = lastPos.back(); // Tambien podría sacarla con papa->getPos
	cout << "CALIBRACION TERMINADA ------------  POSINIT: "<< posicionInicial << " POSFINAL: " << posicionFinal << "  ANGULO: " << elAngulo << endl;
	
		
	}
	
	
	ofVec2f deltaPos = posicionFinal - posicionInicial;
	float elAngulo = deltaPos.angle( ofVec2f(1,0) ); // Angulo con respecto al eje x.
	papa->setAngle( elAngulo );
	
	
	
	
	
}
void SernaBot::advance(){
	cout << " SERNAPODO: En la funcion de avanzar " << endl;
	digitalWrite(15, HIGH);
	digitalWrite(16, LOW);
	digitalWrite(1, HIGH);
	digitalWrite(4, LOW);
	
	
}

void SernaBot:: recoil(){
	
	digitalWrite(15, LOW);
	digitalWrite(16, HIGH);
	digitalWrite(1, LOW);
	digitalWrite(4, HIGH);
	
}

void SernaBot::rotateR(){
	
	digitalWrite(15, LOW);
	digitalWrite(16, HIGH);
	digitalWrite(1, HIGH);
	digitalWrite(4, LOW);
	
}
void SernaBot::rotateL(){
	
	digitalWrite(15, HIGH);
	digitalWrite(16, LOW);
	digitalWrite(1, LOW);
	digitalWrite(4, HIGH);
}

void SernaBot::stop(){
	digitalWrite(15, LOW);
	digitalWrite(16, LOW);
	digitalWrite(1, LOW);
	digitalWrite(4, LOW);
	
}
