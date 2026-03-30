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

/* struct AppState
{
    bool circuitActive = false;
    bool ledState = false;

    int currentPage = -1;
    int circuitLevel = 0;

    float cap1Voltage = 0.0f;
    float cap2Voltage = 0.0f;
    bool charging = true;

    float potValue = 0.1f;

    const float RC1 = 10'000 * 10e-6; // 10k * 10uF = 0.1 s
    const float RC2 = 10'000 * 4.7e-6;  // R * C2
    //const float dt = 1.0f / 60;

    bool rcLedOn = false;
    bool ledFull[4] = {false,false,false,false};

    void HandlePotSlider(){
        if(currentPage !=2) return;

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

    void UpdateCircuit(float dt){
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

}; */

static float potValue = 0.1f; // startvärde för Circuit 3

int main(){
    IGPIO* gpio = CreateGPIO();
    AppState state;
    state.circuitActive = false;
    state.ledState = false;
    state.currentPage = -1;
    state.circuitLevel = 0;
    state.cap1Voltage = 0.0f;
    state.cap2Voltage = 0.0f;
    state.charging = true;
    state.potValue = 0.1f;

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
    //circuitActive = !circuitActive;
    state.circuitActive = !state.circuitActive;
        if(!state.circuitActive)
            //if(currentPage == 1) capacitorVoltage = 0.0f; // Circuit 2
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
    
    
    //int circuitLevel = 0;
    
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
        //buttons[i].SetOnClick([&state.currentPage,&state.circuitLevel,i]{
        buttons[i].SetOnClick([&state,i]{
            state.currentPage = i;
            state.circuitLevel = 0;
        });
    }

    //bool rcLedOn = false;   

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        togglePanelBtn.Draw();
        
        if(state.currentPage == -1)
        // Tom start-sida
        {   
            DrawText("Välj en krets längst ner", 200, 250, 25, GRAY);
        }else{   
            DrawText(TextFormat("Level: %i", state.circuitLevel),20,60,20,GRAY);

            if(state.currentPage == 1) state.UpdateCircuit(dt); 

            if(state.currentPage == 2) state.HandlePotSlider();
            
        // rita kretsen med korrekt LED-status
        bool ledToDraw = (state.currentPage == 1 && state.circuitLevel >= 1) ? state.rcLedOn : state.ledState;
        DrawCircuit(state.currentPage, state.circuitLevel, state.circuitActive, ledToDraw,state.potValue,gpio,state);

            basicBtn.Draw();
            midBtn.Draw();
            fullBtn.Draw();
            activate.Draw();

            basicBtn.CheckClick();
            midBtn.CheckClick();
            fullBtn.CheckClick();
            activate.CheckClick();
            if(state.currentPage == 0 && state.circuitLevel == 1) // Circuit 1 MID
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
            DrawGPIOPanel40(680, 120, 30, 20, pins);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
    
}
