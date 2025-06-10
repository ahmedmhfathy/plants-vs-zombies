#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<algorithm>
#include <iostream>
#include <vector>
#include <string>
#include<time.h>
#include"Tools.h"
#include "Game Settings And Audio.h"
#include"StartAnimation.h"
#include"Plants_Zombies.h"

#pragma region Functiondelaration
void allwave(int, int);
void intersectioncarsandzombies(int);
void DrawWavesAndZombies(RenderWindow&, string);
void startallwave(int, int, float);
void level(int, int, float);
#pragma endregion

#pragma region Textures and Sprites declaration
Texture lawntexture;
Texture rectangletexture;
Texture Textstartwave2texture;
Texture Textstartfinalwavetexture;
Texture Textlosegametexture;

Sprite Textstartwave2sprite;
Sprite Textstartfinalwavesprite;
Sprite Textlosegamesprite;
#pragma endregion

#pragma region Sounds
SoundBuffer HugeWaveOfZombiesSoundBuffer;
Sound HugeWaveOfZombiesSound;
SoundBuffer FinalWaveSoundBuffer;
Sound FinalWaveSound;
SoundBuffer LoseSoundBuffer;
Sound LoseSound;
SoundBuffer carsSoundBuffer;
Sound carsSound;
#pragma endregion

#pragma region booleans
bool nowave = true;
bool checkstart_wave2 = true;
bool checkstart_wave3 = true;
bool endRSP = false;
bool movefromwavetoanother = true;

bool LevelIsOver = false;
bool WinLevel = false;
bool playLoseGameAnim = false;
bool playWaveSounds = false;
#pragma endregion

#pragma region hours and timer
Clock clockwave2;
Clock clockfinalwave;
Clock globalClock;
Clock LoseGameClock;

Time timertostartwave2;
Time timertostartwave3;

float timeSinceStart;
#pragma endregion

#pragma region Scale 
float minscale = 1.7f;                      // Min Scale For Text Start Wave Two And Text Final Wave
float scaleFactor = 6.0f;                   // First scale For  Text Start Wave Two And Text Final Wave
float minscaletextlosegame = 1.17f;         // Min Scale For Text Lose Game
float scalefactortextlosegame = 4.2f;       // First scale For Lose Game
#pragma endregion

#pragma region Structs
struct cars {
    bool startsoundcar = true;
    bool intersection = false;
    float speed = 75;
    Sprite lawnsprite;
    void start(int i) {
        lawntexture.loadFromFile("Assets/Environment/lawnmower.png");
        lawnsprite.setTexture(lawntexture);
        lawnsprite.setScale(0.8, 0.8);
        lawnsprite.setPosition(-90, 60 + (i * 130));
    }
    void update() {
        if (!intersection)
        {
            if (lawnsprite.getPosition().x < -65) {
                lawnsprite.move(speed * deltaTime, 0);
               
            }
        }
        else
        {
            if (lawnsprite.getPosition().x < 960)
            {
                lawnsprite.move(speed * deltaTime, 0);
                if (startsoundcar) {
                    carsSound.play();
                    startsoundcar = false;
                }
            }
            else
            {
               
                lawnsprite.setPosition(1000, 1000);
            }
        }
    }
}car[5];

struct waves {
    float delaybetween;
    int numberzombie;
    bool checkexit_wave = false;
    bool check_startwave = true;
}wave[3];
#pragma endregion

//resets all data so you can retry the level
void setupWaveData() {

    for (int i = 0; i < 5; i++)
    {
        car[i].intersection = false;
        car[i].startsoundcar = true;
    }

    for (int i = 0; i < 3; i++)
    {
        wave[i].checkexit_wave = false;
        wave[i].check_startwave = true;
    }


    clockwave2.restart();
    clockfinalwave.restart();
    globalClock.restart();
    LoseGameClock.restart();
    DeltaTimeClock.restart();

    nowave = true;
    checkstart_wave2 = true;
    checkstart_wave3 = true;
    endRSP = false;
    movefromwavetoanother = true;

    IsPaused = false;
    LevelIsOver = false;
    WinLevel = false;
    playLoseGameAnim = false;
    playWaveSounds = false;

    minscale = 1.7f;
    scaleFactor = 6.0f;
    minscaletextlosegame = 1.17f;
    scalefactortextlosegame = 4.2f;

    timeSinceStart = 0;
    deltaTime = DeltaTimeClock.restart().asSeconds();
}

