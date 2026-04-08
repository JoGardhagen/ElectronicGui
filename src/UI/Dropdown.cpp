#include "Dropdown.h"
#include <algorithm>

Dropdown::Dropdown(float x, float y, float width, float height, const std::vector<std::string>& _items)
    : items(_items)
{
    box = { x, y, width, height };
    maxVisible = 6;
    scrollOffset = 0;
    selectedIndex = -1;
}

// Rita bara huvudknappen (utan listan)
void Dropdown::DrawButtonOnly() {
    DrawRectangleRec(box, GRAY);
     if(selectedIndex >= 0 && selectedIndex < items.size()) {
        DrawText(items[selectedIndex].c_str(), box.x + 5, box.y + 5, 20, BLACK);
    } else {
        DrawText("Select", box.x + 5, box.y + 5, 20, DARKGRAY); // placeholder
    }
}

// Rita endast listan ovanpå allt annat
void Dropdown::DrawListOnly() {
    if(!open) return;

    int start = scrollOffset;
    int end = std::min(scrollOffset + maxVisible, (int)items.size());

    for(int i = start; i < end; i++) {
        Rectangle r = { box.x, box.y + box.height * (i - scrollOffset + 1), box.width, box.height };
        DrawRectangleRec(r, LIGHTGRAY);
        DrawText(items[i].c_str(), r.x + 5, r.y + 5, 20, BLACK);
    }
}

void Dropdown::CheckClick() {
    Vector2 mouse = GetMousePosition();

    // klick på huvudbox
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if(CheckCollisionPointRec(mouse, box)) {
            open = !open;
        } else if(open) {
            int start = scrollOffset;
            int end = std::min(scrollOffset + maxVisible, (int)items.size());
            for(int i = start; i < end; i++) {
                Rectangle r = { box.x, box.y + box.height * (i - scrollOffset + 1), box.width, box.height };
                if(CheckCollisionPointRec(mouse, r)) {
                    selectedIndex = i;
                    open = false;
                }
            }
        }
    }

    // scrolla med mus-hjul
    if(open) {
        float wheel = GetMouseWheelMove();
        if(wheel != 0) {
            scrollOffset -= (int)wheel;
            if(scrollOffset < 0) scrollOffset = 0;
            if(scrollOffset > (int)items.size() - maxVisible)
                scrollOffset = std::max(0, (int)items.size() - maxVisible);
        }
    }
}

int Dropdown::GetSelectedIndex() { return selectedIndex; }
std::string Dropdown::GetSelectedItem() { return items[selectedIndex]; }