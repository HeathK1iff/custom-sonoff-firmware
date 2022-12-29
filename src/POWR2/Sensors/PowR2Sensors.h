#ifndef PowR2Sensors_h
#define PowR2Sensors_h

#include <WebAPIHandler.h>
#include "CSE7766.h"

#define SONOFF_POWER2_SENSORS_TAGS_LENGTH 3

class PowR2Sensors : public WebAPIHandler
{
    private:
        const Tag ARRAY_TAGS[SONOFF_POWER2_SENSORS_TAGS_LENGTH] = {
            {"current", ttReadOnlyProperty},
            {"voltage", ttReadOnlyProperty},
            {"refresh.do", ttMethod}
        };

        unsigned long _tsPowR2Update;
        double _voltage;
        double _current;
        CSE7766 _myCSE7766;
    protected:
        const TagArray getTagArray(){
            return {ARRAY_TAGS, SONOFF_POWER2_SENSORS_TAGS_LENGTH};
        };

        bool setValueByTag(const char* tag, const char* value) {};   
        bool callMethodByTag(const char* tag) {
            if (strcmp(tag, "refresh.do") == 0) {
                refresh();
                return true;
            }
            return false;
        };

        const char* getValueByTag(const char* tag) 
        {
           if (strcmp(tag, "current") == 0) {
                char buf[10];
                return itoa(getCurrent(), buf, 10);
            } else if (strcmp(tag, "voltage") == 0) {
                char buf[10];
                return itoa(getVoltage(), buf, 10);
            }

            return "";
        };

    public:
       PowR2Sensors();

       double getVoltage();
       double getCurrent();
       void refresh();
};
#endif