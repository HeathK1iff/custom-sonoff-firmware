#ifndef SonoffBasic_h
#define SonoffBasic_h

#define RELAY_PIN 12
#define LED_PIN 13
#define ONBOARD_SWITCH_PIN 0

#include "Arduino.h"
#include "../SonoffDevice.h"
#include "../Settings/Settings.h"
#include <WebAPIHandler.h>

#define SONOFF_BASIC_TAGS_LENGTH 1

class SonoffBasic: public SonoffDevice
{
    private:
        const Tag ARRAY_TAGS[SONOFF_BASIC_TAGS_LENGTH] = {
            {"state", ttProperty}
        };

        Settings *_settings;
    
        const TagArray getTagArray(){
            return {ARRAY_TAGS, SONOFF_BASIC_TAGS_LENGTH};
        }

        const char* getValueByTag(const char* tag);
        bool setValueByTag(const char* tag, const char* value);  
        bool callMethodByTag(const char* tag) {};
        
        void registerWebAPIHandler(WebAPI *webApi) {
            webApi->addHandler("/relay", this);
        };
    public:
        SonoffBasic(Settings *settings);
        
        void setup();
        void loop();

        bool isRelayActivated();
        void setRelayState(bool onState, bool byUser);
};



#endif