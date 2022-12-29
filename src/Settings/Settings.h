#ifndef DeviceSettings_h
#define DeviceSettings_h

#include "stdio.h"
#include <WebAPIHandler.h>
#include <HardwareSerial.h>
#include <EEPROM.h>
#include <ESP.h>

#define SETTINGS_FIELD_COUNT 6

#define PARAM_SSID_LENGTH 25
#define PARAM_SSID_PASS_LENGTH 25
#define PARAM_DEVICE_LENGTH 30
#define PARAM_MQTT_HOST_LENGTH 25
#define PARAM_MQTT_USER_LENGTH 25
#define PARAM_MQTT_USER_PASS_LENGTH 25
#define PARAM_OFF_TIME 6

#define EEPROM_SIZE 512
#define EEPROM_DEFAULT_ADDRESS 0

enum SonoffModel {smBasic = 1, smMiniR2 = 2, smPowR2 = 3};

class Settings: public WebAPIHandler
{
    private:
        const Tag ARRAY_TAGS[6] = {
            {"model", ttProperty},
            {"ssid", ttProperty},
            {"ssid_pass", ttWriteOnlyProperty},
            {"device_name", ttProperty},
            {"save.do", ttMethod},
            {"erase.do", ttMethod},
        };

        struct SettingsStruct
        {
            char ssid[PARAM_SSID_LENGTH];
            char ssid_pass[PARAM_SSID_PASS_LENGTH];
            char device_name[PARAM_DEVICE_LENGTH];
            int model;
        } setup;
        
        void clear(){
            setup.ssid[0] = '\0';
            setup.ssid_pass[0] = '\0';
            setup.device_name[0] = '\0';
            setup.model = 0;
        }

        bool isClearEEPROM();

        bool validate(const char* val, int maxLength){
            int valLength = strlen(val); 
            bool error = valLength > maxLength;
            
            if (error){
                char buf[100];
                sprintf(buf, "Length of value (%d) execced max length(%d)", valLength, maxLength);
                this->error(buf);
            }

            return !error;
        }

        const TagArray getTagArray(){
            return {ARRAY_TAGS, 6};
        }
        
    public:
        bool save();
        void load();
        bool erase();
        
        Settings();

        bool callMethodByTag(const char* tag){
            bool error = false;
            if (strcmp(tag, "save.do") == 0)
            {
                error = !this->save();
                ESP.restart();
                if (error == true)
                    this->error("Error of save EEPROM");
                
            } else if (strcmp(tag, "erase.do") == 0)
            {
                error = !this->erase();
                if (error == true)
                    this->error("Error of erase EEPROM");
            }

            return !error;
        }

        const char* getValueByTag(const char* field){
            if (strcmp(field, "ssid") == 0){
                return getSSID();
            } else if (strcmp(field, "ssid_pass") == 0)
            {
                return "**********";
            } else if (strcmp(field, "device_name") == 0)
            {
                return getDeviceName();
            } else if (strcmp(field, "model") == 0)
            {
                char buf[10];
                return itoa((int)getModel(), buf, 10);
            }

            return "";
        }

        bool setValueByTag(const char* field, const char* value){
            if (strcmp(field, "ssid") == 0){
                return setSSID(value);
            } else if (strcmp(field, "ssid_pass") == 0)
            {
                return setSSIDPass(value);
            } else if (strcmp(field, "device_name") == 0)
            {
                return setDeviceName(value);
            } else if (strcmp(field, "model") == 0)
            {
                int model = atoi(value);
                bool error = ((model >= 1) && (model <= 3));

                if (!error)
                    return false;
                    
                return setModel((SonoffModel)model);
            }
            return false;
        }   

        const char* getSSID();
        bool setSSID(const char* ssid);

        const char* getSSIDPass();
        bool setSSIDPass(const char* pass);

        const char* getDeviceName();
        bool setDeviceName(const char* name);

        SonoffModel getModel();
        bool setModel(SonoffModel model);
};

#endif