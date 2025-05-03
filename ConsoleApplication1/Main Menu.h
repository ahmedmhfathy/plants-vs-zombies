
// hello from main menu
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "Game Manager.h"
#include "Tools.h"

using namespace std;
using namespace sf;

#pragma region Texture Declaration
Texture MainMenuBackGroundTex;
Texture StartButtonTex;
Texture StartButtonHoverTex;
Texture CreditButtonTex;
Texture CreditButtonHoverTex;
Texture QuitButtonTex;
Texture QuitButtonHoverTex;
Texture LoadingScreenTex;
Texture LoadingTextTex;
Texture BackTOMainMenuTex;
Texture BackTOMainMenuHoverTex;
#pragma endregion

#pragma region Sprite Delaration
Sprite MainMenuBackGround;
Sprite StartButton;
Sprite CreditButton;
Sprite QuitButton;
Sprite BackTOMainMenuButton;
#pragma endregion

#pragma region Sounds
SoundBuffer HoverMainMenu;
Sound HoverMainMenuSound;
SoundBuffer CreditsTran;
SoundBuffer ButtonSoundBuffer;
Sound ButtonSound;
Sound CreditsTranSound;
SoundBuffer ClickBuffer;
Sound Click;
#pragma endregion

bool SoundStart = false;
bool SoundCredits = false;
bool SoundQuit = false;
bool SoundButton = false;

bool ShowCredits = false;
bool startAnim = false;
Clock animClock;
Time MainMenuAnimationDuration = seconds(1.75);

View MainMenuCamera(FloatRect(0, 0, 1280, 720));

///loads the textures for the main menu
void LoadMainMenuTex()
{
    HoverMainMenu.loadFromFile("Audio/bleep.ogg");
    HoverMainMenuSound.setBuffer(HoverMainMenu);
    CreditsTran.loadFromFile("Audio/tunetank.com_flash-screen.wav");
    CreditsTranSound.setBuffer(CreditsTran);
    ButtonSoundBuffer.loadFromFile("Audio/bleep.ogg");
    ButtonSound.setBuffer(ButtonSoundBuffer);
    ClickBuffer.loadFromFile("Audio/buttonclick.ogg");
    Click.setBuffer(ClickBuffer);

    MainMenuBackGroundTex.loadFromFile("Assets/Main Menu/mainmenu-no-buttons-2.png");
    StartButtonTex.loadFromFile("Assets/Main Menu/startbutton-default.png");
    StartButtonHoverTex.loadFromFile("Assets/Main Menu/startbutton-hover.png");
    CreditButtonTex.loadFromFile("Assets/Main Menu/creditsbutton-default.png");
    CreditButtonHoverTex.loadFromFile("Assets/Main Menu/creditsbutton-hover.png");
    QuitButtonTex.loadFromFile("Assets/Main Menu/quitbutton-default.png");
    QuitButtonHoverTex.loadFromFile("Assets/Main Menu/quitbutton-hover.png");
    BackTOMainMenuTex.loadFromFile("Assets/Main Menu/back to main menu button-default.png");
    BackTOMainMenuHoverTex.loadFromFile("Assets/Main Menu/back to main menu button-hover.png");
}

void MainMenuStart(RenderWindow& window)
{
    MainMenuCamera.setCenter(640, 360);
    window.setView(MainMenuCamera);

    LoadMainMenuTex();

#pragma region setup elements
    //sets the textures
    MainMenuBackGround.setTexture(MainMenuBackGroundTex);
    StartButton.setTexture(StartButtonTex);
    CreditButton.setTexture(CreditButtonTex);
    QuitButton.setTexture(QuitButtonTex);
    BackTOMainMenuButton.setTexture(BackTOMainMenuTex);
    //set up the back to main menu button
    BackTOMainMenuButton.setPosition(2185, 436);
    //set up the start button
    StartButton.setOrigin({ StartButton.getLocalBounds().width / 2, StartButton.getLocalBounds().height / 2 });
    StartButton.rotate(6.7);
    StartButton.setPosition({ 1050, 275 });
    //set up the credits button
    CreditButton.setOrigin({ CreditButton.getLocalBounds().width / 2, CreditButton.getLocalBounds().height / 2 });
    CreditButton.rotate(11);
    CreditButton.setPosition({ 1035, 275 + 115 });
    //set up the quit button
    QuitButton.setOrigin({ QuitButton.getLocalBounds().width / 2, QuitButton.getLocalBounds().height / 2 });
    QuitButton.rotate(13.2);
    QuitButton.setPosition({ 1023, 275 + 115 + 100 });
#pragma endregion
}

