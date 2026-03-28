// src/Components/GPIO/DummyGPIO.h
#pragma once
#include "IGPIO.h"
#include <iostream>

class DummyGPIO : public IGPIO {
public:
    void setLED(bool on) override {
        std::cout << "[DummyGPIO] LED = " << (on ? "ON" : "OFF") << std::endl;
    }

    bool readButton(int pin) override {
        // Alltid falskt (ingen fysisk knapp)
        return false;
    }
};