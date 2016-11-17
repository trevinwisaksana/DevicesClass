#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;
double lastTime = 0;

void setup(){
    pinMode(10,OUTPUT);
    pinMode(2,INPUT);
}

void loop(){
    digitalWrite(10,1);
    _delay(1);
    digitalWrite(10,0);
    _delay(1);
     lastTime = millis()/1000.0;
    while(!(((millis()/1000.0) > (lastTime + (5))) | (((digitalRead(2))==(1)))));
    _loop();
}

void _delay(float seconds){
    long endTime = millis() + seconds * 1000;
    while(millis() < endTime)_loop();
}

void _loop(){
}