void MainMenuUpdate(Vector2f mouse_pos, RenderWindow& window)
{
    window.setView(MainMenuCamera);

    //main menu buttons and animation
    if (!ShowCredits)
    {
        // animation from credits ---> main menu
        if (MainMenuCamera.getCenter().x > 640)
        {
            float startValue = 1920, endValue = 640;
            if (startAnim == false)
            {
                animClock.restart();
                startAnim = true;
            }
            MainMenuCamera.setCenter(easeInOut(CubicEaseInOut, startValue, endValue, animClock, MainMenuAnimationDuration), 360);
        }
        else
        {
            startAnim = false;
        }

        //main menu buttons
        if (mouse_pos.x >= 884 && mouse_pos.x <= 1211 && mouse_pos.y >= 202 && mouse_pos.y <= 310)
        {
            StartButton.setTexture(StartButtonHoverTex);
            if (SoundStart)
            {
            HoverMainMenuSound.play();
            SoundStart = false;
            }
            if (!startAnim && Mouse::isButtonPressed(Mouse::Left))
            {
                Click.play();
                SwitchState(Level1);
            }
        }
        else
        {
            StartButton.setTexture(StartButtonTex);
            SoundStart = true;
        }

        if (mouse_pos.x >= 880 && mouse_pos.x <= 1190 && mouse_pos.y >= 349 && mouse_pos.y <= 410) //creidts button animation
        {
            CreditButton.setTexture(CreditButtonHoverTex);
            if (SoundCredits)
            {
                HoverMainMenuSound.play();
                SoundCredits = false;
            }
            if (!startAnim && Mouse::isButtonPressed(Mouse::Left))
            {
                Click.play();
                //CreditsTranSound.play();
                ShowCredits = true;
            }
        }
        else
        {
            CreditButton.setTexture(CreditButtonTex);
            SoundCredits = true;
        }

        if (mouse_pos.x >= 891 && mouse_pos.x <= 1159 && mouse_pos.y >= 450 && mouse_pos.y <= 557)
        {
            if (SoundQuit)
            {
                HoverMainMenuSound.play();
                SoundQuit = false;
            }
            if (!startAnim && Mouse::isButtonPressed(Mouse::Left))
            {
                Click.play();
                window.close();
            }

            QuitButton.setTexture(QuitButtonHoverTex);
        }
        else
        {
            QuitButton.setTexture(QuitButtonTex);
            SoundQuit = true;
        }
    }
    else //credits menu buttons and animation
    {
        //animate from main menu ---> credits
        if (MainMenuCamera.getCenter().x < 1920)
        {
            float startValue = 640, endValue = 1920;
            if (startAnim == false)
            {
                animClock.restart();
                startAnim = true;
            }
            MainMenuCamera.setCenter(easeInOut(CubicEaseInOut, startValue, endValue, animClock, MainMenuAnimationDuration), 360);
        }
        else
        {
            startAnim = false;
        }

        //credits menu buttons
        if (BackTOMainMenuButton.getGlobalBounds().contains(mouse_pos))
        {
            if (SoundButton)
            {
                ButtonSound.play();
                SoundButton = false;
            }
            BackTOMainMenuButton.setTexture(BackTOMainMenuHoverTex);
            if (!startAnim && Mouse::isButtonPressed(Mouse::Left))
            {
                Click.play();
                //CreditsTranSound.play();
                ShowCredits = false;
            }
        }
        else
        {
            BackTOMainMenuButton.setTexture(BackTOMainMenuTex);
            SoundButton = true;
        }
    }
}

//draws the main menu
void DrawMainMenu(RenderWindow& window)
{
    window.draw(MainMenuBackGround);
    window.draw(StartButton);
    window.draw(CreditButton);
    window.draw(QuitButton);
    window.draw(BackTOMainMenuButton);
}