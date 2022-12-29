#ifndef SonoffDevice_h
#define SonoffDevice_h

#include <WebAPIHandler.h>
#include <WebAPI.h>

#define MQTT_RELAY_STATE_DATA_LENGTH 50 

class SonoffDevice : public WebAPIHandler{
    public:
        virtual void registerWebAPIHandler(WebAPI *webApi) = 0;
        virtual void setup() = 0;
        virtual void loop() = 0;
};

#endif