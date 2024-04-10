//
// Created by SERT on 25.02.2024.
//

#include "modules/Servo.hpp"

CServo::CServo(uint8_t pin)
{
    this->attach(pin);
}