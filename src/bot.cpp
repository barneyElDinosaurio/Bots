/*
 *  bot.cpp
 *  bot
 *
 *  Created by Sergio Bromberg Dimaté on 9/07/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "bot.h"

void Bot::update(){

	// ****** PARSE OSC MESSAGES ******//
	while (oscReciever.hasWaitingMessages()) {
		ofxOscMessage m;
		oscReciever.getNextMessage( &m );
		cout << " In OSC reciever !!!" << endl;
		
		// Position
		
		if ( m.getAddress() == "/blob") { // got blob message
			cout << " In OSC parsing !!!" << endl;
			// Get position vector and direction vector (a unit vector)
			ofVec2f blobPos( m.getArgAsFloat(0), m.getArgAsFloat(1) );
			float angle = m.getArgAsFloat(2);
			
			cout << "Blob position : " << blobPos << endl;
			cout << "Blob angle : "  << angle << endl;
			ofVec2f blobDirection( cos(angle), sin(angle) );
				
			if ( pos.distance(blobPos) < distanceThreshold /* && orientation.angle(blobDirection) < angleThreshold && timer! */){ // Its me!
				pos.set(blobPos);
			}
			else{
				blobData.set(blobPos.x, blobPos.y, angle);
			}
		}
		// Other messages: eg. orders: calibrate, go home... qué se yo...
		else if( m.getAddress() == "/advance"){ 
			/*SernaBot * tempBot;
			tempBot = (SernaBot *) this;
			tempBot.advance();
			 */
			if( this.botType == "sernaBot"){
				((SernaBot) this).advance();
			}
//			(SernaBot)this.adban 
		
		}
		else if( m.getAddress() == "/recoil"){
			if( this.botType == "sernaBot"){
				((SernaBot) this).recoil();
			}
		}
		else if( m.getAddress() == "/stop"){
			SernaBot * tempBot;
			tempBot = (SernaBot *) this;
			tempBot.stop();
		}
		
	}
}
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
void Bot::advance(float speed, float rotAngle){
	
	ofVec2f velocityVector = orientation*speed; 
	pos+=velocityVector;
	rotate(rotAngle);
	
}
void Bot::rotate(float rotAngle){
	angle+=rotAngle;
}
/*void Bot::callibrate(){

}*/


