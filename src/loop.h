#include <Adafruit_NeoPixel.h>
#include "ProtogenHead.h"
#include "draw.h"
#include "AnimationBook.h"
#include "config.h"

#include "volatileEnvironment.h"

int8_t current_frame = 0;
int8_t debug_current_index = 0;

void animation_frame(void *params)
{
    while (true)
    {
        Animation *animation;
        for (int8_t i = 0; i < book->animation_count; i++)
        {
            // Serial.print("Considering ");
            // Serial.println(book->animations[i].animation_name);
            if (book->animations[i].animation_name.equals((const char *)current_animation))
            {
                animation = &book->animations[i];
                // Serial.print("Selected animation ");
                // Serial.println(animation->animation_name);
            }
        }
        uint16_t originalDuration = animation->frame_sequence[current_frame].duration;
        uint16_t variability = animation->frame_sequence[current_frame].variability;
        uint16_t duration = originalDuration + random(variability) - (variability / 2);
        // Serial.print("Frame ");
        // Serial.print(current_frame, DEC);
        // Serial.print(" of ");
        // Serial.print(animation->frame_count);
        // Serial.print(" for ");
        // Serial.println(duration);

        Expression *currentExpression;
        for (int8_t i = 0; i < animation->expression_count; i++)
        {
            if (animation->expressions[i].name.equals(animation->frame_sequence[current_frame].expression_name))
            {
                currentExpression = &animation->expressions[i];
                // Serial.print("Expression ");
                // Serial.println(currentExpression->name);
            }
        }
        for (int8_t x = 0; x < LED_DISPLAY_HEIGHT; x++)
        {
            for (int8_t y = 0; y < LED_DISPLAY_WIDTH; y++)
            {
                uint8_t colorID = getColorID(currentExpression->data, x, y);
                ProtogenColor c = animation->colors[colorID];
                uint8_t left_index = XY(x, y);
                head->left_leds->setPixelColor(left_index, Adafruit_NeoPixel::gamma32(Adafruit_NeoPixel::Color(c.r, c.g, c.b)));
                uint8_t right_index = XY(LED_DISPLAY_HEIGHT - 1 - x, y);
                head->right_leds->setPixelColor(right_index, Adafruit_NeoPixel::gamma32(Adafruit_NeoPixel::Color(c.r, c.g, c.b)));
            }
        }

        // Serial.print("Starting delay for ");
        // Serial.print(duration);
        // Serial.print("... ");
        head->left_leds->show();
        head->right_leds->show();
        delay(duration);

        // Serial.println("Done!");

        current_frame += 1;
        current_frame %= animation->frame_count;
    }
}