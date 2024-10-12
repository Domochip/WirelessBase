#ifndef MQTTMan_h
#define MQTTMan_h

#include "../Main.h"
#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

#include <Ticker.h>
#include <PubSubClient.h>

#define CONNECTED_CALLBACK_SIGNATURE std::function<void(MQTTMan * mqttMan, bool firstConnection)>
#define DISCONNECTED_CALLBACK_SIGNATURE std::function<void()>

class MQTTMan : private PubSubClient
{
private:
    char _username[64] = {0};
    char _password[64] = {0};
    char _baseTopic[65] = {0};
    char _connectedAndWillSubTopic[16] = {0};
    bool _needMqttReconnect = false;
    Ticker _mqttReconnectTicker;

    CONNECTED_CALLBACK_SIGNATURE _connectedCallBack = nullptr;
    DISCONNECTED_CALLBACK_SIGNATURE _disconnectedCallBack = nullptr;

    bool connect(bool firstConnection);

public:
    const char *getBaseTopic() { return _baseTopic; }

    static void prepareTopic(String &topic);

    using PubSubClient::beginPublish;
    using PubSubClient::connected;
    using PubSubClient::endPublish;
    using PubSubClient::getBufferSize;
    using PubSubClient::publish;
    using PubSubClient::publish_P;
    using PubSubClient::setBufferSize;
    using PubSubClient::setCallback;
    using PubSubClient::setClient;
    using PubSubClient::setServer;
    using PubSubClient::state;
    using PubSubClient::subscribe;
    
    MQTTMan &setBaseTopic(const char *baseTopic);
    MQTTMan &setConnectedAndWillSubTopic(const char *subTopic);
    MQTTMan &setConnectedCallback(CONNECTED_CALLBACK_SIGNATURE connectedCallback);
    MQTTMan &setDisconnectedCallback(DISCONNECTED_CALLBACK_SIGNATURE disconnectedCallback);
    bool connect(const char *username = nullptr, const char *password = nullptr);
    void disconnect();
    bool loop();
    bool publishToConnectedTopic(const char *payload);
};

#endif