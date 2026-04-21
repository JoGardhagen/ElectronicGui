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
#include "../Components/IC.h"
#include <map>

void DrawCircuit6_Basic(AppState& state, IGPIO* gpio){
    DrawText("Circuit 6 - 555 Timer", 20, 20, 30, BLACK);
    
    // Skapa beskrivningar för 555-timer pinnar
    std::map<int, ICPinDescription> pinDescs555 = {
        {0, {"GND", "Ground (Pin_1)"}},
        {1, {"TRIG", "Trigger input (Pin_2)"}},
        {2, {"OUT", "Output signal (Pin_3)"}},
        {3, {"THR", "Threshold input (Pin_4)"}},
        {4, {"RST", "Reset input (Pin_5)"}},
        {5, {"CTL", "Control voltage (Pin_6)"}},
        {6, {"DIS", "Disable input (Pin_7)"}},
        {7, {"VCC", "Power supply (5V) (Pin_8)"}}
    };
    
    // Rita en 8-pin IC (som 555)
    auto ic555 = DrawIC(350, 250, 8, "555", "NE555P_Ic 555-Timer", pinDescs555);

    Vector2 IcGndPin = ic555.pins[0];
    //==========GND_WIRE
    DrawGPIOPin(100,IcGndPin.y,"GND","GPIO_GND");
    DrawWire(100,IcGndPin.y,IcGndPin.x,IcGndPin.y);


    Vector2 VccPin = ic555.pins[7];
    //=============VccWire
    DrawGPIOPin(100,VccPin.y-70,"+5Vcc","GPIO +5V");
    DrawWire(100,VccPin.y-70,100,VccPin.y-30);
    DrawWire(100,VccPin.y-30,410,VccPin.y-30);
    DrawWire(410,VccPin.y-30,410,VccPin.y);
    DrawWire(410,VccPin.y,VccPin.x,VccPin.y);
    //====================

    //==========R1
    DrawResistor(VccPin.x+60,VccPin.y-30,"R1","10k Ohm resistor");
    DrawWire(VccPin.x,VccPin.y,VccPin.x+50,VccPin.y);
    DrawWire(VccPin.x+50,VccPin.y,VccPin.x+50,VccPin.y-30);
    DrawWire(VccPin.x+50,VccPin.y-30,VccPin.x+60,VccPin.y-30);
    DrawWire(VccPin.x+120,VccPin.y-30,VccPin.x+140,VccPin.y-30);
    Vector2 DisPin = ic555.pins[6];
    DrawWire(VccPin.x+140,VccPin.y-30,VccPin.x+140,DisPin.y);
    DrawWire(VccPin.x+140,DisPin.y,DisPin.x,DisPin.y);
    
    //=============R2
    DrawResistor(DisPin.x+160,DisPin.y-30,"R2","100k Ohm resistor");
    DrawWire(DisPin.x+140,DisPin.y,DisPin.x+150,DisPin.y);
    DrawWire(DisPin.x+150,DisPin.y,DisPin.x+150,DisPin.y-30);
    DrawWire(DisPin.x+150,DisPin.y-30,DisPin.x+160,DisPin.y-30);
    DrawWire(DisPin.x+220,DisPin.y-30,DisPin.x+235,DisPin.y-30);
    Vector2  CtlPin = ic555.pins[5];
    DrawWire(DisPin.x+235,DisPin.y-30,DisPin.x+235,CtlPin.y);
    DrawWire(DisPin.x+235,CtlPin.y,CtlPin.x,CtlPin.y);
    

    //DrawCapacitor(VccPin.x-200,VccPin.y+50,"C1","10uF Kondensator");


    Vector2 OutPin = ic555.pins[2];

    DrawResistor(OutPin.x-110,OutPin.y+100,"R220","220 Ohm Resistor");

    DrawLED(OutPin.x-160,OutPin.y+100,false,"Lysdiod");




    





}