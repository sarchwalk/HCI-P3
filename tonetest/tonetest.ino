/*
Adafruit Arduino - Lesson 10. Simple Sounds
*/
 
int speakerPin = 12;
 
int numTones = 10;
//int tones[] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440};
//            mid C  C#   D    D#   E    F    F#   G    G#   A

//https://www.arduino.cc/en/Tutorial/toneMelody
int jawsTones[] = {82, 87};
int noteDurations[] = {2, 1};

void setup()
{
 
}
 
void loop()
{

   for (int i = 0; i < numTones; i++)
  {
    tone(speakerPin, tones[i]);
    delay(500);
  }
  noTone(speakerPin);
}
