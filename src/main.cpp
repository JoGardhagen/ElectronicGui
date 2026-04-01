#include <raylib.h>
#include "Button.h"
#include "Circuits/Circuits.h"
#include "Panels/GPIOPanel.h"
#include "Components/GPIO/IGPIO.h"
#include "AppState.h"

//#if defined(__linux__)
//    #include "Components/GPIO/RaspberryGPIO.h"
//#else
//    #include "Components/GPIO/DummyGPIO.h"
//#endif
#if defined(__linux__) && (defined(__arm__) || defined(__aarch64__))
    #include "Components/GPIO/RaspberryGPIO.h"
#else
    #include "Components/GPIO/DummyGPIO.h"
#endif

#include <vector>
#include <string>

IGPIO* CreateGPIO()
{
    #if defined(__linux__) && (defined(__arm__) || defined(__aarch64__))
        return new RaspberryGPIO();
    #else
        return new DummyGPIO();
    #endif
}

void Update(AppState& state,float dt){
    switch (state.currentPage)
    {
        case 1: state.UpdateCircuit(dt);break;
        case 2: state.HandlePotSlider();break;
    }
}
void DrawUI(AppState& state,Button& basicBtn,Button& midbtn,Button& fullbtn,Button& activate,Button& ledBtn){
    DrawText(TextFormat("Level: %i",state.circuitLevel),20,60,20,GRAY);
    basicBtn.Draw();
    midbtn.Draw();
    fullbtn.Draw();
    activate.Draw();

    basicBtn.CheckClick();
    midbtn.CheckClick();
    fullbtn.CheckClick();
    activate.CheckClick();

    if(state.currentPage == 0 && state.circuitLevel == 1){
        ledBtn.Draw();
        ledBtn.CheckClick();
    }
}

int main(){
    IGPIO* gpio = CreateGPIO();
    AppState state;
    state.currentPage = -1;
    //state.circuitLevel = 0;
    //state.cap1Voltage = 0.0f;
    //state.cap2Voltage = 0.0f;
    //state.charging = true;
    //state.potValue = 0.1f;

    float dt = 1.0f / 60;

    const int screenWidth = 850;
    const int screenHeight = 650;

    InitWindow(screenWidth,screenHeight,"El-Lära GUI");
    SetTargetFPS(60);

    std::vector<Button> buttons;
    int btnCount = 6;
    int spacing = 5;

    Button basicBtn(220,500,100,40,"Basic");
    Button midBtn(360,500,100,40,"Mid");
    Button fullBtn(500,500,100,40,"Full");
    Button activate(600,50,200,40,"Activate Circiut");
    activate.SetOnClick([&](){
    state.circuitActive = !state.circuitActive;
        if(!state.circuitActive)
            state.ledState = false;
    });

    activate.SetColor(YELLOW);
    activate.SetColorHover(ORANGE);

    Button ledBtn(350,400,130,40,"Toggle LED");

    ledBtn.SetOnClick([&](){
        if(!state.circuitActive)
            state.ledState = !state.ledState;
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
    
    basicBtn.SetOnClick([&](){ 
        state.circuitLevel = 0;
        state.circuitActive = false;
    });

    midBtn.SetOnClick([&](){
        state.circuitLevel = 1;
        state.circuitActive = false;
        state.cap1Voltage = 0;
        state.cap2Voltage = 0;
        state.charging = true;
    });
    fullBtn.SetOnClick([&](){ 
        state.circuitLevel = 2;
        state.circuitActive = false;
        state.cap1Voltage = 0;
        state.cap2Voltage = 0;
        state.charging = true;
    });
    
    
    for (int i = 0; i < btnCount; i++)
    {
        int x = spacing + i * (btnWidth + spacing);
        buttons.emplace_back(x, btnY, btnWidth, btnHeight, "K" + std::to_string(i + 1));

            buttons[i].SetColor(GREEN);
            buttons[i].SetColorHover(RED);

        buttons[i].SetOnClick([&state,i]{
            state.currentPage = i;
            state.circuitLevel = 0;
        });
    }
   
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        togglePanelBtn.Draw();
        
        if(state.currentPage == -1)
        // Tom start-sida
        {   
            DrawText("Välj en krets längst ner", 200, 250, 25, GRAY);
        }else{   
            Update(state,dt);
        
            bool ledToDraw = (state.currentPage == 1 && state.circuitLevel >= 1) ? state.rcLedOn : state.ledState;
            DrawCircuit(state.currentPage, state.circuitLevel, state.circuitActive, ledToDraw,state.potValue,gpio,state);
            DrawUI(state,basicBtn,midBtn,fullBtn,activate,ledBtn);

        }

        for(auto &btn: buttons){
            btn.Draw();
            btn.CheckClick();
        }
        togglePanelBtn.CheckClick();
        if(showGPIOPanel){
            DrawGPIOPanel40(680, 120, 30, 20, pins);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
    
}
