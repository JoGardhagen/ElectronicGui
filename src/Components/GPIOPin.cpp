#include "GPIOPin.h"
#include "../Utilities/Util.h"

//--- GPIO Pin ---
void DrawGPIOPin(int x, int y, const std::string &label, const std::string &tooltip)
{
    DrawCircle(x, y, 8, BLACK);
    DrawText(label.c_str(), x - 40, y - 30, 20, BLACK);

    Rectangle bounds = {x - 8.0f, y - 8.0f, 16.0f, 16.0f};
    HandleTooltip(bounds, tooltip);
}
// --- GND Pin ---
void DrawGNDPin(int x, int y,const std::string &tooltip)
{
    DrawCircle(x, y, 8, BLACK);
    DrawText("GND", x - 20, y + 15, 20, BLACK);

    Rectangle bounds = {(float)x, (float)y - 20.0f, 40.0f, 40.0f};
    HandleTooltip(bounds,tooltip);
}