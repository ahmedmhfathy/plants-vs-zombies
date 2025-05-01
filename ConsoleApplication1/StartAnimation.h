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
#include <iomanip>
#include"Wave System.h"
using namespace std;
using namespace sf;

#pragma region Textures and sprites declaration
Texture gardentexture;
Sprite gardensprite;
Texture Readytexttexture;
Sprite  Readytextsprite;
Texture Settexttexture;
Sprite Settextsprite;
Texture Planttexttexture;
Sprite Planttextsprite;
#pragma endregion

#pragma region Fuctions
#pragma endregion

#pragma region boolean
bool startdrawRSP = true;
bool EntertostartdrawRSP = false;
// variable check Camera move Right And Left
bool moveright = false;
bool moveleft=false;
bool startAnimcamera = false;

#pragma endregion

#pragma region Hours
// hours
Clock animcameraClock; // Clock use in animation to camera
Clock clockRSP;
#pragma endregion

 namespace  StartAnimationNS {

#pragma region Function Declaration
void startAnimation();
void updateAnimation(RenderWindow&);
void movecamera(RenderWindow&);
void RSP(RenderWindow&); // Ready...Set....Plant....
void loadphoto();
void movecars(); 
#pragma endregion

    View GardenCamera(FloatRect(0, 0, 1280, 720));

    void startAnimation() {
        for (int i = 0; i < 5; i++) {
            car[i].start(i);
        }
        loadphoto();
        srand(time(0));
        for (int i = 0;i < 9; i++) {
            zombie[i].start(i, false);
        }
    }

    void updateAnimation(RenderWindow& window) {
        deltatimetextstartwave2 = clockdrawtextwave2.restart();
        deltatimetextfinalwave = clockdrawtextfinalwave.restart();
        deltatimelosegame = clocklosegame.restart();
        movecamera(window);
        if (moveleft) {
            movecars(); // When Move Camera is end .... Start move car
        }
        // This Restart for the first wave..............
        deltaTime = frameClock.restart().asSeconds();
        timeSinceStart = globalClock.getElapsedTime().asSeconds();
        if (endRSP) {
            level(3, 3, 10);
        }
    }
    
    void loadphoto() {
        // =======================**load photo garden**===================================
        gardentexture.loadFromFile("Assets/Environment/Game-Environment.png");
        gardensprite.setTexture(gardentexture);
        gardensprite.setPosition(-325, -265);
        gardensprite.setScale(0.65, 0.65);
        GardenCamera.setCenter({ 340, 310 });
        // =========================**load photo READY SET PLANT!**======================================
        //*********************(READY)******************
        Readytexttexture.loadFromFile("Assets/Environment/StartReady.png");
        Readytextsprite.setTexture(Readytexttexture);
        Readytextsprite.setOrigin(Readytextsprite.getGlobalBounds().width / 2.0f, Readytextsprite.getGlobalBounds().height / 2.0f);
        Readytextsprite.setPosition(340, 310);
        Readytextsprite.setScale(1.8, 1.8);
        //** *********************(SET)************************ **
        Settexttexture.loadFromFile("Assets/Environment/StartSet.png");
        Settextsprite.setTexture(Settexttexture);
        Settextsprite.setOrigin(Settextsprite.getGlobalBounds().width / 2.0f, Settextsprite.getGlobalBounds().height / 2.0f);
        Settextsprite.setPosition(340, 310);
        Settextsprite.setScale(1.8, 1.8);
        //***********************(PLANT)********************************
        Planttexttexture.loadFromFile("Assets/Environment/StartPlant.png");
        Planttextsprite.setTexture(Planttexttexture);
        Planttextsprite.setOrigin(Planttextsprite.getGlobalBounds().width / 2.0f, Planttextsprite.getGlobalBounds().height / 2.0f);
        Planttextsprite.setPosition(340, 310);
        Planttextsprite.setScale(1.8, 1.8);
        //===================================**load start wave two**==================================
        Textstartwave2texture.loadFromFile("Assets/Environment/A-Huge-Wave-Of-Zombies-Is-Approaching.png");
        Textstartwave2sprite.setTexture(Textstartwave2texture);
        Textstartwave2sprite.setOrigin(Textstartwave2sprite.getGlobalBounds().width / 2.0f, Textstartwave2sprite.getGlobalBounds().height / 2.0f);
        Textstartwave2sprite.setPosition(340, 310);
        Textstartwave2sprite.setOrigin(Textstartwave2texture.getSize().x / 2.f, Textstartwave2texture.getSize().y / 2.f);
        Textstartwave2sprite.setScale(0.8, 0.8);
        //=================================**load Final Wave**=====================================
        Textstartfinalwavetexture.loadFromFile("Assets/Environment/FinalWave.png");
        Textstartfinalwavesprite.setTexture(Textstartfinalwavetexture);
        Textstartfinalwavesprite.setOrigin(Textstartfinalwavesprite.getGlobalBounds().width / 2.0f, Textstartfinalwavesprite.getGlobalBounds().height / 2.0f);
        Textstartfinalwavesprite.setPosition(340, 310);
        // ==============================**load lose Game**========================================
        Textlosegametexture.loadFromFile("Assets/Environment/zombie _won.png");
        Textlosegamesprite.setTexture(Textlosegametexture);
        Textlosegamesprite.setPosition(-20, 10);
        Textlosegamesprite.setOrigin(Textlosegametexture.getSize().x / 2.f, Textlosegametexture.getSize().y / 2.f);
        Textlosegamesprite.setPosition(1280 / 3.5f, 720/ 2.27f);
    }

    void movecamera(RenderWindow& window) {
        // Start Move Camera From Left To Right..... Then From Right To Left.....
        window.setView(GardenCamera);
        if (!moveright) {
            if (GardenCamera.getCenter().x <= 849) {
                float startValue = 340, endValue = 850;
                if (startAnimcamera == false) {
                    animcameraClock.restart();
                    startAnimcamera = true;
                }
                GardenCamera.setCenter(easeInOut(CubicEaseInOut, startValue, endValue, animcameraClock, seconds(3)), 310);
            }
            else {
                moveright = true;
            }
        }
        if (!moveleft && moveright) {
            if (GardenCamera.getCenter().x > 341) {
                float startValue = 850, endValue = 340;
                if (startAnimcamera == true) {
                    animcameraClock.restart();
                    startAnimcamera = false;
                }
                GardenCamera.setCenter(easeInOut(CubicEaseInOut, startValue, endValue, animcameraClock, seconds(4)), 310);
            }
            else {
                moveleft = true;
            }
        }
        // End function ..... and move camera is end..

    }

    void RSP(RenderWindow& window) {
        Time time;
        if (startdrawRSP)
        {
            clockRSP.restart();
            startdrawRSP = false;
        }
        time = clockRSP.getElapsedTime();
        if (time < seconds(1.5))
        {
            window.draw(Readytextsprite);
        }
        else if (time < seconds(3))
        {
            window.draw(Settextsprite);
        }
        else if (time < seconds(4.5))
        {
            window.draw(Planttextsprite);
        }
        else
        {
            endRSP = true;
        }

    }

    void movecars() {
        int stoppedCars = 0;
        Time deltatime = clockmovecars.restart();
        float dt = deltatime.asSeconds();
        for (int i = 0; i < 5; i++) {
            car[i].update(dt);
            if (car[i].lawnsprite.getPosition().x > -70) {
                stoppedCars++;
            }
        }
        if (stoppedCars == 5) {
            EntertostartdrawRSP = true;

        }
    }

    void Renderstartanimation(RenderWindow& window) {
        window.draw(gardensprite);
        for (int i = 0; i < 40; i++) {
            window.draw(zombie[i].rectanglesprite);
        }
        if (EntertostartdrawRSP) {
            RSP(window);
        }
        for (int i = 0; i < 5; i++) {
            window.draw(car[i].lawnsprite);
        }



    }
}


