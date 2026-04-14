#include "Spst.h"
#include "../Utilities/Util.h"

void DrawSwitch(int x, int y, bool pressed, float size, const std::string &tooltip)
{
    float wireLen = 30 * size;
    float terminalOffset = 5 * size;
    float armLength = 15 * size;
    float radius = (3 * size) / 2;

    // ledningar vänster/höger
    DrawLine(x - wireLen, y, x - terminalOffset, y, BLACK);
    DrawLine(x + terminalOffset, y, x + wireLen, y, BLACK);

    // terminaler
    DrawCircle(x - terminalOffset, y, radius, BLACK);
    DrawCircle(x + terminalOffset, y, radius, BLACK);

    // arm
    if (pressed)
    {
        DrawLine(x - terminalOffset, y, x + terminalOffset, y, BLACK);
    }
    else
    {
        DrawLine(x - terminalOffset, y,
                 x + terminalOffset, y - armLength, BLACK);
    }

    Rectangle bounds = {(float)x, (float)y - 20.0f, 40.0f, 40.0f};
    HandleTooltip(bounds, tooltip);
}