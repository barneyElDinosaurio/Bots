/*
 *  bot.h
 *  bot
 *
 *  Created by Sergio Bromberg Dimaté on 9/07/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef BOT_H
#define BOT_H
#endif
#include "ofMain.h"
#include "ofxOsc.h"

#include <algorithm>

#ifndef MODE_H
#define MODE_H
#include "mode.h"
#endif

#ifndef TIMER_H
#define TIMER_H
#include "timer.h"
#endif




class Bot{
	
public:
	// Constructor
	
	Bot(){
		image.setAnchorPercent(0.5, 0.5);
		showMode = false;
		showBlobData = false;
		showNecesidades = false;
		showTuio = false;
		controlledMotion = false;
		reportObstacles = false;
		reportarPosicion = true;
		collisionDistance = 0.2; // 0.2 Parece sensato para una distancia de 2 metros
		setOscSender("192.168.1.50", 9000);

/*
		vision = "camara";
		cout << "Visión :: " << vision << endl;
		// No está perdido en principio.
		isLost = false;


		// MODOS Y VAINAS
		modo = "sediento"; // Tengo que poner esto momentáneamente... creo
		//chooseMode(); // Para elegir inicialmente un modo.
		firstTimeInMode = true;
		tiempoDeBebida = 5000; // En milisegundos... medio charro...
		tiempoDePausa = 10000;


		// LUGARES:
		bebedero.set(0.8, 0.8);
*/

	}
		
	void move();
	void draw();
	void setImage(string imageName);
	void setPos(float x, float y);
	void setAngle(float _angle);
	void update();
	void checkNeeds();
	
	void setListeningPort(int _port);
	void setSendingPort(int _port);
	void setSendingHost( string _host );
	void setOscSender( string _host, int _port);
	void setTrackSize(int);
	void calibrate();
	void isCalibrated();
	
	void setDistanceThreshold(float _d);
	void setAngleThreshold(float _a);
	//void advance(float speed, float rotAngle);
	void rotate(float rotAngle);
	void stop();
	
	void setupSerial(string terminal, int baudRate );
	void setupSerial(int device, int baudRate);
	void trackLastPos( ofVec2f);
	//void setup()
	ofVec2f getPos();

	// Choose mode!
	void chooseMode();
	
	
	
	
	// Position and orientation of the bot
	ofVec2f pos;
	ofVec2f orientation;
	
	float angleFromVision; // Blob angle
	float angle;
	
	ofSerial serial;

	// Tracking of last positions
	vector <ofVec2f> lastPos; 
	int trackSize;
	
	// Identification
	int ID;
	
	// State variables
	bool calibrated;
	
	// Distance threshold for updating position
	float distanceThreshold;
	float angleThreshold;
	
	// Image of the bot (for simulation)
	ofImage image;
	
	// target for movement. Optionally I should program a mover class... I think
	ofVec2f target;
	
	// Just for debugging:
	ofVec3f blobData; //position(x,y) and angle(z)
	
	
	//-----  OSC -----//
	
	ofxOscSender oscSender;
	ofxOscReceiver oscReciever;
	
	// recieving port
	int rPORT;
	
	// sending HOST and PORT
	string sHOST;
	int sPORT;
	
	// Type of bot
	string botType;

	// DEBUGGING STUFF
	bool showBlobData;
	bool showMode;
	bool showNecesidades;
	bool showTuio;
	bool reportarPosicion;

	// Sistema de visión utilizado (kinect o camara)

	string vision;

	//  ******** MODOS *********

	string modo;
	vector <Mode> modos;

	// ++++++++++++++++++ 
	// MOVIMIENTO !!!!
	//+++++++++++++++++++++
	float movementThreshold; // Threshold de acercamiento a un objeto
	bool isStatic; // modo estático o moviéndose
	bool controlledMotion;
	bool reportObstacles;
	vector <ofVec2f> obstaculos;
	float collisionDistance;

	bool isLost; // para saber si está perdido...
	
	// COLOR !!!
    float h, s, v;


    // Modos y cosas...
    Timer timerLost; // Tiempo sin que reciba un blob // CUADRAR ESTO !!!
	Timer timerSediento; // Tiempo que va a pasar bebiendo...
	Timer timerModo;
	Timer timerParado;
	Timer timerCarga;
	Timer timerCangri;
	bool firstTimeInMode;
	float tiempoDeBebida;
	float tiempoDePausa;
	string lastMode;

	// LUGARES
	ofVec2f bebedero; 
	ofVec2f cargadero1;
};
