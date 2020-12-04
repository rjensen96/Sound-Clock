#include <Arduino.h>
#include "VolumeSelector.h"

VolumeSelector::VolumeSelector(int pinWithResistor, int pinNoResistor) :
    pinWithResistor(pinWithResistor), pinNoResistor(pinNoResistor)
{
}

void VolumeSelector::SetLevel(VolumeLevel vol) 
{
    pinMode(pinWithResistor, INPUT);
    pinMode(pinNoResistor, INPUT);

    switch(vol) {
    case EXTRA_QUIET:
        digitalWrite(pinWithResistor, 1);
        pinMode(pinWithResistor, OUTPUT);
        break;
    case QUIET:
        digitalWrite(pinNoResistor, 1);
        pinMode(pinNoResistor, OUTPUT);
        break;
    case NORMAL:
        break;
    case LOUD:
        digitalWrite(pinNoResistor, 0);
        pinMode(pinNoResistor, OUTPUT);
        break;
    case EXTRA_LOUD:
        digitalWrite(pinWithResistor, 0);
        pinMode(pinWithResistor, OUTPUT);
        break;
    }
}
