// Adafruit IO Servo Example
// Tutorial Link: https://learn.adafruit.com/adafruit-io-basics-servo
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016-2017 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

/************************ Example Starts Here *******************************/

#if defined(ARDUINO_ARCH_ESP32)
  // ESP32Servo Library (https://github.com/madhephaestus/ESP32Servo)
  // installation: library manager -> search -> "ESP32Servo"
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

// set up the 'servo' feed
AdafruitIO_Feed *servo_feed = io.feed("4");

void setup() {

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  // tell the servo class which pin we are using
  servo.attach(SERVO_PIN);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // set up a message handler for the 'servo' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  servo_feed->onMessage(handleMessage);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  servo_feed->get();


  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();

  pinMode(SOUND_PIN, OUTPUT);

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  
 /** tone(SOUND_PIN, 200);
  delay(500);

  noTone(SOUND_PIN);
**/
}


void handleMessage(AdafruitIO_Data *data) {

  // convert the data to integer
  int input = data->toInt();


  Serial.print("Recieved: ");
  Serial.println(input);
  
  switch(input){
    case 1:
      leds[0].setRGB(100,0,0);
      leds[1].setRGB(100,0,0);
      FastLED.show();
      chirp();
      break;
    case 2:
      leds[0].setRGB(0,100,0);
      leds[1].setRGB(0,100,0);
      FastLED.show();
      meow();
      break;
    case 3:
      leds[0].setRGB(0,0,100);
      leds[1].setRGB(0,0,100);
      FastLED.show();
      ruff();
      break;
    default:
      break;
  }
/**
  if(angle < 0)
    angle = 0;
  else if(angle > 180)
    angle = 180;
    
  Serial.println("Angle: ");
  Serial.print(angle);
  Serial.println();
  servo.write(angle);

  // LEDS stuff
  
  leds[0].setRGB(100,angle,angle);
  leds[1].setRGB(100,angle,angle);
  FastLED.show();

  //tone(SOUND_PIN, angle);
  playTone(5100,40);
  playTone(1664,150);
  //delay(500);

  //noTone(SOUND_PIN);
  

  arf();
  delay(200);
  chirp();
  delay(200);
  meow();
  delay(200);
  meow2();
  delay(200);
  mew();
  delay(200);
  ruff();
  delay(200);
  FastLED.clear();
**/

  FastLED.delay(1000 / UPDATES_PER_SECOND);
}

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
