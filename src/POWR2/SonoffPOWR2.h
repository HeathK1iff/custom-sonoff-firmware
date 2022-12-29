#ifndef SonofPOWR2_h
#define SonofPOWR2_h

#include "Arduino.h"
#include "../SonoffDevice.h"
#include "../Settings/Settings.h"
#include "Sensors/PowR2Sensors.h"
#include <WebAPIHandler.h>

#define SONOFF_POWER2_TAGS_LENGTH 1

class SonoffPOWR2: public SonoffDevice
{
    private:
        const Tag ARRAY_TAGS[SONOFF_POWER2_TAGS_LENGTH] = {
            {"state", ttProperty}
        };

        Settings *_settings;
        PowR2Sensors _sensors;
        
        unsigned long _tsPowR2Update;


        const TagArray getTagArray(){
            return {ARRAY_TAGS, SONOFF_POWER2_TAGS_LENGTH};
        }
        
        const char* getValueByTag(const char* tag);
        bool setValueByTag(const char* tag, const char* value);
        bool callMethodByTag(const char* tag)  {};

        void registerWebAPIHandler(WebAPI *webApi) {
            webApi->addHandler("/relay", this);
            webApi->addHandler("/sensors", &_sensors);
        };
    public:
        SonoffPOWR2(Settings *setting);

        void setup();
        void loop();
        
        bool isRelayActivated();
        void setRelayState(bool onState, bool byUser);
};

#endif