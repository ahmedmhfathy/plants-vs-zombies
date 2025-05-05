#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<algorithm>
#include <iostream>
#include <vector>
#include <string>
#include<time.h>
#include"Tools.h"
#include"StartAnimation.h"
#include"Plants_Zombies.h"

#pragma region Textures and Sprites declaration
Texture lawntexture;
Texture rectangletexture;
Texture Textstartwave2texture;
Sprite Textstartwave2sprite;
Texture Textstartfinalwavetexture;
Sprite Textstartfinalwavesprite;
Texture Textlosegametexture;
Sprite Textlosegamesprite;
#pragma endregion

#pragma region booleans
// =====================***boolean waves**=================================
bool nowave = true;
bool checkstart_wave2 = true;
bool checkstart_wave3 = true;
bool endRSP = false;
bool movefromwavetoanother = true;
#pragma endregion

#pragma region hours and timer
Clock DeltaTimeClock;
// Hours use in 3 waves 
Time timertostartwave2;
Time timertostartwave3;
Clock clockwave2;
Clock clockfinalwave;
Clock globalClock;
Clock frameClock;

float timeSinceStart;
// Hours  for 3 texts (start wave2, start final wave, lose game)..............
Clock clockdrawtextwave2;              // clock for draw text start wave two.....
Clock clockdrawtextfinalwave;          // clock for draw final wave...
Clock clocklosegame;                   //clock for lose game.....
// deltatime for animation 3 texts(start wave2, start final wave, lose game)......
Time deltatimetextstartwave2, deltatimetextfinalwave, deltatimelosegame;
#pragma endregion

#pragma region Scale 
float minscale = 1.7f;                      // Min Scale For Text Start Wave Two And Text Final Wave
float scaleFactor = 6.0f;                   // First scale For  Text Start Wave Two And Text Final Wave
float minscaletextlosegame = 1.17f;         // Min Scale For Text Lose Game
float scalefactortextlosegame = 4.2f;       // First scale For Lose Game
#pragma endregion

// speed zombies
const float speedzombie = 40.0f;
float deltaTime;

#pragma region Functiondelaration
void allwave(int, int, bool);
void intersectioncarsandzombies(int);
void drawzombies(RenderWindow&, string);
void startallwave(int, int, float);
void level(int, int, float, bool);
#pragma endregion

#pragma region Structs
struct cars {
    bool intersection = false;
    float speed = 150;
    Sprite lawnsprite;
    void start(int i) {
        lawntexture.loadFromFile("Assets/Environment/lawnmower.png");
        lawnsprite.setTexture(lawntexture);
        lawnsprite.setScale(0.8, 0.8);
        lawnsprite.setPosition(-90, 60 + (i * 130));
       
    }
    void update(float dt) {
        if (lawnsprite.getPosition().x < -65) {
            lawnsprite.move(speed * dt, 0);
        }
    }
}car[5];

struct waves {
    float delaybetween;
    int numberzombie ;
    bool checkexit_wave=false;
    bool check_startwave = true;
}wave[3];
#pragma endregion


void start( int i) {
    Plants_Zombies::StartZombies(i);
    int row[5] = { -40, 100, 235, 360,490 };

    for (int i = 0; i < 100; i++) 
    {    
        Plants_Zombies::zombie_array[i].started = false;
        Plants_Zombies::zombie_array[i].isDead = false;

        Plants_Zombies::zombie_array[i].zombieCont.setPosition(1000, row[rand() % 5]);

        if (Plants_Zombies::zombie_array[i].type == Plants_Zombies::trafficCone|| Plants_Zombies::zombie_array[i].type == Plants_Zombies::newsMan) {
            Plants_Zombies::zombie_array[i].zombieCont.setPosition(1000, row[rand() % 5] - 25);
        }
    }
}

void intersectioncarsandzombies(int numberwave) {

    for (int i = 0; i < wave[numberwave].numberzombie; i++) {
        for (int x = 0; x < 5; x++) {
            FloatRect rect1 = car[x].lawnsprite.getGlobalBounds();
            FloatRect rect2 = Plants_Zombies::zombie_array[i].zombieCollider.getGlobalBounds();

            if (rect1.intersects(rect2)) {
                car[x].intersection = true;
                Plants_Zombies::zombie_array[i].isMoving = false;
            }

            if (car[x].intersection) {
                if (car[x].lawnsprite.getPosition().x < 960) {
                    car[x].lawnsprite.move(1000000 * deltaTime, 0);
                }
                else {
                    car[x].lawnsprite.setPosition(1000, 1000);
                }
            }
        }
    }
}

void startallwave(int numberwave, int numberzombie, float delaybetween) {   
    //for (int i = 0; i < numberzombie; i++)
    //{
    //    Plants_Zombies::zombie_array[i].zombieCont.setPosition(2000, 2000);
    //    Plants_Zombies::zombie_array[i].zombieCollider.setPosition(2000, 2000);
    //}

    wave[numberwave].delaybetween = delaybetween;
    wave[numberwave].numberzombie = numberzombie;
    Plants_Zombies:: numberofdeadzombie = 0;

    srand(time(0));
    globalClock.restart();

    deltaTime = DeltaTimeClock.restart().asSeconds();

    timeSinceStart = globalClock.getElapsedTime().asSeconds();

    //for (int i = 0; i < 100; i++) {
    //   Plants_Zombies::zombie_array[i].stoped = false;
    //}

    start(numberzombie);
}

