#pragma once
#include <string>
#include <vector>

struct PinItem {
    std::string label;
    int pin;
};

// Endast GPIO som kan styras (fysiska pin-nummer)
/* static const std::vector<PinItem> controllablePins = {
    {"GPIO_2", 3}, {"GPIO_3", 5}, {"GPIO_4", 7}, {"GPIO_14", 8}, {"GPIO_15", 10},
    {"GPIO_17", 11}, {"GPIO_18", 12}, {"GPIO_27", 13}, {"GPIO_22", 15}, {"GPIO_23", 16},
    {"GPIO_24", 18}, {"GPIO_10", 19}, {"GPIO_9", 21}, {"GPIO_25", 22}, {"GPIO_11", 23},
    {"GPIO_8", 24}, {"GPIO_7", 26}, {"GPIO_5", 29}, {"GPIO_6", 31}, {"GPIO_12", 32},
    {"GPIO_13", 33}, {"GPIO_19", 35}, {"GPIO_16", 36}, {"GPIO_26", 37}, {"GPIO_20", 38},
    {"GPIO_21", 40}
}; */

static const std::vector<PinItem> controllablePins = {
    {"GPIO_2  ", 2},
    {"GPIO_3  ", 3},
    {"GPIO_4  ", 4},
    {"GPIO_14 ", 14},
    {"GPIO_15 ", 15},
    {"GPIO_17 ", 17},
    {"GPIO_18 ", 18},
    {"GPIO_27 ", 27},
    {"GPIO_22 ", 22},
    {"GPIO_23 ", 23},
    {"GPIO_24 ", 24},
    {"GPIO_10 ", 10},
    {"GPIO_9  ", 9},
    {"GPIO_25 ", 25},
    {"GPIO_11 ", 11},
    {"GPIO_8  ", 8},
    {"GPIO_7  ", 7},
    {"GPIO_5  ", 5},
    {"GPIO_6  ", 6},
    {"GPIO_12 ", 12},
    {"GPIO_13 ", 13},
    {"GPIO_19 ", 19},
    {"GPIO_16 ", 16},
    {"GPIO_26 ", 26},
    {"GPIO_20 ", 20},
    {"GPIO_21 ", 21}
};