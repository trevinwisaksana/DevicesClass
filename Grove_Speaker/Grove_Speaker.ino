#include "Ultrasonic.h"

/*macro definition of Speaker pin*/
#define SPEAKER 2
#define ULTRA 10
#define TOUCH 6

Ultrasonic ultrasonic(ULTRA);

const int TouchPin = 6;

// int BassTab[] = {1911,1702,1516,1431,1275,1136,1012}; // Bass 1 ~ 7
int BassTab[]  = {1911, 1702, 1516, 1431, 1275, 1136, 1012, 956, 851, 758, 715, 638, 568, 506, 478, 426, 379, 358, 319, 284, 253};
char NoteTab[] = {'B',  'C',  'D',  'E',  'F',  'G',  'A',  'B', 'C', 'D', 'E', 'F', 'G', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'A'};

void setup() {
    Serial.begin(115200);
    pinInit();
}

void loop() {

    airHarp();
    
    /*sound bass 1~7*/
    /*
    for(int note_index=0; note_index < 21; note_index++) {
        sound(note_index);
        delay(500);
    }
    */
    
}

void pinInit() {
    pinMode(SPEAKER,OUTPUT);
    digitalWrite(SPEAKER,LOW);
    pinMode(TOUCH, INPUT);
}

void sound(uint8_t note_index) {
    // int sensorValue = digitalRead(TouchPin);
    while (digitalRead(TOUCH)) {
        digitalWrite(SPEAKER,HIGH);
        delayMicroseconds(BassTab[note_index]);
        digitalWrite(SPEAKER,LOW);
        delayMicroseconds(BassTab[note_index]);
    } 
}


void airHarp() {

    long range;
    ultrasonic.MeasureInCentimeters();
    range = ultrasonic.RangeInCentimeters;
    delay(20);
  
    // Distance to move hand around
    int note = range / 2;

    // Does not allow the note to be greater than 20
    if (note > 20) {
      note = 20;
    }

    Serial.print("Note = ");
    Serial.println(NoteTab[note]);

    sound(note);
    
}

