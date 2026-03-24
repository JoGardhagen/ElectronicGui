#pragma once
#include <string>
#include <raylib.h>

void DrawLED(int x,int y,bool on,const std::string& tooltip);
void DrawLEDCustom(int x, int y, float potValue, const std::string &tooltip);