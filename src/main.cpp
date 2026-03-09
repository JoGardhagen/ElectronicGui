#include <raylib.h>
#include "Button.h"
#include "Circuits.h"
#include <vector>
#include <string>

//void DrawCircuit1();

int main(){
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth,screenHeight,"El-Lära GUI");
    SetTargetFPS(60);

    std::vector<Button> buttons;
    int btnCount = 8;
    int spacing = 5;

    int totalSpacing = spacing * (btnCount + 1);
    int usableWidth = screenWidth - totalSpacing;
    int btnWidth = usableWidth / btnCount;
    int btnHeight = 40;
    int btnY = screenHeight - btnHeight - 10;

    //std::string topText = "Ingen kanpp vald";

    //int currentCircuit = 0;
    int currentPage = -1;

    for (int i = 0; i < btnCount; i++)
    {
        int x = spacing + i * (btnWidth + spacing);
        buttons.emplace_back(x, btnY, btnWidth, btnHeight, "K" + std::to_string(i + 1));
        buttons[i].SetOnClick([&currentPage, i]() {currentPage = i;});
    }

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);

        //DrawRectangle(0,0,screenWidth,screenHeight*2/3,LIGHTGRAY);
        
        DrawText("El-Lära GUI", 20, 20, 30, BLACK);

         if(currentPage == -1)
        {
            // Tom start-sida
            DrawText("Välj en krets längst ner", 200, 250, 25, GRAY);
        }else
        {
            switch(currentPage)
            {
                case 0: DrawCircuit1(); break;
                case 1: DrawCircuit2(); break;
                case 2: DrawCircuit3(); break;
                case 3: DrawCircuit4(); break;
                case 4: DrawCircuit5(); break;
                case 5: DrawCircuit6(); break;
                case 6: DrawCircuit7(); break;
                case 7: DrawCircuit8(); break;
            }
        }
        

        for(auto &btn: buttons){
            btn.SetColor(GREEN);
            btn.SetColorHover(RED);
            btn.Draw();
            btn.CheckClick();
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
    
}
