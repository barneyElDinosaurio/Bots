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

#include "mode.h" 


class Bot{
	
public:
	// Constructor
	
	Bot(){
		image.setAnchorPercent(0.5, 0.5);
		showMode = false;
		showBlobData = false;
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
	ofVec2f getPos();
	
	
	
	
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


	//  ******** MODOS *********

	string modo;
	vector <Mode> modosPosibles;

};