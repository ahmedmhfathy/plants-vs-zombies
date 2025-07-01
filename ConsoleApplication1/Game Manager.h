#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include "Game Settings And Audio.h"
#include "planting system.h"
#include "StartAnimation.h"
#include "Wave System.h"
using namespace std;
using namespace sf;

enum State { MainMenu, Level1, Level2, Level3, Level4, Level5 } CurrentState, MaxLevelWon;
void SwitchState(State NewState);

bool ButtonTapSoundNextLevel = false;
bool ButtonTapSoundWinMainMenu = false;
bool ButtonTapSoundPauseBackToMainMenu = false;
bool ButtonTapSoundBackToTheGame = false;
bool ButtonTapSoundRetry = false;
bool ButtonTapSoundLoseBackToMainMenu = false;
bool winSound = false;

// file saving for levels
int LastLevelReached;
string LevelReadFromFile;
//ofstream SaveLevelProgressWrite("lastlevelreached.txt");
//ifstream SaveLevelProgressRead("lastlevelreached.txt");

Time TickBoxDelay = seconds(.25);
Clock DelayClock;

Texture ThankYouForPlayingTex;
Sprite ThankYouForPlaying;

Vector2i Mousepostion;
Vector2f MouseWorldPostion;

Vector2f offset = { -300, -50 };
// the center of the GameScreen is 340, 310

#pragma region Pause Menu Textures and Sprites
Texture MainMenuButtonTex;
Texture MainMenuButtonTexHover;
Texture BackToTheGameButtonTex;
Texture BackToTheGameButtonHoverTex;
Texture PauseMenuBlank;
Texture TickBoxBlankTex;
Texture TickBoxSelectedTex;
Texture OpacityTex;

Sprite BackToGame;
Sprite BackToMainMenu;
Sprite BlankPauseMenu;
Sprite FullScreenTickBox;
Sprite SoundEffectTickBox;
Sprite MusicTickBox;
Sprite Opacity;

SoundBuffer PauseMenuOpen;

SoundBuffer PauseMenuClickBuffer;

bool SoundOnPauseMenu = true;
#pragma endregion

#pragma region Level End Menu Textures and Sprites
Texture LostMenuBlankTex;
Texture RetryButtonTex;
Texture RetryButtonHoverTex;
Texture BackToMainMenuLevelEndTex;
Texture BackToMainMenuLevelEndHoverTex;
Texture WinMenuBlankTex;
Texture NextlevelButtonTex;
Texture NextlevelButtonHoverTex;

SoundBuffer LoseAndWinAndPauseBuffer;

Sprite LostMenuBlank;
Sprite RetryButton;

Sprite BackToMainMenuLevelEnd;
Sprite WinMenuBlank;
Sprite NextlevelButton;
#pragma endregion

#pragma region Pause Menu
void LoadPauseMenuTextures() {
    LoseAndWinAndPauseBuffer.loadFromFile("Audio/bleep.ogg");
    PauseMenuOpen.loadFromFile("Audio/pause.ogg");

    PauseMenuClickBuffer.loadFromFile("Audio/buttonclick.ogg");

    MainMenuButtonTex.loadFromFile("Assets/Pause Menu/Main-Menu-Button.png");
    MainMenuButtonTexHover.loadFromFile("Assets/Pause Menu/Main-Menu-Button-Hover.png");
    BackToTheGameButtonTex.loadFromFile("Assets/Pause Menu/Back-To-Game-Button.png");
    BackToTheGameButtonHoverTex.loadFromFile("Assets/Pause Menu/Back-To-Game-Button-Hover.png");
    PauseMenuBlank.loadFromFile("Assets/Pause Menu/Pause-Menu-Blank-2.png");
    OpacityTex.loadFromFile("Assets/Pause Menu/50-Percent-Opacity-Screen.png");

    TickBoxBlankTex.loadFromFile("Assets/Pause Menu/blank.png");
    TickBoxSelectedTex.loadFromFile("Assets/Pause Menu/Selected.png");

}

