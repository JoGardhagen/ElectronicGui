#pragma once
#include <string>
#include <raylib.h>
struct PotPins {
    Vector2 pin1; // vänster (VCC)
    Vector2 pin2; // höger (GND)
    Vector2 pin3; // wiper (output)
};

void DrawGPIO(int x,int y,const std::string& label,const std::string& tooltip);
void DrawLED(int x,int y,bool on,const std::string& tooltip);
void DrawResistor(int x,int y,const std::string& label,const std::string& tooltip);
PotPins DrawPot(int x, int y, float value, const std::string &label, const std::string &tooltip);
void DrawCapacitor(int x, int y, const std::string &label,const std::string& tooltip);
void DrawGND(int x,int y,const std::string& tooltip);
void DrawWire(int x1,int y1,int x2,int y2,bool arrow=false);
void DrawLEDCustom(int x, int y, float potValue, const std::string &tooltip);
void DrawLEDFullRed(int x, int y, bool on, const std::string &tooltip);