// Morse code Decoder project for devices and IOT class
// Solution coded by Shannon Bailey, 11/13/2016
#include <Arduino.h>

double dotRate = (200) / (60);
double sampleRate = 1.0 / (dotRate * 4.0);
#define TRAINING_LENGTH 100

#define SILENT 0
#define ON     1
#define SPACE  2

int sensorPin = A0;

double lastTime = 0;

int thresholdValue;

int decoderState;
int silentCount;
int activeCount;

int ditsAndDahs;
int ditDahCount;

// A table of MorseCode letters are coded as the length of each letter, and in
// in dits and dahs which are coded as 0 bits = dits and 1 bits = dahs
// There are 8 Bits in a Byte and like decimal numbers have thousands, hundreds, tens and ones,
// binary number bits are powers of 2 which are 128, 64, 32, 16, 8, 4, 2, 1
// for example: Morse code letter 'C' is length 4 and dah, dit, dah, dit or 1010 in binary and 
// binary 1010 has a 1 in the 4th bit and 2nd bit so its value is 8 + 2 = 10 in decimal.
char MorseCodeLetters[]        = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"};
//                                  A     B       C       D      E    F       G      H       I     J       K      L       M     N     O      P       Q       R      S      T    U      V       W      X       Y       Z       1        2        3        4        5        6        7        8        9        0
int  MorseCodeLetterLengths[]  = {  2,    4,      4,      3,     1,   4,      3,     4,      2,    4,      3,     4,      2,    2,    3,     4,      4,      3,     3,     1,   3,     4,      3,     4,      4,      4,      5,       5,       5,       5,       5,       5,       5,       5,       5,       5    };
int  MorseCodeLetterDitsDahs[] = {0b01, 0b1000, 0b1010, 0b100, 0b0, 0b0010, 0b110, 0b0000, 0b00, 0b0111, 0b101, 0b0100, 0b11, 0b10, 0b111, 0b0110, 0b1101, 0b010, 0b000, 0b1, 0b001, 0b0001, 0b011, 0b1001, 0b1011, 0b1100, 0b01111, 0b00111, 0b00011, 0b00001, 0b00000, 0b10000, 0b11000, 0b11100, 0b11110, 0b11111};
//int MorseCodeLetterDitsDahs[] ={  1,    8,      10,     4,     0,   2,      6,     0,      0,    7,      5,     4,      3,    2,    7,     6,      13,     2,     0,     1,   1,     1,      3,     9,      11,     12,     15,      7,       3,       1,       0,       16,      24,      28,      30,      31   };

void setup(){
    Serial.begin(115200);
    Serial.println("starting setup");

    calculateThreshold();

    decoderState = SILENT;
    silentCount = 0;
    activeCount = 0;

    ditsAndDahs = 0;
    ditDahCount = 0;

    Serial.println("done with setup");
    
    lastTime = millis()/1000.0;
}

