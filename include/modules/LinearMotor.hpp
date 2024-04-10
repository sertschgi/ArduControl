//
// Created by SERT on 25.02.2024.
//

#ifndef ROBOTER_STEUERUNG_2560_LINEARMOTOR_HPP
#define ROBOTER_STEUERUNG_2560_LINEARMOTOR_HPP

#include "Arduino.h"
#include <stdint.h>

class LinearMotor {
private:
    uint8_t PWM_PIN_1_;
    uint8_t PWM_PIN_2_;
    uint8_t EXTEND_TIME_;
    void wait_() const;
public:
    LinearMotor(uint8_t pwmPin1, uint8_t pwmPin2, uint8_t extendTimeInSec=7);
    void extend(uint8_t dutyCycle, bool wait=false) const;
    void contract(uint8_t dutyCycle, bool wait=false) const;
    void stop() const;
    uint8_t getExtendTime() const;
};


#endif //ROBOTER_STEUERUNG_2560_LINEARMOTOR_HPP
