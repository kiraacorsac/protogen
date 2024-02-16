#include <Arduino.h>
#include <ArduinoJson.h>
#include "config.h"
#include "draw.h"

#ifndef ANIMATIONBOOK_H_
#define ANIMATIONBOOK_H_

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
    char animationBookJson[] = R"({"confuzed":{"mode":"mirror","mirror":{"1":"0000011000000000000000000222200000000000220022000003300220000220000000020022002022000002020020202000000202000020000000020200002000000440002002000000000000022000011000000005500000200020000000000202023300000000200020002000000000000000020001100000000000000000","2":"0000004400000000001100002222200000000000000022000000000022200220000000020002002022000020000200202000002000200220000000020000220000033000222220000000000000000000000000001100000000200020000000000202020200000000200020002004400000000550020000000000000000000000","3":"0000011000000000000000000220000000000000200200000003300200002020000000020000202022000002020020202000000200220020000000022000022000000440220022000000000002222000011000000005500000200020000000000202023300000000200020002000000000000000020001100000000000000000","4":"0000004400000000001100002222200000000002200002000000002200200020000000200200002022000020020002002000002200222000000000022000000000033000222220000000000000000000000000001100000000200020000000000202020200000000200020002004400000000550020000000000000000000000"},"frame-sequence":[{"frame":"1","duration":250,"variability":0},{"frame":"2","duration":250,"variability":0},{"frame":"3","duration":250,"variability":0},{"frame":"4","duration":250,"variability":0}],"colors":{"0":{"r":0,"g":0,"b":0},"1":{"r":13,"g":255,"b":0},"2":{"r":255,"g":255,"b":255},"3":{"r":207,"g":0,"b":255},"4":{"r":0,"g":208,"b":255},"5":{"r":255,"g":0,"b":0}}},"hearts":{"mode":"mirror","mirror":{"heart1":"000000000000000000000000000000000000000000000000000000FF0FF0000000000FFFFFFF000000000FFFFFFF000000000FFFFFFF0000000000FFFFF000000000000FFF00000000000000F0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000","heart2":"0000000000000000000000F000F0000000000FFF0FFF00000000FFFFFFFFF0000000FFFFFFFFF0000000FFFFFFFFF0000000FFFFFFFFF00000000FFFFFFF0000000000FFFFF000000000000FFF00000000000000F000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"},"frame-sequence":[{"frame":"heart1","duration":150,"variability":0},{"frame":"heart2","duration":150,"variability":0},{"frame":"heart1","duration":150,"variability":0},{"frame":"heart2","duration":150,"variability":0},{"frame":"heart1","duration":450,"variability":0}],"colors":{"0":{"r":0,"g":0,"b":0},"F":{"r":255,"g":105,"b":180}}},"squiggle":{"mode":"mirror","mirror":{"closed":"0000000000000000000000010000000000000011111111100000000000000000000000000000000000000011111111110000000111110000000000000000000000000000000000000000000000000000000000000000000000100010000000000101010100000000100010001000000000000000010000000000000000000000","open":"0000000000000000000000110000000000000011111111100000000000000000000000000000000000000011111111110000001100100100000000011000110000000000111110000000000000000000000000000000000000100010000000000101010100000000100010001000000000000000010000000000000000000000","semi":"0000000000000000000000110000000000000011111111100000000000000000000000000000000000000011111111110000001100101100000000011111100000000000000000000000000000000000000000000000000000100010000000000101010100000000100010001000000000000000010000000000000000000000"},"frame-sequence":[{"frame":"open","duration":2000,"variability":1000},{"frame":"semi","duration":50,"variability":10},{"frame":"closed","duration":200,"variability":100},{"frame":"semi","duration":50,"variability":10}],"colors":{"0":{"r":0,"g":0,"b":0},"1":{"r":255,"g":255,"b":255}}},"smile":{"mode":"mirror","mirror":{"closed":"0000000000000000000000011100000000000010000000000000010000000000000000000000000000000000000000001100000011111000100000011111110000000000000000000000000000000000000000000000000000000001100000000000000010000000000000100000000011111100000000000000000000000000","open":"0000000000000000000000011100000000000010000000000000010000111000000000000111110000000000111111101100000111111110100000011111110000000000111110000000000000000000000000000000000000000001100000000000000010000000000000100000000011111100000000000000000000000000","semi":"0000000000000000000000011100000000000010000000000000010000000000000000000011100000000000111111101100000111111110100000011111110000000000111110000000000000000000000000000000000000000001100000000000000010000000000000100000000011111100000000000000000000000000"},"frame-sequence":[{"frame":"open","duration":2000,"variability":1000},{"frame":"semi","duration":50,"variability":10},{"frame":"closed","duration":200,"variability":100},{"frame":"semi","duration":50,"variability":10}],"colors":{"0":{"r":0,"g":0,"b":0},"1":{"r":255,"g":255,"b":255}}},"gay":{"mode":"mirror","mirror":{"straight":"0000000000000000000000000000000001111111111111100111111111111110022222222222222002222222222222200333333333333330033333333333333004444444444444400444444444444440055555555555555005555555555555500666666666666660066666666666666000000000000000000000000000000000","wiggly":"0000000000000000001111000000000001111111100000100122221111111110022222222111112002333322222222200333333332222230034444333333333004444444433333400455554444444440055555555444445005666655555555500666666665555560060000666666666000000000066666000000000000000000"},"frame-sequence":[{"frame":"straight","duration":1500,"variability":500},{"frame":"wiggly","duration":1500,"variability":500}],"colors":{"0":{"r":0,"g":0,"b":0},"1":{"r":227,"g":1,"b":2},"2":{"r":254,"g":143,"b":0},"3":{"r":255,"g":237,"b":5},"4":{"r":2,"g":128,"b":40},"5":{"r":0,"g":76,"b":251},"6":{"r":154,"g":80,"b":171}}},"blush":{"mode":"mirror","mirror":{"closed":"0000000000000000000000111100000000000100000000000000000000000000000000000111110000000001111111111100011111000011100001100000000000000000002020200000000002020200000000000000000000000001100000000000000010000000000000100000000011111100000000000000000000000000","open":"0000000000000000000000111100000000000100000000000000000111111110000000111111111100000111111111111100011111111000100000111000000000000000002020200000000002020200000000000000000000000001100000000000000010000000000000100000000011111100000000000000000000000000"},"frame-sequence":[{"frame":"open","duration":2000,"variability":1000},{"frame":"closed","duration":300,"variability":150}],"colors":{"0":{"r":0,"g":0,"b":0},"1":{"r":255,"g":255,"b":255},"2":{"r":255,"g":0,"b":190}}}})";

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
            debugLog("Expression ");
            debugLog(expression_i, DEC);
            debugLog(" named ");
            debugLog(name);
            debugLog(" contains ");
            debugLog(data);

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