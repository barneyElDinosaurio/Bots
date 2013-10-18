/*
 *  bot.cpp
 *  bot
 *
 *  Created by Sergio Bromberg Dimaté on 9/07/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "bot.h"
#include "sernaBot.h" /// ****** PROBLEMAS DE CROSS HEADERS!!!**** Corregir con ifdefs... !
#include "hexapod.h"
#include "dormilonador.h"

//class SernaBot;
void Bot::update(){
	
	//cout << "update del BOT" << endl; // Por qué coños, no sale esto??
	// ****** PARSE OSC MESSAGES ******//

	if( showMode == true){
		cout << "Estoy en modo --- > " << modo << endl; 
	}
	
	

	while (oscReciever.hasWaitingMessages()) {
		ofxOscMessage m;
		oscReciever.getNextMessage( &m );
		if(ofRandom(1) > 0.9 ){ // Para no mandar todos los mensajes, que son excesivos.
			cout << " In OSC reciever !!!" << endl;
		}	
		// POSICION
		// CREO que hay que forzar el framerate del dispositivo de captura para que sea más bajo
		if ( m.getAddress() == "/blob/data") { // got blob message
		  //cout << " In OSC parsing !!!" << endl;
			// Get position vector and direction vector (a unit vector)
			ofVec2f blobPos( m.getArgAsFloat(0), m.getArgAsFloat(1) );
			
			float angleFromVision = m.getArgAsFloat(2);
			float area = m.getArgAsFloat(3);
			float hu1 = m.getArgAsFloat(4);
			float hu2 = m.getArgAsFloat(5);
			
			if( showBlobData == true){
				cout << showBlobData << endl;
				cout << "Blob **position : " << blobPos << endl;
				cout << "Blob angle : "  << angle << endl;
				cout << "Blob area : "  << area << endl;			
				cout << "Hu moment 1: " << hu1 << endl;
				cout << "Hu moment 2: " << hu2 << endl;


			}	
			
			
			// VALORES PARA EL SERNAPODO
			float hu1fixed = 0.162;
			float hu1thres = 0.01;
			
			if( abs(hu1 - hu1fixed)  < hu1thres ){ // SI SOY UN SERNAPODO
				if( this->botType == "sernaBot"){
					setPos(blobPos.x, blobPos.y);
					cout << "Me llamo SERNAPODO, con posición:---  " << pos.x << " " << pos.y << " HU : " << hu1 <<endl; 
					
					trackLastPos(pos);
				}
				
			}
			
			
			//ofVec2f blobDirection( cos(angle), sin(angle) );
				
			if ( pos.distance(blobPos) < distanceThreshold /* && orientation.angle(blobDirection) < angleThreshold && timer! */){ // Its me!
				pos.set(blobPos);
			}
			else{
				blobData.set(blobPos.x, blobPos.y, angle);
			}
		}
		// Other messages: eg. orders: calibrate, go home... qué se yo...
		else if( m.getAddress() == "/showBlobData"){ // Mensaje para activar la pintada de blobs en cout.
			cout << "En el cambiador de showblob" << endl;
			int val = m.getArgAsInt32(0);
			if( val == 0){
				showBlobData = false;
				cout << "SBD )= " << showBlobData;
			}else if( val == 1 ){
				showBlobData = true;
				cout << "SBD )= " << showBlobData;
			}
		}
		else if( m.getAddress() == "/showMode"){ // Mostar o no mostrar el modo en el que estoy.
			cout << "En el cambiador de showmode" << endl;
			int val = m.getArgAsInt32(0);
			if( val == 0){
				showMode = false;
				cout << "Smode )= " << showMode;
			}else if( val == 1 ){
				showMode = true;
				cout << "Smode )= " << showMode;
	
			}
		}
		else if( m.getAddress() == "/advance"){ // **** ADVANCE **** // ESTO ESTÁ MALO, LAS ORDENES DEBERÍAN ESTAR DIRIGIDAS.HAY QUE HACER PARSING DE OSC
			
			
			// SERNAPODO
			
			if( this->botType == "sernaBot"){
				cout << "Avanzando desde OSC" << endl;
				((SernaBot*) this)->advance();	
			}
			
			//  HEXAPOD 
			
			else if(botType == "hexapod"){
				((Hexapod*) this)->advance();
				((Hexapod*) this)->servocontroller.servoMove(1, ofRandom(1500, 1800) );
				cout << "Avanzando el hexapodo desde osc" << endl;
			
			}
			
		}
		else if( m.getAddress() == "/QP"){

			int channel = m.getArgAsInt32(0);
			cout << "EN QP " << endl;
				if( this->botType == "sernaBot"){
					cout << "Me pide servos, pero no tengo servos" << endl;

				} else if( this->botType == "hexapod"){

					((Hexapod*) this)->servocontroller.queryPulseWidth( channel );

				}else if( this->botType == "dormilonador" ){
					((Dormilonador*) this)->servocontroller.queryPulseWidth( channel );

				}

		}
		else if( m.getAddress() == "/Q"){

			//int channel = m.getArgAsInt32(0);
			cout << "EN Q " << endl;
				if( this->botType == "sernaBot"){
					cout << "Me pide servos, pero no tengo servos" << endl;

				} else if( this->botType == "hexapod"){

					bool isMoving = ((Hexapod*) this)->servocontroller.isMoving();
					cout << "isMoving = " << isMoving << endl;
					//cout << "servo " << channel << "isMoving = " << isMoving << endl; 

				}else if( this->botType == "dormilonador" ){
					bool isMoving = ((Dormilonador*) this)->servocontroller.isMoving();
					cout << "isMoving = " << isMoving << endl;
					//cout << "servo " << channel << "isMoving = " << isMoving << endl;

				}
		}
		else if(m.getAddress() == "/arbitrarySerial"){
				
				const string s = m.getArgAsString(0);
				//const string s = ss.str();
				cout << "tratando de enviar ___ " << s << "____ por serial" << endl;
	
				

				if( this->botType == "sernaBot"){
					cout << "SernaBot: OJO, no tengo puerto serial..." << endl;

				} else if( this->botType == "hexapod"){
					Hexapod * h = (Hexapod*) this;
					serialPuts( h->servocontroller.serialNumber , (char*) s.c_str());
				//	((Hexapod*) this)->servocontroller.queryPulseWidth( channel );

				}else if( this->botType == "dormilonador" ){
					//((Dormilonador*) this)->servocontroller.queryPulseWidth( channel );
					Dormilonador * d = (Dormilonador*) this;
					serialPuts( d->servocontroller.serialNumber , (char*) s.c_str());
				}

		}
		 // DEBUUUUUUG
		else if( m.getAddress() == "/pruebaSS"){ // ServoSpeed
			((Hexapod*) this)->servocontroller.servoMoveSpeed(1, ofRandom(1500, 1800), 2000 );

		
		}
		else if( m.getAddress() == "/pruebaST"){ // ServoTime
			((Hexapod*) this)->servocontroller.servoMoveTime(1, ofRandom(1500, 1800), 2000 );			
		}
		else if(m.getAddress() == "/dormilonador"){
			cout << "En el movedor del triplehijuputa DORM" << endl;
			cout << "numARGS " << m.getNumArgs() << endl;
			float x = m.getArgAsFloat(0);
			float y = m.getArgAsFloat(1);
			float z = m.getArgAsFloat(2);			
			cout << "mandadnome por osc a "<< x << " " << y << " " << z << endl;
			((Dormilonador*)this)->brazo.moveTo( x, y, z, 0);
		}
		else if(m.getAddress() == "/moverServo" ){ // **** MOVER SERVO
			
			cout << "En mover servo. Numargs " << m.getNumArgs() <<endl;
			int servoNum = m.getArgAsInt32(0);
			int pulse = m.getArgAsInt32(1);
			
			// HEXAPODO
			
			if(botType == "hexapod"){
				((Hexapod*) this)->servocontroller.servoMove(servoNum, pulse);
			}	
			
			// DORMILONADOR
			
			if( botType == "dormilonador"){
				((Dormilonador *)this)->servocontroller.servoMove(servoNum, pulse);
				cout <<  "RECIBI ORDEN DE MOVER SERVO"<< endl;
			}
		}
		
		else if( m.getAddress() == "/stop"){ // **** STOP ****
			
			// SERNAPODO
			
			if( this->botType == "sernaBot"){
				((SernaBot*) this)->stop();
			}
			
			// HEXAPOD
			
			else if(botType == "hexapod"){
				((Hexapod*) this)->stop();
			}
			

		}
		else if( m.getAddress() == "/recoil"){ // **** RECOIL ****
			
			// SERNAPODO
			
			if( this->botType == "sernaBot"){
				((SernaBot*) this)->recoil();
			}
			
			// HEXAPOD
			
			else if(botType == "hexapod"){
				((Hexapod*) this)->recoil();
			}
		}
		
		else if( m.getAddress() == "/rotateR"){ // **** ROTATE R ****
			if( this->botType == "sernaBot"){
				((SernaBot*) this)->rotateR();
			}
		}
		else if( m.getAddress() == "/rotateL"){ // **** ROTATE L ****
			if( this->botType == "sernaBot"){
				((SernaBot*) this)->rotateL();
			}
		}
		
	}
}

