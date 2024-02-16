#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <mutex>

#include "volatileEnvironment.h"

#include "ProtogenHead.h"
#include "AnimationBook.h"
#include "config.h"
#include "loop.h"

#define MAIN
#ifdef MAIN
void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info)
{

  debugLogLine("WiFi lost connection. Reason: ");
  debugLogLine(info.wifi_sta_disconnected.reason);
  WiFi.disconnect(true, true);
  delay(30000);
  debugLog("Trying to reconnect to '");
  debugLog(WIFI_NAME);
  debugLog("' '");
  debugLog(WIFI_PASSWORD);
  debugLogLine("'.");
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

  head->telemetry_needs_update = true;
  debugLog(".");
}

AsyncWebServer server(80); // Create a web server on port 80

void handleTestConnection(AsyncWebServerRequest *request)
{
  Serial.println("test request received");
  request->send(200, "text/plain", "working");
}

void handleMessage(AsyncWebServerRequest *request)
{
  const char *msg = request->arg("value").c_str();
  strncpy((char *)head->telemetry_message, msg, 21);

  head->telemetry_needs_update = true;
  request->send(200, "text/plain", "ok");
}

void handleAnimation(AsyncWebServerRequest *request)
{
  const char *anim = request->arg("value").c_str();
  animation_mutex.lock();
  strcpy((char *)current_animation, anim);
  animation_mutex.unlock();

  Serial.print("Setting the animation on ");
  Serial.println(anim);

  head->telemetry_needs_update = true;
  request->send(200, "text/plain", "ok");
}

void handleBrightness(AsyncWebServerRequest *request)
{
  uint8_t brightness = request->arg("value").toInt();
  head->left_leds->setBrightness(brightness);
  head->right_leds->setBrightness(brightness);


  Serial.print("Setting the brightness on ");
  Serial.println(brightness);

  head->telemetry_needs_update = true;
  request->send(200, "text/plain", "ok");
}

void handleFanSpeed(AsyncWebServerRequest *request)
{
  uint8_t fan_speed = request->arg("value").toInt();
  head->fan_speed = fan_speed;

  Serial.print("Setting fan speed to ");
  Serial.println(fan_speed);
  head->telemetry_needs_update = true;
  request->send(200, "text/plain", "ok");
}

void setup()
{
  Serial.begin(9600); // Any baud rate should work
  delay(1000);
  Serial.println("=======Proto-proto-proto-gen!=======");
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true, true);
  // Initialize wifi
  WiFi.onEvent(WiFiStationDisconnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
  debugLog("Trying to reconnect to '");
  debugLog(WIFI_NAME);
  debugLog("' '");
  debugLog(WIFI_PASSWORD);
  debugLogLine("'.");

  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);


  server.on("/test", HTTP_GET, handleTestConnection);
  server.on("/animation", HTTP_GET, handleAnimation);
  server.on("/brightness", HTTP_GET, handleBrightness);
  server.on("/fanSpeed", HTTP_GET, handleFanSpeed);
  server.on("/telemetryMessage", HTTP_GET, handleMessage);
  DefaultHeaders::Instance().addHeader(F("Access-Control-Allow-Origin"), F("*"));
  DefaultHeaders::Instance().addHeader(F("Access-Control-Allow-Headers"), F("content-type"));

  // initialize LED library
  Serial.println("Protogen initialization...");

  head = makeHead();

  Serial.println("Protogen initialization done.");

  // initialize animations
  Serial.println("AnimationBook initialization...");

  book = makeAnimationBook();
  Serial.println("AnimationBook initialization done.");
  Serial.println("=======Setup finished=======");

  xTaskCreatePinnedToCore(protogen_loop, "Animation Task", 16384, NULL, 1, NULL, 1);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(2000);
    Serial.print(".");
  }

  Serial.print("Connected to WiFi as ");
  Serial.println(WiFi.localIP());
  head->telemetry_needs_update = true;
  // Tasks assignment
  server.begin();
}

void loop()
{
}
#endif