//
// Created by SERT on 08.04.2024.
//

#ifndef ROBOTER_STEUERUNG_2560_MILLER_HPP
#define ROBOTER_STEUERUNG_2560_MILLER_HPP

#include "Arduino.h"
#include <stdint.h>

#include "MillMotor.hpp"
#include "LinearMotor.hpp"

class Miller {
private:
    LinearMotor & LINEAR_MOTOR_;
    MillMotor & MILL_MOTOR_;
public:
    Miller(LinearMotor & linearMotor, MillMotor & millMotor);
    void start(float addMillerAfterPercent=0.80, uint8_t slowDownTo=50) const;
    void stop(float shutDownMillerAfterPercent=0.20) const;
    void startMilling(uint8_t dutyCycle=20) const;
    void startMillingSequence(uint8_t cycles=1, float millOutPercent=0.20, uint8_t slowDownTo=50) const;
};


#endif //ROBOTER_STEUERUNG_2560_MILLER_HPP
