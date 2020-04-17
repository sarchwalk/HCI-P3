/**
 *    OWLECTO
 *    By Sarah, Erika, and Valerie
 *    
 *    CPSC 581 - Human Computer Interaction II 
 *    
 *    For ESP8266
 *    
 *    Connects to AdafruitIO and recieves an integer
 *    This program controls an owls head, eyes, and sounds
 *    and plays a sequence of music and movements  
 */
#include "config.h"

#include <Servo.h>
#include <FastLED.h>

// NOTE: Value is the GPIO pin
const int BEAK_SERVO_PIN = 4; // D2
const int NECK_SERVO_PIN = 2; // D4
const int LED_PIN = 13;       // D7
const int SPEAKER_PIN = 5;    // D1

#define NUM_LEDS    2
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 100


CRGB leds[NUM_LEDS];

Servo beakServo;
Servo headServo;

// setting up feed
AdafruitIO_Feed *servo_feed = io.feed("owlectoFeed");

// Beak positions
const int closedBeakPosition = 168;
const int openBeakPosition = 150;

// Head positions
const int centerHeadPosition = 88;
const int rightHalfHeadPosition = 120;
const int rightFullHeadPosition = 150;
const int rightLimitHeadPosition = 170;
const int leftHalfHeadPosition = 60;
const int leftFullHeadPosition = 30;
const int leftLimitHeadPosition = 10;

// Tracking the current head position
int currentHeadPosition;

void setup() {

  Serial.begin(115200);

  // Setting up the beak
  beakServo.attach(BEAK_SERVO_PIN);
  beakClose();

  // Setting up the head
  headServo.attach(NECK_SERVO_PIN);
  headServo.write(centerHeadPosition);
  currentHeadPosition = centerHeadPosition;


  // Connects to adafruit IO
  io.connect();
  servo_feed->onMessage(handleMessage);
  while(io.status() < AIO_CONNECTED) {
    delay(500);
  }
  servo_feed->get();

  // LED setup
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();

  // Speaker setup
  pinMode(SPEAKER_PIN, OUTPUT);

}

void loop() { 
  io.run();
}


/**
 * Handle Message
 * 
 *  Converts message from adafruit io to an integer, then
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
 * State 1 - Spook
 * 
 * The least scary of the hauntings
 * Head looks right and left while
 * hooting
 */
void spook()
{  
  eyesFadeIn();
  moveHead(rightHalfHeadPosition);
  delay(500);
  hoot1();
  delay(500);
  
  returnHeadToCenter();
  delay(500);
  
  moveHead(leftFullHeadPosition);
  delay(500);
  hoot1();
  delay(500);
  
  moveHead(rightFullHeadPosition);
  delay(500);
  
  returnHeadToCenter();
  delay(700);
  hoot2();
  
  eyesFadeOut();
}

/**
 * State 2 - Scare
 * 
 * The second scariest of the hauntings
 * plays the jaws theme
 */
void scare()
{
  eyesFadeIn();
  jaws();
  eyesFadeOut();
  delay(500); 
}

/**
 * State 3 - Traumatize for Life
 * 
 * This is the scariest haunting
 * Head surveys 30 degrees around and 
 * Spooky Scary Skeletons jingle plays
 */
void traumatizeForLife()
{
  eyesOn();
  moveHead(rightLimitHeadPosition);
  delay(20);
  moveHead(leftLimitHeadPosition);
  delay(20);
  moveHead(centerHeadPosition);
  eyesOff();
  
  spookyScarySkeletons();    
}
