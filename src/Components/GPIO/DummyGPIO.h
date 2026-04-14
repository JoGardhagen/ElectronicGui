// src/Components/GPIO/DummyGPIO.h
#pragma once
#include "IGPIO.h"
#include <iostream>
#include <unordered_map>

class DummyGPIO : public IGPIO {
public:
    void setLED(bool on) override {
        std::cout << "DummyGPIO: LED is " << (on ? "ON" : "OFF") << std::endl;
    }

    void setLEDPin(int pin, bool on) override {
        std::cout << "DummyGPIO: LED on GPIO_pin " << pin << " is " << (on ? "ON" : "OFF") << std::endl;
    }
    void setInputPin(int pin, bool value) override {
        inputs[pin] = value;
    }

    bool getInputPin(int pin) override {
        return inputs[pin];
    }

private:
    std::unordered_map<int, bool> inputs;
    std::unordered_map<int, bool> outputs;

};