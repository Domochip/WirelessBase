#ifndef Main_h
#define Main_h

#include <Arduino.h>

// DomoChip Informations
// Configuration Web Pages :
// http://IP/

#define APPLICATION1_HEADER "WirelessBase.h"
#define APPLICATION1_NAME "WBase"
#define APPLICATION1_DESC "DomoChip Wireless Base"
#define APPLICATION1_CLASS MyApplication

#define VERSION_NUMBER "3.0.0"

#define DEFAULT_AP_SSID "WirelessBase"
#define DEFAULT_AP_PSK "PasswordBase"

// Control EventSource code
#define EVTSRC_ENABLED 1
#define EVTSRC_MAX_CLIENTS 2
#define EVTSRC_KEEPALIVE_ENABLED 1

// Enable developper mode
#define DEVELOPPER_MODE 0

// Log Serial Object
#define LOG_SERIAL Serial
// Choose Log Serial Speed
#define LOG_SERIAL_SPEED 115200

// Choose Pin used to boot in Rescue Mode
#define RESCUE_BTN_PIN 2

// Define time to wait for Rescue press (in s)
// #define RESCUE_BUTTON_WAIT 3

// Status LED
// #define STATUS_LED_SETUP pinMode(XX, OUTPUT);pinMode(XX, OUTPUT);
// #define STATUS_LED_OFF digitalWrite(XX, HIGH);digitalWrite(XX, HIGH);
// #define STATUS_LED_ERROR digitalWrite(XX, HIGH);digitalWrite(XX, HIGH);
// #define STATUS_LED_WARNING digitalWrite(XX, HIGH);digitalWrite(XX, HIGH);
// #define STATUS_LED_GOOD digitalWrite(XX, HIGH);digitalWrite(XX, HIGH);

// construct Version text
#if DEVELOPPER_MODE
#define VERSION VERSION_NUMBER "-DEV"
#else
#define VERSION VERSION_NUMBER
#endif

#endif