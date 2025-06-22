#pragma once
#include"Tools.h"
#include<algorithm>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <SFML/Audio.hpp>
#include"Wave System.h"
using namespace std;
using namespace sf;

namespace  StartAnimationNS {

#pragma region Function Declaration
    void startAnimation();
    void updateAnimation(RenderWindow&);
    void movecamera(RenderWindow&);
    void RSP(RenderWindow&); // Ready...Set....Plant....
    void loadphoto();
    void movecars();
#pragma endregion

#pragma region Textures and sprites declaration
    Texture gardenTextureDay;
    Texture gardenTextureNight;
    Sprite gardensprite;
    Texture Readytexttexture;
    Sprite  Readytextsprite;
    Texture Settexttexture;
    Sprite Settextsprite;
    Texture Planttexttexture;
    Sprite Planttextsprite;
    Texture zombieinStreettex;
    Sprite zombieinStreet;

    SoundBuffer RSPSoundBuffer;
    SoundBuffer ZombiesAreComingBuffer;
#pragma endregion

#pragma region boolean
    bool startdrawRSP = true;
    bool EntertostartdrawRSP = false;
    // variable check Camera move Right And Left
    bool moveright = false;
    bool moveleft = false;
    bool startAnimcamera = false;

    bool RSPSonudon = true;
    bool ZombiesAreComingSoundOn = true;
#pragma endregion

    Clock animcameraClock;
    Clock clockRSP;

    View GardenCamera(FloatRect(0, 0, 1280, 720));

    void LoadStartAndWaveAnimationTextures() {
        gardenTextureDay.loadFromFile("Assets/Environment/Game-Environment.png");
        gardenTextureNight.loadFromFile("Assets/Environment/Game-Environment-Night.png");
        zombieinStreettex.loadFromFile("Assets/Environment/zombie.png");
        Readytexttexture.loadFromFile("Assets/Environment/StartReady.png");
        Settexttexture.loadFromFile("Assets/Environment/StartSet.png");
        Planttexttexture.loadFromFile("Assets/Environment/StartPlant.png");

        Textstartwave2texture.loadFromFile("Assets/Environment/A-Huge-Wave-Of-Zombies-Is-Approaching.png");
        Textstartfinalwavetexture.loadFromFile("Assets/Environment/FinalWave.png");
        Textlosegametexture.loadFromFile("Assets/Environment/zombie _won.png");

        RSPSoundBuffer.loadFromFile("Audio/readysetplant.ogg");
        ZombiesAreComingBuffer.loadFromFile("Audio/awooga.ogg");
        HugeWaveOfZombiesSoundBuffer.loadFromFile("Audio/hugewave.ogg");
        FinalWaveSoundBuffer.loadFromFile("Audio/finalwave.ogg");
        LoseSoundBuffer.loadFromFile("Audio/scream.ogg");
        carsSoundBuffer.loadFromFile("Audio/lawnmower.ogg");
        Textgraves.loadFromFile("Assets/Environment/Graves-ST.png");

        //ready text
        Readytextsprite.setTexture(Readytexttexture);
        Readytextsprite.setOrigin(Readytextsprite.getGlobalBounds().width / 2.0f, Readytextsprite.getGlobalBounds().height / 2.0f);
        Readytextsprite.setPosition(340, 310);
        Readytextsprite.setScale(1.8, 1.8);

        // set text
        Settextsprite.setTexture(Settexttexture);
        Settextsprite.setOrigin(Settextsprite.getGlobalBounds().width / 2.0f, Settextsprite.getGlobalBounds().height / 2.0f);
        Settextsprite.setPosition(340, 310);
        Settextsprite.setScale(1.8, 1.8);

        // plant text
        Planttextsprite.setTexture(Planttexttexture);
        Planttextsprite.setOrigin(Planttextsprite.getGlobalBounds().width / 2.0f, Planttextsprite.getGlobalBounds().height / 2.0f);
        Planttextsprite.setPosition(340, 310);
        Planttextsprite.setScale(1.8, 1.8);

        // huge wave of zombies is coming text
        Textstartwave2sprite.setTexture(Textstartwave2texture);
        Textstartwave2sprite.setOrigin(Textstartwave2sprite.getGlobalBounds().width / 2.0f, Textstartwave2sprite.getGlobalBounds().height / 2.0f);
        Textstartwave2sprite.setPosition(340, 310);
        Textstartwave2sprite.setOrigin(Textstartwave2texture.getSize().x / 2.f, Textstartwave2texture.getSize().y / 2.f);
        Textstartwave2sprite.setScale(0.8, 0.8);

        // final wave text
        Textstartfinalwavesprite.setTexture(Textstartfinalwavetexture);
        Textstartfinalwavesprite.setOrigin(Textstartfinalwavesprite.getGlobalBounds().width / 2.0f, Textstartfinalwavesprite.getGlobalBounds().height / 2.0f);
        Textstartfinalwavesprite.setPosition(340, 310);

        // the zombies ate your brains text
        Textlosegamesprite.setTexture(Textlosegametexture);
        Textlosegamesprite.setPosition(-20, 10);
        Textlosegamesprite.setOrigin(Textlosegametexture.getSize().x / 2.f, Textlosegametexture.getSize().y / 2.f);
        Textlosegamesprite.setPosition(1280 / 3.5f, 720 / 2.27f);
    }

