#include <raylib.h>
#include "Button.h"
#include "Circuits.h"
#include "GPIOPanel.h"
#include <vector>
#include <string>

//void DrawCircuit1();

int main(){
    bool circuitActive = false;
    bool ledState = false;

    const int screenWidth = 800;
    const int screenHeight = 600;

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
    
    int currentPage = -1;
    int circuitLevel = 0;
    
    basicBtn.SetOnClick([&](){ circuitLevel = 0; circuitActive == false;});
    midBtn.SetOnClick([&](){ circuitLevel = 1; circuitActive == false;});
    fullBtn.SetOnClick([&](){ circuitLevel = 2; circuitActive == false;});
    
    
    for (int i = 0; i < btnCount; i++)
    {
        int x = spacing + i * (btnWidth + spacing);
        buttons.emplace_back(x, btnY, btnWidth, btnHeight, "K" + std::to_string(i + 1));
        buttons[i].SetOnClick([&currentPage,&circuitLevel,i]{
            currentPage = i;
            circuitLevel = 0;
        });
    }

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        DrawText("El-Lära GUI", 20, 20, 30, BLACK);
        togglePanelBtn.Draw();
        
        if(currentPage == -1)
        // Tom start-sida
        {   
            DrawText("Välj en krets längst ner", 200, 250, 25, GRAY);
             //basicBtn.Draw();
             //midBtn.Draw();
             //fullBtn.Draw();
        }else
        {   
            DrawText(TextFormat("Level: %i", circuitLevel),20,60,20,GRAY);
            //DrawText(circuitActive ? "Krets: AKTIV" : "Krets: AV", 300, 380, 20,
            //circuitActive ? GREEN : RED);

            DrawCircuit(currentPage,circuitLevel,circuitActive,ledState);
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
            //DrawGPIOPanel40(550, 120,20,);
            DrawGPIOPanel40(630, 120, 30, 20, pins);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
    
}
