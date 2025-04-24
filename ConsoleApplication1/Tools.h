//this will include all tools that will be used independently of any other code
//Easing Curve equations took from https://easings.net/ since they are just math functions

#pragma once
#include<SFML/Graphics.hpp>
#include<cmath>
#include<algorithm>

using namespace std;
using namespace sf;

enum EaseType { CubicEaseInOut, ExpoEaseOut };

#pragma region Function Declaration
float CubicEase(float t);
float EaseOutExpo(float t);
float easeInOut(EaseType type, float startValue, float endValue, Clock EaseClock, Time Duration);
#pragma endregion

float easeInOut(EaseType type, float startValue, float endValue, Clock EaseClock, Time Duration) {
    // gets the ratio between the elapsed time and the duration of the animation
    float NormalizedTime = EaseClock.getElapsedTime().asSeconds() / Duration.asSeconds(); 
    NormalizedTime = max(0.0f, min(1.0f, NormalizedTime)); // Clamp the ratio between [0, 1]
    float easedTime;

    switch (type)
    {
    case CubicEaseInOut: {
        easedTime = CubicEase(NormalizedTime);
        break;
    }
    case ExpoEaseOut: {
        easedTime = EaseOutExpo(NormalizedTime);
        break;
    }
    default:
        break;
    }

    float currentValue = startValue + (endValue - startValue) * easedTime;
    return currentValue;
}

float CubicEase(float t) {
    return t < 0.5 ? 4 * t * t * t : 1 - pow(-2 * t + 2, 3) / 2;
}

float EaseOutExpo(float t) {
    return t == 1 ? 1 : 1 - pow(2, -10 * t);
}