#pragma once

struct AppState
{
    bool circuitActive = false;
    bool ledState = false;

    int currentPage = -1;
    int circuitLevel = 0;

    float cap1Voltage = 0.0f;
    float cap2Voltage = 0.0f;
    bool charging = true;

    float potValue = 0.1f;

    const float RC1 = 10'000 * 10e-6;
    const float RC2 = 10'000 * 4.7e-6;

    bool rcLedOn = false;

    void UpdateCircuit(float dt);
    void HandlePotSlider();
};