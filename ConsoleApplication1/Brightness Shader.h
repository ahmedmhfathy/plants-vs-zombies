#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;
using namespace std;

Shader myBrightnessShader;

struct FlashState {
    bool isFlashing = false;         // True if the object is currently flashing.
    Clock flashClock;            // Timer to track how long the flash has been active.
    Time flashDuration = milliseconds(100); // How long the flash effect should last.
    float normalBrightness = 1.0f;   // The brightness level when not flashing.
    float flashBrightness = 2.5f;    // The brightness level when flashing (e.g., 2.0 for double brightness).
    float currentBrightness = normalBrightness;
};
