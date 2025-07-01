#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include "Tools.h"
#include "Game Settings And Audio.h"
#include "StartAnimation.h"
#include "Plants_Zombies.h"
#include "Boss Logic.h"

#pragma region Functiondelaration
void allwave(int, int);
void intersectioncarsandzombies(int);
void DrawWavesAndZombies(RenderWindow&, string);
void startallwave(int, int, float);
void level(int, int, float);

void RSP(RenderWindow&); // Ready...Set....Plant....
#pragma endregion

#pragma region start animation stuff
#pragma region Textures and sprites declaration
Texture gardenTextureDay;
Texture gardenTextureNight;
Texture roofTextureDay;
Texture roofTextureNight;
Sprite gardensprite;
Texture Readytexttexture;
Sprite  Readytextsprite;
Texture Settexttexture;
Sprite Settextsprite;
Texture Planttexttexture;
Sprite Planttextsprite;
Texture zombieinStreettex;
Sprite zombieinStreet;
Texture fogTex;
Sprite fog;

#pragma endregion

#pragma region boolean
bool startdrawRSP = true;
bool startAnimcamera = false;

bool RSPSonudon = true;
bool ZombiesAreComingSoundOn = true;
#pragma endregion

#pragma region sound
SoundBuffer soundfogbuffer;
SoundBuffer RSPSoundBuffer;
SoundBuffer ZombiesAreComingBuffer;
SoundBuffer WinSoundBuffer;
#pragma endregion

#pragma region clock
Clock clockRSP;
#pragma endregion



#pragma endregion

#pragma region Textures and Sprites declaration
Texture Textstartwave2texture;
Texture Textstartfinalwavetexture;
Texture Textlosegametexture;
Texture lawnrooftexture;
Sprite Textstartwave2sprite;
Sprite Textstartfinalwavesprite;

#pragma endregion

#pragma region Sounds
SoundBuffer HugeWaveOfZombiesSoundBuffer;
SoundBuffer FinalWaveSoundBuffer;
#pragma endregion

#pragma region booleans

bool isFog = false;
bool nowave = true;
bool checkstart_wave2 = true;
bool checkstart_wave3 = true;
bool movefromwavetoanother = true;

bool endRSP = false;
bool EntertostartdrawRSP = false;

bool playWaveSounds = false;
bool isNightLevel = false;
#pragma endregion

#pragma region hours and timer
Clock clockwave2;
Clock clockfinalwave;

//Clock GlobalClock;

Time timertostartwave2;
Time timertostartwave3;

float timeSinceStart;
#pragma endregion

#pragma region Scale 
float minscale = 1.7f;                      // Min Scale For Text Start Wave Two And Text Final Wave
float scaleFactor = 6.0f;                   // First scale For  Text Start Wave Two And Text Final Wave

#pragma endregion

#pragma region Structs
struct waves
{
    float delaybetween;
    int numberzombie;
    bool checkexit_wave = false;
    bool check_startwave = true;
}wave[3];


#pragma endregion


//resets all data so you can retry the level
void setupWaveData(bool isNight_) {
    isNightLevel = isNight_;

    for (int i = 0; i < 5; i++)
    {
        boss::car[i].intersection = false;
        boss::car[i].startsoundcar = true;
    }

    for (int i = 0; i < 3; i++)
    {
        wave[i].checkexit_wave = false;
        wave[i].check_startwave = true;
    }

    clockwave2.restart();
    clockfinalwave.restart();
    boss::LoseGameClock.restart();
    DeltaTimeClock.restart();

    jackMusic.stop();

    nowave = true;
    checkstart_wave2 = true;
    checkstart_wave3 = true;
    endRSP = false;
    movefromwavetoanother = true;

    IsPaused = false;
    boss::LevelIsOver = false;
    boss::WinLevel = false;
    boss::playLoseGameAnim = false;
    playWaveSounds = false;
    jackMusicOn = false;

    minscale = 1.7f;
    scaleFactor = 6.0f;


    timeSinceStart = 0;
}