    void SetupStartAndWaveAnimationPhotos(bool isNight) {
        //garden
        if (isNight)
        {
            gardensprite.setTexture(gardenTextureNight);
        }
        else
        {
            gardensprite.setTexture(gardenTextureDay);
        }
        gardensprite.setPosition(-325, -265);
        gardensprite.setScale(0.65, 0.65);
        GardenCamera.setCenter({ 340, 310 });

        //zombies in street
        zombieinStreet.setTexture(zombieinStreettex);
        zombieinStreet.setPosition(980, -250);
        zombieinStreet.setScale(1.4, 1.4);
    }

    void startAnimation(bool isNight) {

        startdrawRSP = true;
        EntertostartdrawRSP = false;
        moveright = false;
        moveleft = false;
        startAnimcamera = false;
        RSPSonudon = true;
        ZombiesAreComingSoundOn = true;

        animcameraClock.restart();
        clockRSP.restart();

        //GardenCamera.zoom(1.5);

        for (int i = 0; i < 5; i++)
        {
            car[i].start(i);
        }

        SetupStartAndWaveAnimationPhotos(isNight);
        srand(time(0));
    }

    void updateAnimation(RenderWindow& window) 
    {
        movecamera(window);

        if (moveleft) 
        {
            movecars(); // When Move Camera is end .... Start move car
        }
    }

    void movecamera(RenderWindow& window) 
    {
        // Start Move Camera From Left To Right.....
        window.setView(GardenCamera);
        if (!moveright) 
        {
            if (GardenCamera.getCenter().x <= 849) 
            {
                float startValue = 340, endValue = 850;
                if (startAnimcamera == false) 
                {
                    animcameraClock.restart();
                    startAnimcamera = true;
                }
                GardenCamera.setCenter(easeInOut(CubicEaseInOut, startValue, endValue, animcameraClock, seconds(3)), 310);
            }
            else 
            {
                moveright = true;
            }
        }

        // Start Move Camera From Right To Left.....
        if (!moveleft && moveright) 
        {
            if (GardenCamera.getCenter().x > 341) 
            {
                float startValue = 850, endValue = 340;
                if (startAnimcamera == true) 
                {
                    animcameraClock.restart();
                    startAnimcamera = false;
                }
                GardenCamera.setCenter(easeInOut(CubicEaseInOut, startValue, endValue, animcameraClock, seconds(4)), 310);
            }
            else 
            {
                moveleft = true;
            }
        }
    }

    void RSP(RenderWindow& window) 
    {
        Time time;
        if (startdrawRSP)
        {
            clockRSP.restart();
            startdrawRSP = false;
        }
        time = clockRSP.getElapsedTime();

        if (time < seconds(0.5))
        {
            if (RSPSonudon)
            {
                PlaySoundEffect(RSPSoundBuffer, false);
                RSPSonudon = false;
            }
            window.draw(Readytextsprite);
        }
        else if (time < seconds(1.2))
        {
            window.draw(Settextsprite);
        }
        else if (time < seconds(2.05))
        {
            window.draw(Planttextsprite);
        }
        else if (time >= seconds(1))// start delay, affects the pause menu though, needs to be fixed
        {
            if (ZombiesAreComingSoundOn)
            {
                PlaySoundEffect(ZombiesAreComingBuffer, false);
                ZombiesAreComingSoundOn = false;
            }
            endRSP = true;
        }
    }

    void movecars() 
    {
        int stoppedCars = 0;

        for (int i = 0; i < 5; i++) 
        {
            car[i].update();
            if (car[i].lawnsprite.getPosition().x > -70) 
            {
                stoppedCars++;
            }
        }

        if (stoppedCars == 5) 
        {
            EntertostartdrawRSP = true;
        }
    }

    void Renderstartanimation(RenderWindow& window) 
    {
        window.draw(gardensprite);

        if (EntertostartdrawRSP) 
        {
            RSP(window);
        }
        for (int i = 0; i < 5; i++) 
        {
            window.draw(car[i].lawnsprite);
        }

        window.draw(zombieinStreet);
    }
}