#include "WirelessBase.h"

//------------------------------------------
// Used to initialize configuration properties to default values
void MyApplication::setConfigDefaultValues()
{
  // TODO
  // property1 = 0;
  // property2 = F("test");
}

//------------------------------------------
// Parse JSON object into configuration properties
void MyApplication::parseConfigJSON(JsonDocument &doc, bool fromWebPage = false)
{
  // TODO
  // JsonVariant jv;
  // if ((jv = doc["prop1"]).is<uint8_t>())
  //   property1 = jv.as<uint8_t>();
  // if ((jv = doc["prop2"]).is<const char *>() && strlen(jv.as<const char *>()) < sizeof(property2))
  //   strcpy(property2, jv.as<const char *>());
}

//------------------------------------------
// Parse HTTP POST parameters in request into configuration properties
bool MyApplication::parseConfigWebRequest(WebServer &server)
{
  // TODO
  // config json is received in POST body (arg("plain"))

  // JsonDocument doc;
  // DeserializationError error = deserializeJson(doc, server.arg("plain"));
  // if (error)
  // {
  //   SERVER_KEEPALIVE_FALSE()
  //   server.send(400, F("text/html"), F("Invalid JSON"));
  //   return false;
  // }

  // // basic control
  // if (!doc["prop1"].is<JsonVariant>())
  // {
  //   SERVER_KEEPALIVE_FALSE()
  //   server.send(400, F("text/html"), F("prop1 missing"));
  //   return false;
  // }

  // parseConfigJSON(doc, true);

  return true;
}

//------------------------------------------
// Generate JSON from configuration properties
String MyApplication::generateConfigJSON(bool forSaveFile = false)
{
  JsonDocument doc;

  // TODO
  // doc["p1"] = property1;
  // doc["p2"] = property2;

  String gc;
  serializeJson(doc, gc);

  return gc;
}

//------------------------------------------
// Generate JSON of application status
String MyApplication::generateStatusJSON()
{
  JsonDocument doc;

  // TODO
  // doc["p1"] = property1;
  // doc["p2"] = property2;

  String gs;
  serializeJson(doc, gs);

  return gs;
}

//------------------------------------------
// code to execute during initialization and reinitialization of the app
bool MyApplication::appInit(bool reInit)
{
  // TODO
  // if (toto.enabled) _sendTimer.setInterval(SEND_PERIOD, [this]() {this->SendTimerTick();});

  return true;
}

//------------------------------------------
// Return HTML Code to insert into Status Web page
const PROGMEM char *MyApplication::getHTMLContent(WebPageForPlaceHolder wp)
{
  switch (wp)
  {
  case status:
    return status1htmlgz;
    break;
  case config:
    return config1htmlgz;
    break;
  default:
    return nullptr;
    break;
  };
  return nullptr;
}

// and his Size
size_t MyApplication::getHTMLContentSize(WebPageForPlaceHolder wp)
{
  switch (wp)
  {
  case status:
    return sizeof(status1htmlgz);
    break;
  case config:
    return sizeof(config1htmlgz);
    break;
  default:
    return 0;
    break;
  };
  return 0;
}

//------------------------------------------
// code to register web request answer to the web server
void MyApplication::appInitWebServer(WebServer &server, bool &shouldReboot, bool &pauseApplication)
{
  // TODO
  // server.on("/getColor", HTTP_GET, [this, &server]() {server.send(200, F("text/html"), GetColor());});
}

//------------------------------------------
// Run for timer
void MyApplication::appRun()
{
#if ENABLE_STATUS_EVTSRC
  // last time status event source was sent
  static unsigned long lastEvtSrcSentMillis;

  unsigned long currentMillis = millis();

  if (currentMillis - lastEvtSrcSentMillis >= 10000)
  {                                                         // Check if it's time to send a new event
    statusEventSourceBroadcast(F("{\"Hello\":\"World\"}")); // Send a message to all connected clients
    lastEvtSrcSentMillis = currentMillis;
  }
#endif

  // TODO : implement run tasks (receive from serial, run timer, etc.)
}

//------------------------------------------
// Constructor
MyApplication::MyApplication(char appId, String appName) : Application(appId, appName)
{
  // TODO : Initialize special structure or libraries in constructor
  // Note : most of the time, init is done during AppInit based on configuration
}