void loop() {
    int sensorValue;
    
    while(!((millis()/1000.0) > (lastTime + sampleRate))) ;
    lastTime = millis()/1000.0;
        
    sensorValue = analogRead(sensorPin);
// enable for debugging
//    Serial.print(sensorValue);  Serial.write(' ');  count++;  if (count > 10) { Serial.println(' ');  count = 0; }

    switch (decoderState) {
        case SILENT:
        // check for sensorValue greater than threshold, set activeCount and change decoderState
            if (sensorValue > thresholdValue) {
                activeCount = 1;
                decoderState = ON;
            }
            break;
        case ON:
        // check sensorValue greater than threshdold, increment activeCount
            if (sensorValue > thresholdValue) {
                activeCount++;
            } else {
        // else check for ActiveCount between 3 and 5 and setElement count 1 and state
                if ((activeCount >= 3) && (activeCount <= 5) ) {
                    setElement ( 1, 1 );
                } else {
                // else check for ActiveCount between 11 and 13 and setElement count 3 and state
                // (these numbers may need slight tuning)
                    if ((activeCount >= 11) && (activeCount <= 13) ) {
                        setElement  ( 3, 1 );
                    }
                }
             // final reset activeCount, set silentCount, change decoderState
                activeCount = 0;
                silentCount = 1;
                decoderState = SPACE;
            }
            break;

        case SPACE:
        // check sensorValue less then threshold, increment silentCount
            if (sensorValue < thresholdValue) {
                silentCount++;
            // check silentCount greater than 32, reset silentCount, change decoderState, setElement count 0 and state
            // this checks for a very long time after sending a character
                if (silentCount > 32) {
                    silentCount = 0;
                    decoderState = SILENT;
                    setElement  ( 0, 0 );
                }
        // else check for a short space between dits and dahs, silentCount of 3 to 5, setElement count 1 and state
            } else {
                if ((silentCount >= 3) && (silentCount <= 5) ) {
                    setElement  ( 1, 0 );
            // else check for a slong space between dits and dahs, silentCount of 15 through 17, setElement count 3 and state
            // this indicates a space between letters/numbers
                } else {
                    if ((silentCount >= 15) && (silentCount <= 17) ) {
                        setElement  ( 3, 0 );
                // else check for a very long short space between dits and dahs, silentCount of 30 through 32, setElement count 7 and state
                // this is a space character between letters and numbers
                    } else {
                        if ((silentCount >= 30) && (silentCount <= 32) ) {
                            setElement  ( 7, 0 );
                        }
                    }
                }
// enable for debugging
//                Serial.println(silentCount);  // enable to see actual pulse counts
                activeCount = 1;
                silentCount = 0;
                decoderState = ON;
            }
            break;
    }
}

void setElement (int count, int state) {
    int index;
// enable for debugging
//    Serial.print("count = ");  Serial.print(count);  Serial.print(" state = ");  Serial.println(state);

 // check state 1, increment ditDahCount, shift ditsAndDahs left 1 and OR in a 1 bit if count is 3 (a dah)    
    if (state == 1) {
        ditDahCount++;
        ditsAndDahs = ((ditsAndDahs << 1) | (count == 3));  // shift left one, OR in Dit or Dah
 // else state is 0, check count == 1
    } else {
        if (count == 1) {
         // to prevent overflow of noise, if ditDahCount > 5, reset ditsAndDahs and ditDahCount (using goto?)
            if (ditDahCount > 5) {
                goto OVERFLOW;
            }
     // else, the state is a character break space so lets lookup the character
        } else {
         // check all the letters and numbers
            for (index = 0; index < sizeof( MorseCodeLetters ); index++) {
             // check if the ditDahCount matches
                if (ditDahCount == MorseCodeLetterLengths [index]) {
                 // check the binary bit value for a match
                    if (ditsAndDahs == MorseCodeLetterDitsDahs [index]) {
                     // print the matching letter/number and break out of the loop
                        Serial.print(MorseCodeLetters [index]);
                        break;
                    }
                }
            }
         // if the count is 7 and not 3, then append a space character
            if ((count == 7) || (count == 0) ){
                // append a space
                Serial.print(' ');
            }
        // reset the ditsAndDahs and ditDahCount to start decoding the next letter
OVERFLOW:
            ditsAndDahs = 0;
            ditDahCount = 0;
        }
    }
}


// calculate a median value for the threshold or if no signal is seen, choose a threshold 10% above baseValue
void calculateThreshold (void) {
    int index, lightValue;
    int baseValue = 1023;
    int peakValue = 0;

// read the light sensor for a while with a sender transmitting to capture the base and peak values
    for (index = 0; index < TRAINING_LENGTH; index++) {
        lastTime = millis()/1000.0;
        while(!((millis()/1000.0) > (lastTime + sampleRate))) ;
        lightValue = analogRead(sensorPin);
        if (baseValue > lightValue ) baseValue = lightValue;
        if (peakValue < lightValue ) peakValue = lightValue;
    }
    if (peakValue > baseValue + 50) { // if the peak is more than 50 above base (or about 5%) then a signal was seen
        thresholdValue = (baseValue + peakValue) / 2;
    } else {
        thresholdValue = baseValue + 100;
    }
    
    Serial.print("base = ");  Serial.print(baseValue);  Serial.print(", peak = ");  Serial.print(peakValue);
    Serial.print(", threshold = ");  Serial.println(thresholdValue);
}