void startZombiePositions(int numZombies, int numberwave, int numlevel)
{
    

    Plants_Zombies::StartZombies(numZombies, numlevel, onRoof);

    int row[5] = { -40, 100, 235, 360, 490 };
    int rowroof[5] = { -50, 70, 175, 280, 400 };

    //normal zombies
    for (int i = 0; i < 100; i++)
    {
        Plants_Zombies::zombie_array[i].started = false;
        Plants_Zombies::zombie_array[i].isDead = false;

        if (!onRoof)
        {
            if (Plants_Zombies::zombie_array[i].type == Plants_Zombies::gargantous)
            {
                Plants_Zombies::zombie_array[i].zombieCont.setPosition(1000, row[rand() % 5]-60);
            }

            else if (Plants_Zombies::zombie_array[i].type == Plants_Zombies::trafficCone
                || Plants_Zombies::zombie_array[i].type == Plants_Zombies::newsMan
                || Plants_Zombies::zombie_array[i].type == Plants_Zombies::jackInTheBox)
            {
                Plants_Zombies::zombie_array[i].zombieCont.setPosition(1000, row[rand() % 5]-25);
            }
            else if (Plants_Zombies::zombie_array[i].type == Plants_Zombies::soccerGuy) {
                Plants_Zombies::zombie_array[i].zombieCont.setPosition(1000, row[rand() % 5] - 15);
            }
            else
            {
                Plants_Zombies::zombie_array[i].zombieCont.setPosition(1000, row[rand() % 5]);
            }
        }
        else
        {
            if (Plants_Zombies::zombie_array[i].type == Plants_Zombies::gargantous)
            {
                Plants_Zombies::zombie_array[i].zombieCont.setPosition(1000, rowroof[rand() % 5] - 60);
            }

            else if (Plants_Zombies::zombie_array[i].type == Plants_Zombies::trafficCone
                || Plants_Zombies::zombie_array[i].type == Plants_Zombies::newsMan
                || Plants_Zombies::zombie_array[i].type == Plants_Zombies::jackInTheBox
                || Plants_Zombies::zombie_array[i].type == Plants_Zombies::soccerGuy
                )
            {
                Plants_Zombies::zombie_array[i].zombieCont.setPosition(1000, rowroof[rand() % 5]-25);

            }
            else if (Plants_Zombies::zombie_array[i].type == Plants_Zombies::poleVault) {
                Plants_Zombies::zombie_array[i].zombieCont.setPosition(1000, rowroof[rand() % 5] - 20);
            }
            else {
                Plants_Zombies::zombie_array[i].zombieCont.setPosition(1000, rowroof[rand() % 5]);
            }
        }
        Plants_Zombies::zombie_array[i].zombieCollider.setPosition(Plants_Zombies::zombie_array[i].zombieCont.getPosition().x + 50, Plants_Zombies::zombie_array[i].zombieCont.getPosition().y + 70); //60
        //cout << Plants_Zombies::zombie_array[i].zombieCont.getPosition().x << " - " << Plants_Zombies::zombie_array[i].zombieCont.getPosition().y << endl;
    }

    //grave zombies
    if (isNightLevel && numberwave >= 1 && !onRoof)
    {
        for (int i = 0; i < numGraves; i++)
        {
            Plants_Zombies::zombie_array[i].started = false;
            Plants_Zombies::zombie_array[i].isDead = false;

            Plants_Zombies::zombie_array[i].zombieCont.setPosition(graves[i].getPosition().x, graves[i].getPosition().y - 30);

            if (Plants_Zombies::zombie_array[i].type == Plants_Zombies::trafficCone
                || Plants_Zombies::zombie_array[i].type == Plants_Zombies::newsMan
                || Plants_Zombies::zombie_array[i].type == Plants_Zombies::jackInTheBox)
            {
                Plants_Zombies::zombie_array[i].zombieCont.setPosition(graves[i].getPosition().x, graves[i].getPosition().y - 55);
            }
        }
    }
}

void startallwave(int numberwave, int numberzombie, float delaybetween, int numlevel) {
    wave[numberwave].delaybetween = delaybetween;
    wave[numberwave].numberzombie = numberzombie;

    srand(time(0));

    timeSinceStart = 0;

    startZombiePositions(numberzombie, numberwave, numlevel);
}

void allwave(int numberwave, int numberzombie)
{
    intersectioncarsandzombies(numberwave);

    //spawn zombies
    for (int i = 0; i < wave[numberwave].numberzombie; ++i)
    {
        timeSinceStart;
        // swarm of zombies
        if (numberwave >= 1 && i >= 0 && i <= 8)
        {
            //cout << timeSinceStart << endl;
            if (timeSinceStart >= (float)(i * 1))
            {
                if (Plants_Zombies::zombie_array[i].startJackClock)
                {
                    Plants_Zombies::zombie_array[i].jackClock = 0;
                    Plants_Zombies::zombie_array[i].startJackClock = false;
                }
                Plants_Zombies::zombie_array[i].started = true;
            }
        }

        // normal behaviour
        else
        {
            //cout << timeSinceStart << endl;
            if (timeSinceStart >= i * wave[numberwave].delaybetween)
            {
                if (Plants_Zombies::zombie_array[i].startJackClock)
                {
                    Plants_Zombies::zombie_array[i].jackClock = 0;
                    Plants_Zombies::zombie_array[i].startJackClock = false;
                }
                Plants_Zombies::zombie_array[i].started = true;
            }
        }
    }

    // update zombies
    for (int i = 0; i < wave[numberwave].numberzombie; i++)
    {
        if (Plants_Zombies::zombie_array[i].started && Plants_Zombies::zombie_array[i].type != Plants_Zombies::Dead)
        {
            if (!IsPaused)
            {
                Plants_Zombies::zombie_array[i].update(deltaTime);
            }
        }
    }

    // check if jack in the box music should play
    for (int i = 0; i < wave[numberwave].numberzombie; i++)
    {
        if (Plants_Zombies::zombie_array[i].type == Plants_Zombies::jackInTheBox)
        {
            if (!Plants_Zombies::zombie_array[i].isDead && Plants_Zombies::zombie_array[i].started)
            {
                jackMusicOn = true;
                break;
            }
            else if (Plants_Zombies::zombie_array[i].isDead || !Plants_Zombies::zombie_array[i].started || Plants_Zombies::zombie_array[i].type == Plants_Zombies::Dead)
            {
                jackMusicOn = false;
            }
        }
        else
        {
            jackMusicOn = false;
        }
    }

    // check if all zombies are dead
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

    //if wave is finished stop playing jack music
    if (wave[numberwave].checkexit_wave == true)
    {
        jackMusicOn = false;
    }
}

