//
// Created by SERT on 08.04.2024.
//

#ifndef ROBOTER_STEUERUNG_2560_BIGMOTOR_HPP
#define ROBOTER_STEUERUNG_2560_BIGMOTOR_HPP

#include "Arduino.h"
#include "Motor.hpp"

class BigMotor : public Impl::Motor {
protected:
    void driveLogic_(int8_t dutyCycle) override;
    void stopLogic_() override;
};


#endif //ROBOTER_STEUERUNG_2560_BIGMOTOR_HPP
