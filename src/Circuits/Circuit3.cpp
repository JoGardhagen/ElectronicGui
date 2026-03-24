#include <raylib.h>
#include "../Components/GPIOPin.h"
#include "../Components/Resistor.h"
#include "../Components/LightEmittingDiode.h"
#include "../Components/Wire.h"
#include "../Components/Capacitor.h"
#include "../Button.h"

void DrawCircuit3_Basic(float potValue)
{
    DrawText("Circuit 3 - Potentiometer Basic", 20, 20, 30, BLACK);

    int y = 200;
    int startX = 120;

    // --- 3.3V ---
    //DrawGPIO(startX, y, "GPIO 3.3V", "Pin 3");
    DrawGPIOPin(startX, y, "GPIO 3.3V", "Pin 3");

    // --- Pot ---
    int potX = startX + 100;
    //PotPins pot = DrawPotentiometer(potX, y, potValue, "Pot", "10-1K OHM");
    //PotPins pot = DrawPotentiometer();
    PotPins pot = DrawPotentiometer(potX, y, potValue, "Pot", "10-1K OHM");

    // --- VCC → pin1 ---
    DrawWire(startX + 8, y, pot.pin1.x, pot.pin1.y);

    // --- pin2 → GND ---
    DrawWire(pot.pin2.x, pot.pin2.y, pot.pin2.x + 100, pot.pin2.y);
    //DrawGND(pot.pin2.x + 100, pot.pin2.y, "GND");
    DrawGNDPin(pot.pin2.x + 100, pot.pin2.y, "GND");

    int yForLed = pot.pin3.y+100;
    int xForLed = pot.pin3.x+100;

    DrawWire(pot.pin3.x,pot.pin3.y+50,pot.pin3.x,yForLed);
    DrawWire(pot.pin3.x,yForLed,pot.pin3.x+5,yForLed);
    DrawResistor(pot.pin3.x+5,yForLed,"R200","R 200 Ohm");

    DrawWire(pot.pin3.x+65,yForLed,xForLed,yForLed);

    //bool ledOn = potValue >= 0.7f;  // LED tänds när potValue > 0.3
    
    DrawLEDCustom(xForLed, yForLed, potValue, "LED");
    //bool ledOn = potValue > 0.7f; // Tröskel för full röd
    //DrawLEDFullRed(xForLed, yForLed, ledOn, "LED");

    //DrawLED(xForLed,yForLed,false,"Led");
    DrawWire(xForLed+40,yForLed,xForLed+100,yForLed);
    //DrawGND(xForLed+100,yForLed,"GND");
    DrawGNDPin(xForLed+100,yForLed,"GND");

}

void DrawCircuit3_Mid(float potValue)
{
    DrawText("Circuit 3 - Potentiometer Mid", 20, 20, 30, BLACK);

    int y = 200;
    int startX = 120;

    // --- 3.3V ---
    //DrawGPIO(startX, y, "GPIO 3.3V", "Pin 3");
    DrawGPIOPin(startX, y, "GPIO 3.3V", "Pin 3");

    // --- Pot ---
    int potX = startX + 100;
    //PotPins pot = DrawPotentiometer(potX, y, potValue, "Pot", "10-1K OHM");
    //PotPins pot = DrawPotentiometer();
    PotPins pot = DrawPotentiometer(potX, y, potValue, "Pot", "10-1K OHM");

    // --- VCC → pin1 ---
    DrawWire(startX + 8, y, pot.pin1.x, pot.pin1.y);

    // --- pin2 → GND ---
    DrawWire(pot.pin2.x, pot.pin2.y, pot.pin2.x + 100, pot.pin2.y);
    //DrawGND(pot.pin2.x + 100, pot.pin2.y, "GND");
    DrawGNDPin(pot.pin2.x + 100, pot.pin2.y, "GND");

    int yForLed = pot.pin3.y+100;
    int xForLed = pot.pin3.x+100;

    DrawWire(pot.pin3.x,pot.pin3.y+50,pot.pin3.x,yForLed);

    //DrawWire(pot.pin3.x,yForLed,xForLed,yForLed);

    //bool ledOn = potValue >= 0.7f;  // LED tänds när potValue > 0.3
    DrawWire(pot.pin3.x,yForLed,pot.pin3.x+20,yForLed);
    DrawGPIOPin(pot.pin3.x,yForLed,"GPIO 11","GPIO 11 Pin 17");
    DrawWire(pot.pin3.x,yForLed,pot.pin3.x+5,yForLed);
    DrawResistor(pot.pin3.x+20,yForLed,"R200","R 200 Ohm");

    DrawWire(pot.pin3.x+80,yForLed,xForLed,yForLed);

    
    DrawLEDCustom(xForLed, yForLed, potValue, "LED");
    //bool ledOn = potValue > 0.7f; // Tröskel för full röd
    //DrawLEDFullRed(xForLed, yForLed, ledOn, "LED");

    //DrawLED(xForLed,yForLed,false,"Led");
    DrawWire(xForLed+40,yForLed,xForLed+100,yForLed);
    //DrawGND(xForLed+100,yForLed,"GND");
    DrawGNDPin(xForLed+100,yForLed,"GND");

}
void DrawCirciut3_Full(float potValue){

    DrawText("Circuit 3 - Potentiometer Full", 20, 20, 30, BLACK);

    int y = 200;
    int startX = 120;

    // --- 3.3V ---
    //DrawGPIO(startX, y, "GPIO 3.3V", "Pin 3");
    DrawGPIOPin(startX, y, "GPIO 3.3V", "Pin 3");

    // --- Pot ---
    int potX = startX + 100;
    //PotPins pot = DrawPotentiometer(potX, y, potValue, "Pot", "10-1K OHM");
    //PotPins pot = DrawPotentiometer();
    PotPins pot = DrawPotentiometer(potX, y, potValue, "Pot", "10-1K OHM");

    // --- VCC → pin1 ---
    DrawWire(startX + 8, y, pot.pin1.x, pot.pin1.y);

    // --- pin2 → GND ---
    DrawWire(pot.pin2.x, pot.pin2.y, pot.pin2.x + 100, pot.pin2.y);
    //DrawGND(pot.pin2.x + 100, pot.pin2.y, "GND");
    DrawGNDPin(pot.pin2.x + 100, pot.pin2.y, "GND");
    // WIPER → GPIO
    DrawWire(pot.pin3.x, pot.pin3.y, pot.pin3.x + 80, pot.pin3.y);
    DrawGPIOPin(pot.pin3.x + 80, pot.pin3.y, "GPIO17", "Analog read");
    
    // GPIO → resistor
    int rx = pot.pin3.x + 140;
    int ry = pot.pin3.y + 80;
    
    DrawWire(pot.pin3.x + 80, pot.pin3.y, pot.pin3.x + 80, ry);
    DrawWire(pot.pin3.x + 80, ry, rx, ry);
    
    // resistor
    DrawResistor(rx, ry, "R220", "Current limit");
    
    // resistor → LED
    DrawWire(rx + 60, ry, rx + 100, ry);
    DrawLEDCustom(rx + 100, ry, potValue, "LED");
    
    // LED → GND
    DrawWire(rx + 140, ry, rx + 180, ry);
    DrawGNDPin(rx + 180, ry, "GND");
}