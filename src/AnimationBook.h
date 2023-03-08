#include <Arduino.h>
#include <ArduinoJson.h>
#include "config.h"
#include "draw.h"

#ifndef ANIMATIONBOOK_H_
#define ANIMATIONBOOK_H_

String animationBookJson = R"({"idle":{"mode":"mirror","mirror":{"open":"00000000000000000000FF00000000000000FFFFFFFFF000000000000000000000000000000000000000FFFFFFFFFF000000FF00F00F000000000FF000FF0000000000FFFFF000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000","semi":"00000000000000000000FF00000000000000FFFFFFFFF000000000000000000000000000000000000000FFFFFFFFFF000000FF00F0FF000000000FFFFFF0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000","closed":"000000000000000000000F00000000000000FFFFFFFFF000000000000000000000000000000000000000FFFFFFFFFF0000000FFFFF000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"},"frame-sequence":[{"frame":"open","duration":2000,"variability":1000},{"frame":"semi","duration":50,"variability":10},{"frame":"closed","duration":200,"variability":100},{"frame":"semi","duration":50,"variability":10}],"colors":{"0":{"r":0,"g":0,"b":0},"F":{"r":0,"g":255,"b":255}}},"hearts":{"mode":"mirror","mirror":{"heart1":"000000000000000000000000000000000000000000000000000000FF0FF0000000000FFFFFFF000000000FFFFFFF000000000FFFFFFF0000000000FFFFF000000000000FFF00000000000000F0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000","heart2":"0000000000000000000000F000F0000000000FFF0FFF00000000FFFFFFFFF0000000FFFFFFFFF0000000FFFFFFFFF0000000FFFFFFFFF00000000FFFFFFF0000000000FFFFF000000000000FFF00000000000000F000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"},"frame-sequence":[{"frame":"heart1","duration":150,"variability":0},{"frame":"heart2","duration":150,"variability":0},{"frame":"heart1","duration":150,"variability":0},{"frame":"heart2","duration":150,"variability":0},{"frame":"heart1","duration":450,"variability":0}],"colors":{"0":{"r":0,"g":0,"b":0},"F":{"r":255,"g":105,"b":180}}},"gay":{"mode":"mirror","mirror":{"straight":"0000000000000000000000000000000001111111111111100111111111111110022222222222222002222222222222200333333333333330033333333333333004444444444444400444444444444440055555555555555005555555555555500666666666666660066666666666666000000000000000000000000000000000","wiggly":"0000000000000000001111000000000001111111100000100122221111111110022222222111112002333322222222200333333332222230034444333333333004444444433333400455554444444440055555555444445005666655555555500666666665555560060000666666666000000000066666000000000000000000"},"frame-sequence":[{"frame":"straight","duration":1500,"variability":500},{"frame":"wiggly","duration":1500,"variability":500}],"colors":{"0":{"r":0,"g":0,"b":0},"1":{"r":227,"g":1,"b":2},"2":{"r":254,"g":143,"b":0},"3":{"r":255,"g":237,"b":5},"4":{"r":2,"g":128,"b":40},"5":{"r":0,"g":76,"b":251},"6":{"r":154,"g":80,"b":171}}}})";
typedef struct ProtogenColor
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} ProtogenColor;

typedef struct Expression
{
    String name;
    String data;

} Expression;

typedef struct Frame
{
    String expression_name;
    uint16_t duration;
    uint16_t variability;
} Frame;

typedef struct Animation
{
    String animation_name;
    Expression *expressions;
    int8_t expression_count;
    Frame *frame_sequence;
    int8_t frame_count;
    ProtogenColor *colors;
} Animation;

typedef struct AnimationBook
{
    Animation *animations;
    int8_t animation_count;
} AnimationBook;

AnimationBook *makeAnimationBook()
{
    DynamicJsonDocument parsedBook(4096);
    Serial.println("Deserializing JSON...");

    DeserializationError error = deserializeJson(parsedBook, animationBookJson);

    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return nullptr;
    }
    JsonObject parsedBookJson = parsedBook.as<JsonObject>();

    Animation *animationArray = new Animation[parsedBookJson.size()];
    int8_t animationCount = 0;

    for (auto animJson : parsedBookJson)
    {
        String animationName = String(animJson.key().c_str());
        JsonObject animationJson = parsedBook[animationName];
        String mode = parsedBook["mode"];

        JsonObject expressionsJson = animationJson["mirror"];
        JsonArray frameSequenceJson = animationJson["frame-sequence"];

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
            uint16_t variability = frameObj["variability"];
            // String durationStr = String(durationChars);
            // int8_t duration = durationStr.toInt();

            Serial.print("Frame ");
            Serial.print(frame_i, DEC);
            Serial.print(" named ");
            Serial.print(frameName);
            Serial.print(" for ");
            Serial.println(duration, DEC);

            Frame frame = {frameName, duration, variability};
            frameSequence[frame_i] = frame;

            frame_i++;
        }

        JsonObject colorJson = animationJson["colors"];
        ProtogenColor *colors = new ProtogenColor[16];
        for (auto colorObj : colorJson)
        {
            String colorIdString = String(colorObj.key().c_str());
            debugLog("Found color ID ");
            debugLogLine(colorIdString);
            uint8_t colorId = hexCharToByte(colorIdString[0]);

            uint8_t r = colorObj.value()["r"];
            uint8_t g = colorObj.value()["g"];
            uint8_t b = colorObj.value()["b"];
            debugLog("On color ID ");
            debugLog(colorId);
            debugLog(" there is color (");
            debugLog(r);
            debugLog(", ");
            debugLog(g);
            debugLog(", ");
            debugLog(b);
            debugLogLine(").");

            ProtogenColor color = {r, g, b};
            colors[colorId] = color;
        }

        Animation animation = {
            animationName,
            expressions,
            numExpressions,
            frameSequence,
            numFrames,
            colors};

        animationArray[animationCount] = animation;
        animationCount++;
    }

    AnimationBook *book = new AnimationBook();
    book->animations = animationArray;
    book->animation_count = animationCount;
    return book;
};

#endif