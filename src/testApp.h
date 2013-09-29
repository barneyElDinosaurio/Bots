#pragma once

#include "ofMain.h"
#include "bot.h"
#include "sernaBot.h"
#include "hexapod.h"
#include "dormilonador.h"

#ifndef LEG_H
#define LEG_H
#include "leg.h"
#endif


class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
	char * string2CharBuf(string str);
		
	Bot elBot;
	SernaBot elGarden;
	Hexapod hexa;
	Dormilonador dorm;
	
	
	
	// Debug:
	Leg leg;
};
