// Encoder project 
#define pinA 2
#define pinB 3
volatile int pos = 0;
volatile unsigned long lastTime;
volatile unsigned long newTime;
int pinALast = LOW;
int n = LOW;
int nHigh = 0;
int nLow = 0;

// Setup
void setup() {
  // Setup pins
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);

  // Used to interupt to parse the digitalRead
  // Asynchronous operation 
  // This sets up the code (similar to an Observer)
  attachInterrupt(0, doEncoderA, CHANGE); // encoder pin on interupt 0 (pin 2)
  attachInterrupt(1, doEncoderB, CHANGE); // enconder pin on interupt 1 (pin 3)

  // Millis is a hardware counter that keeps going
  lastTime = millis();
  
  Serial.begin(9600);
}

void loop() {
  // If new time is greater than the last time, then the interupt is being called
  // The loop only constantly checks if the newTime is greater than lastTime
  if (newTime > lastTime) {
    // Resets the nHigh and nLow into 0
    nHigh = nLow = 0;
    // Sets the newTime with 
    newTime = millis();
    // 
    while ((newTime + 1) > millis()) {
      // If the digitalRead from Pin A is greater 
      (digitalRead(pinA)) ? nHigh++ : nLow++;
    }
    // If the nHigh is greater than low, then set n into HIGH
    n = (nHigh > nLow) ? HIGH : LOW;
    // Reset the last time as the newTime
    // Synchronizes the time
    lastTime = newTime;
  }

  // Checks if the pin
  if ((pinALast == LOW) && (n == HIGH)) {
    if(digitalRead(pinB) == LOW) {
      pos--;
    } else {
      pos++; 
    }
    Serial.println(pos);

  // n's valued is assigned to pinALast
  pinALast = n;
}

// Don't do a lot on encoder handler
// Encoder assigns the newTime into the millis because the encoder 
// stopped all operations
// Used to see if the 
void doEncoderA() {
  newTime = millis();
}

// Encoder assigns the newTime into the millios because the encoder
// stopped all operations
void doEncoderB() {
  newTime = millis();
}

