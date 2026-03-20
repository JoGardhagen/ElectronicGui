#pragma once
#include <raylib.h>
#include <string>

// Rita en GPIO-pin med label och tooltip
void DrawGPIOPin(int x, int y, const std::string &label, const std::string &tooltip);
void DrawGNDPin(int x, int y, const std::string &tooltip);