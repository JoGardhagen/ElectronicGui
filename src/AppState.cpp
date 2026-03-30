#include "AppState.h"
#include <raylib.h>

void AppState::UpdateCircuit(float dt)
{
    if(currentPage != 1) return;
    if(circuitLevel == 1){ // MID, 1 kondensator
        if(circuitActive){
            if(charging)
                cap1Voltage += (1.0f - cap1Voltage) * (dt / RC1);
            else
                cap1Voltage -= cap1Voltage * (dt / RC1);

            if(cap1Voltage >= 0.95f) charging = false;
            if(cap1Voltage <= 0.05f) charging = true;
        }
        rcLedOn = cap1Voltage > 0.3f;
    }

    if(circuitLevel == 2){ // FULL, 2 kondensatorer
        if(circuitActive){
            if(charging){
                cap1Voltage += (1.0f - cap1Voltage) * (dt / RC1);
                cap2Voltage += (cap1Voltage - cap2Voltage) * (dt / RC2);
            } else {
                cap1Voltage -= cap1Voltage * (dt / RC1);
                cap2Voltage -= cap2Voltage * (dt / RC2);
            }

            if(cap2Voltage >= 0.95f) charging = false;
            if(cap2Voltage <= 0.05f) charging = true;
        }
        rcLedOn = cap2Voltage > 0.6f;
    }
}

void AppState::HandlePotSlider()
{
    if(currentPage != 2) return;

    int sliderX = 600;
    int sliderY = 150;
    int sliderWidth = 200;
    int sliderHeight = 20;

    DrawRectangle(sliderX, sliderY, sliderWidth, sliderHeight, GRAY);

    int handleX = sliderX + (int)(potValue * sliderWidth) - 5;
    DrawRectangle(handleX, sliderY - 5, 10, sliderHeight + 10, BLUE);

    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        Vector2 mousePos = GetMousePosition();
        if(mousePos.x >= sliderX && mousePos.x <= sliderX + sliderWidth &&
           mousePos.y >= sliderY - 5 && mousePos.y <= sliderY + sliderHeight + 5)
        {
            potValue = (mousePos.x - sliderX) / (float)sliderWidth;
            if(potValue < 0.0f) potValue = 0.0f;
            if(potValue > 1.0f) potValue = 1.0f;
        }
    }

    DrawText(TextFormat("Pot: %.2f", potValue), sliderX, sliderY - 30, 20, BLACK);
}