//
// Created by SERT on 08.04.2024.
//

#include "modules/BigMotor.hpp"

void BigMotor::driveLogic_(int8_t dutyCycle)
{
    if (dutyCycle > 0)
    {
        digitalWrite(pinA_, HIGH);
    }
    else  if (dutyCycle < 0)
    {
        digitalWrite(pinA_, LOW);
    }
    else
    {
        this->stop();
        return;
    }
    analogWrite(dcPin_, dutyCycle*255/100-1);
}

void BigMotor::stopLogic_()
{
    digitalWrite(pinA_, HIGH);
}
