#include "MQTTMan.h"

bool MQTTMan::connect(bool firstConnection)
{
    char sn[9];
#ifdef ESP8266
    sprintf_P(sn, PSTR("%08x"), ESP.getChipId());
#else
    sprintf_P(sn, PSTR("%08x"), (uint32_t)(ESP.getEfuseMac() << 40 >> 40));
#endif

    // generate clientID
    String clientID(F(APPLICATION1_NAME));
    clientID += sn;

    // Connect
    char *username = (_username[0] ? _username : nullptr);
    char *password = (_username[0] ? _password : nullptr);
    char willTopic[80] = {0};
    if (_baseTopic[0] && _connectedAndWillSubTopic[0])
        sprintf_P(willTopic, PSTR("%s%s"), _baseTopic, _connectedAndWillSubTopic);

    const char *willMessage = (_baseTopic[0] && _connectedAndWillSubTopic[0] ? "0" : nullptr);
    PubSubClient::connect(clientID.c_str(), username, password, (willTopic[0] ? willTopic : nullptr), 0, true, willMessage, true);

    if (connected())
    {
        if (willTopic[0])
            publish(willTopic, "1", true);

        // Subscribe to needed topic
        if (_connectedCallBack)
            _connectedCallBack(this, firstConnection);
    }

    return connected();
}

void MQTTMan::prepareTopic(String &topic)
{
    if (topic.indexOf(F("$sn$")) != -1)
    {
        char sn[9];
#ifdef ESP8266
        sprintf_P(sn, PSTR("%08x"), ESP.getChipId());
#else
        sprintf_P(sn, PSTR("%08x"), (uint32_t)(ESP.getEfuseMac() << 40 >> 40));
#endif
        topic.replace(F("$sn$"), sn);
    }

    if (topic.indexOf(F("$mac$")) != -1)
        topic.replace(F("$mac$"), WiFi.macAddress());

    if (topic.indexOf(F("$model$")) != -1)
        topic.replace(F("$model$"), APPLICATION1_NAME);

    // check for final slash
    if (topic.length() && topic.charAt(topic.length() - 1) != '/')
        topic += '/';
}

MQTTMan &MQTTMan::setBaseTopic(const char *baseTopic)
{
    if (!baseTopic)
        _baseTopic[0] = 0;
    else
    {
        String topic(baseTopic);
        prepareTopic(topic);
        strlcpy(_baseTopic, topic.c_str(), sizeof(_baseTopic));
    }

    return *this;
}

MQTTMan &MQTTMan::setConnectedAndWillSubTopic(const char *subTopic)
{
    if (!subTopic)
        _connectedAndWillSubTopic[0] = 0;
    else
        strlcpy(_connectedAndWillSubTopic, subTopic, sizeof(_connectedAndWillSubTopic));

    return *this;
}

MQTTMan &MQTTMan::setConnectedCallback(CONNECTED_CALLBACK_SIGNATURE connectedCallback)
{
    _connectedCallBack = connectedCallback;
    return *this;
}

MQTTMan &MQTTMan::setDisconnectedCallback(DISCONNECTED_CALLBACK_SIGNATURE disconnectedCallback)
{
    _disconnectedCallBack = disconnectedCallback;
    return *this;
}

bool MQTTMan::connect(const char *username, const char *password)
{
    // check logins
    if (username && strlen(username) >= sizeof(_username))
        return false;
    if (password && strlen(password) >= sizeof(_password))
        return false;

    if (username)
        strlcpy(_username, username, sizeof(_username));
    else
        _username[0] = 0;

    if (password)
        strlcpy(_password, password, sizeof(_password));
    else
        _password[0] = 0;

    return connect(true);
}

void MQTTMan::disconnect()
{
    // publish disconnected just before disconnect...
    if (_baseTopic[0] && _connectedAndWillSubTopic[0])
    {
        String topic(_baseTopic);
        topic += _connectedAndWillSubTopic;

        publish(topic.c_str(), "0", true);
    }

    // Stop MQTT Reconnect
    _mqttReconnectTicker.detach();
    // Disconnect
    if (connected()) // Issue #598 : disconnect() crash if client not yet set
    {
        PubSubClient::disconnect();
        // call disconnected callback if set
        if (_disconnectedCallBack)
            _disconnectedCallBack();
    }
}

bool MQTTMan::loop()
{
    if (state() != MQTT_DISCONNECTED)
    {
        // evaluate connection status and call disconnected callback if needed
        // if we are not connected, reconnect ticker not started nor _needMqttReconnect flag raised and disconnected callback set
        if (!connected() && !(_mqttReconnectTicker.active() || _needMqttReconnect) && _disconnectedCallBack)
            _disconnectedCallBack();

        if (_needMqttReconnect)
        {
            _needMqttReconnect = false;
#ifdef LOG_SERIAL
            LOG_SERIAL.print(F("MQTT Reconnection : "));
#endif
            bool res = connect(false);
#ifdef LOG_SERIAL
            if (res)
                LOG_SERIAL.println(F("OK"));
            else
                LOG_SERIAL.println(F("Failed"));
#endif
        }

        // if not connected and reconnect ticker not started
        if (!connected() && !_mqttReconnectTicker.active())
        {
#ifdef LOG_SERIAL
            LOG_SERIAL.println(F("MQTT Disconnected"));
#endif
            // set Ticker to reconnect after 20 or 60 sec (Wifi connected or not)
#ifdef ESP8266
            _mqttReconnectTicker.once((WiFi.isConnected() ? 20 : 60), [this]()
                                      { _needMqttReconnect = true; });

#else
            _mqttReconnectTicker.once<typeof this>((WiFi.isConnected() ? 20 : 60), [](typeof this mqttMan)
                                                   { mqttMan->_needMqttReconnect = true; }, this);
#endif
        }

        return PubSubClient::loop();
    }
    return true;
}

bool MQTTMan::publishToConnectedTopic(const char *payload)
{
    if (_baseTopic[0] && _connectedAndWillSubTopic[0])
    {
        String topic(_baseTopic);
        topic += _connectedAndWillSubTopic;

        return publish(topic.c_str(), payload, true);
    }
    return false;
}