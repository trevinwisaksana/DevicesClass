/*macro definition of Speaker pin*/
#define SPEAKER 8

const int TouchPin = 6;
const int ledPin = 12;

int BassTab[]={1911,1702,1516,1431,1275,1136,1012};//bass 1~7

void setup()
{
    pinMode(TouchPin, INPUT);
    pinInit();
}
void loop()
{
        /*sound bass 1~7*/
    for(int note_index=0;note_index<7;note_index++)
    {
        sound(note_index);
        delay(500);
    }
}
void pinInit()
{
    pinMode(SPEAKER,OUTPUT);
    digitalWrite(SPEAKER,LOW);
}
void sound(uint8_t note_index)
{
    int sensorValue = digitalRead(TouchPin);
    if(sensorValue==1)
    {
      for(int i=0;i<100;i++) {
        digitalWrite(SPEAKER,HIGH);
        delayMicroseconds(BassTab[note_index]);
        digitalWrite(SPEAKER,LOW);
        delayMicroseconds(BassTab[note_index]);
      }
    }
    
}

