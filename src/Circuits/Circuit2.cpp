#include <raylib.h>
#include "../Components/GPIOPin.h"
#include "../Components/Resistor.h"
#include "../Components/LightEmittingDiode.h"
#include "../Components/Wire.h"
#include "../Components/Capacitor.h"
#include "../Button.h"


void DrawCircuit2_Basic(){
   DrawText("Circuit 2 - RC Charge", 20, 20, 30, BLACK);

    int y = 250;          // horisontell linje
    int startX = 120;     // start från 3.3V

    // 3.3V
    //DrawGPIO(startX, y, "GPIO 3.3V", "Pin 1");
    DrawGPIOPin(startX, y, "GPIO 3.3V", "Pin 1");

    // resistor
    int resistorX = startX + 80;
    DrawWire(startX + 8, y, resistorX, y); // ledning 3.3V -> resistor
    DrawResistor(resistorX, y, "R10k", "10k Ohm resistor");

    // nod för GPIO17
    int gpioX = resistorX + 100;
    DrawWire(resistorX + 60, y, gpioX+10, y); // ledning resistor -> GPIO
    //DrawGPIO(gpioX+10, y, "GPIO17", "Pin 11");
    DrawGPIOPin(gpioX+10, y, "GPIO17", "Pin 11");

    // ledning till kondensator
    int capX = gpioX + 80;
    DrawWire(gpioX + 4, y, capX, y); // horisontell till kondensator

    // kondensator
    DrawCapacitor(capX, y, "10uF", "Capacitor 10uF");

    // ledning från kondensator ner till GND
    DrawWire(capX + 15, y, capX + 40, y );
    //DrawGND(capX + 50, y , "GND");
    DrawGNDPin(capX + 50, y , "GND");
}
void DrawCircuit2_Mid(bool ledOn)
{
    DrawText("Circuit 2 - RC + LED", 20, 20, 30, BLACK);

    int y = 250;

    // 3.3V
    //DrawGPIO(120, y, "GPIO 3.3V", "Pin 1");
    DrawGPIOPin(120, y, "GPIO 3.3V", "Pin 1");

    // Ledning till resistor
    DrawWire(120, y, 220, y);

    // Resistor
    DrawResistor(220, y, "R10k", "10k Ohm resistor");

    // Ledning till kondensator
    DrawWire(280, y, 320, y);

    // Kondensator
    DrawCapacitor(320, y, "10uF", "Capacitor 10uF"); // ritad vertikalt lite ovanför linjen

    DrawWire(350, y , 390, y);
    // LED parallell med kondensatorn
    DrawLED(390, y, ledOn, "LED");

    // Ledning till GND
    DrawWire(430, y , 470, y);
    //DrawGND(470, y , "GND");
    DrawGNDPin(470, y , "GND");
}
void DrawCircuit2_Full(bool ledOn)
{
    DrawText("Circuit 2 - FULL RC", 20, 20, 30, BLACK);

    int y = 250;       // Horisontell linje
    int startX = 120;  // Start från 3.3V

    // --- 3.3V ---
    //DrawGPIO(startX, y, "GPIO 3.3V", "Pin 1");
    DrawGPIOPin(startX, y, "GPIO 3.3V", "Pin 1");

    // --- Resistor ---
    int resistorX = startX + 80;
    DrawWire(startX + 8, y, resistorX, y); // ledning 3.3V → resistor
    DrawResistor(resistorX, y, "R10k", "10k Ohm resistor");

    // --- Kondensator1 ---
    int cap1X = resistorX + 100;
    DrawWire(resistorX + 60, y, cap1X, y); // horisontell till kondensator1
    DrawCapacitor(cap1X, y, "10uF", "Capacitor 1");

    // --- Nod / mätpunkt till GPIO17 ---
    int nodeX = cap1X + 80;
    //DrawCircle(nodeX, y, 5, BLACK); // nod
    //DrawText("GPIO17", nodeX - 20, y - 30, 20, BLACK);
    DrawWire(cap1X+15,y,nodeX,y);
    //DrawGPIO(nodeX, y, "GPIO17", "Pin 11");
    DrawGPIOPin(nodeX, y, "GPIO17", "Pin 11");

    // Ledning till Kondensator2
    int cap2X = nodeX + 60;
    DrawWire(nodeX + 5, y, cap2X, y);
    DrawCapacitor(cap2X, y, "4.7uF", "Capacitor 2");

    // LED parallellt med Kondensator2
    int ledX = cap2X + 50;
    DrawWire(cap2X + 25, y, ledX, y);
    DrawLED(ledX, y, ledOn, "LED");

    // --- Till GND ---
    int gndX = ledX + 70;
    DrawWire(ledX + 35, y, gndX, y);
    //DrawGND(gndX, y, "GND");
    DrawGNDPin(gndX, y, "GND");

    //DrawText(TextFormat("GPIO17: %.2f V", cap1Voltage * 3.3f), 300, 200, 20, DARKGRAY);
}