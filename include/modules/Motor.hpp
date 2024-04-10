//
// Created by SERT on 07.01.2024.
//

#ifndef ROBOTER_STEUERUNG_2560_MOTOR_HPP
#define ROBOTER_STEUERUNG_2560_MOTOR_HPP

#include <Arduino.h>
#include <stdint.h>
#include "modules/Debug.hpp"

namespace Impl {
    class Motor {
    private:
        bool shouldBeDriving_ = false;
        bool driving_ = false;
        bool rolling_ = false;
        bool stopped_ = true;
        uint64_t pulses_ = 0;
        uint64_t drivingLength_ = -1;
        const uint8_t hallPin_;
        const uint8_t fullRPls_;
        void pulse_();
    protected:
        const uint8_t pinA_;
        const uint8_t dcPin_;
        virtual void driveLogic_(int8_t dutyCycle);
        virtual void stopLogic_();
    public:
        Motor(const uint8_t& pinA,
              const uint8_t& dcPin,
              const uint8_t& hallPin,
              const uint8_t& fullRotationPulses);
        void clearRotations();
        uint16_t getRotations() const;
        uint64_t getDrivingLength() const;
        void drive(int8_t dutyCycle);
        void drive(uint16_t distance, int8_t dutyCycle);
        void stop();
        bool driving() const;
        bool rolling() const;
        void setup(void (*pulseCall)()) const;
        void pulseCall();
    };
}


#endif //ROBOTER_STEUERUNG_2560_MOTOR_HPP
