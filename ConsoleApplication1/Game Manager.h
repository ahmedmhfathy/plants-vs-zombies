#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "plants.h"

using namespace std;
using namespace sf;

void SwitchState(String NewState);

Vector2i Mousepostion;
Vector2f MouseWorldPostion;
String CurrentState;
bool IsPaused = false;
int ZombieHealth = 100;

#pragma region LoadPauseMenuTex
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
#pragma endregion

void SetupPauseMenu()
{
    MainMenuButtonTex.loadFromFile("Assets/Pause Menu/Main-Menu-Button.png");
    MainMenuButtonTexHover.loadFromFile("Assets/Pause Menu/Main-Menu-Button-Hover.png");
    BackToTheGameButtonTex.loadFromFile("Assets/Pause Menu/Back-To-Game-Button.png");
    BackToTheGameButtonHoverTex.loadFromFile("Assets/Pause Menu/Back-To-Game-Button-Hover.png");
    PauseMenuBlank.loadFromFile("Assets/Pause Menu/Pause-Menu-Blank.png");
    OpacityTex.loadFromFile("Assets/Pause Menu/50-Percent-Opacity-Screen.png");

    BackToGame.setTexture(BackToTheGameButtonTex);
    BackToMainMenu.setTexture(MainMenuButtonTex);
    BackToMainMenu.setPosition(555, 400);
    BackToMainMenu.setScale(1.75, 1.75);
    BackToGame.setPosition(537, 459);
    BackToGame.setScale(1.75, 1.75);
    BlankPauseMenu.setTexture(PauseMenuBlank);

    BlankPauseMenu.setOrigin(BlankPauseMenu.getGlobalBounds().width / 2, BlankPauseMenu.getGlobalBounds().height / 2);
    BlankPauseMenu.setScale(1.75, 1.75);
    BlankPauseMenu.setPosition(640, 360);
    Opacity.setTexture(OpacityTex);
}

void PauseMenuUpdate()
{
    if (Keyboard::isKeyPressed(Keyboard::Escape))
    {

        IsPaused = true;

    }
    if (IsPaused)
    {
        if (BackToGame.getGlobalBounds().contains(MouseWorldPostion))
        {
            BackToGame.setTexture(BackToTheGameButtonHoverTex);
            if (Mouse::isButtonPressed(Mouse::Left))
            {
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
                CurrentState = "Main Menu";
            }
        }
        else
        {
            BackToMainMenu.setTexture(MainMenuButtonTex);
        }


    }
}

RectangleShape box({ 100, 100 }); // zombie PLACE HOLDER


//handle the code of each level
void DrawPauseMenu(RenderWindow& window)
{
    window.draw(Opacity);
    window.draw(BlankPauseMenu);
    window.draw(BackToGame);
    window.draw(BackToMainMenu);
}
#pragma region Level Functions
void StartLevel1()
{
    khalid::PlantProjectilesARR.clear();
    khalid::StartPlants();

    box.setPosition({ 1000, 100 });
    box.setOrigin({ 50, 50 });
}
void UpdateLevel1()
{
    box.setPosition(MouseWorldPostion);
    khalid::UpdatePlants(box, IsPaused);

    if (Keyboard::isKeyPressed(Keyboard::Backspace))
    {
        SwitchState("Main Menu");
    }
    for (int i = 0; i < 4; i++)
    {
        if (khalid::PlantsArray[i].shape.getGlobalBounds().intersects(box.getGlobalBounds()))
        {
            khalid::PlantsArray[i].takeDmg(1);
        }
    }  
}
void DrawLevel1(RenderWindow& window)
{
    khalid::DrawPlantsAndProjectiles(window);
    window.draw(box);
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
void SwitchState(String NewState)
{
    CurrentState = NewState;

    if (CurrentState == "Level 1")
    {
        StartLevel1();
    }
    else if (CurrentState == "Level 2")
    {
        StartLevel2();
    }
    else if (CurrentState == "Level 3")
    {
        StartLevel3();
    }
}
