#include <Arduino.h>
#include <ArduinoJson.h>
#include "config.h"

#ifndef ANIMATIONBOOK_H_
#define ANIMATIONBOOK_H_

String animationBookJson = R"(
{
    "idle": {
        "mode": "mirror",
        "mirror": {
            "open": "00000000000000000000FF00000000000000FFFFFFFFF000000000000000000000000000000000000000FFFFFFFFFF000000FF00F00F000000000FF000FF0000000000FFFFF000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
            "semi": "00000000000000000000FF00000000000000FFFFFFFFF000000000000000000000000000000000000000FFFFFFFFFF000000FF00F0FF000000000FFFFFF0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
            "closed": "000000000000000000000F00000000000000FFFFFFFFF000000000000000000000000000000000000000FFFFFFFFFF0000000FFFFF000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        },
        "frame-sequence": [
            {
                "frame": "open",
                "duration": 1000
            },
            {
                "frame": "semi",
                "duration": 50
            },
            {
                "frame": "closed",
                "duration": 250
            },
            {
                "frame": "semi",
                "duration": 50
            }
        ]
    }
}
)";

typedef struct Expression
{
    String name;
    String data;

} Expression;

typedef struct Frame
{
    String expression_name;
    uint16_t duration;
} Frame;

typedef struct AnimationBook
{
    Expression *expressions;
    int8_t expression_count;
    Frame *frame_sequence;
    int8_t frame_count;
} AnimationBook;

AnimationBook *makeAnimationBook()
{
    StaticJsonDocument<ANIMATION_BOOK_JSON_SIZE> parsedBook;
    Serial.println("Deserializing JSON...");

    DeserializationError error = deserializeJson(parsedBook, animationBookJson);

    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return nullptr;
    }

    JsonObject idle = parsedBook["idle"];
    String mode = parsedBook["mode"];

    JsonObject expressionsJson = idle["mirror"];
    JsonArray frameSequenceJson = idle["frame-sequence"];

    int8_t numExpressions = expressionsJson.size();
    int8_t numFrames = frameSequenceJson.size();
    Expression *expressions = new Expression[numExpressions];
    Frame *frameSequence = new Frame[numFrames];
    Serial.println("Looking up expressions...");

    int8_t expression_i = 0;
    for (auto expr : expressionsJson)
    {

        String name = expr.key().c_str();
        String data = expr.value().as<String>();
        Expression expression = {name, data};
        expressions[expression_i] = expression;
        Serial.print("Expression ");
        Serial.print(expression_i, DEC);
        Serial.print(" named ");
        Serial.print(name);
        Serial.print(" contains ");
        Serial.println(data);

        expression_i++;
    }

    int8_t frame_i = 0;
    for (auto frameObj : frameSequenceJson)
    {
        const char *frameName = frameObj["frame"];
        uint16_t duration = frameObj["duration"];
        // String durationStr = String(durationChars);
        // int8_t duration = durationStr.toInt();

        Serial.print("Frame ");
        Serial.print(frame_i, DEC);
        Serial.print(" named ");
        Serial.print(frameName);
        Serial.print(" for ");
        Serial.println(duration, DEC);

        Frame frame = {frameName, duration};
        frameSequence[frame_i] = frame;

        frame_i++;
    }

    AnimationBook *book = new AnimationBook;
    book->expressions = expressions;
    book->expression_count = numExpressions;
    book->frame_sequence = frameSequence;
    book->frame_count = numFrames;

    return book;
}

#endif