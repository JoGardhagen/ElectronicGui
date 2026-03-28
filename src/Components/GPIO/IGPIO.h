// src/Components/GPIO/IGPIO.h
#pragma once

class IGPIO {
public:
    virtual void setLED(bool on) = 0;
    virtual bool readButton(int pin) = 0;
    virtual ~IGPIO() {}
};