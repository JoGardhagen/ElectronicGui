#ifndef BUTTON_H
#define BUTTON_H

#include <raylib.h>
#include <string>
#include <functional>

class Button{
private:
    Rectangle rect;
    Color colorNormal;
    Color colorHover;
    std::string text;
    Color textColor;
    std::function<void()> onClick;
    
public:
//Konstruktor
    Button(float x,float y,float width, float heigt,std::string t,Color normal = GRAY,Color hover = LIGHTGRAY,Color txtColor = BLACK)
     : rect{x,y,width,heigt}, text(t),colorNormal(normal),colorHover(hover),textColor(txtColor)
    {}
    
    void Draw(){
        Vector2 mousePos = GetMousePosition();
        bool mouseOver = CheckCollisionPointRec(mousePos,rect);
        DrawRectangleRec(rect,mouseOver ? colorHover : colorNormal);
        DrawText(text.c_str(),rect.x + 10, rect.y + rect.height/4,20,textColor);
    }
    void SetOnClick(std::function<void()>func) {
        onClick = func;
    }
    void CheckClick() { 
        Vector2 mousePos = GetMousePosition();
        if(CheckCollisionPointRec(mousePos,rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            if(onClick) onClick();          
        }
    }
    void SetColor(Color c){
        colorNormal = c;
    }
    void SetColorHover(Color c){
        colorHover = c;
    }

};
#endif