void SetupPauseMenu()
{
    LoadPauseMenuTextures();

    BackToGame.setTexture(BackToTheGameButtonTex);
    BackToGame.setPosition(537 + offset.x, 486 + offset.y);
    BackToGame.setScale(1.75, 1.75);

    BackToMainMenu.setTexture(MainMenuButtonTex);
    BackToMainMenu.setPosition(555 + offset.x, 433 + offset.y);
    BackToMainMenu.setScale(1.75, 1.75);

    BlankPauseMenu.setTexture(PauseMenuBlank);
    BlankPauseMenu.setOrigin(BlankPauseMenu.getGlobalBounds().width / 2, BlankPauseMenu.getGlobalBounds().height / 2);
    BlankPauseMenu.setScale(1.75, 1.75);
    BlankPauseMenu.setPosition(640 + offset.x, 360 + offset.y);
    Opacity.setTexture(OpacityTex);
    Opacity.setPosition(offset.x, offset.y);

#pragma region tickboxes and options
    if (IsFullScreen)
        FullScreenTickBox.setTexture(TickBoxSelectedTex);
    else
        FullScreenTickBox.setTexture(TickBoxBlankTex);

    FullScreenTickBox.setOrigin(FullScreenTickBox.getGlobalBounds().width / 2, FullScreenTickBox.getGlobalBounds().height / 2);
    FullScreenTickBox.setScale(1.75, 1.75);
    FullScreenTickBox.setPosition(430, 265);

    if (IsSoundEffects)
        SoundEffectTickBox.setTexture(TickBoxSelectedTex);
    else
        SoundEffectTickBox.setTexture(TickBoxBlankTex);

    SoundEffectTickBox.setOrigin(SoundEffectTickBox.getGlobalBounds().width / 2, SoundEffectTickBox.getGlobalBounds().height / 2);
    SoundEffectTickBox.setScale(1.75, 1.75);
    SoundEffectTickBox.setPosition(430, 302);

    if (IsMusic)
        MusicTickBox.setTexture(TickBoxSelectedTex);
    else
        MusicTickBox.setTexture(TickBoxBlankTex);

    MusicTickBox.setOrigin(MusicTickBox.getGlobalBounds().width / 2, MusicTickBox.getGlobalBounds().height / 2);
    MusicTickBox.setScale(1.75, 1.75);
    MusicTickBox.setPosition(430, 339);
#pragma endregion
}

void PauseMenuUpdate()
{
    if (endRSP && Keyboard::isKeyPressed(Keyboard::Escape))
    {
        IsPaused = true;
        if (SoundOnPauseMenu)
        {
            PlaySoundEffect(PauseMenuOpen, false);
            SoundOnPauseMenu = false;
        }
    }
    if (IsPaused && !boss::LevelIsOver)
    {
        if (BackToGame.getGlobalBounds().contains(MouseWorldPostion))
        {
            if (ButtonTapSoundBackToTheGame)
            {
                PlaySoundEffect(LoseAndWinAndPauseBuffer, false);
                ButtonTapSoundBackToTheGame = false;
            }
            BackToGame.setTexture(BackToTheGameButtonHoverTex);
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                PlaySoundEffect(PauseMenuOpen, false);
                PlaySoundEffect(PauseMenuClickBuffer, false);
                SoundOnPauseMenu = true;
                IsPaused = false;
            }
        }
        else
        {
            ButtonTapSoundBackToTheGame = true;
            BackToGame.setTexture(BackToTheGameButtonTex);
        }

        if (BackToMainMenu.getGlobalBounds().contains(MouseWorldPostion))
        {
            if (ButtonTapSoundPauseBackToMainMenu)
            {
                PlaySoundEffect(LoseAndWinAndPauseBuffer, false);
                ButtonTapSoundPauseBackToMainMenu = false;
            }
            BackToMainMenu.setTexture(MainMenuButtonTexHover);
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                PlaySoundEffect(PauseMenuClickBuffer, false);
                IsPaused = false;
                CurrentState = MainMenu;
            }
        }
        else
        {
            ButtonTapSoundPauseBackToMainMenu = true;
            BackToMainMenu.setTexture(MainMenuButtonTex);
        }

#pragma region Update Tick Boxes
        if (IsFullScreen)
            FullScreenTickBox.setTexture(TickBoxSelectedTex);
        else
            FullScreenTickBox.setTexture(TickBoxBlankTex);

        if (IsSoundEffects)
            SoundEffectTickBox.setTexture(TickBoxSelectedTex);
        else
            SoundEffectTickBox.setTexture(TickBoxBlankTex);

        if (IsMusic)
            MusicTickBox.setTexture(TickBoxSelectedTex);
        else
            MusicTickBox.setTexture(TickBoxBlankTex);
#pragma endregion

