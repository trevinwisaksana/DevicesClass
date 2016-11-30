#include <Ultrasonic.h>
#include <Arduino.h>

Ultrasonic ultrasonic(6);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  long distance;
  
  distance = ultrasonic.MeasureInCentimeters();

  Serial.print("distance = ");
  Serial.println(distance);

  delay(1000);
}
