#include "testApp.h"

//#include 

//#define HEXAPOD 
//#define SERNAPODO 
#define DORMILONADOR

//#define DEBUG



//--------------------------------------------------------------
void testApp::setup(){
#ifndef DEBUG
	
	
	//elBot.setPos(0.7*ofRandom( ofGetWidth()), 0.7*ofRandom( ofGetHeight() ));
	//elBot.setPos( 0.5 , 0.5 );
	//elBot.setImage("imagenBotSmall.png");
	//elBot.setListeningPort(9001);
	//elBot.setDistanceThreshold(0.01);
	//elBot.setupSerial(0, 9600);
	
	
	// **************** SERNAPODO GARDEN ***************
	//if( )GARDEN
		
#ifdef SERNAPODO
	elGarden.setup();
	cout << "SERNAPODO STARTING..............." << endl;
#endif
	
	
	
	// ******************* HEXAPODO ********************
	
	
#ifdef HEXAPOD	
	hexa.setup();
	cout << " HEXAPODO STARTING..............." << endl;
#endif
	
	
	
	// ******************** DORMILONADOR ***************
	
#ifdef DORMILONADOR
	dorm.setup();
	cout << " DORMILONADOR STARTING........... " << endl;
#endif
	
	// ALGUNOS GLOBALES?
	
//	bebedero.set( 0.3, 0.3 );
	
	// PUEBAS... Borrar 
	
	leg.setOffset(ofVec3f(0, 0, 0));
	leg.setSize(100, 80, 50);
	leg.calcularAngulos( 40, 50, 60, 0);
	cout << leg.angBrazo << " " << leg.angAntebrazo <<  " "  << leg.angMun << endl;

	
	
#else // If debugging
	
	
	
#endif // closes DEBUG
}

//--------------------------------------------------------------
void testApp::update(){
#ifndef DEBUG

	// para el simulado
	//	elBot.update();
	
	
	// **************** SERNAPODO GARDEN ***************
#ifdef SERNAPODO
	elGarden.update();
#endif
	
#ifdef HEXAPOD
	hexa.update();
#endif

#ifdef DORMILONADOR
	dorm.update();
#endif
	
	
	ofLogVerbose()<< "I am running";
	//cout << "ESTOY EJECUTANDP" << endl;
	
#else
	
	
	
#endif // DEBUG
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(150);
	//elBot.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){ //Dirty calibration
	
#ifndef DEBUG
	elBot.setPos( elBot.blobData.x, elBot.blobData.y );
	elBot.setAngle( elBot.blobData.z);
	
	if(key == 's'){
		string s("#0 P1600 T1000");
		
		elBot.serial.writeBytes( (unsigned char *) string2CharBuf(s) , s.length() );
		//elBot.serial.writeByte( "\n" );
	}
	if( key =='m'){
		hexa.mandarUnDato();
		cout << "mandando un dato... en prtincipio" << endl;
		hexa.servocontroller.servoMove(1, 1000);
		hexa.servocontroller.servoMove(2, ofRandom(1500 , 1800) );
	}
	if (key == 'w') {
		elGarden.advance();
		cout << "Avanzando " << endl;
	}
	if (key == 's' ){
		elGarden.recoil();		
		cout << "retrocediendo " << endl;
	}
	if (key == 'd'){
		
	}
#else
	
#endif
}
// ------
char * testApp::string2CharBuf(string str){
	
	//std::string s
	char *a=new char[str.size()+1];
	a[str.size()]=0;
	memcpy(a,str.c_str(),str.size());
	
	return(a);

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