void level(int numberwave, int num, float delaybetweenw1, int numlevel)
{
    timeSinceStart += deltaTime;

    if (endRSP)
    {
        if (numberwave == 2) {
            if (wave[0].check_startwave)
            {
                wave[0].check_startwave = false;
                startallwave(0, num, delaybetweenw1, numlevel);
            }
            if (nowave && endRSP)
            {
                allwave(0, num);
            }
            if (wave[0].checkexit_wave)
            {
                if (movefromwavetoanother)
                {
                    clockwave2.restart();
                    movefromwavetoanother = false;
                    nowave = false;
                }
                timertostartwave2 = clockwave2.getElapsedTime();
                if (timertostartwave2 > seconds(6))
                {
                    if (wave[1].check_startwave)
                    {
                        startallwave(1, num += 8, delaybetweenw1 -= 5.0f, numlevel);
                        wave[1].check_startwave = false;
                        scaleFactor = 6.0f;
                    }
                    allwave(1, num);

                    //check win status
                    if (wave[1].checkexit_wave)
                    {
                        boss::LevelIsOver = true;
                        boss::WinLevel = true;
                        IsPaused = true;
                        PlaySoundEffect(WinSoundBuffer, false);
                    }
                    else
                    {
                        boss::LevelIsOver = false;
                        boss::WinLevel = false;
                        IsPaused = false;
                    }
                }
            }
        }
        else if (numberwave == 3)
        {
            if (wave[0].check_startwave)
            {
                wave[0].check_startwave = false;
                startallwave(0, num, delaybetweenw1, numlevel);
            }

            if (nowave && endRSP)
            {
                allwave(0, num);
            }

            if (wave[0].checkexit_wave)
            {
                if (movefromwavetoanother)
                {
                    clockwave2.restart();
                    movefromwavetoanother = false;
                    nowave = false;
                }

                timertostartwave2 = clockwave2.getElapsedTime();

                if (timertostartwave2 > seconds(6))
                {
                    if (wave[1].check_startwave)
                    {
                        startallwave(1, num += 20, delaybetweenw1 -= 4.0f, numlevel);
                        wave[1].check_startwave = false;
                        scaleFactor = 6.0f;
                    }

                    allwave(1, num);
                }
            }

            if (wave[1].checkexit_wave)
            {
                if (!movefromwavetoanother)
                {
                    clockfinalwave.restart();
                    movefromwavetoanother = true;
                    wave[0].checkexit_wave = false;
                }

                timertostartwave3 = clockfinalwave.getElapsedTime();

                if (timertostartwave3 > seconds(6))
                {
                    if (wave[2].check_startwave)
                    {
                        startallwave(2, num += 20, delaybetweenw1 -= 6.0f, numlevel);
                        wave[2].check_startwave = false;
                    }

                    allwave(2, num);

                    //check win status
                    if (wave[2].checkexit_wave)
                    {
                        boss::LevelIsOver = true;
                        boss::WinLevel = true;
                        IsPaused = true;
                        PlaySoundEffect(WinSoundBuffer, false);
                    }
                    else
                    {
                        boss::LevelIsOver = false;
                        boss::WinLevel = false;
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
        FloatRect rect1 = boss::car[i].lawnsprite.getGlobalBounds();

        for (int j = 0; j < wave[numberwave].numberzombie; j++)
        {
            FloatRect rect2 = Plants_Zombies::zombie_array[j].zombieCollider.getGlobalBounds();

            if (rect1.intersects(rect2)) {
                boss::car[i].intersection = true;
                Plants_Zombies::zombie_array[j].isSquished = true;
            }
        }

        //car[i].update();
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

        if (isbossFight)
        {
            boss::startBossfight = true;
        }

        endRSP = true;
    }
}

void DrawWavesAndZombies(RenderWindow& window)
{
    if (endRSP)
    {
        if (nowave) {

            for (int i = 0; i < wave[0].numberzombie; i++) {
                if (Plants_Zombies::zombie_array[i].type != Plants_Zombies::Dead && Plants_Zombies::zombie_array[i].started)
                {
                    /*if (Plants_Zombies::zombie_array[i].type == Plants_Zombies::jackInTheBox && !Plants_Zombies::zombie_array[i].isDead)
                    {
                        window.draw(Plants_Zombies::zombie_array[i].jackCollider);
                    }*/
                    myBrightnessShader.setUniform("brightness", Plants_Zombies::zombie_array[i].flashData.currentBrightness);

                  //window.draw(Plants_Zombies::zombie_array[i].zombieCollider);
                    window.draw(Plants_Zombies::zombie_array[i].zombieCont, &myBrightnessShader);
                }
            }
        }
        else if (wave[0].checkexit_wave && !nowave) {
            for (int i = 0; i < wave[1].numberzombie; i++) {
                if (Plants_Zombies::zombie_array[i].type != Plants_Zombies::Dead && Plants_Zombies::zombie_array[i].started)
                {
                    /*if (Plants_Zombies::zombie_array[i].type == Plants_Zombies::jackInTheBox && !Plants_Zombies::zombie_array[i].isDead)
                    {
                        window.draw(Plants_Zombies::zombie_array[i].jackCollider);
                    }*/
                    myBrightnessShader.setUniform("brightness", Plants_Zombies::zombie_array[i].flashData.currentBrightness);
                    
                    /*window.draw(Plants_Zombies::zombie_array[i].zombieCollider);*/
                    window.draw(Plants_Zombies::zombie_array[i].zombieCont, &myBrightnessShader);
                }

            }
        }
        else if (wave[1].checkexit_wave) {
            for (int i = 0; i < wave[2].numberzombie; i++) {
                if (Plants_Zombies::zombie_array[i].type != Plants_Zombies::Dead && Plants_Zombies::zombie_array[i].started)
                {
                    /*if (Plants_Zombies::zombie_array[i].type == Plants_Zombies::jackInTheBox && !Plants_Zombies::zombie_array[i].isDead)
                    {
                        window.draw(Plants_Zombies::zombie_array[i].jackCollider);
                    }*/
                    myBrightnessShader.setUniform("brightness", Plants_Zombies::zombie_array[i].flashData.currentBrightness);
                    
                    /*window.draw(Plants_Zombies::zombie_array[i].zombieCollider);*/
                    window.draw(Plants_Zombies::zombie_array[i].zombieCont, &myBrightnessShader);
                }
            }
        }
    }

    if (isFog)
    {
        window.draw(fog);
       
    }

    if (timertostartwave2 > seconds(2) && timertostartwave2 < seconds(6) && wave[0].checkexit_wave)
    {
        if (scaleFactor > minscale) {
            scaleFactor -= deltaTime * 14.0f; // ??????? ????????
        }
        if (!playWaveSounds)
        {
            PlaySoundEffect(HugeWaveOfZombiesSoundBuffer, false);
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
            PlaySoundEffect(FinalWaveSoundBuffer, false);
            playWaveSounds = false;
        }
        Textstartfinalwavesprite.setScale(scaleFactor, scaleFactor);
        window.draw(Textstartfinalwavesprite);
    }

    if (isbossFight)
    {
        if (boss::startBossfight)
        {
            RSP(window);
        }
    }
    else if (EntertostartdrawRSP)
    {
        RSP(window);
    }

    for (int i = 0; i < 100; i++) {
        if (Plants_Zombies::zombie_array[i].zombieCollider.getPosition().x < -50 && Plants_Zombies::zombie_array[i].started)
        {
            if (!boss::playLoseGameAnim)
            {
                PlaySoundEffect(boss::LoseSoundBuffer, false);
                boss::LoseGameClock.restart();
                boss::playLoseGameAnim = true;
            }
            else
            {
                Time animDuration_ = seconds(6);
                if (boss::scalefactortextlosegame > boss::minscaletextlosegame)
                {
                    boss::scalefactortextlosegame = easeInOut(linear, boss::scalefactortextlosegame, boss::minscaletextlosegame, boss::LoseGameClock, animDuration_);
                    boss::Textlosegamesprite.setScale(boss::scalefactortextlosegame, boss::scalefactortextlosegame);
                }
                else
                {
                    IsPaused = true;
                    boss::LevelIsOver = true;
                    boss::WinLevel = false;
                }
            }

            window.draw(boss::Textlosegamesprite);

            for (int i = 0; i < 3; i++)
            {
                wave[i].checkexit_wave = false;
            }
        }
    }
}