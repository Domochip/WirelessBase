#ifndef WirelessBase_h
#define WirelessBase_h

#include "Main.h"
#include "base\Utils.h"
#include "base\MQTTMan.h"
#include "base\Application.h"

const char appDataPredefPassword[] PROGMEM = "ewcXoCt4HHjZUvY1";

#include "data\status1.html.gz.h"
#include "data\config1.html.gz.h"

//TODO : Rename MyApplication
class MyApplication : public Application
{
private:
  //TODO : Declare configuration properies

  //TODO : Declare run/status properties

  //TODO : Declare required private methods

  void setConfigDefaultValues();
  void parseConfigJSON(DynamicJsonDocument &doc);
  bool parseConfigWebRequest(ESP8266WebServer &server);
  String generateConfigJSON(bool forSaveFile);
  String generateStatusJSON();
  bool appInit(bool reInit);
  const PROGMEM char *getHTMLContent(WebPageForPlaceHolder wp);
  size_t getHTMLContentSize(WebPageForPlaceHolder wp);
  void appInitWebServer(ESP8266WebServer &server, bool &shouldReboot, bool &pauseApplication);
  void appRun();

public:
  MyApplication(char appId, String fileName);
};

#endif
