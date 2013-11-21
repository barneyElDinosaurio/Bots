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
	if( reportarPosicion == true ){
		ofxOscMessage elMensaje;
		if( this->botType == "sernaBot"){
			// Tal vex hay que reducir la frecuencia de esto...
			elMensaje.setAddress("/ornitopodo");
			//cout << " Reportando posición " << endl;
		}

		// Espero que no haya null pointer exception la primera vez...

		elMensaje.addFloatArg( pos.x );
		elMensaje.addFloatArg( pos.y ); 
		elMensaje.addFloatArg( angle );
		oscSender.sendMessage( elMensaje );		
	}
	

	while (oscReciever.hasWaitingMessages()) {
		ofxOscMessage m;
		oscReciever.getNextMessage( &m );
		/*if(ofRandom(1) > 0.9 ){ // Para no mandar todos los mensajes, que son excesivos.
			cout << " In OSC reciever !!!" << endl;
		}*/	
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
			h = m.getArgAsFloat(6);
			s = m.getArgAsFloat(7);
			v = m.getArgAsFloat(8);
			
			if( showBlobData == true){
				cout << showBlobData << endl;
				cout << "Blob position : " << blobPos << endl;
				cout << "Blob angle    : "  << angle << endl;
				cout << "Blob area     : "  << area << endl;			
				cout << "Hu moment 1   : " << hu1 << endl;
				cout << "Hu moment 2   : " << hu2 << endl;
				cout << "Hue           : " << h << endl;
				cout << "Saturation    : " << s << endl;
				cout << "Value         : " << v << endl;
			}	
			
			
			// VALORES PARA EL SERNAPODO
			float hu1fixed = 0.2; // CAMBIAR DINÁMICAMENTE
			float hu1thres = 0.1;
			
			if( abs(hu1 - hu1fixed)  < hu1thres && vision == "camara" ){ // SI SOY UN SERNAPODO
				if( this->botType == "sernaBot"){
					setPos(blobPos.x, blobPos.y);
					if(ofRandom(1) < 0.1 ){ // Para no llenar la consola
						cout << "Me llamo SERNAPODO, con posición:---  " << pos.x << " " << pos.y << " HU : " << hu1 <<endl; 
					}
					trackLastPos(pos);
					//Ttimerw
				}
				isLost = false;
				
			}
			/*else { // Problemático cuando hay más blobs...
				isLost = true;
				cout << " ************ I AM LOST, PERRO. VOY A ANDAR POR AHÍ... SUERTE..." << endl;

			}*/
			
			
			//ofVec2f blobDirection( cos(angle), sin(angle) );
				
	/*		if ( pos.distance(blobPos) < distanceThreshold ){ // Its me!
				pos.set(blobPos);
			}
			else{
				blobData.set(blobPos.x, blobPos.y, angle);
			}
			*/
		}
		// ****** TODO SUYO MARIO *********
		else if( m.getAddress() == "/blobK/data"){
			int blobTrackId = m.getArgAsInt32(0);
			float blobTrackX = m.getArgAsFloat(1);
			float blobTrackY = m.getArgAsFloat(2);

			if(vision == "kinect"){

				setPos(blobTrackX, blobTrackY);
				cout << "posición por kinect :: " << blobTrackX << " " << blobTrackY << endl;
			}
			
			
		}
		// ******* QUIETO AQUÍ, CAN *******
		else if( m.getAddress() == "/tuio/2Dobj"){
			if( m.getArgAsString(0) == "set"){ // if message is a set message

				int fid = m.getArgAsInt32(2);
				float x = m.getArgAsFloat(3);
				float y = m.getArgAsFloat(4);
				angle = m.getArgAsFloat(5);

				if( fid == 0){ // El sernápodo
					pos = ofVec2f(x, y);
				}
				/*else if( fid == 1 ){
					((SernaBot *)this)->goTo( x, y );
				}*/
				else{
					obstaculos.push_back( ofVec2f( x, y ) );
				}


				if(showTuio == true){
					cout << "got TUIO" << endl;
					cout << "FID " << fid << endl;
					cout << "POS : "<< x << " " << y << endl;
					cout << "ANGLE RAD: " << angle << "   deg"  << angle*(180/PI) << endl;
				}
				

			}
			

			
			
		}
		else if( m.getAddress() == "/setDestino"){
			if( this->botType == "sernaBot"){
				controlledMotion = false; // Pone el modo de movimiento controlado en falso;
				( (SernaBot*) this)->goTo(  m.getArgAsFloat(0), m.getArgAsFloat(1) );
			}

		}
		else if( m.getAddress() == "/giveMePos"){ // No terminado?
			ofxOscMessage elMensaje;
			elMensaje.setAddress("/pos");
			elMensaje.addFloatArg( pos.x );
			elMensaje.addFloatArg( pos.y ); 

		}
		// Other messages: eg. orders: calibrate, go home... qué se yo...
		else if( m.getAddress() == "/reportObstacles"){ // Mensaje para activar la pintada de blobs en cout.
			cout << "En el cambiador de reporte de obstaculos" << endl;
			int val = m.getArgAsInt32(0);
			if( val == 0){
				reportObstacles = false;
				cout << "reportObstacles =  " << reportObstacles;
			}else if( val == 1 ){
				reportObstacles = true;
				cout << "reportObstacles = " << reportObstacles;
			}
		}
		else if( m.getAddress() == "/setStatic"){ // Mensaje para activar la pintada de blobs en cout.
			cout << "En el cambiador de static" << endl;
			int val = m.getArgAsInt32(0);
			if( val == 0){
				isStatic = false;
				cout << "Static =  " << isStatic;
			}else if( val == 1 ){
				isStatic = true;
				cout << "Static = " << isStatic;
			}
		}
		else if( m.getAddress() == "/showTuio"){ // Mensaje para activar la pintada de blobs en cout.
			cout << "En el cambiador de tuio" << endl;
			int val = m.getArgAsInt32(0);
			if( val == 0){
				showTuio = false;
				cout << "Static =  " <<	showTuio;
			}else if( val == 1 ){
				showTuio = true;
				cout << "Static = " << showTuio;
			}
		}
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
		else if( m.getAddress() == "/showNecesidades"){ // Mostar o no mostrar el modo en el que estoy.
			cout << "En el cambiador de Necesidades" << endl;
			int val = m.getArgAsInt32(0);
			if( val == 0){
				showNecesidades = false;
				cout << "Smode )= " << showNecesidades;
			}else if( val == 1 ){
				showNecesidades = true;
				cout << "Smode )= " << showNecesidades;
	
			}
		}
		else if( m.getAddress() == "/reportarPosicion"){ // Mostar o no mostrar el modo en el que estoy.
			cout << "En el cambiador de reporte de Posición" << endl;
			int val = m.getArgAsInt32(0);
			if( val == 0){
				reportarPosicion = false;
				cout << " reporte de posición : " << reportarPosicion << endl;
			}else if( val == 1 ){
				reportarPosicion = true;
				cout << " reporte de posición : " << reportarPosicion << endl;
	
			}
		}
		else if( m.getAddress() == "/reportAddress"){
			string reportHost = m.getArgAsString(0);
			int reportPort = m.getArgAsInt32(1);
			oscSender.setup(reportHost, reportPort);

			cout << "Cambié dirección de reporte a " << reportHost << ":" << reportPort << endl;
		}
		else if( m.getAddress() == "/vision"){
			int opcion = m.getArgAsInt32(0);
			if( opcion == 0){
				vision = "camara";
			}else if( opcion == 1){
				vision == "kinect";
			}
			else{
				cout << "opción errónea para el sistema de vision" << endl;
			}



		}
		else if( m.getAddress() == "/advance"){ // **** ADVANCE **** // ESTO ESTÁ MALO, LAS ORDENES DEBERÍAN ESTAR DIRIGIDAS.HAY QUE HACER PARSING DE OSC
			
			
			// SERNAPODO
			
			if( this->botType == "sernaBot"){
				cout << "Avanzando desde OSC" << endl;
				((SernaBot*) this)->advance();	
				controlledMotion = true;
				cout << "controlled Motion = " << controlledMotion << endl;
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
				controlledMotion = true;

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
				controlledMotion = true;
			}
			
			// HEXAPOD
			
			else if(botType == "hexapod"){
				((Hexapod*) this)->recoil();
			}
		}
		
		else if( m.getAddress() == "/rotateR"){ // **** ROTATE R ****
			if( this->botType == "sernaBot"){
				((SernaBot*) this)->rotateR();
				controlledMotion = true;
			}
		}
		else if( m.getAddress() == "/rotateL"){ // **** ROTATE L ****
			if( this->botType == "sernaBot"){
				((SernaBot*) this)->rotateL();
				controlledMotion = true;
			}
		}
		
	}
}

void Bot::trackLastPos(ofVec2f laPos){
	lastPos.push_back(laPos);
	while( lastPos.size() > trackSize){ // limitar el número de posiciones tracked a trackSize
		lastPos.erase( lastPos.begin() );
		
		//cout << "numero de posiciones rastreadsdas " <<  lastPos.size() << endl;
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
	oscSender.setup( sHOST, sPORT );
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

void Bot::chooseMode(){

	int val = ofRandom(100); // Lanzo un dado...

	cout << "-----------------" << endl;
	cout << " CAMBIO DE MODO  " << endl;
	cout << "-----------------" << endl;

	if( ofInRange( val, 0, 95) ){
		modo = "sediento";
		/*if(modo == lastMode){ // Para evitar que se repitan los modos.
			chooseMode(); 
		}*/
	} /*else if( ofInRange(val, 40, 100) ){
		modo = "cargar";
	}*/
	else if ( ofInRange(val , 95, 100)){
		modo = "parar";

	}
	cout << " MODO = " << modo << endl;  

	firstTimeInMode = true;
	lastMode = modo;

	//ofSleepMillis(2000);

}


	