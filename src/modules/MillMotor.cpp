//
// Created by SERT on 08.04.2024.
//

#include "modules/MillMotor.hpp"

MillMotor::MillMotor(uint8_t pwmPin1, uint8_t pwmPin2)
{
    this->PWM_PIN_1_ = pwmPin1;
    this->PWM_PIN_2_ = pwmPin2;
    pinMode(this->PWM_PIN_1_, OUTPUT);
    pinMode(this->PWM_PIN_2_, OUTPUT);
}

void MillMotor::start() const
{
    analogWrite(this->PWM_PIN_1_, 0);
    analogWrite(this->PWM_PIN_2_, 255);
}

void MillMotor::stop() const
{
    analogWrite(this->PWM_PIN_1_, 0);
    analogWrite(this->PWM_PIN_2_, 0);
}
