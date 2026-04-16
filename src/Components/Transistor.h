#pragma once
#include <raylib.h>
#include <string>

struct TransistorPins {
    Vector2 base;
    Vector2 collector;
    Vector2 emitter;
};

TransistorPins DrawNPNTransistor(
    int x, int y,
    bool active,
    const std::string& label,
    const std::string& tooltip
);

TransistorPins DrawPNPTransistor(
    int x, int y,
    bool active,
    const std::string& label,
    const std::string& tooltip
);