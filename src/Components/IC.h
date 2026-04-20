#pragma once
#include <raylib.h>
#include <string>
#include <vector>
#include <map>

struct ICPinDescription {
    std::string description;
    std::string name;
};

struct ICPins {
    std::vector<Vector2> pins; // Alla pin-positioner
    int pinCount; // Antal pinar
    std::map<int, ICPinDescription> pinDescriptions; // Beskrivningar per pin
};

ICPins DrawIC(int x, int y, int pinCount, const std::string& label, const std::string& tooltip = "", const std::map<int, ICPinDescription>& descriptions = {});