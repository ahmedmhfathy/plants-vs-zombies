#pragma once
#include"Tools.h"
#include<algorithm>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <SFML/Audio.hpp>
#include <sstream>
#include<time.h>
#include"StartAnimation.h"

#pragma region (Texture,sprite)_declaration
Texture lawntexture;
Texture rectangletexture;
Texture Textstartwave2texture;
Sprite Textstartwave2sprite;
Texture Textstartfinalwavetexture;
Sprite Textstartfinalwavesprite;
Texture Textlosegametexture;
Sprite Textlosegamesprite;
#pragma endregion

#pragma region boolean
// =====================***boolean waves**=================================
bool nowave = true;
bool checkstart_wave2 = true;
bool checkstart_wave3 = true;
bool endRSP = false;
#pragma endregion

#pragma region hours and timer
//================================================================================
Time deltatime; // use in move cars
Clock clockmovecars;
// Hours use in 3 waves 
Time timertostartwave2;
Time timertostartwave3;
Clock clockwave2;
Clock clockfinalwave;
Clock globalClock;
Clock frameClock;
float deltaTime;
float timeSinceStart;
// Hours  for 3 texts (start wave2, start final wave, lose game)..............
Clock clockdrawtextwave2;              // clock for draw text start wave two.....
Clock clockdrawtextfinalwave;           // clock for draw final wave...
Clock clocklosegame;                      //clock for lose game.....
// deltatime for animation 3 texts(start wave2, start final wave, lose game)......
Time deltatimetextstartwave2, deltatimetextfinalwave, deltatimelosegame;
#pragma endregion

#pragma region Scale 
float minscale = 1.7f;               // Min Scale For Text Start Wave Two And Text Final Wave
float scaleFactor = 6.0f;           // First scale For  Text Start Wave Two And Text Final Wave
float minscaletextlosegame = 1.17f;          // Min Scale For Text Lose Game
float scalefactortextlosegame = 4.2f;       // First scale For Lose Game
#pragma endregion
//intersection
FloatRect rect1;
FloatRect rect2;
// speed zombies
const float speedzombie = 40.0f;

#pragma region Functiondelaration
void allwave(int);
void intersectioncarsandzombies(int, RenderWindow&);
void drawzombies(RenderWindow&, string);
void startallwave(int, int, float);
#pragma endregion

struct cars
{
    bool intersection = false;
    float speed = 150;
    Sprite lawnsprite;
    void start(int i)
    {
        lawntexture.loadFromFile("Assets/Environment/lawnmower.png");
        lawnsprite.setTexture(lawntexture);
        lawnsprite.setScale(0.8, 0.8);
        lawnsprite.setPosition(220, 173 + (i * 120));
        intersection = false;
    }
    void update(float dt) 
    {
        if (lawnsprite.getPosition().x < 230)
        {
            lawnsprite.move(speed * dt, 0);
        }
    }
}car[5];

struct zombies {
    int row[5] = { 150, 280, 400,520,640 };
    Sprite rectanglesprite;
    bool started;
    bool stoped;
    void start(int x) {
        rectangletexture.loadFromFile("Assets/Environment/rectangle.png");
        rectanglesprite.setTexture(rectangletexture);
        rectanglesprite.setScale(0.2, 0.1);
        rectanglesprite.setPosition(1300, row[rand() % 5]);
    }
    void update(float dt) {
        rectanglesprite.move(-speedzombie * dt, 0);
    }
}zombie[300];

struct waves {
    float delaybetween;
    int numberzombie;
    bool checkexit_wave=false;
}wave[3];