void allwave(int numberwave, int numberzombie, bool isPaused) {
    if (isPaused)
    {
        deltaTime = 0;
    }
    else
    {
        deltaTime = frameClock.restart().asSeconds();
    }

    for (int i = 0; i < 3; i++) {
        intersectioncarsandzombies(i);
    }

    for (int i = 0; i < wave[numberwave].numberzombie; ++i) {
        if (timeSinceStart >= i * wave[numberwave].delaybetween) {
           
           Plants_Zombies:: zombie_array[i].started = true;
        }
    }
    for (int i = 0; i < wave[numberwave].numberzombie; i++) {
        if (Plants_Zombies::zombie_array[i].started && Plants_Zombies::zombie_array[i].type != Plants_Zombies::Dead) {

            if (!isPaused)
            {
                Plants_Zombies::zombie_array[i].update(deltaTime);
            }
        }
    }       
    if (Plants_Zombies::numberofdeadzombie == numberzombie){
        wave[numberwave].checkexit_wave = true;
    }
    else {
        wave[numberwave].checkexit_wave = false;

    }
} 

void level(int numberwave, int num, float delaybetweenw1, bool isPaused) {
    //cout << "level wave omar";;
    if (endRSP)
    {
        if (numberwave == 2) {
            if (wave[0].check_startwave) {
                wave[0].check_startwave = false;
                startallwave(0, num, delaybetweenw1);
            }
            if (nowave && endRSP) { allwave(0, num, isPaused); }
            if (wave[0].checkexit_wave) {
                if (movefromwavetoanother) {
                    clockwave2.restart();
                    movefromwavetoanother = false;
                    nowave = false;

                    
                }
                timertostartwave2 = clockwave2.getElapsedTime();
                if (timertostartwave2 > seconds(6)) {
                    if (wave[1].check_startwave) {
                        startallwave(1, num += 4, delaybetweenw1 -= 2.0f);
                        wave[1].check_startwave = false;
                        scaleFactor = 6.0f;
                    }
                    allwave(1, num += 30, isPaused);
                }
            }
        }
        else if (numberwave == 3) {
            if (wave[0].check_startwave) {
                wave[0].check_startwave = false;
                startallwave(0, num, delaybetweenw1);
            }
            if (nowave && endRSP) { allwave(0, num, isPaused); }
            if (wave[0].checkexit_wave) {
                if (movefromwavetoanother) {
                    clockwave2.restart();
                    movefromwavetoanother = false;
                    nowave = false;
                }
                timertostartwave2 = clockwave2.getElapsedTime();
                if (timertostartwave2 > seconds(6)) {
                    if (wave[1].check_startwave) {
                        startallwave(1, num+=1, delaybetweenw1-=2.0f);
                        wave[1].check_startwave = false;
                        scaleFactor = 6.0f;
                    }
                    allwave(1, num, isPaused);
                }
            }
            if (wave[1].checkexit_wave) {
                if (!movefromwavetoanother) {
                    clockfinalwave.restart();
                    movefromwavetoanother = true;
                    wave[0].checkexit_wave = false;
                }
                timertostartwave3 = clockfinalwave.getElapsedTime();
                if (timertostartwave3 > seconds(6)) {
                    if (wave[2].check_startwave) {
                        startallwave(2, num += 1, delaybetweenw1 -= 2.0f);
                        wave[2].check_startwave = false;
                    }
                    allwave(2, num, isPaused);
                }
            }
        }
    }
}

void drawzombies(RenderWindow& window) {
    if (nowave) {

        for (int i = 0; i < wave[0].numberzombie; i++) {
            if (Plants_Zombies::zombie_array[i].type != Plants_Zombies::Dead)
            {
                window.draw(Plants_Zombies::zombie_array[i].zombieCollider);
                window.draw(Plants_Zombies::zombie_array[i].zombieCont);
            }
        }
    }
    else if (wave[0].checkexit_wave && !nowave) {
        for (int i = 0; i < wave[1].numberzombie; i++) {
            if (Plants_Zombies::zombie_array[i].type != Plants_Zombies::Dead)
            {
                window.draw(Plants_Zombies::zombie_array[i].zombieCollider);
                window.draw(Plants_Zombies::zombie_array[i].zombieCont);
            }

        }
    }
    else if (wave[1].checkexit_wave) {
        for (int i = 0; i < wave[2].numberzombie; i++) {
            if (Plants_Zombies::zombie_array[i].type != Plants_Zombies::Dead)
            {
                window.draw(Plants_Zombies::zombie_array[i].zombieCollider);
                window.draw(Plants_Zombies::zombie_array[i].zombieCont);
            }
        }
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

    //for (int i = 0; i < 100; i++) {
    //    if (Plants_Zombies::zombie_array[i].zombieCollider.getPosition().x < -50 && Plants_Zombies::zombie_array[i].started) {
    //        if (scalefactortextlosegame > minscaletextlosegame) {
    //            scalefactortextlosegame -= deltatimelosegame.asSeconds() * 1.5f; // ??????? ????????
    //        }
    //        Textlosegamesprite.setScale(scalefactortextlosegame, scalefactortextlosegame);
    //        window.draw(Textlosegamesprite);
    //        wave[0].checkexit_wave = false;
    //        wave[1].checkexit_wave = false;
    //    }
    //}
}