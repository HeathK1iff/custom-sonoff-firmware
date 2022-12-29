#ifndef SonoffMiniR2_h
#define SonoffMiniR2_h

#include "Arduino.h"
#include "../SonoffDevice.h"
#include "../Settings/Settings.h"
#include <WebAPIHandler.h>

#define SONOFF_MINIR2_TAGS_LENGTH 1

class SonoffMiniR2: public SonoffDevice
{
    private:
        const Tag ARRAY_TAGS[SONOFF_MINIR2_TAGS_LENGTH] = {
            {"state", ttProperty}
        };

        Settings *_settings;

        const TagArray getTagArray(){
            return {ARRAY_TAGS, SONOFF_MINIR2_TAGS_LENGTH};
        }

        const char* getValueByTag(const char* tag);
        bool setValueByTag(const char* tag, const char* value);        
        bool callMethodByTag(const char* tag) {};
        
        void registerWebAPIHandler(WebAPI *webApi) {
            webApi->addHandler("/relay", this);
        };
    public:
        SonoffMiniR2(Settings *setting);

        void setup();
        void loop();

        bool isRelayActivated();
        void setRelayState(bool onState, bool byUser);
};



#endif