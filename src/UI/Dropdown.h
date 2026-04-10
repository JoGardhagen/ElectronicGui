#pragma once
#include <vector>
#include <string>
#include "raylib.h"

class Dropdown {
public:
    std::vector<std::string> items;
    //int selectedIndex = -1;
    Rectangle box;
    bool open = false;

    // --- scroll / synliga items ---
    int maxVisible = 6;    // max antal synliga items i dropdown
    int scrollOffset = 0;  // vilken index som visas först
    int selectedIndex = -1;


    Dropdown(float x, float y, float width, float height, const std::vector<std::string>& _items);

    void DrawButtonOnly();  // rita bara knappen
    void DrawListOnly();    // rita endast listan ovanpå allt annat
    void CheckClick();
    //void CheckClick();

    int GetSelectedIndex();
    std::string GetSelectedItem();
};