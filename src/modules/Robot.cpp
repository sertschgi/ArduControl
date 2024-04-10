//
// Created by SERT on 07.01.2024.
//

#include "modules/Robot.hpp"

uint16_t Robot::translateDistance_(uint16_t distance) const
{
    return (uint16_t) ((float) distance/wheelCircumference_/gearRatio_);
}

void Robot::drive(int8_t dutyCycle)
{
    this->motorL_.drive(dutyCycle);
    this->motorR_.drive(dutyCycle);
}

void Robot::drive(int8_t dutyCycleL, int8_t dutyCycleR)
{
    this->motorL_.drive(dutyCycleL);
    this->motorR_.drive(dutyCycleR);
}

void Robot::driveDistance(int16_t distance, int8_t dutyCycle)
{
    uint16_t rotations = translateDistance_(distance);
    this->motorL_.drive(rotations, dutyCycle);
    this->motorR_.drive(rotations, dutyCycle);
}

void Robot::rotate(uint16_t degrees, int8_t dutyCycle)
{
    uint16_t rotations = translateDistance_((uint16_t)(motorDistance_*3.14*degrees/360));
    this->motorL_.drive(rotations, dutyCycle);
    this->motorR_.drive(rotations,(int8_t) -dutyCycle);
}

bool Robot::driving() const
{
    return (this->motorL_.driving() || this->motorR_.driving());
}
