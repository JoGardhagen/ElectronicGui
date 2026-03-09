#include <raylib.h>
#include "Circuits.h"

// Här definierar vi varje krets

void DrawCircuit1() {
    // Exempel: enkel ledning + resistor
    DrawLine(200,250,400,250,BLACK);
    DrawRectangle(290,230,40,40,GRAY);
    DrawText("R", 300, 240, 20, BLACK);
}

void DrawCircuit2() {
    // Exempel: cirkel som “lamp”  
    DrawCircle(300,250,40,YELLOW);
}

void DrawCircuit3() {
    // Tom krets än så länge
    DrawText("Circuit 3", 200, 200, 30, BLACK);
}

// Lägg till DrawCircuit4 - DrawCircuit8 på samma sätt
void DrawCircuit4() { DrawText("Circuit 4", 200,200,30,BLACK);}
void DrawCircuit5() { DrawText("Circuit 5", 200,200,30,BLACK);}
void DrawCircuit6() { DrawText("Circuit 6", 200,200,30,BLACK);}
void DrawCircuit7() { DrawText("Circuit 7", 200,200,30,BLACK);}
void DrawCircuit8() { DrawText("Circuit 8", 200,200,30,BLACK);}