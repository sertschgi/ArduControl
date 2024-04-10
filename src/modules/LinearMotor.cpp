//
// Created by SERT on 25.02.2024.
//

#include "modules/LinearMotor.hpp"

LinearMotor::LinearMotor(uint8_t pwmPin1, uint8_t pwmPin2, uint8_t extendTimeInSec)
{
    this->PWM_PIN_1_ = pwmPin1;
    this->PWM_PIN_2_ = pwmPin2;
    this->EXTEND_TIME_ = extendTimeInSec * 1000;
    pinMode(this->PWM_PIN_1_, OUTPUT);
    pinMode(this->PWM_PIN_2_, OUTPUT);
    this->contract(100);
}

void LinearMotor::wait_() const
{
    delay(this->EXTEND_TIME_);
}

void LinearMotor::extend(uint8_t dutyCycle, bool wait) const
{
    analogWrite(this->PWM_PIN_1_, 0);
    analogWrite(this-> PWM_PIN_2_, dutyCycle*255/100);
    if (wait) this->wait_();
}

void LinearMotor::contract(uint8_t dutyCycle, bool wait) const
{
    analogWrite(this->PWM_PIN_2_, 0);
    analogWrite(this-> PWM_PIN_1_, dutyCycle*255/100);
    if (wait) this->wait_();
}

void LinearMotor::stop() const
{
    analogWrite(this->PWM_PIN_1_, 0);
    analogWrite(this->PWM_PIN_2_, 0);
}

uint8_t LinearMotor::getExtendTime() const
{
    return this->EXTEND_TIME_;
}