void Bot::trackLastPos(ofVec2f laPos){
	lastPos.push_back(laPos);
	while( lastPos.size() > trackSize){ // limitar el número de posiciones tracked a trackSize
		lastPos.erase( lastPos.begin() );
		
		cout << "numero de posiciones rastreadsdas " <<  lastPos.size() << endl;
	}
	
	/*	
vector <ofVec2f> :: iterator it;
		
	for( it = lastPos.begin() ; it!=lastPos.end(); it++){
		cout << *it << " ";
	}
	cout << endl;
	*/
}
// Tal vez algunos de estos métodos deberían estar dentro de la clase sintética.
void Bot::setImage( string imageName ){
	image.loadImage(imageName);
}
void Bot::setPos(float x, float y){
	pos.set(x, y);
}
void Bot::setAngle(float _angle){
	angle = _angle;
}
void Bot::setupSerial(int device, int baudRate){
	serial.setup(device, baudRate);
}
void Bot::setupSerial(string port, int baudRate){
	serial.setup(port, baudRate);
}
void Bot::draw(){
	ofEnableAlphaBlending();
	image.draw( pos.x*ofGetWidth(), pos.y*ofGetHeight() );
	ofDisableAlphaBlending();
}
void Bot::setListeningPort(int _port){
	rPORT = _port;
	oscReciever.setup(rPORT);
}
void Bot::setSendingPort(int _port){
	sPORT = _port;
	oscSender.setup( sHOST, sPORT );
}
void Bot::setSendingHost( string _host ){
	sHOST = _host;
	oscSender.setup(sHOST, sPORT);
}
void Bot::setOscSender( string _host, int _port){
	sHOST = _host;
	sPORT = _port;
}
void Bot::setDistanceThreshold(float _d){
	distanceThreshold = _d;
}
void Bot::setAngleThreshold(float _a){
	angleThreshold = _a;
}
ofVec2f Bot::getPos(){
	return( pos );
}
void Bot::setTrackSize(int _ts){
	trackSize = _ts;
}
/*void Bot::advance(float speed, float rotAngle){
	
	ofVec2f velocityVector = orientation*speed; 
	pos+=velocityVector;
	rotate(rotAngle);
	
}
void Bot::rotate(float rotAngle){
	angle+=rotAngle;
}
void Bot::callibrate(){

}*/


