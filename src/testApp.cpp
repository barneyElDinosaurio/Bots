#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	//elBot.setPos(0.7*ofRandom( ofGetWidth()), 0.7*ofRandom( ofGetHeight() ));
	elBot.setPos( 0.5 , 0.5 );
	elBot.setImage("imagenBotSmall.png");
	elBot.setListeningPort(9001);
	elBot.setDistanceThreshold(0.01);
	
}

//--------------------------------------------------------------
void testApp::update(){
	elBot.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(150);
	elBot.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){ //Dirty calibration
	elBot.setPos( elBot.blobData.x, elBot.blobData.y );
	elBot.setAngle( elBot.blobData.z);

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}