#ifndef Application_h
#define Application_h

#include "../Main.h"
#include <LittleFS.h>
#ifdef ESP8266
#include <ESP8266WebServer.h>
using WebServer = ESP8266WebServer;
#define SERVER_KEEPALIVE_FALSE() server.keepAlive(false);
#else
#include <WebServer.h>
#define SERVER_KEEPALIVE_FALSE()
#endif
#include <ArduinoJson.h>
#include <Ticker.h>

class Application
{
protected:
  typedef enum
  {
    status,
    config
  } WebPageForPlaceHolder;

  typedef enum
  {
    Core,
    WifiMan,
    Application1
  } Applications;

  char _appId;
  String _appName;
  Application **_applicationList;
  bool _reInit = false;

  // already built methods
  bool saveConfig();
  bool loadConfig();

  // specialization required from the application
  virtual void setConfigDefaultValues() = 0;
  virtual bool parseConfigJSON(JsonDocument &doc, bool fromWebPage = false) = 0;
  virtual String generateConfigJSON(bool forSaveFile = false) = 0;
  virtual String generateStatusJSON() = 0;
  virtual bool appInit(bool reInit = false) = 0;
  virtual const PROGMEM char *getHTMLContent(WebPageForPlaceHolder wp) = 0;
  virtual size_t getHTMLContentSize(WebPageForPlaceHolder wp) = 0;
  virtual void appInitWebServer(WebServer &server, bool &shouldReboot, bool &pauseApplication) = 0;
  virtual void appRun() = 0;

public:
  // already built methods
  Application(char appId, String appName, Application **applicationList) : _appId(appId), _appName(appName), _applicationList(applicationList) {}

  void init(bool skipExistingConfig);
  void initWebServer(WebServer &server, bool &shouldReboot, bool &pauseApplication);
  void run();
};

#endif