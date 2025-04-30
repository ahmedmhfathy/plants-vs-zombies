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
void allwave(int);
void intersectioncarsandzombies(int, RenderWindow&);
void drawzombies(RenderWindow&, string);
void startallwave(int, int, float);
void level(int, int, float);
#pragma endregion
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
struct zombies {
    int row[5] = {30, 150, 280, 400,520};
    Sprite rectanglesprite;
    bool started;
    bool stoped;
    void start(int x, bool finanim) {
        rectangletexture.loadFromFile("Assets/Environment/rectangle.png");
        rectanglesprite.setTexture(rectangletexture);
        rectanglesprite.setScale(0.13, 0.13);
        if (finanim) {
            rectanglesprite.setPosition(1100, row[rand() % 5]);
        }
        else {
           rectanglesprite.setPosition(1100+rand()%100,( -30 +(70*rand()%600)));
        }
    }
    void update(float dt) {
        rectanglesprite.move(-speedzombie * dt, 0);

    }
}zombie[300];
struct waves {
    float delaybetween;
    int numberzombie;
    bool checkexit_wave=false;
    bool check_startwave = true;
}wave[3];
void drawzombies(RenderWindow& window) {
    if (nowave) {
        for (int i = 0; i < wave[0].numberzombie; i++) {
            window.draw(zombie[i].rectanglesprite);
        }
    }
    else if (wave[0].checkexit_wave && !nowave) {
        for (int i = 0; i < wave[1].numberzombie; i++) {
            window.draw(zombie[i].rectanglesprite);
        }
    }
    else if (wave[1].checkexit_wave) {
        for (int i = 0; i < wave[2].numberzombie; i++) {
            window.draw(zombie[i].rectanglesprite);
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
    Time deltatime = clockmovecars.restart();
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
    for (int i = 0;i < 15; i++) {
        zombie[i].start(i, true);
    }

}
void allwave(int numberwave) {
    for (int i = 0; i < wave[numberwave].numberzombie; ++i) {
        if (timeSinceStart >= i * wave[numberwave].delaybetween) {
            zombie[i].started = true;
        }
    }
    for (int i = 0; i < wave[numberwave].numberzombie; i++) {
        if (zombie[i].rectanglesprite.getPosition().x > -60) {
            if (zombie[i].started) {
                zombie[i].update(deltaTime);
            }
            }
        }
        for (int i = 0; i < wave[numberwave].numberzombie; ++i) {
            if (zombie[i].rectanglesprite.getPosition().x < -57) {
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
void level(int numberwave, int numberzombiew1, float delaybetweenw1) {
    if (numberwave == 2) {
        if (wave[0].check_startwave) {
            wave[0].check_startwave = false;
            startallwave(0, numberzombiew1, delaybetweenw1);
        }
        if (nowave && endRSP) { allwave(0); }
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
                allwave(1);
            }
        }
    }
    if (numberwave == 3) {
        if (wave[0].check_startwave) {
            wave[0].check_startwave = false;
            startallwave(0, numberzombiew1, delaybetweenw1);
        }
        if (nowave && endRSP) { allwave(0); }
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
                allwave(1);
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
                allwave(2);
            }

        }
    }
    
}