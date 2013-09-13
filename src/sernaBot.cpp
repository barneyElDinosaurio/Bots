/*
 *  sernaBot.cpp
 *  bot
 *
 *  Created by Sergio Bromberg Dimaté on 6/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "sernaBot.h"

void setup::setup(){
	
	//Setear wiringPI
	wiringPiSetup();
	int serialFlag  = serialOpen("/dev/ttyAMA0",9600);
	
	cout << "Se ha conectado al puerto serial número: " << endl;
}
void sernaBot::advance(float speed, float rotAngle){
void sernaBot::advance(){

digitalWrite(15, HIGH);
digitalWrite(16, LOW);
digitalWrite(1, HIGH);
digitalWrite(4, LOW);


}

void sernaBot:: recoil(){
  digitalWrite(15, HIGH);
  digitalWrite(16, LOW);
  digitalWrite(1, LOW);
  digitalWrite(4, HIGH);

}

void sernaBot::rotateR(){

digitalWrite(15, LOW);
digitalWrite(16, HIGH);
digitalWrite(1, HIGH);
digitalWrite(4, LOW);

}
void sernaBot::rotateL(){
digitalWrite(15, LOW);
digitalWrite(16, HIGH);
digitalWrite(1, LOW);
digitalWrite(4, HIGH);
}

void sernaBot::stop(){
digitalWrite(15, LOW);
digitalWrite(16, LOW);
digitalWrite(1, LOW);
digitalWrite(4, LOW);

}
