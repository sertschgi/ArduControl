//
// Created by SERT on 08.04.2024.
//

#include "modules/Miller.hpp"

Miller::Miller(LinearMotor &linearMotor,  MillMotor &millMotor) :
    LINEAR_MOTOR_(linearMotor),
    MILL_MOTOR_(millMotor) {};

void Miller::start(float addMillerAfterPercent, uint8_t slowDownTo) const
{
    uint8_t extTime = this->LINEAR_MOTOR_.getExtendTime();
    this->LINEAR_MOTOR_.extend(100);
    delay(extTime * addMillerAfterPercent);
    this->startMilling(slowDownTo);
    delay(extTime * (1 - addMillerAfterPercent));
}

void Miller::startMilling(uint8_t dutyCycle) const
{
    this->MILL_MOTOR_.start();
    this->LINEAR_MOTOR_.extend(dutyCycle);
}

void Miller::stop(float shutDownMillerAfterPercent) const
{
    uint8_t extTime = this->LINEAR_MOTOR_.getExtendTime();
    this->LINEAR_MOTOR_.contract(100);
    delay(extTime * shutDownMillerAfterPercent);
    this->MILL_MOTOR_.stop();
}

void Miller::startMillingSequence(uint8_t cycles, float millOutPercent, uint8_t slowDownTo) const
{
    uint8_t extTime = this->LINEAR_MOTOR_.getExtendTime();
    this->start(1-millOutPercent, slowDownTo);
    this->stop(millOutPercent);
    for (uint8_t i = 0; i < cycles; ++i)
    {
        this->startMilling(slowDownTo);
        delay(extTime * millOutPercent);
        this->stop(millOutPercent);
    }
}