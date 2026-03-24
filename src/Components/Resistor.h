#pragma once
#include <raylib.h>
#include <string> 
struct PotPins {
    Vector2 pin1; // vänster (VCC)
    Vector2 pin2; // höger (GND)
    Vector2 pin3; // wiper (output)
};

void DrawResistor(int x,int y,const std::string& label,const std::string& tooltip);
PotPins DrawPotentiometer(int x, int y, float value, const std::string &label, const std::string &tooltip);