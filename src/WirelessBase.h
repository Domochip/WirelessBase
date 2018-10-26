#ifndef WirelessBase_h
#define WirelessBase_h

#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "Main.h"
#include "base\Utils.h"
#include "base\Base.h"

#include "data\status1.html.gz.h"
#include "data\config1.html.gz.h"
#include "data\fw1.html.gz.h"
#include "data\discover1.html.gz.h"

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
  const uint8_t* GetHTMLContent(WebPageForPlaceHolder wp);
  size_t GetHTMLContentSize(WebPageForPlaceHolder wp);
  void AppInitWebServer(AsyncWebServer &server, bool &shouldReboot, bool &pauseApplication);
  void AppRun();

public:
  MyApplication(char appId, String fileName);
};

#endif
