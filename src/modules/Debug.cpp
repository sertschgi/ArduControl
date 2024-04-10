//
// Created by SERT on 09.04.2024.
//

#include "modules/Debug.hpp"

size_t Debug::baudRate_ = 19200;
bool Debug::active_ = false;

void Debug::setup(size_t baudRate, bool active)
{
    baudRate_ = baudRate;
    active_ = active;
    if (active)
        activate();
}

void Debug::activate()
{
    active_ = true;
    Serial.begin(baudRate_);
};

void Debug::debug(const String & message)
{
    if (active_)
        Serial.write(message.c_str());
}

void Debug::debug(const int & value)
{
    debug(String(value));
}
