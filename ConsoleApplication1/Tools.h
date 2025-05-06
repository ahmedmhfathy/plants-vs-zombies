//this will include all tools that will be used independently of any other code
//Easing Functions
//Easing data took from https://easings.net/
//since they are just math functions

#pragma once
#include<SFML/Graphics.hpp>
#include<cmath>
#include<algorithm>

using namespace std;
using namespace sf;

enum EaseType { CubicEaseInOut, ExpoEaseOut, linear };

#pragma region Function Declaration
float CubicEase(float t);
float EaseOutExpo(float t);
float linearEase(float t);
float easeInOut(EaseType type, float startValue, float endValue, Clock EaseClock, Time Duration);
#pragma endregion

float easeInOut(EaseType type, float startValue, float endValue, Clock EaseClock, Time Duration) {
    float NormalizedTime = EaseClock.getElapsedTime().asSeconds() / Duration.asSeconds(); // gets the ratio between
    //the elapsed time and the duration
    NormalizedTime = max(0.0f, min(1.0f, NormalizedTime)); // Clamp to [0, 1]
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
    case linear: {
        easedTime = linearEase(NormalizedTime);
    }
    default:
        break;
    }

    float currentValue = startValue + (endValue - startValue) * easedTime;
    return currentValue;
}

float CubicEase(float t) {
    // t is the normalized time from 0 to 1
    return t < 0.5 ? 4 * t * t * t : 1 - pow(-2 * t + 2, 3) / 2;
}

float EaseOutExpo(float t) {
    // t is the normalized time from 0 to 1
    return t == 1 ? 1 : 1 - pow(2, -10 * t);
}

float linearEase(float t) {
    return t;
}