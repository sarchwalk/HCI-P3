/**
 * Moves servo attached to the bottom beak to make it appear open
 */
void beakOpen()
{
  beakServo.write(openBeakPosition);
}

/**
 * Moves servo attached to the bottom beak to make it appear closed
 */
void beakClose()
{
  beakServo.write(closedBeakPosition);
}

/**
 * LED brightness slowly fades in
 */
void eyesFadeIn()
{
  int MaximumBrightness = 255;

  // Make the lights breathe
  for (int intensity = 0; intensity < MaximumBrightness; intensity+=5)
  {
    FastLED.setBrightness(intensity);
  
    for (int ledNumber=0; ledNumber<NUM_LEDS; ledNumber++) 
    {
      leds[ledNumber].setRGB(255, 0, 0);
    }

    FastLED.show();
    delay(2);
  }
}

/**
 * Eyes fade to off
 */
void eyesFadeOut()
{

  for(int intensity = 255; intensity > 0; intensity-=5)
  {
    FastLED.setBrightness(intensity);
    FastLED.show();
    delay(2);
  }
  eyesOff();
}

/**
 * Turns on eyes
 */
void eyesOn()
{
  leds[0] = CRGB::Red;
  leds[1] = CRGB::Red;
  FastLED.show();
}

/*
 * Turns off eyes
 */
void eyesOff()
{
  FastLED.clear();
  FastLED.show();
}


/**
 * Moves head to the position parameter
 */
void moveHead(int targetPosition)
{
  int changeFactor = currentHeadPosition < targetPosition ? 1 : -1;

  for(; currentHeadPosition != targetPosition; currentHeadPosition += changeFactor)
  {
       headServo.write(currentHeadPosition);
       delay(4);
  }
}


/**
 * Returns head to center from limit or full positions
 */
void returnHeadToCenter()
{
  int changeFactor = currentHeadPosition < centerHeadPosition? 1 : -1;

  for(; currentHeadPosition != centerHeadPosition; currentHeadPosition += changeFactor)
  {
       headServo.write(currentHeadPosition);
       delay(5);
  }
}
