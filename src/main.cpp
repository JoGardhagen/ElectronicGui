#include <raylib.h>
#include "Button.h"
#include "Circuits.h"
#include "Panels/GPIOPanel.h"
#include <vector>
#include <string>

//void DrawCircuit1();
static float potValue = 0.1f; // startvärde för Circuit 3

int main(){
    bool circuitActive = false;
    bool ledState = false;
    float RC1 = 10'000 * 10e-6; // 10k * 10uF = 0.1 s
    float RC2 = 10'000 * 4.7e-6;  // R * C2
    //static float capacitorVoltage = 0.0f; // 0 = urladdad, 1 = full laddning
    float dt = 1.0f / 60;
    static bool charging = true;
    static float cap1Voltage = 0.0f;
    static float cap2Voltage = 0.0f;

    const int screenWidth = 800;
    const int screenHeight = 600;
    int currentPage = -1;

    InitWindow(screenWidth,screenHeight,"El-Lära GUI");
    SetTargetFPS(60);

    std::vector<Button> buttons;
    int btnCount = 6;
    int spacing = 5;

    Button basicBtn(220,450,100,40,"Basic");
    Button midBtn(360,450,100,40,"Mid");
    Button fullBtn(500,450,100,40,"Full");
    Button activate(600,50,200,40,"Activate Circiut");
    activate.SetOnClick([&](){
    circuitActive = !circuitActive;
        if(!circuitActive)
            //if(currentPage == 1) capacitorVoltage = 0.0f; // Circuit 2
            ledState = false;
    });

    activate.SetColor(YELLOW);
    activate.SetColorHover(ORANGE);

    Button ledBtn(350,400,130,40,"Toggle LED");

    ledBtn.SetOnClick([&](){
        if(!circuitActive)
            ledState = !ledState;
    });

    bool showGPIOPanel = false;

    Button togglePanelBtn(620, 10, 150, 40, "GPIO Panel");
    togglePanelBtn.SetColor(BLUE);
    togglePanelBtn.SetColorHover(VIOLET);
    togglePanelBtn.SetOnClick([&](){
        showGPIOPanel = !showGPIOPanel; // växla true/false
    });


    
    int totalSpacing = spacing * (btnCount + 1);
    int usableWidth = screenWidth - totalSpacing;
    int btnWidth = usableWidth / btnCount;
    int btnHeight = 40;
    int btnY = screenHeight - btnHeight - 10;
    
    
    int circuitLevel = 0;
    
    basicBtn.SetOnClick([&](){ 
        circuitLevel = 0;
        circuitActive = false;
    });

    midBtn.SetOnClick([&](){
        circuitLevel = 1;
        circuitActive = false;
        cap1Voltage = 0;
        cap2Voltage = 0;
        charging = true;
    });
    fullBtn.SetOnClick([&](){ 
        circuitLevel = 2;
        circuitActive = false;
        cap1Voltage = 0;
        cap2Voltage = 0;
        charging = true;
    });
    
    
    for (int i = 0; i < btnCount; i++)
    {
        int x = spacing + i * (btnWidth + spacing);
        buttons.emplace_back(x, btnY, btnWidth, btnHeight, "K" + std::to_string(i + 1));
        buttons[i].SetOnClick([&currentPage,&circuitLevel,i]{
            currentPage = i;
            circuitLevel = 0;
        });
    }

    bool rcLedOn = false;   

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        DrawText("El-Lära GUI", 20, 20, 30, BLACK);
        togglePanelBtn.Draw();
        
        if(currentPage == -1)
        // Tom start-sida
        {   
            DrawText("Välj en krets längst ner", 200, 250, 25, GRAY);
        }else{   
            DrawText(TextFormat("Level: %i", circuitLevel),20,60,20,GRAY);

            if(currentPage == 1) // Circuit 2
            {
                // -------- MID (1 kondensator) --------
                if(circuitLevel == 1)
                {
                    if(circuitActive)
                    {
                        if(charging)
                            cap1Voltage += (1.0f - cap1Voltage) * (dt / RC1);
                        else
                            cap1Voltage -= cap1Voltage * (dt / RC1);
                    
                        if(cap1Voltage >= 0.95f) charging = false;
                        if(cap1Voltage <= 0.05f) charging = true;
                    }
                
                    rcLedOn = cap1Voltage > 0.3f;
                }
            
                // -------- FULL (2 kondensatorer) --------
                if(circuitLevel == 2)
                {
                    if(circuitActive)
                    {
                        if(charging)
                        {
                            cap1Voltage += (1.0f - cap1Voltage) * (dt / RC1);
                            cap2Voltage += (cap1Voltage - cap2Voltage) * (dt / RC2);
                        }
                        else
                        {
                            cap1Voltage -= cap1Voltage * (dt / RC1);
                            cap2Voltage -= cap2Voltage * (dt / RC2);
                        }
                    
                        if(cap2Voltage >= 0.95f) charging = false;
                        if(cap2Voltage <= 0.05f) charging = true;
                    }
                    
                    rcLedOn = cap2Voltage > 0.6f;
                }
            }
            if(currentPage == 2 && circuitLevel == 0)
                {
                    int sliderX = 600;
                    int sliderY = 150;
                    int sliderWidth = 200;
                    int sliderHeight = 20;
                
                    // Bakgrund
                    DrawRectangle(sliderX, sliderY, sliderWidth, sliderHeight, GRAY);
                
                    // Handle
                    int handleX = sliderX + (int)(potValue * sliderWidth) - 5;
                    DrawRectangle(handleX, sliderY - 5, 10, sliderHeight + 10, BLUE);
                
                    // Interaktion
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

        // rita kretsen med korrekt LED-status
        bool ledToDraw = (currentPage == 1 && circuitLevel >= 1) ? rcLedOn : ledState;
        DrawCircuit(currentPage, circuitLevel, circuitActive, ledToDraw,potValue);

            //DrawCircuit(currentPage,circuitLevel,circuitActive,ledState);
            basicBtn.Draw();
            midBtn.Draw();
            fullBtn.Draw();
            activate.Draw();

            basicBtn.CheckClick();
            midBtn.CheckClick();
            fullBtn.CheckClick();
            activate.CheckClick();
            if(currentPage == 0 && circuitLevel == 1) // Circuit 1 MID
            {
                ledBtn.Draw();
                ledBtn.CheckClick();
            }
        }

        for(auto &btn: buttons){
            btn.SetColor(GREEN);
            btn.SetColorHover(RED);
            btn.Draw();
            btn.CheckClick();
        }
        togglePanelBtn.CheckClick();
        if(showGPIOPanel){
            DrawGPIOPanel40(630, 120, 30, 20, pins);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
    
}
