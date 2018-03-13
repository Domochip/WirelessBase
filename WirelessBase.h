#ifndef WirelessBase_h
#define WirelessBase_h

#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "Main.h"
#include "src\Utils.h"


const char appDataPredefPassword[] PROGMEM = "ewcXoCt4HHjZUvY1";

//Structure of Application Data 1
class AppData1 {

  public:
    //TODO : declare required properties

    void SetDefaultValues() {
      //TODO : init properties
    }

    String GetJSON();
    bool SetFromParameters(AsyncWebServerRequest* request, AppData1 &tempAppData);
};

//TODO : Rename MyClass
class MyClass {

  private:
    AppData1* _appData1;

    //TODO : Declare private properies and method

    String GetStatus();

  public:
    void Init(AppData1 &appData1);
    void InitWebServer(AsyncWebServer &server);
    void Run();
};

#endif
