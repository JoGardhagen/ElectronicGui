#include "GPIOPanel.h"
#include "Util.h"

// Skapa arrayen med alla 40 pins
PinInfo pins[40] = {
    {"3.3V", "Pin 1: 3.3V", RED}, 
    {"5V", "Pin 2: 5V", ORANGE},
    {"GPIO2", "Pin 3: SDA1 / GPIO2", LIGHTGRAY}, 
    {"5V", "Pin 4: 5V", ORANGE},
    {"GPIO3", "Pin 5: SCL1 / GPIO3", LIGHTGRAY}, 
    {"GND", "Pin 6: GND", DARKGRAY},
    {"GPIO4", "Pin 7 / GPIO4", LIGHTGRAY}, 
    {"GPIO14", "Pin 8: TXD0 / GPIO14", LIGHTGRAY},
    {"GND", "Pin 9: GND", DARKGRAY}, 
    {"GPIO15", "Pin10: RXD0 / GPIO15", LIGHTGRAY},
    {"GPIO17", "Pin11 / GPIO17", LIGHTGRAY}, 
    {"GPIO18", "Pin12 / GPIO18", LIGHTGRAY},
    {"GPIO27", "Pin13 / GPIO27", LIGHTGRAY}, 
    {"GND", "Pin14: GND", DARKGRAY},
    {"GPIO22", "Pin15 / GPIO22", LIGHTGRAY}, 
    {"GPIO23", "Pin16 / GPIO23", LIGHTGRAY},
    {"3.3V", "Pin17: 3.3V", RED}, 
    {"GPIO24", "Pin18 / GPIO24", LIGHTGRAY},
    {"GPIO10", "Pin19: MOSI / GPIO10", LIGHTGRAY}, 
    {"GND", "Pin20: GND", DARKGRAY},
    {"GPIO9", "Pin21: MISO / GPIO9", LIGHTGRAY}, 
    {"GPIO25", "Pin22 / GPIO25", LIGHTGRAY},
    {"GPIO11", "Pin23: SCLK / GPIO11", LIGHTGRAY}, 
    {"GPIO8", "Pin24: CE0 / GPIO8", LIGHTGRAY},
    {"GND", "Pin25: GND", DARKGRAY}, 
    {"GPIO7", "Pin26: CE1 / GPIO7", LIGHTGRAY},
    {"ID_SD", "Pin27: ID_SD / GPIO0", LIGHTGRAY}, 
    {"ID_SC", "Pin28: ID_SC / GPIO1", LIGHTGRAY},
    {"GPIO5", "Pin29 / GPIO5", LIGHTGRAY}, 
    {"GND", "Pin30: GND", DARKGRAY},
    {"GPIO6", "Pin31 / GPIO6", LIGHTGRAY}, 
    {"GPIO12", "Pin32 / GPIO12", LIGHTGRAY},
    {"GPIO13", "Pin33 / GPIO13", LIGHTGRAY}, 
    {"GND", "Pin34: GND", DARKGRAY},
    {"GPIO19", "Pin35 / GPIO19", LIGHTGRAY}, 
    {"GPIO16", "Pin36 / GPIO16", LIGHTGRAY},
    {"GPIO26", "Pin37 / GPIO26", LIGHTGRAY}, 
    {"GPIO20", "Pin38 / GPIO20", LIGHTGRAY},
    {"GND", "Pin39: GND", DARKGRAY}, 
    {"GPIO21", "Pin40 / GPIO21", LIGHTGRAY}
};


// Rita panelen
void DrawGPIOPanel40(int startX, int startY, int colSpacing, int rowSpacing, const PinInfo pins[40])
{
    Vector2 mousePos = GetMousePosition();

    for(int i = 0; i < 40; i++)
    {
        int row = i / 2;       // varje rad har två pins
        int col = i % 2;       // vänster = 0, höger = 1
        int x = startX + col * colSpacing;
        int y = startY + row * rowSpacing;

        // Rita pin
        DrawRectangle(x, y, 15, 15, pins[i].color);

        // Räkna ut textposition
        int textX;
        if(col == 0) 
            textX = x - MeasureText(pins[i].name.c_str(), 12) - 5; // vänster om pin
        else 
            textX = x + 20; // höger om pin

        DrawText(pins[i].name.c_str(), textX, y, 12, BLACK);

        // Tooltip om musen hovrar
        Rectangle bounds = {float(x), float(y), 15, 15};
        if(CheckCollisionPointRec(mousePos, bounds))
        {
            DrawTooltip(mousePos.x, mousePos.y, pins[i].tooltip);
        }
    }
}