#pragma region Pause menu options logic
        if (FullScreenTickBox.getGlobalBounds().contains(MouseWorldPostion) && Mouse::isButtonPressed(Mouse::Left))
        {
            if (IsFullScreen && DelayClock.getElapsedTime() >= TickBoxDelay)
            {
                DelayClock.restart();
                IsFullScreen = false;
                changeFullScreenState = true;
            }
            else if (DelayClock.getElapsedTime() >= TickBoxDelay)
            {
                DelayClock.restart();
                IsFullScreen = true;
                changeFullScreenState = true;
            }
        }

        if (SoundEffectTickBox.getGlobalBounds().contains(MouseWorldPostion) && Mouse::isButtonPressed(Mouse::Left))
        {
            if (!IsSoundEffects && DelayClock.getElapsedTime() >= TickBoxDelay)
            {
                DelayClock.restart();
                IsSoundEffects = true;
            }
            else if (DelayClock.getElapsedTime() >= TickBoxDelay)
            {
                DelayClock.restart();
                IsSoundEffects = false;
            }
        }

        if (MusicTickBox.getGlobalBounds().contains(MouseWorldPostion) && Mouse::isButtonPressed(Mouse::Left))
        {
            if (!IsMusic && DelayClock.getElapsedTime() >= TickBoxDelay)
            {
                DelayClock.restart();
                IsMusic = true;
            }
            else if (DelayClock.getElapsedTime() >= TickBoxDelay)
            {
                DelayClock.restart();
                IsMusic = false;
            }
        }
#pragma endregion

    }
}

void DrawPauseMenu(RenderWindow& window)
{
    if (!boss::LevelIsOver)
    {
        window.draw(Opacity);
        window.draw(BlankPauseMenu);
        window.draw(BackToGame);
        window.draw(BackToMainMenu);
        window.draw(FullScreenTickBox);
        window.draw(SoundEffectTickBox);
        window.draw(MusicTickBox);
    }
}
#pragma endregion

#pragma region Level End Menus
void LoadLevelEndTextures() {
    //Button Click
    PauseMenuClickBuffer.loadFromFile("Audio/buttonclick.ogg");

    //lose case
    LoseAndWinAndPauseBuffer.loadFromFile("Audio/bleep.ogg");

    LostMenuBlankTex.loadFromFile("Assets/Lost Menu/lost-menu-blank.png");
    RetryButtonTex.loadFromFile("Assets/Lost Menu/retry-button.png");
    RetryButtonHoverTex.loadFromFile("Assets/Lost Menu/retry-button-hover.png");

    //win case
    WinSoundBuffer.loadFromFile("Audio/pvz jingle.wav");
    
    WinMenuBlankTex.loadFromFile("Assets/Win Menu/win-menu-blank.png");
    NextlevelButtonTex.loadFromFile("Assets/Win Menu/next-level-button.png");
    NextlevelButtonHoverTex.loadFromFile("Assets/Win Menu/next-level-button-hover.png");
    //Game Over
    ThankYouForPlayingTex.loadFromFile("Assets/Win Menu/Game Over.png");
    ThankYouForPlaying.setTexture(ThankYouForPlayingTex);
    ThankYouForPlaying.setOrigin(640, 360);
    ThankYouForPlaying.setPosition(400, 900);
    //main
    BackToMainMenuLevelEndTex.loadFromFile("Assets/Lost Menu/Main-Menu-Button.png");
    BackToMainMenuLevelEndHoverTex.loadFromFile("Assets/Lost Menu/Main-Menu-Button-Hover.png");
}

void LevelEndSetup()
{
    LoadLevelEndTextures();

    BackToMainMenuLevelEnd.setTexture(BackToMainMenuLevelEndTex);
    BackToMainMenuLevelEnd.setPosition(555 + offset.x, 459 + offset.y);
    BackToMainMenuLevelEnd.setScale(1.75, 1.75);

    LostMenuBlank.setTexture(LostMenuBlankTex);
    LostMenuBlank.setOrigin(LostMenuBlank.getGlobalBounds().width / 2, LostMenuBlank.getGlobalBounds().height / 2);
    LostMenuBlank.setScale(1.75, 1.75);
    LostMenuBlank.setPosition(640 + offset.x, 360 + offset.y);

    RetryButton.setTexture(RetryButtonTex);
    RetryButton.setPosition(585 + offset.x, 400 + offset.y);
    RetryButton.setScale(1.75, 1.75);

    WinMenuBlank.setTexture(WinMenuBlankTex);
    WinMenuBlank.setOrigin(WinMenuBlank.getGlobalBounds().width / 2, WinMenuBlank.getGlobalBounds().height / 2);
    WinMenuBlank.setScale(1.75, 1.75);
    WinMenuBlank.setPosition(640 + offset.x, 360 + offset.y);

    NextlevelButton.setTexture(NextlevelButtonTex);
    NextlevelButton.setPosition(555 + offset.x, 400 + offset.y);
    NextlevelButton.setScale(1.75, 1.75);
}

