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

bool LevelIsOver = false;
bool WinLevel = false;
bool IsPaused = false;

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

Sprite BackToMainMenuLevelEnd;

Sprite WinMenuBlank;
Sprite NextlevelButton;
#pragma endregion

#pragma region Pause Menu
void LoadPauseMenuTextures() {
    PauseMenuOpen.loadFromFile("Audio/tunetank.com_menu-pop.wav");
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
            BackToGame.setTexture(BackToTheGameButtonHoverTex);
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                PauseMenuOpenSound.play();
                SoundOnPauseMenu = true;
                IsPaused = false;
            }
        }
        else
        {
            BackToGame.setTexture(BackToTheGameButtonTex);
        }

        if (BackToMainMenu.getGlobalBounds().contains(MouseWorldPostion))
        {
            BackToMainMenu.setTexture(MainMenuButtonTexHover);
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                IsPaused = false;
                CurrentState = MainMenu;
            }
        }
        else
        {
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
    //lose case
    LostMenuBlankTex.loadFromFile("Assets/Lost Menu/lost-menu-blank.png");
    RetryButtonTex.loadFromFile("Assets/Lost Menu/retry-button.png");
    RetryButtonHoverTex.loadFromFile("Assets/Lost Menu/retry-button-hover.png");

    //win case
    WinMenuBlankTex.loadFromFile("Assets/Win Menu/win-menu-blank.png");
    NextlevelButtonTex.loadFromFile("Assets/Win Menu/next-level-button.png");
    NextlevelButtonHoverTex.loadFromFile("Assets/Win Menu/next-level-button-hover.png");

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
            if (NextlevelButton.getGlobalBounds().contains(MouseWorldPostion))
            {
                NextlevelButton.setTexture(NextlevelButtonHoverTex);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    if (CurrentState == Level1)
                    {
                        SwitchState(Level2);
                    }
                    else if (CurrentState == Level2)
                    {
                        SwitchState(Level3);
                    }
                    else
                    {
                        //Ty for playing();
                    }
                }
            }
            else
            {
                NextlevelButton.setTexture(NextlevelButtonTex);
            }

            if (BackToMainMenuLevelEnd.getGlobalBounds().contains(MouseWorldPostion))
            {
                BackToMainMenuLevelEnd.setTexture(BackToMainMenuLevelEndHoverTex);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    CurrentState = MainMenu;
                }
            }
            else
            {
                BackToMainMenuLevelEnd.setTexture(BackToMainMenuLevelEndTex);
            }


        }
        if (!WinLevel)
        {
            if (BackToMainMenuLevelEnd.getGlobalBounds().contains(MouseWorldPostion))
            {
                BackToMainMenuLevelEnd.setTexture(BackToMainMenuLevelEndHoverTex);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    CurrentState = MainMenu;
                }
            }
            else
            {
                BackToMainMenuLevelEnd.setTexture(BackToMainMenuLevelEndTex);
            }


            if (RetryButton.getGlobalBounds().contains(MouseWorldPostion))
            {
                RetryButton.setTexture(RetryButtonHoverTex);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
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
                RetryButton.setTexture(RetryButtonTex);
            }
        }

    }
}

void DrawLevelEnd(RenderWindow& window)
{
    if (WinLevel)
    {
        window.draw(Opacity);
        window.draw(WinMenuBlank);
        window.draw(NextlevelButton);
        window.draw(BackToMainMenuLevelEnd);
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
    StartPlantingAndCurrencySystem(offset);

    StartAnimationNS::startAnimation();
}
void UpdateLevel1(RenderWindow& window)
{
    UpdatePlantingAndCurrencySystem(MouseWorldPostion, offset);
    StartAnimationNS::updateAnimation(window);

    if (!IsPaused)
    {
        level(2, 4, 7.0f);
    }

    Plants_Zombies::UpdatePlants(Plants_Zombies::zombie_array, MouseWorldPostion);
}
void DrawLevel1(RenderWindow& window)
{
    StartAnimationNS::Renderstartanimation(window);
    DrawPlantingAndCurrencySystem(window);
    Plants_Zombies::DrawPlantsAndProjectiles(window);
    drawzombies(window);
}

void StartLevel2()
{

}
void UpdateLevel2()
{

}
void DrawLevel2(RenderWindow& window)
{

}

void StartLevel3()
{

}
void UpdateLevel3()
{

}
void DrawLevel3(RenderWindow& window)
{

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