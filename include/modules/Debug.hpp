//
// Created by SERT on 09.04.2024.
//

#ifndef ROBOTER_STEUERUNG_2560_DEBUG_HPP
#define ROBOTER_STEUERUNG_2560_DEBUG_HPP

#include <Arduino.h>

class Debug {
private:
    static size_t baudRate_;
    static bool active_;
public:
    static void setup(size_t baudRate, bool active=true);
    static void activate();
    static void debug(const String & message);
    static void debug(const int & value);
};

#endif //ROBOTER_STEUERUNG_2560_DEBUG_HPP
