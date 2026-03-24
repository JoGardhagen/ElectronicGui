#include "Resistor.h"
#include "../Utilities/Util.h"

// --- Resistor ---
void DrawResistor(int x, int y, const std::string &label,const std::string &tooltip)
{
    DrawRectangleLines(x, y - 15, 60, 30, BLACK);
    DrawText(label.c_str(), x + 10, y - 10, 20, BLACK);

    Rectangle bounds = {(float)x, (float)y - 20.0f, 40.0f, 40.0f};
    HandleTooltip(bounds,tooltip);
}
//---VridPotentiometer
PotPins DrawPotentiometer(int x, int y, float value, const std::string &label, const std::string &tooltip)
{
    int width = 60;

    // --- Bas (resistor) ---
    DrawRectangleLines(x, y - 15, width, 30, BLACK);

    // --- Pins ---
    Vector2 pin1 = {(float)x, (float)y};               // vänster
    Vector2 pin2 = {(float)(x + width), (float)y};     // höger
    Vector2 pin3 = {(float)(x + width / 2), (float)y}; // mitten (OUT)

    // --- Ledningar ---
    DrawLine(x - 20, y, x, y, BLACK);                 // VCC
    DrawLine(x + width, y, x + width + 20, y, BLACK); // GND

    // --- WIPER (pil mot potten, ingen linje) ---
    int midX = (int)pin3.x;
    int downY = y + 25;

    // bara pilspetsen
    DrawLine(midX - 5, downY, midX, downY - 10, BLACK);
    DrawLine(midX + 5, downY, midX, downY - 10, BLACK);
    
    DrawLine(midX,downY-10,midX,downY+40,BLACK);
    // liten nod (valfri men snygg)
    //DrawCircle(midX, downY-10, 3, RED);

    // --- Label ---
    DrawText(label.c_str(), x + 5, y - 40, 20, BLACK);

    Rectangle bounds = {(float)x, (float)(y - 20), 60.0f, 50.0f};
    HandleTooltip(bounds, tooltip);  

    return {pin1, pin2, pin3};
}