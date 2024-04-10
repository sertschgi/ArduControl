//
// Created by SERT on 07.01.2024.
//

#include "modules/Motor.hpp"


using namespace Impl;

void Motor::clearRotations()
{
    this->pulses_ = 0;
}

uint16_t Motor::getRotations() const
{
    return pulses_/(fullRPls_*2);
}

uint64_t Motor::getDrivingLength() const
{
    return drivingLength_;
}

Motor::Motor(const uint8_t &pinA, const uint8_t &dcPin, const uint8_t &hallPin,
             const uint8_t &fullRotationPulses) : hallPin_(hallPin),
                                                  fullRPls_(fullRotationPulses), pinA_(pinA),
                                                  dcPin_(dcPin)
{
    pinMode(pinA_, OUTPUT);
    pinMode(dcPin_, OUTPUT);
}

void Motor::pulse_()
{
//    if (!shouldBeDriving_)
//    {
//        Debug::debug("\nshould not be driving.");
//        driving_ = false;
//        analogWrite(this->dcPin_, 0);
//        return;
//    }
//    if (stopped_)
//    {
//        Debug::debug("\nrolling.");
//        analogWrite(this->dcPin_, 0);
//        rolling_ = true;
//        driving_ = false;
//        return;
//    }
//    Debug::debug("\npulse.");
//    rolling_ = false;
//    driving_ = true;
    pulses_++;
    if(getRotations() >= getDrivingLength())
    {
        Debug::debug("\nDriving Length: ");
        Debug::debug(getDrivingLength());
        Debug::debug("\nRotations: ");
        Debug::debug(getRotations());
        Debug::debug("\nstopping.");
        stop();
    }
}

void Motor::pulseCall()
{
    this->pulse_();
}

void Motor::setup(void (*pulseCall)()) const
{
    pinMode(this->hallPin_, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(this->hallPin_), pulseCall, CHANGE);
}

void Motor::drive(int8_t dutyCycle)
{
//    this->stopped_ = false;
    this->driveLogic_(dutyCycle);
    this->clearRotations();
    driving_ = true;
//    this->shouldBeDriving_ = true;
}

void Motor::driveLogic_(int8_t dutyCycle) {}

void Motor::stopLogic_() {}

void Motor::drive(uint16_t distance, int8_t dutyCycle)
{
    this->drivingLength_ = distance;
    this->drive(dutyCycle);
}

void Motor::stop()
{
    this->stopLogic_();
    analogWrite(this->dcPin_, 0);
    driving_ = false;
}

bool Motor::driving() const
{
    return driving_;
}

bool Motor::rolling() const
{
    return rolling_;
}