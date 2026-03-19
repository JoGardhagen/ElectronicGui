#ifndef GPIOPANEL_H
#define GPIOPANEL_H

#include <raylib.h>
#include <string>

struct PinInfo {
    std::string name;    // t.ex. "GPIO17"
    std::string tooltip; // t.ex. "Pin 11 / GPIO17"
    Color color;         // färg på pin
};

extern PinInfo pins[40];
void DrawGPIOPanel40(int startX, int startY, int colSpacing, int rowSpacing, const PinInfo pins[40]);

#endif