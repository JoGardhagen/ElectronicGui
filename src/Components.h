#pragma once
#include <string>
#include <raylib.h>

void DrawGPIO(int x,int y,const std::string& label,const std::string& tooltip);
void DrawLED(int x,int y,bool on,const std::string& tooltip);
void DrawResistor(int x,int y,const std::string& label,const std::string& tooltip);
void DrawGND(int x,int y,const std::string& tooltip);
void DrawWire(int x1,int y1,int x2,int y2,bool arrow=false);