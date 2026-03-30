#include "Circuits.h"

// forward declarations
void DrawCircuit1_Basic(bool ,IGPIO* gpio);
void DrawCircuit1_Mid(AppState& state);
void DrawCircuit1_Full();

void DrawCircuit2_Basic();
void DrawCircuit2_Mid(bool ledOn);
void DrawCircuit2_Full(bool ledOn);

void DrawCircuit3_Basic(float potValue); 
void DrawCircuit3_Mid(float potValue);
void DrawCirciut3_Full(float potValue);



void DrawCircuit(int circuit, int level,bool active,bool ledState,float potValue,IGPIO* gpio,AppState& state)
{
    switch(circuit)
    {
        case 0:

            if(level == 0) DrawCircuit1_Basic(active, gpio);
            if(level == 1) DrawCircuit1_Mid(state);
            if(level == 2) DrawCircuit1_Full();
            break;

        case 1:
            if(level==0) DrawCircuit2_Basic();
            if(level==1) DrawCircuit2_Mid(ledState);
            if(level==2) DrawCircuit2_Full(ledState);
            break;

        case 2:
            if(level==0) DrawCircuit3_Basic(potValue);
            if(level==1) DrawCircuit3_Mid(potValue);
            if(level==2) DrawCirciut3_Full(potValue);
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