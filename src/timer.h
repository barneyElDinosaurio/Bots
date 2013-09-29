/*
 *  timer.h
 *  bot
 *
 *  Created by Sergio Bromberg Dimaté on 28/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofMain.h"
class Timer{
public:
	
	Timer(){ started = false;}
	void start(){
		startTime = ofGetElapsedTimeMillis();
		started = true;
	}
	unsigned long long getTime(){
		if(started){
			return( ofGetElapsedTimeMillis() - startTime);
		}
		else{
			return(0);
		}
	}
	
	void restart() {
		started = true;
		start();
	}
	
	unsigned long long startTime;
	bool started;

};