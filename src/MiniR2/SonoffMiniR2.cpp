#include "SonoffMiniR2.h"

#define RELAY_PIN 12
#define LED_PIN 13
#define ONBOARD_SWITCH_PIN 0
#define EXTERNAL_SWITCH_PIN 4

bool _skipMiniR2Interrupts;  
unsigned long _tsMiniR2ButtonClick;
unsigned long _tsMiniR2ExternalButtonClick;
SonoffMiniR2 * _miniR2;

void ICACHE_RAM_ATTR miniR2ExtSwitchInterrupt(){
    if ((_miniR2 == NULL) || (_skipMiniR2Interrupts))
            return;

    if (millis() > _tsMiniR2ExternalButtonClick){
        if (digitalRead(EXTERNAL_SWITCH_PIN) == LOW){
            _miniR2->setRelayState(true, true);
        } else {  
            _miniR2->setRelayState(false, true);   
        }

        _tsMiniR2ExternalButtonClick = millis() + 100;
    }
}

SonoffMiniR2::SonoffMiniR2(Settings *settings){
    _miniR2 = this;
    _settings = settings;
}

const char* SonoffMiniR2::getValueByTag(const char* tag) 
{
    if (strcmp(tag, "state") == 0) {
        if (isRelayActivated()){
            return "on";
        }
        return "off";
    }
};
        
bool SonoffMiniR2::setValueByTag(const char* tag, const char* value) 
{
    if (strcmp(tag, "state") == 0){
        if (strcmp(value, "on") == 0){
            setRelayState(true, false);
            return true;
        } else if (strcmp(value, "off") == 0){;
            setRelayState(false, false);
            return true;
        }     
    }
    
    this->error("Value is not updated");
    return false; 
};

void SonoffMiniR2::setup(){
    pinMode(LED_PIN, OUTPUT);            
    pinMode(EXTERNAL_SWITCH_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(EXTERNAL_SWITCH_PIN), miniR2ExtSwitchInterrupt,  CHANGE);

    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);   
}

void SonoffMiniR2::loop(){

}

bool SonoffMiniR2::isRelayActivated(){
    return digitalRead(RELAY_PIN) == HIGH;
}

void SonoffMiniR2::setRelayState(bool onState, bool byUser){
    if (onState){
        digitalWrite(RELAY_PIN, HIGH);
        digitalWrite(LED_PIN, HIGH);
    } else {
        digitalWrite(RELAY_PIN, LOW);
        digitalWrite(LED_PIN, LOW);
    }
}