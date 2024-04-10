//
// Created by SERT on 08.04.2024.
//

#ifndef ROBOTER_STEUERUNG_2560_SMALLMOTOR_HPP
#define ROBOTER_STEUERUNG_2560_SMALLMOTOR_HPP

#include "Arduino.h"
#include "Motor.hpp"

class SmallMotor : public Impl::Motor {
private:
    const uint8_t pinB_;
    void driveLogic_(int8_t dutyCycle) override;
    void stopLogic_() override;
public:
    SmallMotor(const uint8_t& pinA,
          const uint8_t& pinB,
          const uint8_t& dcPin,
          const uint8_t& hallPin,
          const uint8_t& fullRotationPulses);
};


#endif //ROBOTER_STEUERUNG_2560_SMALLMOTOR_HPP