void LevelEndUpdate()
{
    //for testing will be removed in full release
    if (Keyboard::isKeyPressed(Keyboard::PageUp))
    {
        IsPaused = true;
        boss::LevelIsOver = true;
        boss::WinLevel = true;
    }
    if (Keyboard::isKeyPressed(Keyboard::PageDown))
    {
        IsPaused = true;
        boss::LevelIsOver = true;
        boss::WinLevel = false;
    }

    if (boss::LevelIsOver)
    {

        /*if (winSound)
        {
            PlaySoundEffect(WinSoundBuffer,false);

        }*/
        if (boss::WinLevel)
        {
            if (CurrentState == Level5 && boss::LevelIsOver && boss::WinLevel)
            {
                if (ThankYouForPlaying.getPosition().y > 310)
                {
                    ThankYouForPlaying.move(0, -7);
                }
                else if (Mouse::isButtonPressed(Mouse::Left))
                {
                    PlaySoundEffect(PauseMenuClickBuffer, false);
                    CurrentState = MainMenu;
                }

                MaxLevelWon = Level5;
            }
            else
            {
                if (CurrentState == Level1)
                {
                    MaxLevelWon = Level1;
                }
                else if (CurrentState == Level2)
                {
                    MaxLevelWon = Level2;
                }
                else if (CurrentState == Level3)
                {
                    MaxLevelWon = Level3;
                }
                else if (CurrentState == Level4)
                {
                    MaxLevelWon == Level4;
                }
                else if (CurrentState == Level5)
                {
                    MaxLevelWon = Level5;
                }

                

                //go to next level button logic
                if (NextlevelButton.getGlobalBounds().contains(MouseWorldPostion))
                {
                    if (ButtonTapSoundNextLevel)
                    {
                        PlaySoundEffect(LoseAndWinAndPauseBuffer, false);
                        ButtonTapSoundNextLevel = false;
                    }
                    NextlevelButton.setTexture(NextlevelButtonHoverTex);
                    if (Mouse::isButtonPressed(Mouse::Left))
                    {
                        PlaySoundEffect(PauseMenuClickBuffer, false);
                        if (CurrentState == Level1)
                        {
                            SwitchState(Level2);
                            MaxLevelWon = Level2;
                        }
                        else if (CurrentState == Level2)
                        {
                            SwitchState(Level3);
                            MaxLevelWon = Level3;
                        }
                        else if (CurrentState == Level3)
                        {
                            SwitchState(Level4);
                            MaxLevelWon = Level4;
                        }
                        else if (CurrentState == Level4)
                        {
                            SwitchState(Level5);
                            MaxLevelWon = Level5;
                        }
                        // opens file and wrties level number
                        ofstream SaveLevelProgressWrite("lastlevelreached.txt");
                        LastLevelReached = MaxLevelWon;
                        SaveLevelProgressWrite << LastLevelReached - 1;
                        SaveLevelProgressWrite.close();

                        cout << "====================== " << (LastLevelReached - 1) << " ======================" << endl;
                    }
                }
                else
                {
                    ButtonTapSoundNextLevel = true;
                    NextlevelButton.setTexture(NextlevelButtonTex);
                }

                //back to main menu button logic
                if (BackToMainMenuLevelEnd.getGlobalBounds().contains(MouseWorldPostion))
                {
                    if (ButtonTapSoundWinMainMenu)
                    {
                        PlaySoundEffect(LoseAndWinAndPauseBuffer, false);
                        ButtonTapSoundWinMainMenu = false;
                    }
                    BackToMainMenuLevelEnd.setTexture(BackToMainMenuLevelEndHoverTex);
                    if (Mouse::isButtonPressed(Mouse::Left))
                    {
                        PlaySoundEffect(PauseMenuClickBuffer, false);
                        CurrentState = MainMenu;
                    }
                }
                else
                {
                    ButtonTapSoundWinMainMenu = true;
                    BackToMainMenuLevelEnd.setTexture(BackToMainMenuLevelEndTex);
                }
            }
        }
        if (!boss::WinLevel)
        {
            //back to main menu button logic
            if (BackToMainMenuLevelEnd.getGlobalBounds().contains(MouseWorldPostion))
            {
                if (ButtonTapSoundLoseBackToMainMenu)
                {
                    PlaySoundEffect(LoseAndWinAndPauseBuffer, false);
                    ButtonTapSoundLoseBackToMainMenu = false;
                }
                BackToMainMenuLevelEnd.setTexture(BackToMainMenuLevelEndHoverTex);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    PlaySoundEffect(PauseMenuClickBuffer, false);
                    CurrentState = MainMenu;
                }
            }
            else
            {
                ButtonTapSoundLoseBackToMainMenu = true;
                BackToMainMenuLevelEnd.setTexture(BackToMainMenuLevelEndTex);
            }

            //retry button logic
            if (RetryButton.getGlobalBounds().contains(MouseWorldPostion))
            {
                RetryButton.setTexture(RetryButtonHoverTex);

                if (ButtonTapSoundRetry)
                {
                    PlaySoundEffect(LoseAndWinAndPauseBuffer, false);
                    ButtonTapSoundRetry = false;
                }

                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    PlaySoundEffect(PauseMenuClickBuffer, false);

                    if (CurrentState == Level1)
                    {
                        SwitchState(Level1);
                    }
                    else if (CurrentState == Level2)
                    {
                        SwitchState(Level2);
                    }
                    else if (CurrentState == Level3)
                    {
                        SwitchState(Level3);
                    }
                    else if (CurrentState == Level4)
                    {
                        SwitchState(Level4);
                    }
                    else if (CurrentState == Level5)
                    {
                        SwitchState(Level5);
                    }
                }
            }
            else
            {
                ButtonTapSoundRetry = true;
                RetryButton.setTexture(RetryButtonTex);
            }
        }
    }
}