void drawzombies(RenderWindow& window) {
    if (nowave) {
        for (int i = 0; i < wave[0].numberzombie; i++) {
            if (zombie[i].rectanglesprite.getPosition().x > 260 ) {
                if (zombie[i].started) {
                    zombie[i].update(deltaTime);
                    window.draw(zombie[i].rectanglesprite);
                }
            }
        }    
    }
    else if (wave[0].checkexit_wave&&!nowave) {    
        for (int i = 0; i < wave[1].numberzombie; i++) {
            if (zombie[i].rectanglesprite.getPosition().x > 260) {
                if (zombie[i].started) {
                    zombie[i].update(deltaTime);
                    window.draw(zombie[i].rectanglesprite);
                }
            }
        }
    }
    else if (wave[1].checkexit_wave) {
        for (int i = 0; i < wave[2].numberzombie; i++) {
            if (zombie[i].rectanglesprite.getPosition().x > 260) {
                if (zombie[i].started) {
                    zombie[i].update(deltaTime);
                    window.draw(zombie[i].rectanglesprite);
                }
            }
        }
    }  
    for (int i = 0; i < 3; i++) {
        intersectioncarsandzombies(i, window);
    }
    if (timertostartwave2 > seconds(2) && timertostartwave2 < seconds(6) && wave[0].checkexit_wave)
    {
        if (scaleFactor > minscale) {
            scaleFactor -= deltatimetextstartwave2.asSeconds() * 14.0f; // ??????? ????????
        }
        Textstartwave2sprite.setScale(scaleFactor, scaleFactor);
        window.draw(Textstartwave2sprite);
    }
    if (timertostartwave3 > seconds(2) && timertostartwave3 < seconds(6) && wave[1].checkexit_wave) {
        if (scaleFactor > minscale) {
            scaleFactor -= deltatimetextfinalwave.asSeconds() * 14.0f; // ??????? ????????
        }
        Textstartfinalwavesprite.setScale(scaleFactor, scaleFactor);
        window.draw(Textstartfinalwavesprite);
    }
     for (int i = 0; i < 150; i++) {
            if (zombie[i].rectanglesprite.getPosition().x < 265 && zombie[i].started) {
                if (scalefactortextlosegame > minscaletextlosegame) {
                    scalefactortextlosegame -= deltatimelosegame.asSeconds() * 0.5f; // ??????? ????????
                }
                Textlosegamesprite.setScale(scalefactortextlosegame, scalefactortextlosegame);
                window.draw(Textlosegamesprite);
                wave[0].checkexit_wave = false;
                wave[1].checkexit_wave = false;
            }
     }
}

void intersectioncarsandzombies(int numberwave, RenderWindow& window) {
     deltatime = clockmovecars.restart();
    float dt = deltatime.asSeconds();
    for (int i = 0; i < wave[numberwave].numberzombie; i++) {
        for (int x = 0; x < 5; x++) {
            rect1 = car[x].lawnsprite.getGlobalBounds();
            rect2 = zombie[i].rectanglesprite.getGlobalBounds();
            if (rect1.intersects(rect2)) {
                car[x].intersection = true;
                car[x].lawnsprite.move(800 * dt, 0);
                window.draw(car[x].lawnsprite);
            }
            if (car[x].intersection) {
                if (car[x].lawnsprite.getPosition().x < 3000) {
                    car[x].lawnsprite.move(800 * dt, 0);
                    window.draw(car[x].lawnsprite);

                }
            }
        }
    }
}

void startallwave(int numberwave, int numberzombie, float delaybetween) {
    srand(time(0));
    float deltaTime;
    globalClock.restart();
    deltaTime = frameClock.restart().asSeconds();
    timeSinceStart = globalClock.getElapsedTime().asSeconds();
    for (int i = 0; i < 300; i++) {
        zombie[i].started = false;
    }
    for (int i = 0; i < 300; i++) {
        zombie[i].stoped = false;
    }
    wave[numberwave].delaybetween = delaybetween;
    wave[numberwave].numberzombie = numberzombie;
    for (int i = 0;i < wave[numberwave].numberzombie; i++) {
        zombie[i].start(i);
    }

}
void allwave(int numberwave) {
    for (int i = 0; i < wave[numberwave].numberzombie; ++i) {
        if (timeSinceStart >= i * wave[numberwave].delaybetween) {
            zombie[i].started = true;
        }
    }
    for (int i = 0; i < wave[numberwave].numberzombie; ++i) {
        if (zombie[i].rectanglesprite.getPosition().x < 260) {
            zombie[i].stoped = true;
        }
    }
    for (int i = 0; i < wave[numberwave].numberzombie; ++i) {
        if (zombie[i].stoped != true) {
            wave[numberwave].checkexit_wave = false;
            break;
        }
        else {
            wave[numberwave].checkexit_wave = true;

        }
    }
}