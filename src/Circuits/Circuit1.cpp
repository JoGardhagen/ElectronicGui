#include <raylib.h>
#include "../Components/GPIOPin.h"
#include "../Components/Resistor.h"
#include "../Components/LightEmittingDiode.h"
#include "../Components/Wire.h"
#include "../Button.h"
#include "../Components/GPIO/IGPIO.h"
#include "../AppState.h"
#include "../UI/Dropdown.h"
#include "../Components/GPIO/PinMap.h"
#include <algorithm>
#include <iostream>
static bool ledState[4] = {false, false, false, false};

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
    //gpioDropdown.Draw();
    //gpioDropdown.CheckClick();
    gpioDropdown.DrawButtonOnly();
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
    //för felsök
    std::cout << "GPIO ptr = " << gpio << std::endl;
    std::cout << "selectedPin = " << selectedPin << std::endl;
    std::cout << "led state = " << state.rcLedOn << std::endl;

    // --- Uppdatera GPIO ---
    if(gpio)
    {   
        //int selectedPin = std::stoi(gpioDropdown.GetSelectedItem());
        gpio->setLEDPin(selectedPin,state.rcLedOn); // LED på Raspberry Pi eller DummyGPIO
    }
    gpioDropdown.DrawListOnly();
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
    static bool ledState[4] = {false,false,false,false};
    static int previousSelectedPin[4] = {-1,-1,-1,-1};

    // Rita krets, LED, knappar och klick
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

        // Dropdown init
        if(!gpioDropdowns[i]) {
            std::vector<std::string> labels;
            for(auto& p : controllablePins) labels.push_back(p.label);
            gpioDropdowns[i] = new Dropdown(startX + 230, y - 15, 100, 30, labels);
            gpioDropdowns[i]->selectedIndex = -1;
        }

        // Button
        if(!buttons[i]) {
            buttons[i] = new Button(startX + 360, y - 15, 120, 30, "Toggle LED");
            buttons[i]->SetColor(BLUE);
            buttons[i]->SetColorHover(PINK);
            buttons[i]->SetOnClick([i]() { ledState[i] = !ledState[i]; });
        }
        buttons[i]->Draw();
        buttons[i]->CheckClick();
    }

    // --- Bygg lista över använda pins ---
    std::vector<int> usedPins;
    for(int i = 0; i < 4; i++) if(previousSelectedPin[i] != -1) usedPins.push_back(previousSelectedPin[i]);

    // --- Klick-logik och filtrera items ---
    for(int i = 0; i < 4; i++) {
        std::vector<std::string> filteredLabels;
        for(auto& p : controllablePins) {
            if(std::find(usedPins.begin(), usedPins.end(), p.pin) == usedPins.end() || previousSelectedPin[i] == p.pin) {
                filteredLabels.push_back(p.label);
            }
        }
        gpioDropdowns[i]->items = filteredLabels;

        gpioDropdowns[i]->DrawButtonOnly();
        gpioDropdowns[i]->CheckClick();

        int selectedIndex = gpioDropdowns[i]->GetSelectedIndex();
        int selectedPin = -1;
        if(selectedIndex >= 0 && selectedIndex < (int)gpioDropdowns[i]->items.size()) {
            for(auto& p : controllablePins) {
                if(p.label == gpioDropdowns[i]->items[selectedIndex]) {
                    selectedPin = p.pin;
                    break;
                }
            }
        }

        if(selectedPin != previousSelectedPin[i]) previousSelectedPin[i] = selectedPin;

        // Uppdatera GPIO
        if(gpio && selectedPin != -1) gpio->setLEDPin(selectedPin, ledState[i]);
    }

    // --- Rita dropdown-listorna ovanpå allt ---
    for(int i = 0; i < 4; i++) {
        gpioDropdowns[i]->DrawListOnly();
    }
}