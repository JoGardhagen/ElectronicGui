#include <raylib.h>
#include <cmath>

void DrawCircuitUnderConstruction()
{   
    DrawText("Under Construction", 20, 20, 30, BLACK);

    int centerX = 425;
    int baseY = 250;

    int lx = centerX - 150;
    int rx = centerX + 150;

    // ===== KONER =====
    DrawTriangle({(float)lx, (float)baseY},
                 {(float)lx - 40, (float)baseY + 100},
                 {(float)lx + 40, (float)baseY + 100},
                 ORANGE);

    DrawTriangleLines({(float)lx, (float)baseY},
                      {(float)lx - 40, (float)baseY + 100},
                      {(float)lx + 40, (float)baseY + 100},
                      BLACK);

    DrawRectangle(lx - 30, baseY + 40, 60, 10, WHITE);
    DrawRectangle(lx - 25, baseY + 70, 50, 10, WHITE);

    DrawTriangle({(float)rx, (float)baseY},
                 {(float)rx - 40, (float)baseY + 100},
                 {(float)rx + 40, (float)baseY + 100},
                 ORANGE);

    DrawTriangleLines({(float)rx, (float)baseY},
                      {(float)rx - 40, (float)baseY + 100},
                      {(float)rx + 40, (float)baseY + 100},
                      BLACK);

    DrawRectangle(rx - 30, baseY + 40, 60, 10, RAYWHITE);
    DrawRectangle(rx - 25, baseY + 70, 50, 10, RAYWHITE);

    // ===== BANDEROLL =====
    int segments = 40;
    float thickness = 30.0f;

    Vector2 start = {(float)lx, (float)baseY};
    Vector2 end   = {(float)rx, (float)baseY};

    for(int i = 0; i < segments; i++)
    {
        float t1 = (float)i / segments;
        float t2 = (float)(i + 1) / segments;

        float x1 = start.x + (end.x - start.x) * t1;
        float x2 = start.x + (end.x - start.x) * t2;

        float sag1 = 40 * std::sin(t1 * PI);
        float sag2 = 40 * std::sin(t2 * PI);

        float y1 = start.y + sag1;
        float y2 = start.y + sag2;

        // fyllning
        DrawTriangle({x1, y1}, {x2, y2}, {x1, y1 + thickness}, YELLOW);
        DrawTriangle({x2, y2}, {x2, y2 + thickness}, {x1, y1 + thickness}, YELLOW);

        // outline
        DrawLineEx({x1, y1}, {x2, y2}, 2, BLACK);
        DrawLineEx({x1, y1 + thickness}, {x2, y2 + thickness}, 2, BLACK);
    }
}