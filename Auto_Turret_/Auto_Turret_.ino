/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>


Servo servoX;  // Create servo object to control a servo
Servo servoY; // Create second servo object to control a second servo

double XPos = 1;  // Variable to store the servo position
double YPos = 1;
double traverseForce = 0.1;

void setup() {

  Serial.begin(115200); // Connected to the joystick
  
  servoX.attach(4);  // Attaches the servo on pin 2 to the servo object
  servoY.attach(3);  // Attaches the servo on pin 3 to the servo object
}

void loop() {
    int sensorValueX = analogRead(A0);
    int sensorValueY = analogRead(A1);
    Serial.println(sensorValueX);
    
    // For the X Axis 
    if (sensorValueX > 509) {
        if (XPos < 0) {
          XPos = 0;
        }
        if (XPos > 180) {
          XPos = 180;
        }
        XPos += traverseForce;
        servoX.write(XPos); // Tells servo to go to position in variable 'pos' 
        Serial.println(XPos);
    }

    // Traverse left
    if (sensorValueX < 509 && sensorValueX <= 766) {
        if (XPos < 0) {
          XPos = 0;
        }
        if (XPos > 180) {
          XPos = 180;
        }
        XPos -= traverseForce;
        servoX.write(XPos); // Tells servo to go to position in variable 'pos' 
        Serial.println(XPos);
    }
    
    // For the Y Axis
    if (sensorValueY > 508 && sensorValueY <= 761) {
        if (YPos < 50) {
          YPos = 50;
        }
        if (YPos > 130) {
          YPos = 130;
        }
        YPos += traverseForce;     
        servoY.write(YPos); // Tells servo to go to position in variable 'pos' 
        Serial.println(YPos);
    }

    // Tilt down
    if (sensorValueY < 508 && sensorValueY <= 761) {  
        if (YPos < 80) {
          YPos = 80;
        }
        if (YPos > 130) {
          YPos = 130;
        }
        YPos -= traverseForce; 
        servoY.write(YPos); // Tells servo to go to position in variable 'pos'
        Serial.println(YPos); 
    }  

    delay(1);
}