void DrawLevelEnd(RenderWindow& window)
{
    if (boss::WinLevel)
    {
        if (CurrentState == Level5)
        {
            window.draw(ThankYouForPlaying);
        }
        else
        {
            window.draw(Opacity);
            window.draw(WinMenuBlank);
            window.draw(NextlevelButton);
            window.draw(BackToMainMenuLevelEnd);
        }
    }
    else
    {
        window.draw(Opacity);
        window.draw(LostMenuBlank);
        window.draw(RetryButton);
        window.draw(BackToMainMenuLevelEnd);
    }

}
#pragma endregion

//handle the code of each level
#pragma region Level Functions

#pragma region Level 1
void StartLevel1()
{
    bool isNight = false;
    bool isfog = false;
    bool onRoof = false;
    bool isBossFight = false;
    setupWaveData(isNight);
    StartPlantingAndCurrencySystem(offset, isNight, onRoof, isBossFight);
    startZombiePositions(100, 1, 1);
    StartAnimationNS::startAnimation(isNight, onRoof, isfog);
}
void UpdateLevel1(RenderWindow& window)
{
    UpdatePlantingAndCurrencySystem(MouseWorldPostion, offset);
    StartAnimationNS::updateAnimation(window);

    level(2, 4, 12.0f, 1); // 2, 10 , 10;

    Plants_Zombies::UpdatePlants(Plants_Zombies::zombie_array, MouseWorldPostion);
}
void DrawLevel1(RenderWindow& window)
{
    StartAnimationNS::Renderstartanimation(window);
    Plants_Zombies::DrawPlantsAndProjectiles(window);
    DrawPlantingAndCurrencySystem(window);
    DrawWavesAndZombies(window);
}
#pragma endregion

#pragma region Level 2
void StartLevel2()
{
    bool isNight = true;
    bool onRoof = false;
    bool isfog = false;
    bool isBossFight = false;
    setupWaveData(isNight);
    StartPlantingAndCurrencySystem(offset, isNight, onRoof, isBossFight);
    startZombiePositions(100, 2, 2);
    StartAnimationNS::startAnimation(isNight, onRoof, isfog);
}
void UpdateLevel2(RenderWindow& window)
{
    UpdatePlantingAndCurrencySystem(MouseWorldPostion, offset);
    StartAnimationNS::updateAnimation(window);

    level(2, 20, 7.0f, 2); // 2, 15 , 10

    Plants_Zombies::UpdatePlants(Plants_Zombies::zombie_array, MouseWorldPostion);
}
void DrawLevel2(RenderWindow& window)
{
    StartAnimationNS::Renderstartanimation(window);
    Plants_Zombies::DrawPlantsAndProjectiles(window);
    DrawPlantingAndCurrencySystem(window);
    DrawWavesAndZombies(window);
}
#pragma endregion

