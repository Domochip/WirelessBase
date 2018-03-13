#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include "WirelessBase.h"


//Return JSON of AppData1 content
String AppData1::GetJSON() {

  String gc;

  //TODO : build JSON string for config webpage without {}

  return gc;
}

//Parse HTTP Request into an AppData1 structure
bool AppData1::SetFromParameters(AsyncWebServerRequest* request, AppData1 &tempAppData1) {

  //TODO : Parse HTTP request from config web page into tempAppData1
  
  return true;
}




//------------------------------------------
//return MyClass Status in JSON
String MyClass::GetStatus() {

  String statusJSON('{');
  //TODO : build JSON answer
  statusJSON += '}';

  return statusJSON;
}


//------------------------------------------
//Function to initiate MyClass with Config
void MyClass::Init(AppData1 &appData1) {

  Serial.print(F("Start MyClass"));

  _appData1 = &appData1;

  //TODO : Initialiaze

  Serial.println(F(" : OK"));
}

//------------------------------------------
void MyClass::InitWebServer(AsyncWebServer &server) {

  server.on("/gs1", HTTP_GET, [this](AsyncWebServerRequest * request) {
    request->send(200, F("text/json"), GetStatus());
  });

  //TODO : Implement required Webpage responses
}

//------------------------------------------
//Run for timer
void MyClass::Run() {

  //TODO : implement run tasks (receive from serial, run timer, etc.)
}
