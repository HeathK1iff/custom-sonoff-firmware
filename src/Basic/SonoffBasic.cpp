#include "SonoffBasic.h"

#define RELAY_PIN 12
#define LED_PIN 13
#define ONBOARD_SWITCH_PIN 0

bool _skipInterrupts;  
unsigned long _tsExternalButtonClick;
SonoffBasic * _basic;

void ICACHE_RAM_ATTR basicOnboardSwitchInterrupt(){
    if ((_basic == NULL) || (_skipInterrupts))
        return;
    
    if (_tsExternalButtonClick < millis())
    {             
        _basic->setRelayState(!_basic->isRelayActivated(), true);        
        _tsExternalButtonClick = millis() + 60;
    }
}

const char* SonoffBasic::getValueByTag(const char* tag) 
{
    if (strcmp(tag, "state") == 0) {
        if (isRelayActivated()){
            return "on";
        }
        return "off";
    }
};
        
bool SonoffBasic::setValueByTag(const char* tag, const char* value) 
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

SonoffBasic::SonoffBasic(Settings *settings){
    _basic = this;
    _settings = settings;
}

void SonoffBasic::setup(){ 
    setRelayState(false, false);
    
    pinMode(ONBOARD_SWITCH_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);            
    attachInterrupt(digitalPinToInterrupt(ONBOARD_SWITCH_PIN), basicOnboardSwitchInterrupt, FALLING);  

    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);   
}

void SonoffBasic::loop(){

}

bool SonoffBasic::isRelayActivated(){
    return digitalRead(RELAY_PIN) == HIGH;
}

void SonoffBasic::setRelayState(bool onState, bool byUser){
    if (onState){
        digitalWrite(RELAY_PIN, HIGH);
        digitalWrite(LED_PIN, HIGH);
    } else {
        digitalWrite(RELAY_PIN, LOW);
        digitalWrite(LED_PIN, LOW);
    }
}