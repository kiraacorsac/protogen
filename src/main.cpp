#include <Arduino.h>
#include <FastLED.h>
#include <ArduinoJson.h>
#include "AnimationBook.h"
#include "config.h"

CRGB left_leds[LEDS_PER_DISPLAY];
StaticJsonDocument<ANIMATION_LIBRARY_SIZE> animationBook;

void setup()
{
  // initialize FastLED
  FastLED.addLeds<NEOPIXEL, DATA_PIN_LEFT>(left_leds, LEDS_PER_DISPLAY);

  // initialize AnimationBook
  DeserializationError animationLibraryError = deserializeJson(animationBook, animationBookJson);
}

void loop()
{
  left_leds[5].b = 255;
  FastLED.delay(1000);
  left_leds[5].b = 0;
  FastLED.delay(1000);
}
