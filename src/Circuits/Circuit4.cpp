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


void DrawCircuit4_Basic()
{
    DrawText("Circuit 2 - Switch + Resistor + LED", 20, 20, 30, BLACK);

    int y = 250;

    // 3.3V
    DrawGPIOPin(120, y, "GPIO 3.3V", "3V3");
    DrawWire(120, y, 220, y);

    // SWITCH (din egen)
    static bool pressed = false;

    // enkel klick-zon (du kan ersätta med riktig input senare)
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mouse = GetMousePosition();
        if (mouse.x > 190 && mouse.x < 290 && mouse.y > y - 20 && mouse.y < y + 20)
        {
            pressed = !pressed;
        }
    }

    DrawSwitch(250, y, pressed,3.0f,"Switch");

    // koppling vidare
    DrawWire(280, y, 340, y);

    // RESISTOR
    DrawResistor(340, y, "R330", "330 Ohm");
    DrawWire(400, y, 480, y);

    // LED
    DrawLED(480, y, pressed, "LED");
    DrawWire(520, y, 580, y);

    // GND
    DrawGPIOPin(580, y, "GND", "GND");
}

void DrawCircuit4_Mid(AppState& state, IGPIO* gpio)
{
    DrawText("Circuit 2 - SPST -> GPIO -> LED", 20, 20, 30, BLACK);

    int y = 250;

    static std::vector<std::string> gpioLabels;
    if (gpioLabels.empty())
    {
        for (auto& p : controllablePins)
            gpioLabels.push_back(p.label);
    }

    static Dropdown inputDropdown(500, y-20, 140, 30, gpioLabels);
    static Dropdown outputDropdown(500, y + 80, 140, 30, gpioLabels);

    inputDropdown.DrawButtonOnly();
    inputDropdown.CheckClick();

    outputDropdown.DrawButtonOnly();
    outputDropdown.CheckClick();

    int inputPin = -1;
    int outputPin = -1;

    int inIdx = inputDropdown.GetSelectedIndex();
    if (inIdx >= 0 && inIdx < controllablePins.size())
        inputPin = controllablePins[inIdx].pin;

    int outIdx = outputDropdown.GetSelectedIndex();
    if (outIdx >= 0 && outIdx < controllablePins.size())
        outputPin = controllablePins[outIdx].pin;

    std::string inLabel = (inputPin != -1) ?
        "Pin " + std::to_string(inputPin) : "Select pin";

    DrawGPIOPin(120, y, "GPIO 3.3v","pin 1 eller 17");
    DrawWire(128, y, 220, y);

    static bool switchClosed = false;

    Rectangle sw = {220.0f, (float)y - 25.0f, 140.0f, 50.0f};

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 m = GetMousePosition();
        if (CheckCollisionPointRec(m, sw))
            switchClosed = !switchClosed;
    }

    DrawSwitch(290, y, switchClosed, 3.0f, "SPST || Button");

    DrawWire(350,y,350,y-50);
    DrawWire(350,y-50,370,y-50);
    DrawResistor(370,y-50,"R10K","!- Pull-up 10k Ohm resistor -! ");
    DrawWire(430,y-50,450,y-50);
    DrawWire(450,y-50,450,y-150);
    DrawWire(450,y-150,420,y-150);
    DrawGNDPin(420, y - 150, "GND");

    DrawWire(320, y, 420, y);

    DrawGPIOPin(420, y, "GPIO IN", inLabel);

    std::string outLabel = (outputPin != -1) ?
        "Pin " + std::to_string(outputPin) : "Select pin";

    DrawGPIOPin(120, y + 100, "GPIO OUT", outLabel);
    DrawWire(128, y + 100, 200, y + 100);

    DrawResistor(200, y + 100, "R330", "330 Ohm");
    DrawWire(260, y + 100, 300, y + 100);

    DrawWire(340, y + 100, 420, y + 100);
    DrawGNDPin(420, y + 100, "GND");

    bool signal = switchClosed;

    #ifdef PLATFORM_RPI
    if (gpio && inputPin != -1)
    {
        signal = gpio->getInputPin(inputPin);
    }
    #endif

    DrawLED(300, y + 100, signal, "LED");

    if (gpio && outputPin != -1)
    {
        gpio->setLEDPin(outputPin, signal);
    }

    inputDropdown.DrawListOnly();
    outputDropdown.DrawListOnly();

    if (inputPin == outputPin && inputPin != -1)
    {
        DrawText("Same GPIO pin selected!", 200, y + 200, 20, RED);
    }
}