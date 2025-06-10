#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "Main Menu.h"
#include "Game Manager.h"
#include "StartAnimation.h"
#include "planting system.h"
#include "Tools.h"
#include "Game Settings And Audio.h"
using namespace std;
using namespace sf;

RenderWindow window(VideoMode(1280, 720), "Plants VS Zombies");
RenderWindow fullScreenWindow(VideoMode(1280, 720), "Plants VS Zombies", Style::Fullscreen);

SoundBuffer GameMusicBuffer;
Sound GameMusic;

#pragma region Function Declaration
void Start();
void Update();
void RenderScreen();
#pragma endregion

int main()
{
    Start();
    while (window.isOpen()) // game loop
    {
        #pragma region MISC
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
    GameMusicBuffer.loadFromFile("Audio/Plants vs. Zombies BackGround.wav");
    GameMusic.setBuffer(GameMusicBuffer);
    GameMusic.setVolume(5);
    GameMusic.setLoop(true);
    GameMusic.play();

    Plants_Zombies::LoadPlantTexturesAndSounds(); //textures loaded here once
    Plants_Zombies::LoadZombieTextures();
    StartAnimationNS::LoadStartAndWaveAnimationTextures();
    LoadSelectionTexture();

    CurrentState = MainMenu;

    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    MainMenuStart(window); //textures loaded here once

    SetupPauseMenu(); //textures loaded here once
    LevelEndSetup(); //textures loaded here once

    wasPausedLastFrame = IsPaused;
}

void Update()
{
    //gets mouse world position from screen position
    Mousepostion = Mouse::getPosition(window);
    MouseWorldPostion = window.mapPixelToCoords(Mousepostion);

    if (Mouse::isButtonPressed(Mouse::Left))
    {
        cout << int(MouseWorldPostion.x) << "    " << int(MouseWorldPostion.y) << endl;
    }

    DeltaTimeManager(IsPaused);


    if (IsMusic)
    {
        GameMusic.setVolume(5);
    }
    if (!IsMusic)
    {
        GameMusic.setVolume(0);
    }

    //calls the update function depending on current state and pause state
    if (CurrentState == MainMenu)
    {   
        /*if (IsMusic || IsMusicO) 
        {
        GameMusic.setVolume(5);
        }
        else if (!IsMusic || !IsMusicO)
        {
        GameMusic.setVolume(0);
        }*/
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
            UpdateLevel2(window);
        }
        else if (CurrentState == Level3 && !IsPaused)
        {
            UpdateLevel3(window);
        }

        PauseMenuUpdate();
        LevelEndUpdate();
    }
}

// this function will be used to render the screen depending on current state
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
