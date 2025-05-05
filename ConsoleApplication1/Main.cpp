#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "Main Menu.h"
#include "Game Manager.h"
#include "StartAnimation.h"
#include"planting system.h"
using namespace std;
using namespace sf;

RenderWindow window(VideoMode(1280, 720), "Plant vs zombie");

#pragma region Function Declaration
void Start();
void Update();
void RenderScreen();
#pragma endregion

float DeltaTime;
int main()
{
    Start();
    Clock clock;
    while (window.isOpen()) // game loop
    {
#pragma region MISC
        DeltaTime = clock.restart().asSeconds();
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
#pragma endregion

        Update();
        RenderScreen();
    }
    return 0;
}

void Start()
{
    Plants_Zombies::LoadPlantTextures(); //textures loaded here once
    Plants_Zombies::LoadZombieTextures();
    LoadSelectionTexture();

    CurrentState = MainMenu;

    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    MainMenuStart(window); //textures loaded here once
    //StartLevel1();

    SetupPauseMenu(); //textures loaded here once
    LevelEndSetup(); //textures loaded here once
}

void Update()
{
    //gets mouse world position from screen position
    Mousepostion = Mouse::getPosition(window);
    MouseWorldPostion = window.mapPixelToCoords(Mousepostion);

    //calls the update function depending on current state and pause state
    if (CurrentState == MainMenu)
    {
        MainMenuUpdate(MouseWorldPostion, window);
    }
    else
    {
        if (CurrentState == Level1 && !IsPaused)
        {
            UpdateLevel1(window);
        }
        else if (CurrentState == Level2 && !IsPaused)
        {
            UpdateLevel2();
        }
        else if (CurrentState == Level3 && !IsPaused)
        {
            UpdateLevel3();
        }

        PauseMenuUpdate();
        LevelEndUpdate();
    }
}
// this function will be used to render the screen
void RenderScreen()
{
    window.clear();

    //draws screen depending on current state
    if (CurrentState == MainMenu)
    {
        DrawMainMenu(window);
    }
    else
    {
        if (CurrentState == Level1)
        {
            DrawLevel1(window);
        }
        else if (CurrentState == Level2)
        {
            DrawLevel2(window);
        }
        else if (CurrentState == Level3)
        {
            DrawLevel3(window);
        }

        if (IsPaused && !LevelIsOver)
        {
            DrawPauseMenu(window);
        }
        if (LevelIsOver)
        {
            DrawLevelEnd(window);
        }
    }
    window.display();
}
