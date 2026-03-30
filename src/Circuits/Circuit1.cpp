#include <raylib.h>
#include "../Components/GPIOPin.h"
#include "../Components/Resistor.h"
#include "../Components/LightEmittingDiode.h"
#include "../Components/Wire.h"
#include "../Button.h"
#include "../Components/GPIO/IGPIO.h"
#include "../AppState.h"


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

void DrawCircuit1_Mid(AppState& state)
{
    DrawText("Circuit 1 - MID",20,20,30,BLACK);
    int y = 250;
    DrawGPIOPin(120,y,"GPIO +V","Pin 1 eller 17");
    DrawWire(128,y,200,y);
    DrawResistor(200,y,"R330","330 OHM resistor");
    DrawWire(260,y,320,y);
    DrawLED(320,y,state.rcLedOn,"Lysdiod");
    DrawWire(360,y,430,y);
    DrawGNDPin(430,y,"GND pins");

    if(state.circuitActive)
        ; // GPIO-output: gpio->setLED(0, state.rcLedOn);

}

void DrawCircuit1_Full(/*bool led1, bool led2, bool led3, bool led4*/)
{
   DrawText("Circuit 1 - FULL", 20, 20, 30, BLACK);

    int startX = 200;   // X-position för resistor
    int ledSpacingY = 80; // Vertikal avstånd mellan LEDs
    int gndY = 400;       // Y-position för GND
    int wireForward = 160; // Hur långt ledningen går horisontellt innan den går ner

    static bool ledState[4] = {false, false, false, false}; // LED-status
    static Button* buttons[4] = {nullptr,nullptr,nullptr,nullptr};

    for(int i = 0; i < 4; i++)
    {
        int y = 150 + i * ledSpacingY;  
        //bool ledOn = (i == 0 ? led1 : i == 1 ? led2 : i == 2 ? led3 : led4);

        // GPIO
        //DrawGPIO(startX - 120, y, "GPIO " + std::to_string(i+1), "Pin GPIO " + std::to_string(i+1));
        DrawGPIOPin(startX -120,y,"GPIO +V"+ std::to_string(i+1), "Pin GPIO " + std::to_string(i+1));

        // Ledning GPIO → resistor
        DrawWire(startX - 112, y, startX - 40, y);

        // Resistor
        DrawResistor(startX - 40, y, "R330", "330 Ohm resistor");

        // Ledning resistor → LED
        DrawWire(startX+20, y, startX + 40, y);

        // LED
        DrawLED(startX + 40, y, ledState[i], "LED " + std::to_string(i+1));

        // LED → horisontell fram → vertikal ner till GND
        int horizEndX = startX + 40 + wireForward;
        DrawWire(startX + 75, y, horizEndX, y);      // horisontellvvs
        DrawWire(horizEndX, y, horizEndX, gndY);     // vertikal

        // GND längst ner
        //DrawGND(horizEndX, gndY, "GND");
        DrawGNDPin(horizEndX, gndY, "GND");

        // --- Button för LED ---
        if(!buttons[i]) // skapa knappen första gången
        {
            buttons[i] = new Button(startX + 300, y - 15, 75, 30, "LED " + std::to_string(i+1));
            buttons[i]->SetColor((BLUE));
            buttons[i]->SetColorHover((PINK));
            buttons[i]->SetOnClick([i]() { ledState[i] = !ledState[i]; });
        }

        buttons[i]->Draw();
        buttons[i]->CheckClick();

        
    }
}