#pragma region Level 3
void StartLevel3()
{
    bool isNight = true;
    bool onRoof = false;
    bool isfog = true;
    bool isBossFight = false;
    setupWaveData(isNight);
    StartPlantingAndCurrencySystem(offset, isNight, onRoof, isBossFight);
    startZombiePositions(100, 3, 3);
    StartAnimationNS::startAnimation(isNight, onRoof, isfog);
}
void UpdateLevel3(RenderWindow& window)
{
    UpdatePlantingAndCurrencySystem(MouseWorldPostion, offset);
    StartAnimationNS::updateAnimation(window);

    level(3, 4, 10.0f, 3); // 3 , 35 , 7

    Plants_Zombies::UpdatePlants(Plants_Zombies::zombie_array, MouseWorldPostion);
}
void DrawLevel3(RenderWindow& window)
{
    StartAnimationNS::Renderstartanimation(window);
    Plants_Zombies::DrawPlantsAndProjectiles(window);
    DrawPlantingAndCurrencySystem(window);
    DrawWavesAndZombies(window);
}
#pragma endregion

#pragma region Level 4
void StartLevel4()
{
    bool isNight = false;
    bool onRoof = true;
    bool isfog = false;
    bool isBossFight = false;
    setupWaveData(isNight);
    StartPlantingAndCurrencySystem(offset, isNight, onRoof, isBossFight);
    startZombiePositions(100, 3, 3);
    StartAnimationNS::startAnimation(isNight, onRoof, isfog);

}
void UpdateLevel4(RenderWindow& window)
{
    UpdatePlantingAndCurrencySystem(MouseWorldPostion, offset);
    StartAnimationNS::updateAnimation(window);

    level(3, 2, 10.0f, 4); // 3 , 35 , 7

    Plants_Zombies::UpdatePlants(Plants_Zombies::zombie_array, MouseWorldPostion);
}
void DrawLevel4(RenderWindow& window)
{
    StartAnimationNS::Renderstartanimation(window);
    Plants_Zombies::DrawPlantsAndProjectiles(window);
    DrawPlantingAndCurrencySystem(window);
    DrawWavesAndZombies(window);
}
#pragma endregion

#pragma region Level 5
void StartLevel5()
{
    bool isNight = true;
    bool onRoof = true;
    bool isfog = false;
    bool isBossFight = true;
    setupWaveData(isNight);
    StartPlantingAndCurrencySystem(offset, isNight, onRoof, isBossFight);
    startZombiePositions(100, 3, 3);
    StartAnimationNS::startAnimation(isNight, onRoof, isfog);
    boss::SetupBossData();

}
void UpdateLevel5(RenderWindow& window)
{
    UpdatePlantingAndCurrencySystem(MouseWorldPostion, offset);
    StartAnimationNS::updateAnimation(window);
    boss::UpdateBossLogic();
    // level(3, 35, 10.0f, 3); // 3 , 35 , 7

    Plants_Zombies::UpdateBossPlants(MouseWorldPostion);
}
void DrawLevel5(RenderWindow& window)
{
    StartAnimationNS::Renderstartanimation(window);
    Plants_Zombies::DrawPlantsAndProjectiles(window);
    DrawWavesAndZombies(window);
    boss::DrawBoss(window);
    DrawPlantingAndCurrencySystem(window);
    boss::endlevel();
}
#pragma endregion
#pragma endregion

// switches the state of the game and calls the start function of the new state
void SwitchState(State NewState)
{
    boss::LevelIsOver = false;
    boss::WinLevel = false;
    IsPaused = false;
    jackMusicOn = false;
    CurrentState = NewState;

    if (CurrentState == Level1)
    {
        StartLevel1();
    }
    else if (CurrentState == Level2)
    {
        StartLevel2();
    }
    else if (CurrentState == Level3)
    {
        StartLevel3();
    }
    else if (CurrentState == Level4)
    {
        StartLevel4();
    }
    else if (CurrentState == Level5)
    {
        StartLevel5();
    }
}