//this will include all tools that will be used independently of any other code
// Easing Functions
// clock start stop functionality (to do)


#pragma once
#include<SFML/Graphics.hpp>
#include<cmath>
#include<algorithm>

using namespace std;
using namespace sf;

#pragma region Function Declaration
float smoothstep(float t);
float easeInOut(float startValue, float endValue, Clock EaseClock, Time Duration);
#pragma endregion

float easeInOut(float startValue, float endValue, Clock EaseClock, Time Duration) {
    float NormalizedTime = EaseClock.getElapsedTime().asSeconds() / Duration.asSeconds(); // gets the ratio between
    //the elapsed time and the duration
    NormalizedTime = max(0.0f, min(1.0f, NormalizedTime)); // Clamp to [0, 1]

    float easedTime = smoothstep(NormalizedTime);
    float currentValue = startValue + (endValue - startValue) * easedTime;
    return currentValue;
}

float smoothstep(float t) {
    // t is the normalized time from 0 to 1

    //Easing data took from https://easings.net/
    //since they are just math functions

    //cubic ease in-out 1
    return t < 0.5 ? 4 * t * t * t : 1 - pow(-2 * t + 2, 3) / 2;

    //cubic ease in-out 2
    //return t * t * (3.0 - 2.0 * t);

    //ease In-Out Quint
    //return t < 0.5 ? 16 * t * t * t * t * t : 1 - (pow(-2 * t + 2, 5) / 2);

    //ease In-Out Expo
    //return t == 0 ? 0 : t == 1 ? 1 : t < 0.5 ? pow(2, 20 * t - 10) / 2 : (2 - pow(2, -20 * t + 10)) / 2;
}
