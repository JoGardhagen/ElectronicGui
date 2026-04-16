#pragma once
#include "IGPIO.h"
#include <gpiod.h>
#include <map>
#include <string>

class RaspberryGPIO : public IGPIO {
public:
    RaspberryGPIO(const std::string& chipname = "/dev/gpiochip0");
    ~RaspberryGPIO();

    void setLED(bool on) override;
    void setLEDPin(int pin, bool on) override;

    void setInputPin(int pin, bool value) override;
    bool getInputPin(int pin) override;

private:
    gpiod_chip* chip = nullptr;

    std::map<int, gpiod_line_request*> inputRequests;
    std::map<int, gpiod_line_request*> outputRequests;

    std::map<int, bool> inputCache;
};