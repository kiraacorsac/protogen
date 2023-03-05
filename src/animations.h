#include <Arduino.h>
#include "config.h"

uint8_t hexCharToByte(char c)
{
    if (c >= '0' && c <= '9')
    {
        return (c - '0') * 16;
    }
    if (c >= 'A' && c <= 'F')
    {
        return (c - 'A' + 10) * 16;
    }
    return 0;
}

uint8_t getColorMonochromeHex(char *data, String animation, String display, String frame, int x, int y)
{
    return hexCharToByte(data[x * 16 + y]);
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