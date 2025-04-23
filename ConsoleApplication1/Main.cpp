// aywa yaba leader Ali Ba4a ya welad :(nefse al3ab valoo,REPO,any other games)
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "Main Menu.h"
#include "Game Manager.h"
using namespace std;
using namespace sf;

RenderWindow window(VideoMode(1280, 720), "Plant vs zombie");

#pragma region Function Declaration
void Start();
void Update();
void RenderScreen();
#pragma endregion

float deltaTime;
int main()
{
    Start();
    Clock clock;
    while (window.isOpen()) // game loop
    {
#pragma region MISC
        deltaTime = clock.restart().asSeconds();
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
    CurrentState = MainMenu;
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    MainMenuStart(window);
    SetupPauseMenu();
}
void Update()
{

    Mousepostion = Mouse::getPosition(window);
    MouseWorldPostion = window.mapPixelToCoords(Mousepostion);
    if (CurrentState == MainMenu)
    {
        MainMenuUpdate(MouseWorldPostion, window);
    }
    else
    {
        if (CurrentState == Level1 && !IsPaused)
        {
            UpdateLevel1();
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
    }
}
// this function will be used to render the screen
void RenderScreen()
{
    window.clear();

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

        if (IsPaused)
        {
            DrawPauseMenu(window);
        }
    }
    window.display();
}
