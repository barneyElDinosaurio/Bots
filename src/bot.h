/*
 *  bot.h
 *  bot
 *
 *  Created by Sergio Bromberg Dimaté on 9/07/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofMain.h"
#include "ofxOsc.h"

class Bot{
	
public:
	// Constructor
	
	Bot(){
		image.setAnchorPercent(0.5, 0.5);
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
	void calibrate();
	void isCalibrated();
	
	void setDistanceThreshold(float _d);
	void setAngleThreshold(float _a);
	//void advance(float speed, float rotAngle);
	void rotate(float rotAngle);
	void stop();
	
	void setupSerial(string terminal, int baudRate );
	void setupSerial(int device, int baudRate);
	
	
	
	// Position and orientation of the bot
	ofVec2f pos;
	ofVec2f orientation;
	float angle;
	
	ofSerial serial;

	
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

};