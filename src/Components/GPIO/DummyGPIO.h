// src/Components/GPIO/DummyGPIO.h
#pragma once
#include "IGPIO.h"
#include <iostream>

class DummyGPIO : public IGPIO {
public:
    void setLED(bool on) override {
        std::cout << "DummyGPIO: LED is " << (on ? "ON" : "OFF") << std::endl;
    }

    void setLEDPin(int pin, bool on) override {
        std::cout << "DummyGPIO: LED on GPIO_pin " << pin << " is " << (on ? "ON" : "OFF") << std::endl;
    }
};