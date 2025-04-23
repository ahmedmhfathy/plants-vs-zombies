// ANA FEL LABORYA 
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
    CurrentState = "Main Menu";
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    MainMenuStart(window);
    SetupPauseMenu();
}
void Update()
{

    Mousepostion = Mouse::getPosition(window);
    MouseWorldPostion = window.mapPixelToCoords(Mousepostion);
    if (CurrentState == "Main Menu")
    {
        MainMenuUpdate(MouseWorldPostion, window);
    }
    else
    {
        if (CurrentState == "Level 1" && !IsPaused)
        {
            UpdateLevel1();
        }
        else if (CurrentState == "Level 2" && !IsPaused)
        {
            UpdateLevel2();
        }
        else if (CurrentState == "Level 3" && !IsPaused)
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

    if (CurrentState == "Main Menu")
    {
        DrawMainMenu(window);
    }
    else
    {
        if (CurrentState == "Level 1")
        {
            DrawLevel1(window);
        }
        else if (CurrentState == "Level 2")
        {
            DrawLevel2(window);
        }
        else if (CurrentState == "Level 3")
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
