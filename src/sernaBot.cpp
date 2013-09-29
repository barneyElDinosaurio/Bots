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
}
void SernaBot::update(){
	((Bot* )this)->update(); // Aquí adentro están los recibidores de osc.
	
	// Encontrar el máximo de las necesidades
	
	float necesidades [] = {sensorHumedad, sensorLuz, necesidadCal }; // Es importante que estén en el mismo orden en modos!!!
	
	// Brujería para encontrar el máximo de las necesidades
	const int N = sizeof(necesidades) / sizeof(float);
	
	float  maxIndex = distance( necesidades, max_element(necesidades, necesidades + N));
	
	modo = modos.at(maxIndex);
	
	
	if( modo == "relajado"){
		cout << "estoy relajado" << endl;
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
	papa->update();
	
	ofVec2f posicionInicial = papa->getPos();
	Timer timerCal;
	timerCal.start();
	advance();
	
	while ( timerCal.getTime() < 400 ){ // Esperar un ratico
	 // ***sdfsdfsfsd  >>>
	}
	stop();
	papa->update(); // Leer de nuevo la posición
	ofVec2f posicionFinal = papa->getPos();
	
	ofVec2f deltaPos = posicionFinal - posicionInicial;
	float elAngulo = deltaPos.angle( ofVec2f(1,0) ); // Angulo con respecto al eje x.
	papa->setAngle( elAngulo );
	
	cout << "CALIBRACION TERMINADA ------------  POS: " << posicionFinal << "  ANGULO: " << elAngulo << endl;
	


	
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
