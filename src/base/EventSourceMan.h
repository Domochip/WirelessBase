#ifndef EventSourceMan_h
#define EventSourceMan_h

#include "../Main.h"
#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
using WebServer = ESP8266WebServer;
#else
#include <WiFi.h>
#include <WebServer.h>
#endif

#include <Ticker.h>

class EventSourceMan
{
private:
#if ENABLE_EVTSRC
    WiFiClient _EventSourceClientList[STATUS_EVTSRC_MAX_CLIENTS];
#if ENABLE_EVTSRC_KEEPALIVE
    bool _needEventSourceKeepAlive = false;
    Ticker _eventSourceKeepAliveTicker;
#endif
#endif

public:
    void initEventSourceServer(char appId, WebServer &server);

#if ENABLE_EVTSRC
    void eventSourceHandler(WebServer &server);
    void eventSourceBroadcast(const String &message, const String &eventType = "message");
#if ENABLE_EVTSRC_KEEPALIVE
    void eventSourceKeepAlive();
#endif
#endif
};

#endif