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
#pragma region (Texture,sprite)_declaration
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
void startAnimation(RenderWindow&);
void updateAnimation(RenderWindow&);
void loadphoto(RenderWindow&);
void movecamera(RenderWindow&);
void RSP(RenderWindow&); // Ready...Set....Plant....
void movecars(); 
#pragma endregion
#pragma region boolean
bool startdrawRSP = true;
bool EntertostartdrawRSP = false;
// variable check Camera move Right And Left
bool moveright = false;
bool moveleft=false;
bool startAnimcamera = false;
bool movefromwavetoanother = true;
#pragma endregion
#pragma region Hours
// hours
Clock animcameraClock; // Clock use in animation to camera
Clock clockRSP;
#pragma endregion
// ==***Declare Camera***===
 View GardenCamera(FloatRect(0, 0, 1280, 720));
void startAnimation(RenderWindow&window) {
    for (int i = 0; i < 5; i++) {
        car[i].start(i);
    }
    loadphoto(window);
    startallwave(0, 5, 5.0f); // calling function to start wave one 
}
void updateAnimation(RenderWindow&window) {
    deltatimetextstartwave2= clockdrawtextwave2.restart();
    deltatimetextfinalwave = clockdrawtextfinalwave.restart();
    deltatimelosegame = clocklosegame.restart();
    movecamera(window);
    if (moveleft) {
        movecars(); // When Move Camera is end .... Start move car
    }
    // This Restart for the first wave..............
    deltaTime = frameClock.restart().asSeconds(); 
    timeSinceStart = globalClock.getElapsedTime().asSeconds();
        if (nowave && endRSP) { allwave(0); }
        if (wave[0].checkexit_wave) {
            if (movefromwavetoanother) {
                clockwave2.restart();
                movefromwavetoanother =false;
                nowave = false;
            }
            timertostartwave2 = clockwave2.getElapsedTime();
            if (timertostartwave2 > seconds(6)) {
                if (checkstart_wave2) {
                    startallwave(1, 7, 3.0f);
                    checkstart_wave2 = false;
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
            if (timertostartwave3>seconds(6)) {
                if (checkstart_wave3) {
                    startallwave(2, 8, 3.0f);
                    checkstart_wave3 = false;
                }
                allwave(2);
            }
            
        }
    
}
void loadphoto(RenderWindow&window) {
    // =======================**load photo garden**===================================
    gardentexture.loadFromFile("photo/garden - Plants vs Zombies - Day.png");
    gardensprite.setTexture(gardentexture);
    gardensprite.setScale(1.2, 1.2);
    gardensprite.setPosition(-300, -80);
    gardensprite.move(300, 120);
    // =========================**load photo READY SET PLANT!**======================================
    //*********************(READY)******************
    Readytexttexture.loadFromFile("photo/StartReady.png");
    Readytextsprite.setTexture(Readytexttexture);
    Readytextsprite.setPosition(400, 280);
    Readytextsprite.setScale(1.8, 1.8);
    //** *********************(SET)************************ **
    Settexttexture.loadFromFile("photo/StartSet.png");
    Settextsprite.setTexture(Settexttexture);
    Settextsprite.setPosition(400, 280);
    Settextsprite.setScale(1.8, 1.8);
    //***********************(PLANT)********************************
    Planttexttexture.loadFromFile("photo/StartPlant.png");
    Planttextsprite.setTexture(Planttexttexture);
    Planttextsprite.setPosition(400, 280);
    Planttextsprite.setScale(1.8, 1.8);
    //===================================**load start wave two**==================================
    Textstartwave2texture.loadFromFile("photo/A-Huge-Wave-Of-Zombies-Is-Approaching.png");
    Textstartwave2sprite.setTexture(Textstartwave2texture);
    Textstartwave2sprite.setPosition(80, 700);
    Textstartwave2sprite.setOrigin(Textstartwave2texture.getSize().x / 2.f, Textstartwave2texture.getSize().y / 2.f);
    Textstartwave2sprite.setPosition(window.getSize().x / 1.8f, window.getSize().y / 1.8f);
    //=================================**load Final Wave**=====================================
    Textstartfinalwavetexture.loadFromFile("photo/FinalWave.png");
    Textstartfinalwavesprite.setTexture(Textstartfinalwavetexture);
    Textstartfinalwavesprite.setPosition(320, 350);
    Textstartfinalwavesprite.setOrigin(Textstartfinalwavetexture.getSize().x / 2.f, Textstartfinalwavetexture.getSize().y / 2.f);
    Textstartfinalwavesprite.setPosition(window.getSize().x / 1.8f, window.getSize().y / 1.8f);
    // ==============================**load lose Game**========================================
    Textlosegametexture.loadFromFile("photo/zombie _won.png");
    Textlosegamesprite.setTexture(Textlosegametexture);
    Textlosegamesprite.setPosition(-20,10 );
    Textlosegamesprite.setOrigin(Textlosegametexture.getSize().x / 2.f, Textlosegametexture.getSize().y / 2.f);
    Textlosegamesprite.setPosition(window.getSize().x / 2.f, window.getSize().y / 1.8f);
}
void movecamera(RenderWindow& window) {
    // Start Move Camera From Left To Right..... Then From Right To Left.....
   window.setView(GardenCamera);
   if (!moveright) {
       if (GardenCamera.getCenter().x <= 1040) {
           float startValue = 660, endValue = 1050;
           if (startAnimcamera == false) {
               animcameraClock.restart();
               startAnimcamera = true;
           }
           GardenCamera.setCenter(easeInOut(startValue, endValue, animcameraClock, seconds(3)), 400);
       }
       else {
           moveright = true;
       }
   }
   if (!moveleft && moveright) {
       if (GardenCamera.getCenter().x > 645) {
           float startValue = 1040, endValue = 645;
           if (startAnimcamera == true) {
               animcameraClock.restart();
               startAnimcamera = false;
           }
           GardenCamera.setCenter(easeInOut(startValue, endValue, animcameraClock, seconds(4)), 400);
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
     deltatime = clockmovecars.restart();
    float dt = deltatime.asSeconds();
    for (int i = 0; i < 5; i++) {
        car[i].update(dt);
        if (car[i].lawnsprite.getPosition().x > 225) {
            stoppedCars++;
        }
    }
    if (stoppedCars == 5) {
        EntertostartdrawRSP= true;
        
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
