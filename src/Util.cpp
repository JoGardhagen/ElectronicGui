#include "Util.h"

void HandleTooltip(Rectangle bounds, const std::string& tooltip)
{
    if (tooltip.empty()) return;

    Vector2 mousePos = GetMousePosition();

    if (CheckCollisionPointRec(mousePos, bounds))
    {
        DrawTooltip(mousePos.x, mousePos.y, tooltip);
    }
}
