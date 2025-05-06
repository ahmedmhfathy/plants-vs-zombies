#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "StartAnimation.h"
#include "Wave System.h"
#include"planting system.h"

using namespace std;
using namespace sf;

enum State { MainMenu, Level1, Level2, Level3 } CurrentState;
void SwitchState(State NewState);

bool ButtonTapSoundNextLevel = false;
bool ButtonTapSoundWinMainMenu = false;
bool ButtonTapSoundPauseBackToMainMenu = false;
bool ButtonTapSoundBackToTheGame = false;
bool ButtonTapSoundRetry = false;
bool ButtonTapSoundLoseBackToMainMenu = false;
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
Texture OpacityTex;

Sprite BackToGame;
Sprite BackToMainMenu;
Sprite BlankPauseMenu;
Sprite Opacity;

SoundBuffer PauseMenuOpen;
Sound PauseMenuOpenSound;

SoundBuffer PauseMenuClickBuffer;
Sound PauseMenuClick;

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

Sprite LostMenuBlank;
Sprite RetryButton;

SoundBuffer LoseAndWinAndPauseBuffer;
Sound LoseAndWinAndPause;

Sprite BackToMainMenuLevelEnd;

Sprite WinMenuBlank;
Sprite NextlevelButton;
SoundBuffer WinSoundBuffer;
Sound WinSound;
#pragma endregion

#pragma region Pause Menu
void LoadPauseMenuTextures() {
    LoseAndWinAndPauseBuffer.loadFromFile("Audio/bleep.ogg");
    PauseMenuOpen.loadFromFile("Audio/pause.ogg");

    PauseMenuClickBuffer.loadFromFile("Audio/buttonclick.ogg");
    PauseMenuClick.setBuffer(PauseMenuClickBuffer);

    MainMenuButtonTex.loadFromFile("Assets/Pause Menu/Main-Menu-Button.png");
    MainMenuButtonTexHover.loadFromFile("Assets/Pause Menu/Main-Menu-Button-Hover.png");
    BackToTheGameButtonTex.loadFromFile("Assets/Pause Menu/Back-To-Game-Button.png");
    BackToTheGameButtonHoverTex.loadFromFile("Assets/Pause Menu/Back-To-Game-Button-Hover.png");
    PauseMenuBlank.loadFromFile("Assets/Pause Menu/Pause-Menu-Blank.png");
    OpacityTex.loadFromFile("Assets/Pause Menu/50-Percent-Opacity-Screen.png");
}

void SetupPauseMenu()
{
    LoadPauseMenuTextures();

    LoseAndWinAndPause.setBuffer(LoseAndWinAndPauseBuffer);
    PauseMenuOpenSound.setBuffer(PauseMenuOpen);

    BackToGame.setTexture(BackToTheGameButtonTex);
    BackToGame.setPosition(537 + offset.x, 459 + offset.y);
    BackToGame.setScale(1.75, 1.75);

    BackToMainMenu.setTexture(MainMenuButtonTex);
    BackToMainMenu.setPosition(555 + offset.x, 400 + offset.y);
    BackToMainMenu.setScale(1.75, 1.75);

    BlankPauseMenu.setTexture(PauseMenuBlank);
    BlankPauseMenu.setOrigin(BlankPauseMenu.getGlobalBounds().width / 2, BlankPauseMenu.getGlobalBounds().height / 2);
    BlankPauseMenu.setScale(1.75, 1.75);
    BlankPauseMenu.setPosition(640 + offset.x, 360 + offset.y);
    Opacity.setTexture(OpacityTex);
    Opacity.setPosition(offset.x, offset.y);
}

void PauseMenuUpdate()
{
    if (endRSP && Keyboard::isKeyPressed(Keyboard::Escape))
    {
        IsPaused = true;
        if (SoundOnPauseMenu)
        {
        PauseMenuOpenSound.play();
        SoundOnPauseMenu = false;
        }
    }
    if (IsPaused && !LevelIsOver)
    {
        if (BackToGame.getGlobalBounds().contains(MouseWorldPostion))
        {
            if (ButtonTapSoundBackToTheGame)
            {
                LoseAndWinAndPause.play();
                ButtonTapSoundBackToTheGame = false;
            }
            BackToGame.setTexture(BackToTheGameButtonHoverTex);
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                PauseMenuOpenSound.play();
                PauseMenuClick.play();
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
                LoseAndWinAndPause.play();
                ButtonTapSoundPauseBackToMainMenu = false;
            }
            BackToMainMenu.setTexture(MainMenuButtonTexHover);
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                PauseMenuClick.play();
                IsPaused = false;
                CurrentState = MainMenu;
            }
        }
        else
        {
            ButtonTapSoundPauseBackToMainMenu = true;
            BackToMainMenu.setTexture(MainMenuButtonTex);
        }
    }
}

void DrawPauseMenu(RenderWindow& window)
{
    if (!LevelIsOver)
    {
        window.draw(Opacity);
        window.draw(BlankPauseMenu);
        window.draw(BackToGame);
        window.draw(BackToMainMenu);
    }
}
#pragma endregion

#pragma region Level End Menus
void LoadLevelEndTextures() {
    //Button Click
    PauseMenuClickBuffer.loadFromFile("Audio/buttonclick.ogg");
    PauseMenuClick.setBuffer(PauseMenuClickBuffer);

    //lose case
    LoseAndWinAndPauseBuffer.loadFromFile("Audio/bleep.ogg");
    LoseAndWinAndPause.setBuffer(LoseAndWinAndPauseBuffer);
    LostMenuBlankTex.loadFromFile("Assets/Lost Menu/lost-menu-blank.png");
    RetryButtonTex.loadFromFile("Assets/Lost Menu/retry-button.png");
    RetryButtonHoverTex.loadFromFile("Assets/Lost Menu/retry-button-hover.png");

    //win case
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
};

