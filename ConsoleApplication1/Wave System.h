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
//================================================================================
Clock clockmovecars; // use in move cars
Time deltatime;
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
void allwave(int, int);
void intersectioncarsandzombies(int, RenderWindow&);
void drawzombies(RenderWindow&, string);
void startallwave(int, int, float);
void level(int, int, float);
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


void start( bool finanim) {
    Plants_Zombies::StartZombies();
    int row[5] = { 20, 100, 225, 315,435 };
    for (int i = 0; i < 4; i++) {
        if (finanim) {
            Plants_Zombies::zombie_array[i].zombieCont.setPosition(1000,row[rand()%5]);
        }
        else {
            Plants_Zombies::zombie_array[i].zombieCont.setPosition(1100 + rand() % 100, (-30 + (70 * rand() % 600)));
        }
   }
}



struct waves {
    float delaybetween;
    int numberzombie;
    bool checkexit_wave=false;
    bool check_startwave = true;
}wave[3];
#pragma endregion



void drawzombies(RenderWindow& window) {
    //cout << "draw wave omar";;
    if (nowave) {
        
        for (int i = 0; i < 4; i++) {
            window.draw(Plants_Zombies::zombie_array[i].zombieCollider);
            window.draw(Plants_Zombies::zombie_array[i].zombieCont);
        }
    }
   /* else if (wave[0].checkexit_wave && !nowave) {
        for (int i = 0; i < wave[1].numberzombie; i++) {
            window.draw(zombie[i].rectanglesprite);
        }
    }
    else if (wave[1].checkexit_wave) {
        for (int i = 0; i < wave[2].numberzombie; i++) {
            window.draw(zombie[i].rectanglesprite);
        }
    }*/
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
   /*for (int i = 0; i < 150; i++) {
        if (zombie[i].rectanglesprite.getPosition().x < -50 && zombie[i].started) {
            if (scalefactortextlosegame > minscaletextlosegame) {
                scalefactortextlosegame -= deltatimelosegame.asSeconds() * 1.5f; // ??????? ????????
            }
            Textlosegamesprite.setScale(scalefactortextlosegame, scalefactortextlosegame);
            window.draw(Textlosegamesprite);
            wave[0].checkexit_wave = false;
            wave[1].checkexit_wave = false;
        }
    } */
}



void intersectioncarsandzombies(int numberwave, RenderWindow& window) {
  /*  Time deltatime = clockmovecars.restart();
    float dt = deltatime.asSeconds();
    for (int i = 0; i < wave[numberwave].numberzombie; i++) {
        for (int x = 0; x < 5; x++) {
            rect1 = car[x].lawnsprite.getGlobalBounds();
            rect2 = zombie[i].rectanglesprite.getGlobalBounds();
            if (rect1.intersects(rect2)) {
                car[x].intersection = true;
            }
            if (car[x].intersection) {
                if (car[x].lawnsprite.getPosition().x < 960) {
                    car[x].lawnsprite.move(5000 * dt, 0);
                }
                else {
                    car[x].lawnsprite.setPosition(0, 1000);
                }
            }
        }
    }*/
}



void startallwave(int numberwave, int numberzombie, float delaybetween) {
    //cout << "start all wave omar";;
    srand(time(0));
    float deltaTime;
    globalClock.restart();
    deltaTime = frameClock.restart().asSeconds();
    timeSinceStart = globalClock.getElapsedTime().asSeconds();
    wave[numberwave].delaybetween = delaybetween;
    wave[numberwave].numberzombie = numberzombie;
    Plants_Zombies::LoadZombieTextures();
       start( true);
}



void allwave(int numberwave, int numberzombie) {
    //cout << " all wave omar";
  Plants_Zombies::UpdateZombies(deltaTime);
  /*  for (int i = 0; i < wave[numberwave].numberzombie; i++) {
        if (zombie[i].rectanglesprite.getPosition().x > -60) {
            if (zombie[i].started) {
               Plants_Zombies::UpdateZombies(deltaTime);
            }
        }
    }*/
       
    if (Plants_Zombies::numberofdeadzombie == numberzombie){
        wave[numberwave].checkexit_wave = true;
    }
    else {
        wave[numberwave].checkexit_wave = false;

    }
} 


void level(int numberwave, int numberzombiew1, float delaybetweenw1) {
    //cout << "level wave omar";;
    if (endRSP)
    {
        if (numberwave == 2) {
            if (wave[0].check_startwave) {
                wave[0].check_startwave = false;
                startallwave(0, numberzombiew1, delaybetweenw1);
            }
            if (nowave && endRSP) { allwave(0, numberzombiew1); }
            if (wave[0].checkexit_wave) {
                if (movefromwavetoanother) {
                    clockwave2.restart();
                    movefromwavetoanother = false;
                    nowave = false;
                }
                timertostartwave2 = clockwave2.getElapsedTime();
                if (timertostartwave2 > seconds(6)) {
                    if (wave[1].check_startwave) {
                        startallwave(1, numberzombiew1+=30, delaybetweenw1-=2.0f);
                        wave[1].check_startwave = false;
                        scaleFactor = 6.0f;
                    }
                    allwave(1, numberzombiew1 += 30);
                }
            }
        }
        if (numberwave == 3) {
            if (wave[0].check_startwave) {
                wave[0].check_startwave = false;
                startallwave(0, numberzombiew1, delaybetweenw1);
            }
            if (nowave && endRSP) { allwave(0, numberzombiew1); }
            if (wave[0].checkexit_wave) {
                if (movefromwavetoanother) {
                    clockwave2.restart();
                    movefromwavetoanother = false;
                    nowave = false;
                }
                timertostartwave2 = clockwave2.getElapsedTime();
                if (timertostartwave2 > seconds(6)) {
                    if (wave[1].check_startwave) {
                        startallwave(1, numberzombiew1+=20, delaybetweenw1-=2.0f);
                        wave[1].check_startwave = false;
                        scaleFactor = 6.0f;
                    }
                    allwave(1, numberzombiew1 += 20);
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
                        startallwave(2, numberzombiew1 += 20, delaybetweenw1 -= 2.0f);
                        wave[2].check_startwave = false;
                    }
                    allwave(2, numberzombiew1 += 20);
                }

            }
        }
    }
}