
#include "ofMain.h"


#ifndef SERNABOT_H
#define SERNABOT_H
//#include "sernaBot.h"
#endif

#include "SSC32.h"

class Mover{
	public:

	void setup(/*SernaBot * elSerna*/);
	void updateAngle();
	void compute();
	void move();
	void changeDestination( ofVec2f dest);
	
	ofVec2f destination;
	SSC32 * servocontroller;

};