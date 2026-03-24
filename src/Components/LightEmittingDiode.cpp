#include "LightEmittingDiode.h"
#include "../Utilities/Util.h"

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