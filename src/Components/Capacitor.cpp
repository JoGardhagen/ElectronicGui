#include "Capacitor.h"
#include "../Utilities/Util.h"

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