void LevelEndUpdate()
{
    if (Keyboard::isKeyPressed(Keyboard::W))
    {
        IsPaused = true;
        LevelIsOver = true;
        WinLevel = true;
    }
    if (Keyboard::isKeyPressed(Keyboard::S))
    {
        IsPaused = true;
        LevelIsOver = true;
        WinLevel = false;
    }

    if (LevelIsOver)
    {
        if (WinLevel)
        {
            if(CurrentState==Level3&&LevelIsOver&&WinLevel)
            {
                if (ThankYouForPlaying.getPosition().y > 310)
                {
                    ThankYouForPlaying.move(0, -7);
                }
                else if (Mouse::isButtonPressed(Mouse::Left))
                {
                    PauseMenuClick.play();
                    CurrentState = MainMenu;
                }
            }
            else
            {
                if (NextlevelButton.getGlobalBounds().contains(MouseWorldPostion))
                {
                    if (ButtonTapSoundNextLevel)
                    {
                        LoseAndWinAndPause.play();
                        ButtonTapSoundNextLevel = false;
                    }
                    NextlevelButton.setTexture(NextlevelButtonHoverTex);
                    if (Mouse::isButtonPressed(Mouse::Left))
                    {
                        PauseMenuClick.play();
                        if (CurrentState == Level1)
                        {
                            SwitchState(Level2);
                        }
                        else if (CurrentState == Level2)
                        {
                            SwitchState(Level3);
                        }
                    }
                }
                else
                {
                    ButtonTapSoundNextLevel = true;
                    NextlevelButton.setTexture(NextlevelButtonTex);
                }

                if (BackToMainMenuLevelEnd.getGlobalBounds().contains(MouseWorldPostion))
                {
                    if (ButtonTapSoundWinMainMenu)
                    {
                        LoseAndWinAndPause.play();
                        ButtonTapSoundWinMainMenu = false;
                    }
                    BackToMainMenuLevelEnd.setTexture(BackToMainMenuLevelEndHoverTex);
                    if (Mouse::isButtonPressed(Mouse::Left))
                    {
                        PauseMenuClick.play();
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
        if (!WinLevel)
        {
            if (BackToMainMenuLevelEnd.getGlobalBounds().contains(MouseWorldPostion))
            {
                if (ButtonTapSoundLoseBackToMainMenu)
                {
                    LoseAndWinAndPause.play();
                    ButtonTapSoundLoseBackToMainMenu = false;
                }
                BackToMainMenuLevelEnd.setTexture(BackToMainMenuLevelEndHoverTex);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    PauseMenuClick.play();
                    CurrentState = MainMenu;
                }
            }
            else
            {
                ButtonTapSoundLoseBackToMainMenu = true;
                BackToMainMenuLevelEnd.setTexture(BackToMainMenuLevelEndTex);
            }


            if (RetryButton.getGlobalBounds().contains(MouseWorldPostion))
            {
                if (ButtonTapSoundRetry)
                {
                    LoseAndWinAndPause.play();
                    ButtonTapSoundRetry = false;
                }
                RetryButton.setTexture(RetryButtonHoverTex);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    PauseMenuClick.play();
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
    if (WinLevel)
    {
        if (CurrentState == Level3)
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
void StartLevel1()
{
    setupWaveData();
    StartPlantingAndCurrencySystem(offset);
    startZombiePositions(100);
    StartAnimationNS::startAnimation();
}
void UpdateLevel1(RenderWindow& window)
{
    UpdatePlantingAndCurrencySystem(MouseWorldPostion, offset);
    StartAnimationNS::updateAnimation(window);

    level(2, 5, 7.0f);

    Plants_Zombies::UpdatePlants(Plants_Zombies::zombie_array, MouseWorldPostion);
}
void DrawLevel1(RenderWindow& window)
{
    StartAnimationNS::Renderstartanimation(window);
    Plants_Zombies::DrawPlantsAndProjectiles(window);
    DrawPlantingAndCurrencySystem(window);
    DrawWavesAndZombies(window);
}

void StartLevel2()
{
    setupWaveData();
    StartPlantingAndCurrencySystem(offset);
    startZombiePositions(100);
    StartAnimationNS::startAnimation();
}
void UpdateLevel2(RenderWindow& window)
{
    UpdatePlantingAndCurrencySystem(MouseWorldPostion, offset);
    StartAnimationNS::updateAnimation(window);

    level(2, 5, 5.0f);

    Plants_Zombies::UpdatePlants(Plants_Zombies::zombie_array, MouseWorldPostion);
}
void DrawLevel2(RenderWindow& window)
{
    StartAnimationNS::Renderstartanimation(window);
    Plants_Zombies::DrawPlantsAndProjectiles(window);
    DrawPlantingAndCurrencySystem(window);
    DrawWavesAndZombies(window);
}

void StartLevel3()
{
    setupWaveData();
    StartPlantingAndCurrencySystem(offset);
    startZombiePositions(100);
    StartAnimationNS::startAnimation();
    
}
void UpdateLevel3(RenderWindow& window)
{
    UpdatePlantingAndCurrencySystem(MouseWorldPostion, offset);
    StartAnimationNS::updateAnimation(window);

    level(3, 10, 5.0f);

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

// switches the state of the game and calls the start function of the new state
void SwitchState(State NewState)    
{
    LevelIsOver = false;
    WinLevel = false;
    IsPaused = false;
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
}