void startZombiePositions(int numZombies) {
    Plants_Zombies::StartZombies(numZombies);

    int row[5] = { -40, 100, 235, 360,490 };

    for (int i = 0; i < 100; i++)
    {
        Plants_Zombies::zombie_array[i].started = false;
        Plants_Zombies::zombie_array[i].isDead = false;

        Plants_Zombies::zombie_array[i].zombieCont.setPosition(1000, row[rand() % 5]);

        if (Plants_Zombies::zombie_array[i].type == Plants_Zombies::trafficCone || Plants_Zombies::zombie_array[i].type == Plants_Zombies::newsMan) {
            Plants_Zombies::zombie_array[i].zombieCont.setPosition(1000, row[rand() % 5] - 25);
        }
        Plants_Zombies::zombie_array[i].zombieCollider.setPosition(Plants_Zombies::zombie_array[i].zombieCont.getPosition().x + 50, Plants_Zombies::zombie_array[i].zombieCont.getPosition().y + 60);
        //cout << Plants_Zombies::zombie_array[i].zombieCont.getPosition().x << " - " << Plants_Zombies::zombie_array[i].zombieCont.getPosition().y << endl;
    }
}

void startallwave(int numberwave, int numberzombie, float delaybetween) {
    wave[numberwave].delaybetween = delaybetween;
    wave[numberwave].numberzombie = numberzombie;

    srand(time(0));
    globalClock.restart();

    timeSinceStart = globalClock.getElapsedTime().asSeconds();

    startZombiePositions(numberzombie);
}

void allwave(int numberwave, int numberzombie) {

    intersectioncarsandzombies(numberwave);

    for (int i = 0; i < wave[numberwave].numberzombie; ++i) {
        if (timeSinceStart >= i * wave[numberwave].delaybetween) {

            Plants_Zombies::zombie_array[i].started = true;
        }
    }
    for (int i = 0; i < wave[numberwave].numberzombie; i++) {
        if (Plants_Zombies::zombie_array[i].started && Plants_Zombies::zombie_array[i].type != Plants_Zombies::Dead) {
            if (!IsPaused)
            {
                Plants_Zombies::zombie_array[i].update(deltaTime);
            }
        }
    }


    for (int i = 0; i < wave[numberwave].numberzombie; i++)
    {
        if (Plants_Zombies::zombie_array[i].type == Plants_Zombies::Dead)
        {
            wave[numberwave].checkexit_wave = true;
        }
        else
        {
            wave[numberwave].checkexit_wave = false;
            break;
        }
    }
}

void level(int numberwave, int num, float delaybetweenw1) {
    if (endRSP)
    {
        if (numberwave == 2) {
            if (wave[0].check_startwave) {
                wave[0].check_startwave = false;
                startallwave(0, num, delaybetweenw1);
            }
            if (nowave && endRSP) { allwave(0, num); }
            if (wave[0].checkexit_wave) {
                if (movefromwavetoanother) {
                    clockwave2.restart();
                    movefromwavetoanother = false;
                    nowave = false;
                }
                timertostartwave2 = clockwave2.getElapsedTime();
                if (timertostartwave2 > seconds(6)) {
                    if (wave[1].check_startwave) {
                        startallwave(1, num += 7, delaybetweenw1 -= 2.0f);
                        wave[1].check_startwave = false;
                        scaleFactor = 6.0f;
                    }
                    allwave(1, num);

                    //check win status
                    if (wave[1].checkexit_wave)
                    {
                        LevelIsOver = true;
                        WinLevel = true;
                        IsPaused = true;
                    }
                    else
                    {
                        LevelIsOver = false;
                        WinLevel = false;
                        IsPaused = false;
                    }
                }
            }
        }
        else if (numberwave == 3) {
            if (wave[0].check_startwave) {
                wave[0].check_startwave = false;
                startallwave(0, num, delaybetweenw1);
            }
            if (nowave && endRSP) { allwave(0, num); }
            if (wave[0].checkexit_wave) {
                if (movefromwavetoanother) {
                    clockwave2.restart();
                    movefromwavetoanother = false;
                    nowave = false;
                }
                timertostartwave2 = clockwave2.getElapsedTime();
                if (timertostartwave2 > seconds(6)) {
                    if (wave[1].check_startwave) {
                        startallwave(1, num += 10, delaybetweenw1 -= 2.0f);
                        wave[1].check_startwave = false;
                        scaleFactor = 6.0f;
                    }
                    allwave(1, num);
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
                        startallwave(2, num += 20, delaybetweenw1 -= 2.0f);
                        wave[2].check_startwave = false;
                    }
                    allwave(2, num);


                    //check win status
                    if (wave[2].checkexit_wave)
                    {
                        LevelIsOver = true;
                        WinLevel = true;
                        IsPaused = true;
                    }
                    else
                    {
                        LevelIsOver = false;
                        WinLevel = false;
                        IsPaused = false;
                    }
                }
            }
        }
    }
}

