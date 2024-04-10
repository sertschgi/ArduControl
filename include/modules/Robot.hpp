//
// Created by SERT on 07.01.2024.
//

#ifndef ROBOTER_STEUERUNG_2560_ROBOT_HPP
#define ROBOTER_STEUERUNG_2560_ROBOT_HPP

#include <stdint.h>
#include "Motor.hpp"

using namespace Impl;

class Robot {
private:
    Motor & motorL_;
    Motor & motorR_;
    float wheelCircumference_;
    float motorDistance_;
    float gearRatio_;
    uint16_t translateDistance_(uint16_t distance) const;
public:
    Robot(Motor & motorL,
          Motor & motorR,
          const float& wheelCircumference,
          const float& motorDistance,
          const float& gearRatio) : motorL_(motorL), motorR_(motorR), wheelCircumference_(wheelCircumference),
                                    motorDistance_(motorDistance), gearRatio_(gearRatio) {};
    void drive(int8_t dutyCycle);
    void drive(int8_t dutyCycleL, int8_t dutyCycleR);
    void driveDistance(int16_t distance, int8_t dutyCycle);
    void rotate(uint16_t degrees, int8_t dutyCycle);
    bool driving() const;
    // void circle(int16_t radius, int8_t dutyCycle);
};


#endif //ROBOTER_STEUERUNG_2560_ROBOT_HPP
