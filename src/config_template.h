
#define DEBUG

#ifdef DEBUG
#define debugLog(args...) Serial.print(args)
#define debugLogLine(args...) Serial.println(args)
#else
#define debugLog(args...)
#define debugLogLine(args...)
#endif

// SW INITIALIZATION
#define ANIMATION_BOOK_JSON_SIZE 8000 // set number equal to length of the JSON string or more, crashes when too big tho...

#ifdef DEBUG
#define WIFI_NAME ""
#define WIFI_PASSWORD ""
#else
#define WIFI_NAME ""
#define WIFI_PASSWORD ""
#endif

// HW INITIALIZAITON
#define LED_DISPLAY_WIDTH 16
#define LED_DISPLAY_HEIGHT 16
#define LEDS_PER_DISPLAY LED_DISPLAY_WIDTH *LED_DISPLAY_HEIGHT
#define DATA_PIN_LEFT 32
#define DATA_PIN_RIGHT 33

#define FAN_PIN_LEFT 25
#define FAN_PIN_RIGHT 26
#define FAN_CCHANNEL 0
#define FAN_PWM_FREQ 20

#define TELEMETRY_SDA 21 // does not change the pin ESP is using
#define TELEMETRY_SCL 22 // does not change the pin ESP is using

// BEHAVIOUR INITIALIZATION
#define STARTUP_ANIMATION "smile"
#define DEFAULT_FAN_SPEED 10
#define DEFAULT_BRIGHTNESS 1
