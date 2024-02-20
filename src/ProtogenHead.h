#ifndef PROTOGENHEAD_H
#define PROTOGENHEAD_H

#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include "config.h"
#include <Arduino.h>



typedef struct ProtogenHead
{
    Adafruit_NeoPixel *left_leds;
    Adafruit_NeoPixel *right_leds;
    Adafruit_SH1106 *telemetry;
    SemaphoreHandle_t telemetry_needs_update;
    int fan_speed;
    char telemetry_message[21];
} ProtogenHead;

Adafruit_NeoPixel left_display(LEDS_PER_DISPLAY, DATA_PIN_LEFT, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel right_display(LEDS_PER_DISPLAY, DATA_PIN_RIGHT, NEO_GRB + NEO_KHZ800);
Adafruit_SH1106 telemetry_display(TELEMETRY_SDA, TELEMETRY_SCL);

ProtogenHead *makeHead()
{
    ProtogenHead *head = new ProtogenHead();
    Serial.println("  display initialization");

    head->left_leds = &left_display;
    head->left_leds->setBrightness(DEFAULT_BRIGHTNESS);
    head->left_leds->begin();

    head->right_leds = &right_display;
    head->right_leds->setBrightness(DEFAULT_BRIGHTNESS);
    head->right_leds->begin();

    Serial.println("  telemetry initialization");
    head->telemetry = &telemetry_display;
    head->telemetry->begin(SH1106_EXTERNALVCC, 0x3C);
    head->telemetry->setRotation(2);
    head->telemetry->setTextSize(1);
    head->telemetry->setTextColor(WHITE);
    head->telemetry->cp437(true);
    head->telemetry->setCursor(0, 0); // Start at top-left corner
    head->telemetry->println("Proto-proto-protogen!\n");
    head->telemetry->setTextSize(2);
    head->telemetry->println("\\(^w^)/");
    head->telemetry->setTextSize(1);
    head->telemetry->println("");
    head->telemetry->println("Looking for wifi: ");
    head->telemetry->println(WIFI_NAME);
    head->telemetry->println(WIFI_PASSWORD);
    head->telemetry->display();

    head->telemetry_needs_update = xSemaphoreCreateMutex();

    strncpy(head->telemetry_message, "", sizeof(head->telemetry_message));

    // Serial.println("  fan initialization");
    // pinMode(FAN_PWM_PIN, OUTPUT);
    // ledcAttachPin(FAN_PWM_PIN, FAN_CCHANNEL);
    // ledcSetup(FAN_CCHANNEL, FAN_PWM_FREQ, 8);
    // head->fan_speed = DEFAULT_FAN_SPEED;
    return head;
}

uint8_t XY(uint8_t x, uint8_t y)
{
    // any out of bounds address maps to the first hidden pixel
    if ((x >= LED_DISPLAY_WIDTH) || (y >= LED_DISPLAY_HEIGHT))
    {
        return 0;
    }

    const uint8_t XYTable[] = {
        0, 31, 32, 63, 64, 95, 96, 127, 128, 159, 160, 191, 192, 223, 224, 255,
        1, 30, 33, 62, 65, 94, 97, 126, 129, 158, 161, 190, 193, 222, 225, 254,
        2, 29, 34, 61, 66, 93, 98, 125, 130, 157, 162, 189, 194, 221, 226, 253,
        3, 28, 35, 60, 67, 92, 99, 124, 131, 156, 163, 188, 195, 220, 227, 252,
        4, 27, 36, 59, 68, 91, 100, 123, 132, 155, 164, 187, 196, 219, 228, 251,
        5, 26, 37, 58, 69, 90, 101, 122, 133, 154, 165, 186, 197, 218, 229, 250,
        6, 25, 38, 57, 70, 89, 102, 121, 134, 153, 166, 185, 198, 217, 230, 249,
        7, 24, 39, 56, 71, 88, 103, 120, 135, 152, 167, 184, 199, 216, 231, 248,
        8, 23, 40, 55, 72, 87, 104, 119, 136, 151, 168, 183, 200, 215, 232, 247,
        9, 22, 41, 54, 73, 86, 105, 118, 137, 150, 169, 182, 201, 214, 233, 246,
        10, 21, 42, 53, 74, 85, 106, 117, 138, 149, 170, 181, 202, 213, 234, 245,
        11, 20, 43, 52, 75, 84, 107, 116, 139, 148, 171, 180, 203, 212, 235, 244,
        12, 19, 44, 51, 76, 83, 108, 115, 140, 147, 172, 179, 204, 211, 236, 243,
        13, 18, 45, 50, 77, 82, 109, 114, 141, 146, 173, 178, 205, 210, 237, 242,
        14, 17, 46, 49, 78, 81, 110, 113, 142, 145, 174, 177, 206, 209, 238, 241,
        15, 16, 47, 48, 79, 80, 111, 112, 143, 144, 175, 176, 207, 208, 239, 240};

    uint8_t i = (y * LED_DISPLAY_WIDTH) + x;
    uint8_t j = XYTable[i];

    return j;
}

#endif