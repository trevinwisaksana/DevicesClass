// Morse code encoder project for devices and IOT class
// Skeleton coded by Shannon Bailey, 11/9/2016
// Updated with MorseCodeLetters arrays corrected 11/13/2016
#include <Arduino.h>

// How fast will a single dit will come out.
double dotRate = (200) / (60);
char   letter;
double lastTime = 0;
int    letterIndex;
int    letterLength;
int    alphabet;
int    ditsDahs;
int    count;
int    ditOrDah;

// A table of MorseCode letters are coded as the length of each letter, and in
// in dits and dahs which are coded as 0 bits = dits and 1 bits = dahs
// There are 8 Bits in a Byte and like decimal numbers have thousands, hundreds, tens and ones,
// binary number bits are powers of 2 which are 128, 64, 32, 16, 8, 4, 2, 1
// for example: Morse code letter 'C' is length 4 and dah, dit, dah, dit or 1010 in binary and 
// binary 1010 has a 1 in the 4th bit and 2nd bit so its value is 8 + 2 = 10 in decimal.
char MorseCodeLetters[]        = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
//                                  A     B       C       D      E    F       G      H       I     J       K      L       M     N     O      P       Q       R      S      T    U      V       W      X       Y       Z       1        2        3        4        5        6        7        8        9        0
int  MorseCodeLetterLengths[]  = {  2,    4,      4,      3,     1,   4,      3,     4,      2,    4,      3,     4,      2,    2,    3,     4,      4,      3,     3,     1,   3,     4,      3,     4,      4,      4,      5,       5,       5,       5,       5,       5,       5,       5,       5,       5    };
int  MorseCodeLetterDitsDahs[] = {0b01, 0b1000, 0b1010, 0b100, 0b0, 0b0010, 0b110, 0b0000, 0b00, 0b0111, 0b101, 0b0100, 0b11, 0b10, 0b111, 0b0110, 0b1101, 0b010, 0b000, 0b1, 0b001, 0b0001, 0b011, 0b1001, 0b1011, 0b1100, 0b01111, 0b00111, 0b00011, 0b00001, 0b00000, 0b10000, 0b11000, 0b11100, 0b11110, 0b11111};
//int MorseCodeLetterDitsDahs[] ={  1,    8,      10,     4,     0,   2,      6,     0,      0,    7,      5,     4,      3,    2,    7,     6,      13,     2,     0,     1,   1,     1,      3,     9,      11,     12,     15,      7,       3,       1,       0,       16,      24,      28,      30,      31   };
// dah = 1, dit = 0
// formula = 2*n, formula on the right side of the tree = (2*n) + 1

void setup(){
    Serial.begin(115200);
    pinMode(10, OUTPUT);
}

void loop() {
    if((Serial.available()) > (0)) {
        letter = toupper( Serial.read() );
        Serial.write(letter);

        // If the letter is a space, wait 7 dot times lots   
        if (letter == ' '){
            // The time is not based on real clock
            lastTime = millis()/1000.0;
            // Current milli has to be greater than the time started
            while(!((millis()/1000.0) >= (lastTime + (4) / (dotRate))));
        } else { 
          // If the letter is not a space
          for (letterIndex = 0; letterIndex < sizeof( MorseCodeLetters );  letterIndex++)  
          {
  
            if (letter == MorseCodeLetters [ letterIndex ] ) 
            {
              // note: a faster solution would use if statements to check the range A-Z and 0-9 and calculate the letterIndex
                  letterLength = MorseCodeLetterLengths[ letterIndex ];
                  ditsDahs     = MorseCodeLetterDitsDahs[ letterIndex ];

                  for (count = 1; count <= letterLength; count++) 
                  {
                    // Shift and isolate each bit and set its to 1 if dit, and 3 if a dah
                    // If true, return a 3, if not return a 1
                    ditOrDah = (1 & (ditsDahs >> (letterLength - count))) ? 3 : 1;

                    // Setting the digital write pin to ON
                    digitalWrite(10, 1);
                    lastTime = millis()/1000.0;
                    // Waits to turn it off by either 3 or 1 second
                    while(!((millis()/1000.0) >= (lastTime + (ditOrDah) / (dotRate))));
                    // Setting the digital write pin to OFF
                    digitalWrite(10, 0);
                    lastTime = millis()/1000.0;
                    // Waits 1 second before turning the light on again
                    while(!((millis()/1000.0) >  (lastTime + (1) / (dotRate))));
              
                  }
                  // After each alphabet, add a 3 dit time wait between each letter
                  lastTime = millis()/1000.0;
                  // This is used when there's a new alphabet as each alphabet needs to be spaced 
                  while(!((millis()/1000.0) >= (lastTime + (3) / (dotRate))));
            }
          }
        }
    }
}
 

