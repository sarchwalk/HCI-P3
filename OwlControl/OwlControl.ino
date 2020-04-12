/**
 *    SPOOKY OWL
 *    By Sarah, Erika, and Valerie
 *    
 *    CPSC 581 - Human Computer Interaction II 
 */

#if defined(ARDUINO_ARCH_ESP32)
  #include <ESP32Servo.h>
#else
  #include <Servo.h>
#endif

#include <FastLED.h>


#define SERVO_PIN 4
#define LED_PIN 13
#define SOUND_PIN 5

#define NUM_LEDS    2
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 100


CRGB leds[NUM_LEDS];

Servo servo;

// setting up feed
AdafruitIO_Feed *servo_feed = io.feed("4");

void setup() {

  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  servo.attach(SERVO_PIN);

  Serial.print("Connecting to Adafruit IO");
  io.connect();

  servo_feed->onMessage(handleMessage);

  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());
  servo_feed->get();


  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();

  pinMode(SOUND_PIN, OUTPUT);

}

void loop() {
  io.run();
}


/**
 * Handle Message
 * 
 *  Converts message from adafruit io to aninteger, then
 *  triggers appropriate action
 */
void handleMessage(AdafruitIO_Data *data) {

  int input = data->toInt();

  // ------------ For testing -------------
    Serial.print("Recieved: ");
    Serial.println(input);
  // --------------------------------------
  
  switch(input){
    case 1:
      spook();
      break;
    case 2:
      scare();
      break;
    case 3:
      traumatizeForLife();
      break;
    default:
      break;
  }
}


/**
 * STATE 1
 */
void spook()
{
  leds[0].setRGB(100,0,0);
  leds[1].setRGB(100,0,0);
  FastLED.show();
  chirp();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}

/**
 * STATE 2
 */
void scare()
{
  leds[0].setRGB(0,100,0);
  leds[1].setRGB(0,100,0);
  FastLED.show();
  meow();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}

/**
 * STATE 3
 */
void truamatizeForLife()
{
  leds[0].setRGB(0,0,100);
  leds[1].setRGB(0,0,100);
  FastLED.show();
  ruff();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}










// ------------------------- REPLACE WITH JINGLES ----------------------------

void arf() {    // dog arf
  uint16_t i;
  playTone(890,25);          // "a"    (short)
  for(i=890; i<910; i+=2)    // "rrr"  (vary down)
     playTone(i,5);
  playTone(4545,80);         // intermediate
  playTone(12200,70);        // "ff"   (shorter, hard to do)
}

void chirp() {  // Bird chirp
  for(uint8_t i=200; i>180; i--)
     playTone(i,9);
}
 
void meow() {  // cat meow (emphasis ow "me")
  uint16_t i;
  playTone(5100,50);        // "m" (short)
  playTone(394,180);        // "eee" (long)
  for(i=990; i<1022; i+=2)  // vary "ooo" down
     playTone(i,8);
  playTone(5100,40);        // "w" (short)
}
 
void meow2() {  // cat meow (emphasis on "ow")
  uint16_t i;
  playTone(5100,55);       // "m" (short)
  playTone(394,170);       // "eee" (long)
  delay(30);               // wait a tiny bit
  for(i=330; i<360; i+=2)  // vary "ooo" down
     playTone(i,10);
  playTone(5100,40);       // "w" (short)
}
 
void mew() {  // cat mew
  uint16_t i;
  playTone(5100,55);       // "m"   (short)
  playTone(394,130);       // "eee" (long)
  playTone(384,35);        // "eee" (up a tiny bit on end)
  playTone(5100,40);       // "w"   (short)
}
 
void ruff() {   // dog ruff
  uint16_t i;
  for(i=890; i<910; i+=2)     // "rrr"  (vary down)
     playTone(i,3);
  playTone(1664,150);         // "uuu" (hard to do)
  playTone(12200,70);         // "ff"  (long, hard to do)
}

void playTone(uint16_t tone1, uint16_t duration) {
  if(tone1 < 50 || tone1 > 15000) return;  // these do not play on a piezo
  for (long i = 0; i < duration * 1000L; i += tone1 * 2) {
     digitalWrite(SOUND_PIN, HIGH);
     delayMicroseconds(tone1);
     digitalWrite(SOUND_PIN, LOW);
     delayMicroseconds(tone1);
  }     
}

// -------------------------------------------------------------------------------
