#include "Transistor.h"
#include <cmath>
#include "../Utilities/Util.h"

static void DrawArrow(Vector2 from, Vector2 to, Color col)
{
    DrawLineV(from, to, col);

    Vector2 dir = { to.x - from.x, to.y - from.y };
    float len = sqrtf(dir.x * dir.x + dir.y * dir.y);
    if (len == 0) return;

    dir.x /= len;
    dir.y /= len;

    Vector2 left  = { to.x - dir.x * 8 + dir.y * 4, to.y - dir.y * 8 - dir.x * 4 };
    Vector2 right = { to.x - dir.x * 8 - dir.y * 4, to.y - dir.y * 8 + dir.x * 4 };

    DrawLineV(to, left, col);
    DrawLineV(to, right, col);
}

TransistorPins DrawNPNTransistor(int x, int y, bool active, const std::string& label, const std::string& tooltip)
{   
    DrawText(label.c_str(), x - 40, y - 30, 20, BLACK);
    // BASE
    Vector2 baseStart = { (float)(x - 40), (float)y };
    Vector2 baseEnd = { (float)x, (float)y };
    DrawLine(baseStart.x, baseStart.y, baseEnd.x, baseEnd.y, BLACK);

    // Lodrät linje (tjockare)
    float lineThickness = 5.0f; // Tjocklek på linjen
    float lineLength = 20.0f; // Längd på den lodräta linjen
    DrawRectangle(baseEnd.x - lineThickness / 2, baseEnd.y - lineLength / 2, lineThickness, lineLength, BLACK);

    // COLLECTOR (vertikal och diagonal linje)
    Vector2 cTop = { (float)x, (float)(y - 40) };
    Vector2 cMid = { (float)(x + 20), (float)(y - 20) };
    //DrawLine(x, y - 5, x, y - 40, BLACK); // Vertikal linje
    DrawLine(x, y - 5, cMid.x, cMid.y, BLACK); // Diagonal linje
    DrawLine(cMid.x, cMid.y, cMid.x, y - 40, BLACK); // Vertikal linje

    // EMITTER (diagonal och vertikal linje)
    Vector2 eMid = { (float)(x + 20), (float)(y + 20) };
    Vector2 emitterEnd = { eMid.x, eMid.y + 20 };
    DrawLine(x, y + 5, eMid.x, eMid.y, BLACK); // Diagonal linje
    DrawLine(eMid.x, eMid.y, emitterEnd.x, emitterEnd.y, BLACK); // Vertikal linje

    // PIL PÅ DEN DIAGONALA EMITTERLINJEN (NPN)
    //Vector2 arrowStart = { x, y + 5 };
    Vector2 arrowStart = { static_cast<float>(x), static_cast<float>(y + 5) };
    Vector2 arrowEnd = { eMid.x, eMid.y };
    DrawArrow(arrowStart, arrowEnd, BLACK);

    Rectangle bounds = {(float)x, (float)(y - 20), 60.0f, 50.0f};
    HandleTooltip(bounds, tooltip);  


    // Returnera basen och kollektorn för vidare användning
    return { baseStart, cMid, emitterEnd };
}

TransistorPins DrawPNPTransistor(int x, int y, bool active, const std::string& label, const std::string& tooltip)
{     
    DrawText(label.c_str(), x - 40, y - 30, 20, BLACK);
    // BASE (horisontell linje)
    Vector2 baseStart = { (float)(x - 40), (float)y };
    Vector2 baseEnd = { (float)x, (float)y };
    DrawLine(baseStart.x, baseStart.y, baseEnd.x, baseEnd.y, BLACK);

    // Lodrät linje (tjockare)
    float lineThickness = 5.0f; // Tjocklek på linjen
    float lineLength = 20.0f; // Längd på den lodräta linjen
    DrawRectangle(baseEnd.x - lineThickness / 2, baseEnd.y - lineLength / 2, lineThickness, lineLength, BLACK);

    // COLLECTOR (vertikal och diagonal linje)
    Vector2 cMid = { (float)(x + 20), (float)(y - 20) };
    DrawLine(x, y - 5, cMid.x, cMid.y, BLACK); // Diagonal linje
    DrawLine(cMid.x, cMid.y, cMid.x, y - 40, BLACK); // Vertikal linje

    // EMITTER (diagonal och vertikal linje)
    Vector2 eMid = { (float)(x + 20), (float)(y + 20) };
    Vector2 emitterEnd = { eMid.x, eMid.y + 20 };
    DrawLine(x, y + 5, eMid.x, eMid.y, BLACK); // Diagonal linje
    DrawLine(eMid.x, eMid.y, emitterEnd.x, emitterEnd.y, BLACK); // Vertikal linje

    // PIL PÅ DEN DIAGONALA EMITTERLINJEN (PNP)
    Vector2 arrowStart = { eMid.x, eMid.y };
    //Vector2 arrowEnd = { x, y + 5 };
    Vector2 arrowEnd = { static_cast<float>(x), static_cast<float>(y + 5) };
    DrawArrow(arrowStart, arrowEnd, BLACK);

    Rectangle bounds = {(float)x, (float)(y - 20), 60.0f, 50.0f};
    HandleTooltip(bounds, tooltip);  


    // Returnera basen, kollektorn och emitteren för vidare användning
    return { baseStart, cMid, emitterEnd };
}