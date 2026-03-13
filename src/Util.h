#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <raylib.h>

// Små hjälpfunktioner för GUI, t.ex. tooltip
inline void DrawTooltip(int mouseX, int mouseY, const std::string &text)
{
    int padding = 5;
    int width = MeasureText(text.c_str(), 16) + padding * 2;
    int height = 20 + padding * 2;

    DrawRectangle(mouseX, mouseY - height, width, height, RAYWHITE);
    DrawRectangleLines(mouseX, mouseY - height, width, height, BLACK);
    DrawText(text.c_str(), mouseX + padding, mouseY - height + padding, 16, BLACK);
}

#endif