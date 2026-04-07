#include <raylib.h>
#include "../Components/GPIOPin.h"
#include "../Components/Resistor.h"
#include "../Components/LightEmittingDiode.h"
#include "../Components/Wire.h"
#include "../Button.h"
#include "../Components/GPIO/IGPIO.h"
#include "../AppState.h"
#include "../UI/Dropdown.h"

static bool ledState[4] = {false, false, false, false};

struct PinItem {
    std::string label;
    int pin;
};

// Endast GPIO som kan styras
std::vector<PinItem> controllablePins = {
    {"GPIO_2", 3}, {"GPIO_3", 5}, {"GPIO_4", 7}, {"GPIO_14", 8}, {"GPIO_15", 10},
    {"GPIO_17", 11}, {"GPIO_18", 12}, {"GPIO_27", 13}, {"GPIO_22", 15}, {"GPIO_23", 16},
    {"GPIO_24", 18}, {"GPIO_10", 19}, {"GPIO_9", 21}, {"GPIO_25", 22}, {"GPIO_11", 23},
    {"GPIO_8", 24}, {"GPIO_7", 26}, {"GPIO5", 29}, {"GPIO_6", 31}, {"GPIO_12", 32},
    {"GPIO_13", 33}, {"GPIO_19", 35}, {"GPIO_16", 36}, {"GPIO_26", 37}, {"GPIO_20", 38},
    {"GPIO_21", 40}
};

void DrawCircuit1_Basic(bool active,IGPIO* gpio)
{   

    DrawText("Circuit 1 - BASIC", 20, 20, 30, BLACK);

    int y = 250;

    // Startpunkt: GPIO +V
    //DrawGPIO(120,y,"GPIO +V","Pin 1 eller 17");
    DrawGPIOPin(120,y,"GPIO +V","Pin 1 eller 17");

    // Ledning till resistor
    DrawWire(128, y, 200, y);

    // Resistor
    DrawResistor(200, y, "R330","330 OHM resistor");

    // Ledning till LED
    DrawWire(260, y, 320, y);

    // LED
    DrawLED(320, y, active,"Lysdiod");

    // Koppla mock / GPIO
    if (gpio) {
        gpio->setLED(active);  // Tänder LED på Pi eller loggar i DummyGPIO
    }

    // Ledning till GND
    DrawWire(360, y, 430, y);

    // GND
    //DrawGND(430, y,"GND pin 6,9,14,20,25,30,34,39");
    DrawGNDPin(430, y,"GND pin 6,9,14,20,25,30,34,39");
}

void DrawCircuit1_Mid(AppState& state, IGPIO* gpio)
{
    DrawText("Circuit 1 - MID",20,20,30,BLACK);
    int y = 250;
    DrawGPIOPin(120,y,"GPIO ","Pin 1 eller 17");
    DrawWire(128,y,200,y);
    DrawResistor(200,y,"R330","330 OHM resistor");
    DrawWire(260,y,320,y);
    DrawLED(320,y,state.rcLedOn,"Lysdiod");
    DrawWire(360,y,430,y);
    DrawGNDPin(430,y,"GND pins");

    std::vector<std::string> gpioLabels;
    for(auto& p : controllablePins) gpioLabels.push_back(p.label);

    static Dropdown gpioDropdown(100, 350, 120, 30, gpioLabels);
    gpioDropdown.Draw();
    gpioDropdown.CheckClick();
    //int selectedPin = std::stoi(gpioDropdown.GetSelectedItem());
    int selectedIndex = gpioDropdown.GetSelectedIndex();
    int selectedPin = controllablePins[selectedIndex].pin; // riktig BCM GPIO

    // --- Knapp för LED ---
    static Button* ledButton = nullptr; // skapa knappen första gången
    if(!ledButton)
    {
        ledButton = new Button(480, y - 15, 150, 30, "Toggle LED");
        ledButton->SetColor(BLUE);
        ledButton->SetColorHover(PINK);
        ledButton->SetOnClick([&state](){ state.rcLedOn = !state.rcLedOn; });
    }

    ledButton->Draw();
    ledButton->CheckClick();

    // --- Uppdatera GPIO ---
    if(gpio)
    {   
        //int selectedPin = std::stoi(gpioDropdown.GetSelectedItem());
        gpio->setLEDPin(selectedPin,state.rcLedOn); // LED på Raspberry Pi eller DummyGPIO
    }

}

void DrawCircuit1_Full(AppState& state, IGPIO* gpio)
{
    DrawText("Circuit 1 - FULL", 20, 20, 30, BLACK);

    int startX = 200;
    int ledSpacingY = 80;
    int gndY = 400;
    int wireForward = 160;

    static Button* buttons[4] = {nullptr,nullptr,nullptr,nullptr};
    static Dropdown* gpioDropdowns[4] = {nullptr,nullptr,nullptr,nullptr};

    for(int i = 0; i < 4; i++)
    {
        int y = 150 + i * ledSpacingY;

        DrawGPIOPin(startX - 120, y, "GPIO +V" + std::to_string(i+1), "Pin GPIO");
        DrawWire(startX - 112, y, startX - 40, y);
        DrawResistor(startX - 40, y, "R330", "330 Ohm resistor");
        DrawWire(startX+20, y, startX + 40, y);
        DrawLED(startX + 40, y, ledState[i], "LED " + std::to_string(i+1));

        int horizEndX = startX + 40 + wireForward;
        DrawWire(startX + 75, y, horizEndX, y);
        DrawWire(horizEndX, y, horizEndX, gndY);
        DrawGNDPin(horizEndX, gndY, "GND");

        // Dropdown
        if(!gpioDropdowns[i]) {
            std::vector<std::string> labels;
            for(auto& p : controllablePins) labels.push_back(p.label);
            gpioDropdowns[i] = new Dropdown(startX + 230, y - 15, 100, 30, labels);
        }

        gpioDropdowns[i]->Draw();
        gpioDropdowns[i]->CheckClick();

        int selectedIndex = gpioDropdowns[i]->GetSelectedIndex();
        int selectedPin = controllablePins[selectedIndex].pin;

        // Button
        if(!buttons[i]) {
            buttons[i] = new Button(startX + 360, y - 15, 120, 30, "Toggle LED");
            buttons[i]->SetColor(BLUE);
            buttons[i]->SetColorHover(PINK);
            buttons[i]->SetOnClick([i]() { ledState[i] = !ledState[i]; }); // FIX
        }

        buttons[i]->Draw();
        buttons[i]->CheckClick();

        // GPIO
        if(gpio) {
            gpio->setLEDPin(selectedPin, ledState[i]);
        }
    }
}