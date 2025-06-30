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
#include "Boss Logic.h"
#include "Brightness Shader.h"
using namespace std;
using namespace sf;

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
    myBrightnessShader.loadFromFile("Brightness.frag", Shader::Fragment);
    //myBrightnessShader.setUniform("brightness", normalBrightness);

    SetupGameSettings();

    Plants_Zombies::LoadPlantTexturesAndSounds(); //textures loaded here once
    Plants_Zombies::LoadZombieTextures();
    StartAnimationNS::LoadStartAndWaveAnimationTextures();
    LoadSelectionTexture();
	boss::LoadBossTexturesAndAudio(); //textures loaded here once

    CurrentState = MainMenu;

    MainMenuStart(window); //textures loaded here once

    SetupPauseMenu(); //textures loaded here once
    LevelEndSetup(); //textures loaded here once
}

void Update()
{
    DeltaTimeManager();
    GameSettingsUpdate();
    SoundsUpdate();

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
            UpdateLevel2(window);
        }
        else if (CurrentState == Level3 && !IsPaused)
        {
            UpdateLevel3(window);
        }
        else if(CurrentState == Level4 && !IsPaused)
        {
			UpdateLevel4(window);
        }
        else if (CurrentState == Level5 && !IsPaused)
        {
            UpdateLevel5(window);
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
        else if (CurrentState == Level4)
        {
			DrawLevel4(window);
        }
        else if (CurrentState == Level5)
        {
			DrawLevel5(window);
        }

        if (IsPaused && !boss::LevelIsOver)
        {
            DrawPauseMenu(window);
        }
        if (boss::LevelIsOver)
        {
            DrawLevelEnd(window);
        }
    }

    window.display();
}
