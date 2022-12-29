#include "PowR2Sensors.h"

PowR2Sensors::PowR2Sensors(){
    _myCSE7766.setRX(1);
    _myCSE7766.begin();
};

double PowR2Sensors::getVoltage(){
    return _voltage;
}

double PowR2Sensors::getCurrent(){
    return _current;
}

void PowR2Sensors::refresh(){
    _myCSE7766.handle();
    _voltage = _myCSE7766.getVoltage();
    _current = _myCSE7766.getCurrent();
}
