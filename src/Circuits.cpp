#include <raylib.h>
#include "Circuits.h"
#include <string>
#include "Utilities/Util.h"
#include "Components.h"
#include "Button.h"


void DrawCircuit1_Basic(bool active)
{   

    DrawText("Circuit 1 - BASIC", 250, 50, 30, BLACK);

    int y = 250;

    // Startpunkt: GPIO +V
    DrawGPIO(120,y,"GPIO +V","Pin 1 eller 17");

    // Ledning till resistor
    DrawWire(128, y, 200, y);

    // Resistor
    DrawResistor(200, y, "R330","330 OHM resistor");

    // Ledning till LED
    DrawWire(260, y, 320, y);

    // LED
    DrawLED(320, y, active,"Lysdiod");

    // Ledning till GND
    DrawWire(360, y, 430, y);

    // GND
    DrawGND(430, y,"GND pin 6,9,14,20,25,30,34,39");
}

void DrawCircuit1_Mid(bool ledOn)
{
    DrawText("Circuit 1 - MID",250,50,30,BLACK);

    int y = 250;

    DrawGPIO(120,y,"GPIO +V","Pin 1 eller 17");

    DrawWire(128,y,200,y);

    DrawResistor(200,y,"R330","330 OHM resistor");

    DrawWire(260,y,320,y);

    DrawLED(320,y,ledOn,"Lysdiod");

    DrawWire(360,y,430,y);

    DrawGND(430,y,"GND pins");
}

void DrawCircuit1_Full(/*bool led1, bool led2, bool led3, bool led4*/)
{
   DrawText("Circuit 1 - FULL", 250, 50, 30, BLACK);

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
        DrawGPIO(startX - 120, y, "GPIO " + std::to_string(i+1), "Pin GPIO " + std::to_string(i+1));

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
        DrawWire(startX + 75, y, horizEndX, y);      // horisontell
        DrawWire(horizEndX, y, horizEndX, gndY);     // vertikal

        // GND längst ner
        DrawGND(horizEndX, gndY, "GND");

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
void DrawCircuit2_Basic(){
   DrawText("Circuit 2 - RC Charge", 250, 50, 30, BLACK);

    int y = 250;          // horisontell linje
    int startX = 120;     // start från 3.3V

    // 3.3V
    DrawGPIO(startX, y, "GPIO 3.3V", "Pin 1");

    // resistor
    int resistorX = startX + 80;
    DrawWire(startX + 8, y, resistorX, y); // ledning 3.3V -> resistor
    DrawResistor(resistorX, y, "R10k", "10k Ohm resistor");

    // nod för GPIO17
    int gpioX = resistorX + 100;
    DrawWire(resistorX + 60, y, gpioX+10, y); // ledning resistor -> GPIO
    DrawGPIO(gpioX+10, y, "GPIO17", "Pin 11");

    // ledning till kondensator
    int capX = gpioX + 80;
    DrawWire(gpioX + 4, y, capX, y); // horisontell till kondensator

    // kondensator
    DrawCapacitor(capX, y, "10uF", "Capacitor 10uF");

    // ledning från kondensator ner till GND
    DrawWire(capX + 15, y, capX + 40, y );
    DrawGND(capX + 50, y , "GND");
}
void DrawCircuit2_Mid(bool ledOn)
{
    DrawText("Circuit 2 - RC + LED", 250, 50, 30, BLACK);

    int y = 250;

    // 3.3V
    DrawGPIO(120, y, "GPIO 3.3V", "Pin 1");

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
    DrawGND(470, y , "GND");
}
void DrawCircuit2_Full(bool ledOn)
{
    DrawText("Circuit 2 - FULL RC", 250, 50, 30, BLACK);

    int y = 250;       // Horisontell linje
    int startX = 120;  // Start från 3.3V

    // --- 3.3V ---
    DrawGPIO(startX, y, "GPIO 3.3V", "Pin 1");

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
    DrawGPIO(nodeX, y, "GPIO17", "Pin 11");

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
    DrawGND(gndX, y, "GND");

    //DrawText(TextFormat("GPIO17: %.2f V", cap1Voltage * 3.3f), 300, 200, 20, DARKGRAY);
}
void DrawCircuit3_Basic(float potValue)
{
    DrawText("Circuit 3 - Potentiometer Basic", 250, 50, 30, BLACK);

    int y = 200;
    int startX = 120;

    // --- 3.3V ---
    DrawGPIO(startX, y, "GPIO 3.3V", "Pin 3");

    // --- Pot ---
    int potX = startX + 100;
    PotPins pot = DrawPot(potX, y, potValue, "Pot", "10-1K OHM");

    // --- VCC → pin1 ---
    DrawWire(startX + 8, y, pot.pin1.x, pot.pin1.y);

    // --- pin2 → GND ---
    DrawWire(pot.pin2.x, pot.pin2.y, pot.pin2.x + 100, pot.pin2.y);
    DrawGND(pot.pin2.x + 100, pot.pin2.y, "GND");

    int yForLed = pot.pin3.y+100;
    int xForLed = pot.pin3.x+100;

    DrawWire(pot.pin3.x,pot.pin3.y+50,pot.pin3.x,yForLed);

    DrawWire(pot.pin3.x,yForLed,xForLed,yForLed);

    //bool ledOn = potValue >= 0.7f;  // LED tänds när potValue > 0.3
    
    DrawLEDCustom(xForLed, yForLed, potValue, "LED");
    //bool ledOn = potValue > 0.7f; // Tröskel för full röd
    //DrawLEDFullRed(xForLed, yForLed, ledOn, "LED");

    //DrawLED(xForLed,yForLed,false,"Led");
    DrawWire(xForLed+40,yForLed,xForLed+100,yForLed);
    DrawGND(xForLed+100,yForLed,"GND");

}
void DrawCircuit(int circuit, int level,bool active,bool ledState,float potValue)
{
    switch(circuit)
    {
        case 0:

            if(level == 0) DrawCircuit1_Basic(active);
            if(level == 1) DrawCircuit1_Mid(ledState);
            if(level == 2) DrawCircuit1_Full();

            break;

        case 1:
            if(level==0) DrawCircuit2_Basic();
            if(level==1) DrawCircuit2_Mid(ledState);
            if(level==2) DrawCircuit2_Full(ledState);
            break;

        case 2:
            if(level==0) DrawCircuit3_Basic(potValue);
            break;

        case 3:
           // DrawCircuit4();
            break;

        case 4:
           // DrawCircuit5();
            break;

        case 5:
           // DrawCircuit6();
            break;
    }
}