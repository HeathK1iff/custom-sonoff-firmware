#include "SonoffPOWR2.h"

#define RELAY_PIN 12
#define LED_PIN 13
#define ONBOARD_SWITCH_PIN 0

bool _skipPowR2Interrupts;  
unsigned long _tsPowR2ButtonClick;
unsigned long _tsPowR2ExternalButtonClick;
SonoffPOWR2 * _powR2;

void ICACHE_RAM_ATTR powR2OnboardMiniR2SwitchInterrupt(){
    if ((_powR2 == NULL) || (_skipPowR2Interrupts))
        return;
    
    if (_tsPowR2ButtonClick < millis())
    {             
        _powR2->setRelayState(!_powR2->isRelayActivated(), true);        
        _tsPowR2ButtonClick = millis() + 60;
    }
}

SonoffPOWR2::SonoffPOWR2(Settings *settings){
    _powR2 = this;
    _settings = settings;
}

const char* SonoffPOWR2::getValueByTag(const char* tag) 
{
    if (strcmp(tag, "state") == 0) {
        if (isRelayActivated()){
            return "on";
        }
        return "off";
    } 
    return "";
};
        
bool SonoffPOWR2::setValueByTag(const char* tag, const char* value) 
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

void SonoffPOWR2::setup(){
    pinMode(LED_PIN, OUTPUT);            
    
    pinMode(ONBOARD_SWITCH_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(ONBOARD_SWITCH_PIN), powR2OnboardMiniR2SwitchInterrupt, FALLING); 

    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
}

void SonoffPOWR2::loop(){
     if (_tsPowR2Update < millis()) {
        _sensors.refresh();
        _tsPowR2Update = millis() + 15 * 1000;
     }
}

bool SonoffPOWR2::isRelayActivated(){
    return digitalRead(RELAY_PIN) == HIGH;
}

void SonoffPOWR2::setRelayState(bool onState, bool byUser){
    if (onState){
        digitalWrite(RELAY_PIN, HIGH);
        digitalWrite(LED_PIN, HIGH);
    } else {
        digitalWrite(RELAY_PIN, LOW);
        digitalWrite(LED_PIN, LOW);
    }
}