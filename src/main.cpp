#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#include "volatileEnvironment.h"

#include "ProtogenHead.h"
#include "AnimationBook.h"
#include "config.h"
#include "loop.h"

void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
  debugLogLine("WiFi lost connection. Reason: ");
  debugLogLine(info.wifi_sta_disconnected.reason);
  delay(30000);
  debugLog("Trying to reconnect to ");
  debugLogLine(WIFI_NAME);
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
  debugLog(".");
}

AsyncWebServer server(80); // Create a web server on port 80

void handleTestConnection(AsyncWebServerRequest *request)
{
  Serial.println("test request received");
  request->send(200, "text/plain", "working");
}

void handleAnimation(AsyncWebServerRequest *request)
{
  const char *anim = request->arg("name").c_str();
  strcpy((char *)current_animation, anim);

  request->send(200, "text/plain", "ok");
  Serial.print("Setting the animation on ");
  Serial.println(anim);

  return;
}

void handleBrightness(AsyncWebServerRequest *request)
{
  uint8_t brightness = request->arg("value").toInt();
  head->left_leds->setBrightness(brightness);
  head->right_leds->setBrightness(brightness);

  request->send(200, "text/plain", "ok");

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
  WiFi.onEvent(WiFiStationDisconnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
  debugLog("Trying to connect to ");
  debugLogLine(WIFI_NAME);

  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(2000);
    Serial.print(".");
  }

  Serial.print("Connected to WiFi as ");
  Serial.println(WiFi.localIP());

  server.on("/test", HTTP_GET, handleTestConnection);
  server.on("/animation", HTTP_GET, handleAnimation);
  server.on("/brightness", HTTP_GET, handleBrightness);
  DefaultHeaders::Instance().addHeader(F("Access-Control-Allow-Origin"), F("*"));
  DefaultHeaders::Instance().addHeader(F("Access-Control-Allow-Headers"), F("content-type"));

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
