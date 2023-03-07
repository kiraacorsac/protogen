
#define DEBUG

#ifdef DEBUG
#define log(s) Serial.print(s)
#define logln(s) Serial.println(s)
#else
#define log(s)
#define logln(s)
#endif

// SW INITIALIZATION
#define ANIMATION_BOOK_JSON_SIZE 4000 // set number equal to length of the JSON string or more

#ifdef DEBUG
#define WIFI_NAME ""
#define WIFI_PASSWORD ""
#else
#define WIFI_NAME ""
#define WIFI_NAME ""
#endif

// HW INITIALIZAITON
#define LED_DISPLAY_WIDTH 16
#define LED_DISPLAY_HEIGHT 16
#define LEDS_PER_DISPLAY LED_DISPLAY_WIDTH *LED_DISPLAY_HEIGHT
#define DATA_PIN_LEFT 4
#define DATA_PIN_RIGHT 14
#define BRIGHTNESS 1

// BEHAVIOUR INITIALIZATION
#define STARTUP_ANIMATION "idle"
