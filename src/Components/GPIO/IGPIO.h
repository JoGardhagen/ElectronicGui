// src/Components/GPIO/IGPIO.h
#pragma once

class IGPIO {
public:
    virtual ~IGPIO() = default;
    virtual void setLED(bool on) = 0;
    virtual void setLEDPin(int pin, bool on) = 0;
    //virtual bool readButton(int pin) = 0;
};