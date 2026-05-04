#include "Circuits.h"

// forward declarations
// Circuit 1
void DrawCircuit1_Basic(bool ,IGPIO* gpio);
void DrawCircuit1_Mid(AppState& state,IGPIO* gpio);
void DrawCircuit1_Full(AppState& state, IGPIO* gpio);

// Circuit 2
void DrawCircuit2_Basic();
void DrawCircuit2_Mid(bool ledOn);
void DrawCircuit2_Full(bool ledOn);

// Circuit 3
void DrawCircuit3_Basic(float potValue); 
void DrawCircuit3_Mid(float potValue);
void DrawCirciut3_Full(float potValue);

// Circuit 4
void DrawCircuit4_Basic();
void DrawCircuit4_Mid(AppState& state, IGPIO* gpio);

//Circuit 5 Transistorer 
void DrawCircuit5_Basic(AppState& state, IGPIO* gpio);
void DrawCircuit5_Mid(AppState& state, IGPIO* gpio);

//Circuit 6
void DrawCircuit6_Basic(AppState& state, IGPIO* gpio);

// Circuit 7
void DrawCircuit7_Basic(bool ,IGPIO* gpio);
void DrawCircuit7_Mid(bool active,IGPIO* gpio);


void DrawCircuitUnderConstruction();




void DrawCircuit(int circuit, int level,bool active,bool ledState,float potValue,IGPIO* gpio,AppState& state)
{
    switch(circuit)
    {
        case 0:

            if(level == 0) DrawCircuit1_Basic(active, gpio);
            if(level == 1) DrawCircuit1_Mid(state,gpio);
            if(level == 2) DrawCircuit1_Full(state,gpio);
            break;

        case 1:
            if(level == 0)DrawCircuit4_Basic();
            if(level == 1)DrawCircuit4_Mid(state,gpio);
            if(level==2)DrawCircuitUnderConstruction();
            break;

        case 2:
            if(level==0) DrawCircuit3_Basic(potValue);
            //if(level==1) DrawCircuit3_Mid(potValue);
            //if(level==2) DrawCirciut3_Full(potValue);
            if( level==1 || level==2)DrawCircuitUnderConstruction();
            break;

        case 3:
            // DrawCircuit4();
            // if(level==0) DrawCircuit2_Basic();
            // if(level==1) DrawCircuit2_Mid(ledState);
            // if(level==2) DrawCircuit2_Full(ledState);
            //if(level==0 || level==1 || level==2)DrawCircuitUnderConstruction();
            if(level == 0) DrawCircuit7_Basic(active,gpio);
            if(level == 1) DrawCircuit7_Mid(active,gpio);
            if(level==2)DrawCircuitUnderConstruction();
            break;

        case 4:
           // DrawCircuit5();
            if(level== 0)DrawCircuit5_Basic(state,gpio);
            if(level == 1)DrawCircuit5_Mid(state,gpio);
            if(level==2)DrawCircuitUnderConstruction();
            break;

        case 5:
           // DrawCircuit6();
            if(level == 0) DrawCircuit6_Basic(state,gpio);
            if( level==1 || level==2)DrawCircuitUnderConstruction();
            break;
    }
}