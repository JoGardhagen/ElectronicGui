#include "Components.h"
#include "Util.h"

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

// --- Resistor ---
void DrawResistor(int x, int y, const std::string &label,const std::string &tooltip)
{
    DrawRectangleLines(x, y - 15, 60, 30, BLACK);
    DrawText(label.c_str(), x + 10, y - 10, 20, BLACK);

    Rectangle bounds = {(float)x, (float)y - 20.0f, 40.0f, 40.0f};
    HandleTooltip(bounds,tooltip);
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