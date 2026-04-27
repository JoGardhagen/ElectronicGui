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

void DrawCircuit7_Basic(bool active,IGPIO* gpio){
    DrawText("Circuit 4 - Seriel Circuit", 20, 20, 30, BLACK);

    int y = 250;

    // 3.3V
    DrawGPIOPin(120, y, "GPIO 3.3V", "3V3");
    DrawWire(120, y,170, y);
    DrawWire(170, y,170, y + 30);
    DrawWire(170, y + 30,200, y + 30);
    DrawResistor(200, y+30,"R330","Resistor 330 Ohm");
    DrawWire(260,y+30,280,y+30);
    DrawLED(280,y+30,active,"LED");
    DrawWire(320,y+30,350,y+30);
    DrawResistor(350,y+30,"R330","Resistor 330 Ohm");
    DrawWire(410,y+30,440,y+30);
    DrawLED(440,y+30,active,"LED");
    DrawWire(480,y+30,500,y+30);
    DrawResistor(500,y+30,"R330","Resistor 330 Ohm");
    DrawWire(560,y+30,580,y+30);
    DrawLED(580,y+30,active,"LED");
    DrawWire(620,y+30,670,y+30);
    DrawGPIOPin(670,y+30,"GND","GND GPIO Pin");
}

void DrawCircuit7_Mid(bool active,IGPIO* gpio){
    DrawText("Circuit 4 - Parallel Circuit", 20, 20, 30, BLACK);

    int y = 150;

    DrawGPIOPin(120,y,"GPIO 3.3V","3.3V pin");
    DrawWire(120,y,120,y+200);

    //DrawWire(120,y+50,200,y+50);

    DrawWire(120,y+100,200,y+100);
    DrawResistor(200,y+100,"R330","330 Ohm Resistor");
    DrawWire(260,y+100,300,y+100);
    DrawLED(300,y+100,active,"LED");
    DrawWire(340,y+100,400,y+100);


    DrawWire(120,y+150,200,y+150);
    DrawResistor(200,y+150,"R330","330 Ohm Resistor");
    DrawWire(260,y+150,300,y+150);
    DrawLED(300,y+150,active,"LED");
    DrawWire(340,y+150,400,y+150);


    DrawWire(120,y+200,200,y+200);
    DrawResistor(200,y+200,"R330","330 Ohm Resistor");
    DrawWire(260,y+200,300,y+200);
    DrawLED(300,y+200,active,"LED");
    DrawWire(340,y+200,400,y+200);

    DrawWire(400,y+100,400,y+250);
    DrawWire(400,y+250,450,y+250);

    DrawGPIOPin(450,y+250,"GND","GPIO GND");


}