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
    auto ic555 = DrawIC(350, 250, 8, "555", "IC-555", pinDescs555);

    Vector2 IcGndPin = ic555.pins[0];
    DrawGPIOPin(IcGndPin.x-200,IcGndPin.y,"GND","GPIO_GND");
    DrawWire(IcGndPin.x,IcGndPin.y,IcGndPin.x-200,IcGndPin.y);

    Vector2 VccPin = ic555.pins[7];
    DrawWire(VccPin.x,VccPin.y,VccPin.x+100,VccPin.y);
    DrawWire(VccPin.x+100,VccPin.y,VccPin.x+100,VccPin.y-70);
    DrawGPIOPin(VccPin.x+100,VccPin.y-70,"+5Vcc","GPIO +5V");

    DrawWire(VccPin.x+100,VccPin.y-70,VccPin.x,VccPin.y-70);
    DrawResistor(VccPin.x-60,VccPin.y-70,"R1","10k Ohm resistor");
    DrawWire(VccPin.x-60,VccPin.y-70,VccPin.x-80,VccPin.y-70);
    DrawResistor(VccPin.x-140,VccPin.y-70,"R2","100k Ohm resistor");
    DrawWire(VccPin.x-70,VccPin.y-70,VccPin.x-70,VccPin.y-40);
    DrawWire(VccPin.x-70,VccPin.y-40,VccPin.x-220,VccPin.y-40);
    DrawWire(VccPin.x-220,VccPin.y-40,VccPin.x-220,VccPin.y+30);
    DrawWire(VccPin.x-220,VccPin.y+30,VccPin.x-220,VccPin.y+50);

    DrawCapacitor(VccPin.x-220,VccPin.y+50,"C1","10uF Kondensator");

    Vector2 OutPin = ic555.pins[2];
    DrawWire(OutPin.x,OutPin.y,OutPin.x-30,OutPin.y);
    DrawWire(OutPin.x-30,OutPin.y,OutPin.x-30,OutPin.y+100);
    DrawWire(OutPin.x-30,OutPin.y+100,OutPin.x-50,OutPin.y+100);
    DrawResistor(OutPin.x-110,OutPin.y+100,"R220","220 Ohm Resistor");
    DrawWire(OutPin.x-110,OutPin.y+100,OutPin.x-120,OutPin.y+100);
    DrawLED(OutPin.x-160,OutPin.y+100,false,"Lysdiod");
    DrawWire(OutPin.x-160,OutPin.y+100,OutPin.x-200,OutPin.y+100);
    DrawWire(OutPin.x-200,OutPin.y+100,IcGndPin.x-200,IcGndPin.y);



    





}