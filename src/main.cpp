#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "ProtogenHead.h"
#include "AnimationBook.h"
#include "config.h"
#include "loop.h"

ProtogenHead *head;
AnimationBook *book;
uint8_t loop_count = 0;
void setup()
{
  Serial.begin(115200); // Any baud rate should work

  Serial.println("=======Proto-proto-proto-gen!=======");

  // initialize LED library
  Serial.println("LED initialization...");

  head = makeHead();
  head->left_leds->setBrightness(BRIGHTNESS);
  head->left_leds->begin();

  head->right_leds->setBrightness(BRIGHTNESS);
  head->right_leds->begin();

  Serial.println("LED initializaion done.");

  // initialize animations
  Serial.println("AnimationBook initialization...");

  book = makeAnimationBook();
  Serial.println("AnimationBook initialization done.");
  Serial.println("=======Setup finshed=======");
}

void loop()
{
  animation_frame(head, book);
}
