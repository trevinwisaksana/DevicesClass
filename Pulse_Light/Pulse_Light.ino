int ledPin = 10;                 // LED connected to digital pin 10
int brightness = 20;
int direct = 1;
int repeat;
int steps = 20;   // change to 20 and then 100 to see the on/off blinks distinctly
int change = 1;   // change from 0 to 1 to go from fixed dim to changing 
void setup()
{
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output
}
void loop()
{
  Serial.write ('.');
  
  if ( change ) {
    if ( direct == 1 ) {
      if ( brightness < steps ) {
        brightness++;
      } else {
        direct = 0;
      }
    } else {
      if ( brightness > 0 ) {
        brightness--;
      } else {
        direct = 1;
      }
    }
  }
  for ( repeat = 0; repeat < 2 + (steps - brightness); repeat++) {
    digitalWrite(ledPin, HIGH);   // sets the LED on
    delay(1);                     // waits for a fixed duration
    digitalWrite(ledPin, LOW);    // sets the LED off
    delay(brightness);    // waits for a variable duration
  }
}

