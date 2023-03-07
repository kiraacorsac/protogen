#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#include "volatileEnvironment.h"

#include "ProtogenHead.h"
#include "AnimationBook.h"
#include "config.h"
#include "loop.h"

AsyncWebServer server(80); // Create a web server on port 80

IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

void handleTestConnection(AsyncWebServerRequest *request)
{
  Serial.println("test request received");
  request->send(200, "text/plain", "working");
}

void handleAnimation(AsyncWebServerRequest *request)
{
  const char *anim = request->arg("name").c_str();
  strcpy((char *)current_animation, anim);

  request->send(200, "text/plain", "");
  Serial.print("Setting the animation on ");
  Serial.println(anim);

  return;
}

void handleBrightness(AsyncWebServerRequest *request)
{
  uint8_t brightness = request->arg("value").toInt();
  head->left_leds->setBrightness(brightness);
  head->right_leds->setBrightness(brightness);

  request->send(200, "text/plain", "");

  Serial.print("Setting the brightness on ");
  Serial.println(brightness);

  return;
}
void setup()
{
  Serial.begin(9600); // Any baud rate should work
  delay(1000);
  Serial.println("=======Proto-proto-proto-gen!=======");

  // Initialize wifi
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Connected to WiFi as ");
  Serial.println(WiFi.localIP());

  server.on("/test", HTTP_GET, handleTestConnection);
  server.on("/animation", HTTP_GET, handleAnimation);
  server.on("/brightness", HTTP_GET, handleBrightness);

  // initialize LED library
  Serial.println("LED initialization...");

  head = makeHead();
  head->left_leds->setBrightness(BRIGHTNESS);
  head->left_leds->begin();

  head->right_leds->setBrightness(BRIGHTNESS);
  head->right_leds->begin();

  Serial.println("LED initializaion done.");

  // initialize animations
  Serial.println("AnimationBook initialization...");

  book = makeAnimationBook();
  Serial.println("AnimationBook initialization done.");
  Serial.println("=======Setup finshed=======");

  // Tasks assignment
  server.begin();

  xTaskCreatePinnedToCore(animation_frame, "Animation Task", 4086, NULL, 1, NULL, 1);
}

void loop()
{
  // server.handleClient(); // Listen for incoming client requests
  // animation_frame(nullptr);
}
