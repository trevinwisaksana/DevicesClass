/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>


Servo firstServo;  // create servo object to control a servo
Servo secondServo; // create second servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {

  Serial.begin(115200); // Connected to the joystick
  
  firstServo.attach(3);  // attaches the servo on pin 3 to the servo object
  secondServo.attach(4);  // attaches the servo on pin 4 to the servo object
}

void loop() {

    int sensorValue1 = (analogRead(A0) - 240) / 4;
    int sensorValue2 = (analogRead(A1) - 240) / 4;
    
    // Tells the servo to move based on the joystick input
    firstServo.write(sensorValue1);              
    secondServo.write(sensorValue2);
                     
    /* firstServo.write(pos);              
    secondServo.write(pos); */

    /* Serial.print("The X and Y coordinate is:");
    Serial.print(sensorValue1, DEC);
    Serial.print(",");
    Serial.println(sensorValue2, DEC);
    Serial.println(" "); 
    delay(200); */
  
  /* for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    firstServo.write(pos);              // tell servo to go to position in variable 'pos'
    secondServo.write(pos);
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    firstServo.write(pos);              // tell servo to go to position in variable 'pos'
    secondServo.write(pos);
    delay(15);                       // waits 15ms for the servo to reach the position
    
  } */
  
}
