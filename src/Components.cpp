#include "Components.h"
#include "Utilities/Util.h"


// --- GPIO ---
void DrawGPIO(int x, int y, const std::string &label, const std::string &tooltip)
{
    DrawCircle(x, y, 8, BLACK);
    DrawText(label.c_str(), x - 40, y - 30, 20, BLACK);

    Rectangle bounds = {x - 8.0f, y - 8.0f, 16.0f, 16.0f};
    HandleTooltip(bounds,tooltip);
}

// --- LED ---
void DrawLED(int x, int y, bool on,const std::string &tooltip)
{
    // Fyll färg för LED-ljus
    Color ledColor = on ? RED : DARKGRAY;

    
    Vector2 t1 = {(float)x, (float)y - 20.0f};
    Vector2 t2 = {(float)x, (float)y + 20.0f};
    Vector2 t3 = {(float)x + 40.0f, (float)y};

    DrawTriangle(t1, t2, t3, ledColor);

    // Diode-streck (katod)
    DrawLine(x + 40, y - 20, x + 40, y + 20, BLACK);

    // Strömpilar (valfritt)
    if(on)
    {
        DrawLine(x + 25, y - 30, x + 40, y - 45, RED);
        DrawLine(x + 35, y - 30, x + 50, y - 45, RED);
    }
    Rectangle bounds = {(float)x, (float)y - 20.0f, 40.0f, 40.0f};
    HandleTooltip(bounds,tooltip);
}
void DrawLEDCustom(int x, int y, float potValue, const std::string &tooltip)
{
    int red = (int)(potValue * 255.0f);
    if(red > 255) red = 255;
    if(red < 0) red = 0;
    //Color ledColor = {red, 0, 0, 255 };
    Color ledColor = { static_cast<unsigned char>(red), 0, 0, 255 };

    // Triangel
    Vector2 t1 = {(float)x, (float)y - 20};
    Vector2 t2 = {(float)x, (float)y + 20};
    Vector2 t3 = {(float)x + 40, (float)y};
    DrawTriangle(t1, t2, t3, ledColor);

    // Diode-streck (katod)
    DrawLine(x + 40, y - 20, x + 40, y + 20, BLACK);

    // Valfri pil om du vill
    if(potValue > 0.3f) {
        DrawLine(x + 25, y - 30, x + 40, y - 45, ledColor);
        DrawLine(x + 35, y - 30, x + 50, y - 45, ledColor);
    }

    Rectangle bounds = {(float)x, (float)y - 20.0f, 40.0f, 40.0f};
    HandleTooltip(bounds, tooltip);
}
void DrawLEDFullRed(int x, int y, bool on, const std::string &tooltip)
{
    Color fillColor = on ? RED : DARKGRAY;

    // Rektangel som fyller hela LED-området
    DrawRectangle(x, y - 20, 40, 40, fillColor);

    // Valfria konturer
    DrawTriangle({(float)x, (float)y - 20}, {(float)x, (float)y + 20}, {(float)x + 40, (float)y}, BLACK);
    DrawLine(x + 40, y - 20, x + 40, y + 20, BLACK);

    Rectangle bounds = {(float)x, (float)y - 20.0f, 40.0f, 40.0f};
    HandleTooltip(bounds, tooltip);
}

// --- Resistor ---
void DrawResistor(int x, int y, const std::string &label,const std::string &tooltip)
{
    DrawRectangleLines(x, y - 15, 60, 30, BLACK);
    DrawText(label.c_str(), x + 10, y - 10, 20, BLACK);

    Rectangle bounds = {(float)x, (float)y - 20.0f, 40.0f, 40.0f};
    HandleTooltip(bounds,tooltip);
}
//---VridPotentiometer
PotPins DrawPot(int x, int y, float value, const std::string &label, const std::string &tooltip)
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
void DrawCapacitor(int x, int y, const std::string &label,const std::string &tooltip)
{
    // anslutning vänster
    DrawLine(x - 20, y, x, y, BLACK);

    // kondensatorplattor
    DrawLine(x, y - 20, x, y + 20, BLACK);
    DrawLine(x + 15, y - 20, x + 15, y + 20, BLACK);

    // anslutning höger
    DrawLine(x + 15, y, x + 35, y, BLACK);

    // label
    DrawText(label.c_str(), x - 10, y - 40, 20, BLACK);

    // Om du vill ha tooltip i framtiden:
    Rectangle bounds = {float(x-8), float(y-8), 16.0f, 16.0f};
    HandleTooltip(bounds, tooltip);
}

// --- GND ---
void DrawGND(int x, int y,const std::string &tooltip)
{
    DrawCircle(x, y, 8, BLACK);
    DrawText("GND", x - 20, y + 15, 20, BLACK);

    Rectangle bounds = {(float)x, (float)y - 20.0f, 40.0f, 40.0f};
    HandleTooltip(bounds,tooltip);
}

// --- Ledning/Wire ---
void DrawWire(int x1, int y1, int x2, int y2, bool arrow)
{
    DrawLine(x1, y1, x2, y2, BLACK);
    if(arrow)
    {
        // enkel pil i slutet
        DrawLine(x2 - 10, y2 - 10, x2, y2, BLACK);
        DrawLine(x2 - 10, y2 + 10, x2, y2, BLACK);
    }
}