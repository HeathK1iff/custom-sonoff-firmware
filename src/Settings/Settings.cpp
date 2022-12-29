 #include "Settings.h"
 
Settings::Settings(){
   
}

 bool Settings::erase(){
    EEPROM.begin(EEPROM_SIZE);
    for (int i = 0; i < EEPROM_SIZE; i++)
        EEPROM.write(i, 0);
    bool result = EEPROM.commit();
    EEPROM.end();
    return result;
}

bool Settings::isClearEEPROM(){
    for (int i = EEPROM_SIZE - 10; i < EEPROM_SIZE - 1; i++){
        if (EEPROM.read(i) != 0)
            return false;
    } 
    return true; 
}


void Settings::load(){
    clear();

    if (!isClearEEPROM())
        erase();

    EEPROM.begin(EEPROM_SIZE);
    EEPROM.get(EEPROM_DEFAULT_ADDRESS, setup);
    EEPROM.end();
}

bool Settings::save(){
    EEPROM.begin(EEPROM_SIZE);
    EEPROM.put(EEPROM_DEFAULT_ADDRESS, setup);
    bool result = EEPROM.commit();
    EEPROM.end();
    return result;
}

const char* Settings::getSSID(){
    return setup.ssid;
} 

bool Settings::setSSID(const char* ssid){
    bool result = validate(ssid, PARAM_SSID_LENGTH);
    if (result){
        memset(setup.ssid, '\0', PARAM_SSID_LENGTH);
        strcat(setup.ssid, ssid);
    }
    return result;
} 

const char* Settings::getSSIDPass(){
    return setup.ssid_pass;
}

bool Settings::setSSIDPass(const char* pass){
    bool result = validate(pass, PARAM_SSID_PASS_LENGTH);
    if (result){
        memset(setup.ssid_pass, '\0', PARAM_SSID_PASS_LENGTH);
        strcat(setup.ssid_pass, pass);
    }
    return result;
}

const char* Settings::getDeviceName(){
    return setup.device_name;
}

bool Settings::setDeviceName(const char* name){
    bool result = validate(name, PARAM_DEVICE_LENGTH);
    if (result){
        memset(setup.device_name, '\0', PARAM_DEVICE_LENGTH);
        strcat(setup.device_name, name);
    }
    return result;
}

SonoffModel Settings::getModel(){
    return (SonoffModel) setup.model;
}

bool Settings::setModel(SonoffModel model){
    setup.model = (int) model;
    return true;
}

