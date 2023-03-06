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

uint8_t getColorMonochromeHex(String data, int x, int y)
{
    return hexCharToByte(data[x * 16 + y]);
}
