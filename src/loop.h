#include "ProtogenHead.h"
#include "draw.h"
#include "AnimationBook.h"
#include "config.h"

int8_t current_frame = 0;
int8_t debug_current_index = 0;
String current_animation = STARTUP_ANIMATION;

void animation_frame(ProtogenHead *head, AnimationBook *book)
{
    Animation *animation;
    for (int8_t i = 0; i < book->animation_count; i++)
    {
        Serial.print("Considering ");
        Serial.println(book->animations[i].animation_name);
        if (book->animations[i].animation_name.equals(current_animation))
        {
            animation = &book->animations[i];
            Serial.print("Selected animation ");
            Serial.println(animation->animation_name);
        }
    }
    uint16_t duration = animation->frame_sequence[current_frame].duration;
    Serial.print("Frame ");
    Serial.print(current_frame, DEC);
    Serial.print(" of ");
    Serial.print(animation->frame_count);
    Serial.print(" for ");
    Serial.println(duration);

    Expression *currentExpression;
    for (int8_t i = 0; i < animation->expression_count; i++)
    {
        if (animation->expressions[i].name.equals(animation->frame_sequence[current_frame].expression_name))
        {
            currentExpression = &animation->expressions[i];
            Serial.print("Expression ");
            Serial.println(currentExpression->name);
        }
    }
    for (int8_t x = 0; x < LED_DISPLAY_HEIGHT; x++)
    {
        for (int8_t y = 0; y < LED_DISPLAY_WIDTH; y++)
        {
            uint8_t value = getColorMonochromeHex(currentExpression->data, x, y);
            uint8_t left_index = XY(x, y);
            head->left_leds->setPixelColor(left_index, head->left_leds->Color(0, value, 0));
            uint8_t right_index = XY(x, LED_DISPLAY_WIDTH - y);
            head->right_leds->setPixelColor(right_index, head->left_leds->Color(0, value, 0));
        }
    }

    Serial.print("Starting delay for ");
    Serial.print(duration);
    Serial.print("... ");
    head->left_leds->show();
    head->right_leds->show();
    delay(duration);

    Serial.println("Done!");

    current_frame += 1;
    current_frame %= animation->frame_count;
}