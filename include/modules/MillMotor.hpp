//
// Created by SERT on 08.04.2024.
//

#ifndef ROBOTER_STEUERUNG_2560_MILLMOTOR_HPP
#define ROBOTER_STEUERUNG_2560_MILLMOTOR_HPP

#include "Arduino.h"
#include <stdint.h>

class MillMotor {
private:
    uint8_t PWM_PIN_1_;
    uint8_t PWM_PIN_2_;
public:
    MillMotor(uint8_t pwmPin1, uint8_t pwmPin2);
    void start() const;
    void stop() const;
};


#endif //ROBOTER_STEUERUNG_2560_MILLMOTOR_HPP
