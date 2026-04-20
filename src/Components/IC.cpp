#include "IC.h"
#include "../Utilities/Util.h"
#include <cmath>

ICPins DrawIC(int x, int y, int pinCount, const std::string& label, const std::string& tooltip, const std::map<int, ICPinDescription>& descriptions)
{
    ICPins icPins;
    icPins.pinCount = pinCount;
    icPins.pinDescriptions = descriptions;

    // Beräkna dimensioner
    int width = 80;
    int height = 50 + (pinCount * 2);

    // Om fler än 8 pinar, använd horisontell layout
    bool horizontalLayout = pinCount > 8;

    if (horizontalLayout) {
        width = 100 + (pinCount * 5);
        height = 50;
    }

    // Rita IC-rektangel
    DrawRectangleLines(x - width/2, y - height/2, width, height, BLACK);

    // Rita etikett
    DrawText(label.c_str(), x - 20, y - 5, 20, BLACK);

    // Placera pinnar beroende på layout
    if (horizontalLayout) {
        int pinsPerSide = pinCount / 2;
        if (pinCount % 2 == 1) pinsPerSide++;

        // Övre rad
        for (int i = 0; i < pinsPerSide && i < pinCount; i++) {
            float pinX = x - width/2 + 10 + (i * (width - 20) / (pinsPerSide > 1 ? (pinsPerSide - 1) : 1));
            float pinY = y - height/2;

            icPins.pins.push_back({pinX, pinY});
            DrawCircle(pinX, pinY, 3, BLACK);
            DrawLine(pinX, pinY, pinX, pinY - 10, BLACK);
        }

        // Nedre rad
        for (int i = pinsPerSide; i < pinCount; i++) {
            int indexInBottomSide = i - pinsPerSide;
            float pinX = x - width/2 + 10 + (indexInBottomSide * (width - 20) / (pinCount - pinsPerSide > 1 ? (pinCount - pinsPerSide - 1) : 1));
            float pinY = y + height/2;

            icPins.pins.push_back({pinX, pinY});
            DrawCircle(pinX, pinY, 3, BLACK);
            DrawLine(pinX, pinY, pinX, pinY + 10, BLACK);
        }
    } else {
        int pinsPerSide = pinCount / 2;
        if (pinCount % 2 == 1) pinsPerSide++;

        // Vänster sida (pins 1,2,3,4) - från topp till botten
        for (int i = 0; i < pinsPerSide && i < pinCount; i++) {
            float pinX = x - width/2;  // Vänster kant
            float pinY = y - height/2 + 10 + (i * (height - 20) / (pinsPerSide > 1 ? (pinsPerSide - 1) : 1));
            
            icPins.pins.push_back({pinX, pinY});
            
            // Rita pin
            DrawCircle(pinX, pinY, 3, BLACK);
            DrawLine(pinX, pinY, pinX - 15, pinY, BLACK);  // Ledning till vänster
        }
        
        // Höger sida (pins 8,7,6,5) - från topp till botten
        for (int i = pinsPerSide; i < pinCount; i++) {
            int indexInRightSide = i - pinsPerSide;
            float pinX = x + width/2;  // Höger kant
            // För att få rätt ordning: index 4=8, 5=7, 6=6, 7=5
            // Så vi vill att y-positionen ska vara samma som på vänster sida, men med omvänd ordning
            float pinY = y - height/2 + 10 + ((pinsPerSide - 1 - indexInRightSide) * (height - 20) / (pinsPerSide > 1 ? (pinsPerSide - 1) : 1));
            
            icPins.pins.push_back({pinX, pinY});
            
            // Rita pin
            DrawCircle(pinX, pinY, 3, BLACK);
            DrawLine(pinX, pinY, pinX + 15, pinY, BLACK);  // Ledning till höger
        }
    }

    // Tooltip för hela komponenten
    Rectangle bounds = {(float)(x - width/2), (float)(y - height/2), (float)width, (float)height};
    HandleTooltip(bounds, tooltip);

    // Kontroll för hover på pinnar
    Vector2 mousePos = GetMousePosition();
    for (int i = 0; i < pinCount; i++) {
        if (i < icPins.pins.size()) {
            Vector2 pinPos = icPins.pins[i];

            // Beräkna avstånd manuellt istället för Vector2Distance
            float dx = mousePos.x - pinPos.x;
            float dy = mousePos.y - pinPos.y;
            float distance = sqrt(dx * dx + dy * dy);

            // Om musen är nära en pinne (radius 15)
            if (distance < 15) {
                // Visa tooltip för den specifika pinnen
                std::string pinName = "";
                std::string pinDesc = "";

                if (descriptions.find(i) != descriptions.end()) {
                    pinName = descriptions.at(i).name;
                    pinDesc = descriptions.at(i).description;
                }

                // Skapa texten som ska visas
                std::string tooltipText = TextFormat("%s: %s", pinName.c_str(), pinDesc.c_str());

                // Mät textens bredd och höjd för att skapa bakgrund
                int textSize = 20;
                Vector2 textSizeVec = MeasureTextEx(GetFontDefault(), tooltipText.c_str(), textSize, 1);

                // Rita vit bakgrund (med en liten marginal)
                Rectangle backgroundRect = {
                    mousePos.x + 10, 
                    mousePos.y + 10, 
                    textSizeVec.x + 10+20, 
                    textSizeVec.y + 10
                };
                DrawRectangleRec(backgroundRect, WHITE);
                DrawRectangleLinesEx(backgroundRect, 1, BLACK);

                // Rita tooltip-text
                DrawText(tooltipText.c_str(), mousePos.x + 15, mousePos.y + 15, textSize, BLACK);
                break; // Visa bara en tooltip åt gången
            }
        }
    }

    return icPins;
}