// #define DISPLAYTEST
#ifdef DISPLAYTEST
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

#define OLED_SDA 21
#define OLED_SCL 22

Adafruit_SH1106 display(OLED_SDA, OLED_SCL);
int loopn = 0;

void setup()
{
    Serial.begin(9600);
    Serial.printf("Initing!");
    // C 32, D the big one 
    display.begin(SH1106_EXTERNALVCC, 0x3C);
    display.clearDisplay();
    Serial.printf("Done!");
}
void loop()
{
    /* set text size, color, cursor position,
    set buffer with  Hello world and show off*/
    Serial.printf("loop!");
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Hello, world! How long of a thing I can write here? Let's try!");
    display.println(loopn);

    display.display();
    delay(2000);
    display.clearDisplay();
    loopn += 1;
}
#endif