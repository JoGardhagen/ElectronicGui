// src/Components/GPIO/RaspberryGPIO.h
#pragma once
#include "IGPIO.h"
#include <pigpio.h>
#include <iostream>

class RaspberryGPIO : public IGPIO {
public:
    RaspberryGPIO() {
        if(gpioInitialise() < 0)
            std::cerr << "GPIO init failed" << std::endl;
    }

    ~RaspberryGPIO() { gpioTerminate(); }

    void setLED(bool on) override {
        gpioWrite(17, on ? 1 : 0); // GPIO17 exempel
    }

    bool readButton(int pin) override {
        return gpioRead(pin) == 1;
    }
};