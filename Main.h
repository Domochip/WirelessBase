#ifndef Main_h
#define Main_h

#include "data\status.html.gz.h"
#include "data\config.html.gz.h"
#include "data\fw.html.gz.h"
#include "data\discover.html.gz.h"

//DomoChip Informations
//------------Compile for 1M 64K SPIFFS------------
//Configuration Web Pages :
//http://IP/
//http://IP/config
//http://IP/fw

//include Application header file
#include "WirelessBase.h"

#define APPLICATION_NAME "DomoChip Wireless Base"
//#define APPLICATION_CLASS MyClass
//#define APPLICATION_VAR myClass

#define VERSION_NUMBER "3.X"

#define MODEL "WBase"

#define DEFAULT_AP_SSID "WirelessBase"
#define DEFAULT_AP_PSK "PasswordBase"

//Enable developper mode (fwdev webpage and SPIFFS is used)
#define DEVELOPPER_MODE 0

//Choose Serial Speed
#define SERIAL_SPEED 115200

//Choose Pin used to boot in Rescue Mode
#define RESCUE_BTN_PIN 2

//Status LED
//#define STATUS_LED_SETUP pinMode(XX, OUTPUT);pinMode(XX, OUTPUT);
//#define STATUS_LED_OFF digitalWrite(XX, HIGH);digitalWrite(XX, HIGH);
//#define STATUS_LED_ERROR digitalWrite(XX, HIGH);digitalWrite(XX, HIGH);
//#define STATUS_LED_WARNING digitalWrite(XX, HIGH);digitalWrite(XX, HIGH);
//#define STATUS_LED_GOOD digitalWrite(XX, HIGH);digitalWrite(XX, HIGH);

//construct Version text
#if DEVELOPPER_MODE
#define VERSION VERSION_NUMBER "-DEV"
#else
#define VERSION VERSION_NUMBER
#endif

#endif


