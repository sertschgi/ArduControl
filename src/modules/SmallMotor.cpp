//
// Created by SERT on 08.04.2024.
//

#include "modules/SmallMotor.hpp"

SmallMotor::SmallMotor(const uint8_t& pinA,
            const uint8_t& pinB,
            const uint8_t& dcPin,
            const uint8_t& hallPin,
            const uint8_t& fullRotationPulses) : Motor(pinA, dcPin, hallPin, fullRotationPulses), pinB_(pinB) {
                pinMode(pinB_, OUTPUT);
            };

void SmallMotor::driveLogic_(int8_t dutyCycle)
{
    if (dutyCycle > 0)
    {
        digitalWrite(pinA_, HIGH);
        digitalWrite(pinB_, LOW);
    }
    else  if (dutyCycle < 0)
    {
        digitalWrite(pinA_, LOW);
        digitalWrite(pinB_, HIGH);
    }
    else
    {
        this->stop();
        return;
    }
//    Debug::debug("\n dcPin");
//    Debug::debug(dcPin_);
    analogWrite(dcPin_, abs(dutyCycle)*255/100);
}

void SmallMotor::stopLogic_()
{
    digitalWrite(pinA_, HIGH);
    digitalWrite(pinB_, HIGH);
}
