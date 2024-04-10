//
// Created by SERT on 25.02.2024.
//

#ifndef ROBOTER_STEUERUNG_2560_SERVO_HPP
#define ROBOTER_STEUERUNG_2560_SERVO_HPP

#include "Servo.h"

class CServo : public Servo {
public:
    CServo(uint8_t pin);
};


#endif //ROBOTER_STEUERUNG_2560_SERVO_HPP
