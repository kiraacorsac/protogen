#include "ProtogenHead.h"
#include "draw.h"
#include "AnimationBook.h"

int8_t current_frame = 0;
int8_t debug_current_index = 0;

void animation_frame(ProtogenHead *head, AnimationBook *book)
{
    uint16_t duration = book->frame_sequence[current_frame].duration;
    Serial.print("Frame ");
    Serial.print(current_frame, DEC);
    Serial.print(" of ");
    Serial.print(book->frame_count);
    Serial.print(" for ");
    Serial.println(duration);

    Expression *currentExpression;
    for (int8_t i = 0; i < book->expression_count; i++)
    {
        if (book->expressions[i].name.equals(book->frame_sequence[current_frame].expression_name))
        {
            currentExpression = &book->expressions[i];
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
    current_frame %= book->frame_count;
}