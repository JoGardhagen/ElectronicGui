#include <raylib.h>
#include "../Components/GPIOPin.h"
#include "../Components/Resistor.h"
#include "../Components/LightEmittingDiode.h"
#include "../Components/Wire.h"
#include "../Components/Capacitor.h"
#include "../Button.h"
#include "../Components/Spst.h"
#include "../AppState.h"
#include "../Components/GPIO/IGPIO.h"
#include "../UI/Dropdown.h"
#include "../Components/GPIO/PinMap.h"
#include "../Components/Transistor.h"

void DrawCircuit5_Basic(AppState& state, IGPIO* gpio)
{
    DrawText("Circuit 5 -  NPN Transistor ", 20, 20, 30, BLACK);

    int y = 250;

    static std::vector<std::string> gpioLabels;
    if (gpioLabels.empty())
    {
        for (auto& p : controllablePins)
            gpioLabels.push_back(p.label);
    }

    static Dropdown outputDropdown(500, y - 20, 140, 30, gpioLabels);

    outputDropdown.DrawButtonOnly();
    outputDropdown.CheckClick();

    int outputPin = -1;

    int outIdx = outputDropdown.GetSelectedIndex();
    if (outIdx >= 0 && outIdx < controllablePins.size())
        outputPin = controllablePins[outIdx].pin;

    std::string outLabel = (outputPin != -1) ?
        "Pin " + std::to_string(outputPin) : "Select pin";

    DrawGPIOPin(150, y, "GPIO", outLabel);

    // Resistor till basen
    DrawWire(158, y, 170, y);
    DrawResistor(170, y, "R1", "1k");

    // Ledning till transistorns bas
    DrawWire(230, y, 300, y);

    static bool transistorOn = false;

    Rectangle button = {650.0f, (float)y - 25.0f, 100.0f, 50.0f};

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 m = GetMousePosition();
        if (CheckCollisionPointRec(m, button))
            transistorOn = !transistorOn;
    }

    DrawRectangleRec(button, transistorOn ? GREEN : RED);
    DrawText("Toggle", button.x + 20, button.y + 15, 20, BLACK);

    // NPN-transistor
    auto t = DrawNPNTransistor(300, y, transistorOn, "Q1", "NPN");

    // Resistor till LED
    DrawWire(t.collector.x, t.collector.y, t.collector.x, t.collector.y - 50);
    DrawWire(t.collector.x, t.collector.y - 50, t.collector.x + 10, t.collector.y - 50);
    DrawResistor(t.collector.x + 10, t.collector.y - 50, "R2", "220 ohm");

    // Ledning till LED
    DrawWire(t.collector.x + 70, t.collector.y - 50, t.collector.x + 100, t.collector.y - 50);

    // LED
    DrawLED(t.collector.x + 100, t.collector.y - 50, transistorOn, "LED");

    // Ledning från LED till VCC
    DrawWire(t.collector.x + 140, t.collector.y - 50, t.collector.x + 200, t.collector.y - 50);

    // VCC
    DrawGPIOPin(t.collector.x + 200, t.collector.y - 50, "+3.3V", "VCC");

    // Ledning från transistorns emitter till GND
    DrawWire(t.emitter.x, t.emitter.y, t.emitter.x, t.emitter.y + 70);

    // GND
    DrawGNDPin(t.emitter.x, t.emitter.y + 70, "GND");

    if (gpio && outputPin != -1)
    {
        gpio->setLEDPin(outputPin, transistorOn);
    }

    outputDropdown.DrawListOnly();
}