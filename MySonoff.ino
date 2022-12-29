#include <WiFiClient.h>
#include <EEPROM.h>

#ifdef ESP8266
    #include <ESP8266WebServer.h>
#elif ESP32
    #include <WebServer.h>
#endif

#define HTTP_WEB_PORT 80
#define SERIAL_BANDRATE 115200L

#include <WebAPI.h>
#include <WifiCtrl.h>

#include "src/Settings/Settings.h"
#include "src/Basic/SonoffBasic.h"
#include "src/MiniR2/SonoffMiniR2.h"
#include "src/POWR2/SonoffPOWR2.h"

WifiCtrl wifi(&WiFi, false, "device-iot-help", "12345678");

#ifdef ESP8266
    ESP8266WebServer server(HTTP_WEB_PORT);
#elif ESP32
    WebServer server(HTTP_WEB_PORT);
#endif

Settings settings;
WebAPI webApi(&server);
SonoffDevice *device;

void setup(){
  Serial.begin(SERIAL_BANDRATE); 
  settings.load();
 
  switch (settings.getModel())
  {
    case SonoffModel::smBasic:
      device = new SonoffBasic(&settings);
      break;
    case SonoffModel::smMiniR2:
      device = new SonoffMiniR2(&settings);
      break;
    #ifndef ESP32
    case SonoffModel::smPowR2:
      device = new SonoffPOWR2(&settings);
      break;
    #endif
    default:
      device = new SonoffBasic(&settings);
      break;
  }
  
  
  wifi.begin(settings.getDeviceName(), settings.getSSID(), settings.getSSIDPass());

  webApi.begin();
  webApi.addHandler("/settings", &settings);
  device->registerWebAPIHandler(&webApi);    
  
  server.begin();

  device->setup();
}

void loop(){
  wifi.loop();
  server.handleClient();
  device->loop(); 
}