#include "Wire.h"

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