void intersectioncarsandzombies(int numberwave) {
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < wave[numberwave].numberzombie; j++)
        {
            FloatRect rect1 = car[i].lawnsprite.getGlobalBounds();
            FloatRect rect2 = Plants_Zombies::zombie_array[j].zombieCollider.getGlobalBounds();

            if (rect1.intersects(rect2)) {
                car[i].intersection = true;
                Plants_Zombies::zombie_array[j].isSquished = true;
            }
            car[i].update();
        }
    }
}

void DrawWavesAndZombies(RenderWindow& window) {
    if (endRSP)
    {
        if (nowave) {

            for (int i = 0; i < wave[0].numberzombie; i++) {
                if (Plants_Zombies::zombie_array[i].type != Plants_Zombies::Dead)
                {
                   // window.draw(Plants_Zombies::zombie_array[i].zombieCollider);
                    window.draw(Plants_Zombies::zombie_array[i].zombieCont);
                }
            }
        }
        else if (wave[0].checkexit_wave && !nowave) {
            for (int i = 0; i < wave[1].numberzombie; i++) {
                if (Plants_Zombies::zombie_array[i].type != Plants_Zombies::Dead)
                {
                   // window.draw(Plants_Zombies::zombie_array[i].zombieCollider);
                    window.draw(Plants_Zombies::zombie_array[i].zombieCont);
                }

            }
        }
        else if (wave[1].checkexit_wave) {
            for (int i = 0; i < wave[2].numberzombie; i++) {
                if (Plants_Zombies::zombie_array[i].type != Plants_Zombies::Dead)
                {
                   // window.draw(Plants_Zombies::zombie_array[i].zombieCollider);
                    window.draw(Plants_Zombies::zombie_array[i].zombieCont);
                }
            }
        }
    }

    if (timertostartwave2 > seconds(2) && timertostartwave2 < seconds(6) && wave[0].checkexit_wave)
    {
        if (scaleFactor > minscale) {
            scaleFactor -= deltaTime * 14.0f; // ??????? ????????
        }
        if (!playWaveSounds)
        {
            HugeWaveOfZombiesSound.play();
            playWaveSounds = true;
        }

        Textstartwave2sprite.setScale(scaleFactor, scaleFactor);
        window.draw(Textstartwave2sprite);
    }
    if (timertostartwave3 > seconds(2) && timertostartwave3 < seconds(6) && wave[1].checkexit_wave) {
        if (scaleFactor > minscale) {
            scaleFactor -= deltaTime * 14.0f; // ??????? ????????
        }
        if (playWaveSounds)
        {
            FinalWaveSound.play();
            playWaveSounds = false;
        }
        Textstartfinalwavesprite.setScale(scaleFactor, scaleFactor);
        window.draw(Textstartfinalwavesprite);
    }

    for (int i = 0; i < 100; i++) {
        if (Plants_Zombies::zombie_array[i].zombieCollider.getPosition().x < -50 && Plants_Zombies::zombie_array[i].started)
        {
            if (!playLoseGameAnim)
            {
                LoseSound.play();
                LoseGameClock.restart();
                playLoseGameAnim = true;
            }
            else
            {
                Time animDuration_ = seconds(6);
                if (scalefactortextlosegame > minscaletextlosegame)
                {
                    scalefactortextlosegame = easeInOut(linear, scalefactortextlosegame, minscaletextlosegame, LoseGameClock, animDuration_);
                    Textlosegamesprite.setScale(scalefactortextlosegame, scalefactortextlosegame);
                }
                else
                {
                    IsPaused = true;
                    LevelIsOver = true;
                    WinLevel = false;
                }
            }

            window.draw(Textlosegamesprite);

            for (int i = 0; i < 3; i++)
            {
                wave[i].checkexit_wave = false;
            }
        }
    }
}