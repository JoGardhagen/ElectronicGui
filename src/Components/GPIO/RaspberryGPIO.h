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

private:
    gpiod_chip* chip = nullptr;

    // Spara requests per pin
    std::map<int, gpiod_line_request*> requests;
};