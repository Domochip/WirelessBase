#ifndef WirelessBase_h
#define WirelessBase_h

#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "Main.h"
#include "src\Utils.h"
#include "src\Base.h"

const char appDataPredefPassword[] PROGMEM = "ewcXoCt4HHjZUvY1";

//TODO : Rename MyApplication
class MyApplication : public Application
{
private:
  //TODO : Declare configuration properies

  //TODO : Declare run/status properties

  //TODO : Declare required private methods

  void SetConfigDefaultValues();
  void ParseConfigJSON(JsonObject &root);
  bool ParseConfigWebRequest(AsyncWebServerRequest *request);
  String GenerateConfigJSON(bool forSaveFile);
  String GenerateStatusJSON();
  bool AppInit(bool reInit);
  void AppInitWebServer(AsyncWebServer &server, bool &shouldReboot, bool &pauseApplication);
  void AppRun();

public:
  MyApplication(char appId, String fileName);
};

#endif
