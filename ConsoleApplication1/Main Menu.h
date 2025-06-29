#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "Game Settings And Audio.h"
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
Texture BackTOMainMenuCreditsTex;
Texture BackTOMainMenuCreditsHoverTex;
Texture BackTOMainMenuTex;
Texture BackTOMainMenuHoverTex;
Texture Level1Tex;
Texture Level1HoverTex;
Texture Level2Tex;
Texture Level2HoverTex;
Texture Level3Tex;
Texture Level3HoverTex;
Texture Level4Tex;
Texture Level4HoverTex;
Texture Level5Tex;
Texture Level5HoverTex;
Texture LevelLockTex;
Texture OptionsButtonTex;
Texture OptionsButtonHoverTex;
Texture OptionsBlankTex;
Texture OpacityOPtions;
Texture BackFromOptionsTex;
Texture BackFromOptionsHoverTex;
Texture TickBoxBlankTexO;
Texture TickBoxSelectedTexO;
#pragma endregion

#pragma region Sprite Delaration
Sprite MainMenuBackGround;
Sprite StartButton;
Sprite CreditButton;
Sprite QuitButton;
Sprite BackTOMainMenuCreditsButton;
Sprite Level1Button;
Sprite Level2Button;
Sprite Level3Button;
Sprite Level4Button;
Sprite Level5Button;
Sprite Level2Lock;
Sprite Level3Lock;
Sprite Level4Lock;
Sprite Level5Lock;
Sprite BackTOMainMenuButtonLS;
Sprite OptionsButton;
Sprite OptionOpacityTex;
Sprite OptionsBlank;
Sprite FullScreenTickBoxO;
Sprite SoundEffectTickBoxO;
Sprite MusicTickBoxO;
Sprite BackFromOptions;
#pragma endregion

#pragma region Sounds
SoundBuffer HoverMainMenu;
SoundBuffer ClickBuffer;
Sound HoverMainMenuSound;
Sound Click;
#pragma endregion

#pragma region Booleans
// sound
bool soundFinished = true;
bool SoundStart = false;
bool SoundOptions = false;
bool SoundCredit = false;
bool SoundQuit = false;
bool SoundButton = false;
bool SoundLevel1Button = false;
bool SoundLevel2Button = false;
bool SoundLevel3Button = false;
bool SoundLevel4Button = false;
bool SoundLevel5Button = false;
bool BackFromOptionsSound = false;

// animation and logic
bool ShowCredits = false;
bool ShowOptions = false;
bool startAnim = false;
bool startAnimLevel = false;
bool ShowLevelSelectionMenu = false;
#pragma endregion

Clock animClock;
Time MainMenuAnimationDuration = seconds(1.75);

Clock DelayClockO;
Time TickBoxDelayO = seconds(.25);

View MainMenuCamera(FloatRect(0, 0, 1280, 720));

///loads the textures for the main menu
void LoadMainMenuTex()
{
    HoverMainMenu.loadFromFile("Audio/bleep.ogg");
    HoverMainMenuSound.setBuffer(HoverMainMenu);
    ClickBuffer.loadFromFile("Audio/buttonclick.ogg");
    Click.setBuffer(ClickBuffer);

    MainMenuBackGroundTex.loadFromFile("Assets/Main Menu/pvs main menu (khalid version).png");
    StartButtonTex.loadFromFile("Assets/Main Menu/startbutton-default.png");
    StartButtonTex.setSmooth(true);
    StartButtonHoverTex.loadFromFile("Assets/Main Menu/startbutton-hover.png");
    StartButtonHoverTex.setSmooth(true);
    CreditButtonTex.loadFromFile("Assets/Main Menu/creditsbutton-default-2.png");
    CreditButtonTex.setSmooth(true);
    CreditButtonHoverTex.loadFromFile("Assets/Main Menu/creditsbutton-hover-2.png");
    CreditButtonHoverTex.setSmooth(true);
    QuitButtonTex.loadFromFile("Assets/Main Menu/quitbutton-default.png");
    QuitButtonTex.setSmooth(true);
    QuitButtonHoverTex.loadFromFile("Assets/Main Menu/quitbutton-hover.png");
    QuitButtonHoverTex.setSmooth(true);
    BackTOMainMenuCreditsTex.loadFromFile("Assets/Main Menu/back to main menu button-default.png");
    BackTOMainMenuCreditsHoverTex.loadFromFile("Assets/Main Menu/back to main menu button-hover.png");
    BackTOMainMenuTex.loadFromFile("Assets/Main Menu/back-default.png");
    BackTOMainMenuHoverTex.loadFromFile("Assets/Main Menu/back-hover.png");
    OptionsButtonTex.loadFromFile("Assets/Main Menu/optionsbutton-default.png");
    OptionsButtonTex.setSmooth(true);
    OptionsButtonHoverTex.loadFromFile("Assets/Main Menu/optionsbutton-hover.png");
    OptionsButtonHoverTex.setSmooth(true);

    //Level Selection 
    Level1Tex.loadFromFile("Assets/Main Menu/Level 1.png");
    Level1HoverTex.loadFromFile("Assets/Main Menu/Level 1 hover.png");
    Level2Tex.loadFromFile("Assets/Main Menu/Level 2.png");
    Level2HoverTex.loadFromFile("Assets/Main Menu/Level 2 hover.png");
    Level3Tex.loadFromFile("Assets/Main Menu/Level 3.png");
    Level3HoverTex.loadFromFile("Assets/Main Menu/Level 3 hover.png");
    Level4Tex.loadFromFile("Assets/Main Menu/level 4-default.png");
    Level4HoverTex.loadFromFile("Assets/Main Menu/level 4-hover.png");
    Level5Tex.loadFromFile("Assets/Main Menu/level 5-default.png");
    Level5HoverTex.loadFromFile("Assets/Main Menu/level 5-hover.png");
    LevelLockTex.loadFromFile("Assets/Main Menu/lock.png");

    //Options
    OptionsBlankTex.loadFromFile("Assets/Main Menu/Options-Menu-Blank.png");
    OpacityOPtions.loadFromFile("Assets/Pause Menu/50-Percent-Opacity-Screen.png");
    BackFromOptionsTex.loadFromFile("Assets/Main Menu/Options-Backbutton-default.png");
    BackFromOptionsHoverTex.loadFromFile("Assets/Main Menu/Options-Backbutton-hover.png");

    TickBoxBlankTexO.loadFromFile("Assets/Main Menu/blank.png");
    TickBoxSelectedTexO.loadFromFile("Assets/Main Menu/Selected.png");
}

void MainMenuStart(RenderWindow& window)
{
    jackMusicOn = false;
    MaxLevelWon = Level4;

    MainMenuCamera.setCenter(640, 360);
    window.setView(MainMenuCamera);
    LoadMainMenuTex();

#pragma region setup elements
    //sets the textures
    MainMenuBackGround.setTexture(MainMenuBackGroundTex);
    StartButton.setTexture(StartButtonTex);
    CreditButton.setTexture(CreditButtonTex);
    QuitButton.setTexture(QuitButtonTex);
    BackTOMainMenuCreditsButton.setTexture(BackTOMainMenuCreditsTex);
    OptionsButton.setTexture(OptionsButtonTex);
    //set up the back to main menu button
    BackTOMainMenuCreditsButton.setPosition(2185, 436);
    //set up the start button
    StartButton.setOrigin({ StartButton.getLocalBounds().width / 2, StartButton.getLocalBounds().height / 2 });
    StartButton.rotate(6.7);
    StartButton.setPosition({ 1050, 275 });
    //set up the Option button
    OptionsButton.setOrigin({ OptionsButton.getLocalBounds().width / 2, OptionsButton.getLocalBounds().height / 2 });
    OptionsButton.rotate(11);
    OptionsButton.setPosition({ 1035, 275 + 115 });
    //set up the credits button
    CreditButton.setOrigin({ CreditButton.getLocalBounds().width / 2, CreditButton.getLocalBounds().height / 2 });
    CreditButton.setPosition({ 1081, 640 });
    //set up the quit button
    QuitButton.setOrigin({ QuitButton.getLocalBounds().width / 2, QuitButton.getLocalBounds().height / 2 });
    QuitButton.rotate(13.2);
    QuitButton.setPosition({ 1023, 275 + 115 + 100 });
    //set up level Selection buttons
    //Level 1
    Level1Button.setTexture(Level1Tex);
    Level1Button.setOrigin({ Level1Button.getLocalBounds().width / 2, Level1Button.getLocalBounds().height / 2 });
    Level1Button.setPosition(288, 845);
    //Level 2
    Level2Button.setTexture(Level2Tex);
    Level2Button.setOrigin({ Level2Button.getLocalBounds().width / 2, Level2Button.getLocalBounds().height / 2 });
    Level2Button.setPosition(288, 965);
    //Level 3
    Level3Button.setTexture(Level3Tex);
    Level3Button.setOrigin({ Level3Button.getLocalBounds().width / 2, Level3Button.getLocalBounds().height / 2 });
    Level3Button.setPosition(288, 1087);
    //Level 4
    Level4Button.setTexture(Level4Tex);
    Level4Button.setOrigin({ Level4Button.getLocalBounds().width / 2, Level4Button.getLocalBounds().height / 2 });
    Level4Button.setPosition(633, 840);
    //Level 5
    Level5Button.setTexture(Level5Tex);
    Level5Button.setOrigin({ Level5Button.getLocalBounds().width / 2, Level5Button.getLocalBounds().height / 2 });
    Level5Button.setPosition(633, 963);
    //Back to main menu 
    BackTOMainMenuButtonLS.setTexture(BackTOMainMenuTex);
    BackTOMainMenuButtonLS.setOrigin({ BackTOMainMenuButtonLS.getLocalBounds().width / 2, BackTOMainMenuButtonLS.getLocalBounds().height / 2 });
    BackTOMainMenuButtonLS.setPosition(633, 1083);
    //locks
    Level2Lock.setTexture(LevelLockTex);
    Level2Lock.setPosition(375, 965);
    Level3Lock.setTexture(LevelLockTex);
    Level3Lock.setPosition(375, 1087);
    Level4Lock.setTexture(LevelLockTex);
    Level4Lock.setPosition(725, 840);
    Level5Lock.setTexture(LevelLockTex);
    Level5Lock.setPosition(725, 965);

#pragma region Options menu setup
    //blank menu
    OptionsBlank.setTexture(OptionsBlankTex);
    OptionsBlank.setOrigin(OptionsBlank.getGlobalBounds().width / 2, OptionsBlank.getGlobalBounds().height / 2);
    OptionsBlank.setScale(2, 2);
    OptionsBlank.setPosition(640, 360);
    //opacity bg
    OptionOpacityTex.setTexture(OpacityOPtions);
    OptionOpacityTex.setPosition(0, 0);
    //back button
    BackFromOptions.setTexture(BackFromOptionsTex);
    BackFromOptions.setOrigin(BackFromOptions.getGlobalBounds().width / 2, BackFromOptions.getGlobalBounds().height / 2);
    BackFromOptions.setScale(2.25, 2.25);
    BackFromOptions.setPosition(638, 497);

    //tickboxes
    //fullscreen tickbox
    FullScreenTickBoxO.setTexture(TickBoxBlankTexO);
    FullScreenTickBoxO.setOrigin(FullScreenTickBoxO.getGlobalBounds().width / 2, FullScreenTickBoxO.getGlobalBounds().height / 2);
    FullScreenTickBoxO.setScale(2, 2);
    FullScreenTickBoxO.setPosition(750, 335);
    //sound effect tickbox
    SoundEffectTickBoxO.setTexture(TickBoxSelectedTexO);
    SoundEffectTickBoxO.setOrigin(SoundEffectTickBoxO.getGlobalBounds().width / 2, SoundEffectTickBoxO.getGlobalBounds().height / 2);
    SoundEffectTickBoxO.setScale(2, 2);
    SoundEffectTickBoxO.setPosition(750, 385);
    //music tick box
    MusicTickBoxO.setTexture(TickBoxSelectedTexO);
    MusicTickBoxO.setOrigin(MusicTickBoxO.getGlobalBounds().width / 2, MusicTickBoxO.getGlobalBounds().height / 2);
    MusicTickBoxO.setScale(2, 2);
    MusicTickBoxO.setPosition(750, 435);
#pragma endregion
#pragma endregion
}

void MainMenuUpdate(Vector2f mouse_pos, RenderWindow& window)
{
    jackMusicOn = false;
    window.setView(MainMenuCamera);

    float randPitch[3] = { 0.85, 1, 1.15 };

    //main menu buttons and animation
    if (!ShowCredits && !ShowLevelSelectionMenu)
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

        // animation from level select ---> main menu
        if (MainMenuCamera.getCenter().y > 360)
        {
            float startValue = 1080, endValue = 360;
            if (startAnimLevel == false)
            {
                animClock.restart();
                startAnimLevel = true;
            }
            MainMenuCamera.setCenter(640, easeInOut(CubicEaseInOut, startValue, endValue, animClock, MainMenuAnimationDuration));
        }
        else
        {
            startAnimLevel = false;
        }

#pragma region Main menu Buttons
        //start adventure button
        if (mouse_pos.x >= 884 && mouse_pos.x <= 1211 && mouse_pos.y >= 202 && mouse_pos.y <= 310 && !ShowOptions)
        {
            StartButton.setTexture(StartButtonHoverTex);
            if (SoundStart)
            {
                PlaySoundEffect(HoverMainMenu, true);
                //HoverMainMenuSound.setPitch(randPitch[rand() % 3]);
                //HoverMainMenuSound.play();
                SoundStart = false;
            }
            if (!startAnim && Mouse::isButtonPressed(Mouse::Left) && !startAnimLevel)
            {
                PlaySoundEffect(ClickBuffer, true);
                //Click.setPitch(randPitch[rand() % 3]);
                //Click.play();
                ShowLevelSelectionMenu = true;
            }
        }
        else
        {
            StartButton.setTexture(StartButtonTex);
            SoundStart = true;
        }

        if (mouse_pos.x >= 880 && mouse_pos.x <= 1190 && mouse_pos.y >= 349 && mouse_pos.y <= 410 && !ShowOptions) //creidts button animation
        {
            OptionsButton.setTexture(OptionsButtonHoverTex);
            if (SoundOptions)
            {
                PlaySoundEffect(HoverMainMenu, true);
                //HoverMainMenuSound.setPitch(randPitch[rand() % 3]);
                //HoverMainMenuSound.play();
                SoundOptions = false;
            }
            if (!startAnim && Mouse::isButtonPressed(Mouse::Left) && !startAnimLevel)
            {
                PlaySoundEffect(ClickBuffer, true);
                //Click.setPitch(randPitch[rand() % 3]);
                //Click.play();
                ShowOptions = true;
            }
        }
        else
        {
            OptionsButton.setTexture(OptionsButtonTex);
            SoundOptions = true;
        }


        if (mouse_pos.x >= 891 && mouse_pos.x <= 1159 && mouse_pos.y >= 450 && mouse_pos.y <= 557 && !ShowOptions)
        {
            if (SoundQuit)
            {
                PlaySoundEffect(HoverMainMenu, true);
                //HoverMainMenuSound.setPitch(randPitch[rand() % 3]);
                //HoverMainMenuSound.play();
                SoundQuit = false;
            }
            if (!startAnim && Mouse::isButtonPressed(Mouse::Left) && !startAnimLevel)
            {
                PlaySoundEffect(ClickBuffer, true);
                //Click.setPitch(randPitch[rand() % 3]);
                //Click.play();
                window.close();
            }

            QuitButton.setTexture(QuitButtonHoverTex);
        }
        else
        {
            QuitButton.setTexture(QuitButtonTex);
            SoundQuit = true;
        }

        if (CreditButton.getGlobalBounds().contains(mouse_pos) && !ShowOptions)
        {
            CreditButton.setTexture(CreditButtonHoverTex);
            if (SoundCredit)
            {
                PlaySoundEffect(HoverMainMenu, true);
                //ButtonSound.setPitch(randPitch[rand() % 3]);
                //ButtonSound.play();
                SoundCredit = false;
            }
            if (!startAnim && Mouse::isButtonPressed(Mouse::Left) && !startAnimLevel)
            {
                PlaySoundEffect(ClickBuffer, true);
                //Click.setPitch(randPitch[rand() % 3]);
                //Click.play();
                ShowCredits = true;
            }
        }
        else
        {
            CreditButton.setTexture(CreditButtonTex);
            SoundCredit = true;
        }
#pragma endregion        
    }
    else if (ShowCredits && !ShowLevelSelectionMenu) //credits menu buttons and animation
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
        if (BackTOMainMenuCreditsButton.getGlobalBounds().contains(mouse_pos))
        {
            if (SoundButton)
            {
                PlaySoundEffect(HoverMainMenu, true);
                //ButtonSound.setPitch(randPitch[rand() % 3]);
                //ButtonSound.play();
                SoundButton = false;
            }
            BackTOMainMenuCreditsButton.setTexture(BackTOMainMenuCreditsHoverTex);
            if (!startAnim && Mouse::isButtonPressed(Mouse::Left))
            {
                PlaySoundEffect(ClickBuffer, true);
                //Click.setPitch(randPitch[rand() % 3]);
                //Click.play();
                ShowCredits = false;
            }
        }
        else
        {
            BackTOMainMenuCreditsButton.setTexture(BackTOMainMenuCreditsTex);
            SoundButton = true;
        }
    }
    else if (!ShowCredits && ShowLevelSelectionMenu)
    {
        // animation from main menu ---> level select
        if (MainMenuCamera.getCenter().y < 1080)
        {
            float startValue = 360, endValue = 1080;
            if (startAnimLevel == false)
            {
                animClock.restart();
                startAnimLevel = true;
            }
            MainMenuCamera.setCenter(640, easeInOut(CubicEaseInOut, startValue, endValue, animClock, MainMenuAnimationDuration));
        }
        else
        {
            startAnimLevel = false;
        }

#pragma region Buttons
        //Back to main menu
        if (BackTOMainMenuButtonLS.getGlobalBounds().contains(mouse_pos))
        {
            if (SoundButton)
            {
                PlaySoundEffect(HoverMainMenu, true);
                //ButtonSound.setPitch(randPitch[rand() % 3]);
                //ButtonSound.play();
                SoundButton = false;
            }
            BackTOMainMenuButtonLS.setTexture(BackTOMainMenuHoverTex);
            if (!startAnim && Mouse::isButtonPressed(Mouse::Left) && !startAnimLevel)
            {
                PlaySoundEffect(ClickBuffer, true);
                //Click.setPitch(randPitch[rand() % 3]);
                //Click.play();
                ShowLevelSelectionMenu = false;
                ShowCredits = false;
            }
        }
        else
        {
            BackTOMainMenuButtonLS.setTexture(BackTOMainMenuTex);
            SoundButton = true;
        }
        //level 1 button
        if (Level1Button.getGlobalBounds().contains(mouse_pos))
        {
            if (SoundLevel1Button)
            {
                PlaySoundEffect(HoverMainMenu, true);
                //ButtonSound.setPitch(randPitch[rand() % 3]);
                //ButtonSound.play();
                SoundLevel1Button = false;
            }
            Level1Button.setTexture(Level1HoverTex);
            if (!startAnim && Mouse::isButtonPressed(Mouse::Left) && !startAnimLevel)
            {
                PlaySoundEffect(ClickBuffer, true);
                //Click.setPitch(randPitch[rand() % 3]);
                //Click.play();

                SwitchState(Level1);

                ShowLevelSelectionMenu = false;
                MainMenuCamera.setCenter(640, 360);
            }
        }
        else
        {
            Level1Button.setTexture(Level1Tex);
            SoundLevel1Button = true;
        }
        //level 2 button
        if (Level2Button.getGlobalBounds().contains(mouse_pos) && MaxLevelWon >= Level1)
        {
            if (SoundLevel2Button)
            {
                PlaySoundEffect(HoverMainMenu, true);
                //ButtonSound.setPitch(randPitch[rand() % 3]);
                //ButtonSound.play();
                SoundLevel2Button = false;
            }

            Level2Button.setTexture(Level2HoverTex);
            Level2Lock.setScale(0, 0);

            if (!startAnim && Mouse::isButtonPressed(Mouse::Left) && !startAnimLevel)
            {
                PlaySoundEffect(ClickBuffer, true);
                //Click.setPitch(randPitch[rand() % 3]);
                //Click.play();

                SwitchState(Level2);

                ShowLevelSelectionMenu = false;
                MainMenuCamera.setCenter(640, 360);
            }

        }
        else if (MaxLevelWon < Level1)
        {
            Level2Lock.setScale(1, 1);
        }
        else
        {
            Level2Button.setTexture(Level2Tex);
            Level2Lock.setScale(0, 0);
            SoundLevel2Button = true;
        }
        //level 3 button
        if (Level3Button.getGlobalBounds().contains(mouse_pos) && MaxLevelWon >= Level2)
        {
            if (SoundLevel3Button)
            {
                PlaySoundEffect(HoverMainMenu, true);
                //ButtonSound.setPitch(randPitch[rand() % 3]);
                //ButtonSound.play();
                SoundLevel3Button = false;
            }

            Level3Button.setTexture(Level3HoverTex);
            Level3Lock.setScale(0, 0);

            if (!startAnim && Mouse::isButtonPressed(Mouse::Left) && !startAnimLevel)
            {
                PlaySoundEffect(ClickBuffer, true);
                //Click.setPitch(randPitch[rand() % 3]);
                //Click.play();

                SwitchState(Level3);

                ShowLevelSelectionMenu = false;
                MainMenuCamera.setCenter(640, 360);
            }
        }
        else if (MaxLevelWon < Level2)
        {
            Level3Lock.setScale(1, 1);
        }
        else
        {
            Level3Button.setTexture(Level3Tex);
            SoundLevel3Button = true;
            Level3Lock.setScale(0, 0);
        }
        //level 4 button
        if (Level4Button.getGlobalBounds().contains(mouse_pos) && MaxLevelWon >= Level3)
        {
            if (SoundLevel4Button)
            {
                PlaySoundEffect(HoverMainMenu, true);
                //ButtonSound.setPitch(randPitch[rand() % 3]);
                //ButtonSound.play();
                SoundLevel4Button = false;
            }
            Level4Button.setTexture(Level4HoverTex);
            if (!startAnim && Mouse::isButtonPressed(Mouse::Left) && !startAnimLevel)
            {
                PlaySoundEffect(ClickBuffer, true);
                //Click.setPitch(randPitch[rand() % 3]);
                //Click.play();

                SwitchState(Level4);

                ShowLevelSelectionMenu = false;
                MainMenuCamera.setCenter(640, 360);
            }
        }
        else if (MaxLevelWon < Level3)
        {
            Level4Lock.setScale(1, 1);
        }
        else
        {
            Level4Lock.setScale(0, 0);
            Level4Button.setTexture(Level4Tex);
            SoundLevel4Button = true;
        }
        //level 5 button
        if (Level5Button.getGlobalBounds().contains(mouse_pos) && MaxLevelWon >= Level4)
        {
            if (SoundLevel5Button)
            {
                PlaySoundEffect(HoverMainMenu, true);
                //ButtonSound.setPitch(randPitch[rand() % 3]);
                //ButtonSound.play();
                SoundLevel5Button = false;
            }
            Level5Button.setTexture(Level5HoverTex);
            if (!startAnim && Mouse::isButtonPressed(Mouse::Left) && !startAnimLevel)
            {
                PlaySoundEffect(ClickBuffer, true);
                //Click.setPitch(randPitch[rand() % 3]);
                //Click.play();

                SwitchState(Level5);

                ShowLevelSelectionMenu = false;
                MainMenuCamera.setCenter(640, 360);
            }
        }
        else if (MaxLevelWon < Level4)
        {
            Level5Lock.setScale(1, 1);
        }
        else
        {
            Level5Button.setTexture(Level5Tex);
            Level5Lock.setScale(0, 0);
            SoundLevel5Button = true;
        }
#pragma endregion
    }

#pragma region Options
    if (ShowOptions)
    {
#pragma region update TickBoxes
        if (IsFullScreen)
            FullScreenTickBoxO.setTexture(TickBoxSelectedTexO);
        else
            FullScreenTickBoxO.setTexture(TickBoxBlankTexO);

        if (IsSoundEffects)
            SoundEffectTickBoxO.setTexture(TickBoxSelectedTexO);
        else
            SoundEffectTickBoxO.setTexture(TickBoxBlankTexO);

        if (IsMusic)
            MusicTickBoxO.setTexture(TickBoxSelectedTexO);
        else
            MusicTickBoxO.setTexture(TickBoxBlankTexO);
#pragma endregion

        if (BackFromOptions.getGlobalBounds().contains(mouse_pos))
        {
            BackFromOptions.setTexture(BackFromOptionsHoverTex);
            if (BackFromOptionsSound)
            {
                PlaySoundEffect(HoverMainMenu, true);
                //ButtonSound.setPitch(randPitch[rand() % 3]);
                //ButtonSound.play();
                BackFromOptionsSound = false;
            }

            if (Mouse::isButtonPressed(Mouse::Left))
            {
                PlaySoundEffect(ClickBuffer, true);
                //Click.setPitch(randPitch[rand() % 3]);
                //Click.play();
                ShowOptions = false;
            }
        }
        else
        {
            BackFromOptions.setTexture(BackFromOptionsTex);
            BackFromOptionsSound = true;
        }

        if (FullScreenTickBoxO.getGlobalBounds().contains(mouse_pos) && Mouse::isButtonPressed(Mouse::Left))
        {
            if (IsFullScreen && DelayClock.getElapsedTime() >= TickBoxDelayO)
            {
                DelayClock.restart();
                IsFullScreen = false;
                changeFullScreenState = true;
            }
            else if (DelayClock.getElapsedTime() >= TickBoxDelayO)
            {
                DelayClock.restart();
                IsFullScreen = true;
                changeFullScreenState = true;
            }
        }

        if (SoundEffectTickBoxO.getGlobalBounds().contains(mouse_pos) && Mouse::isButtonPressed(Mouse::Left))
        {
            if (!IsSoundEffects && DelayClockO.getElapsedTime() >= TickBoxDelayO)
            {
                DelayClockO.restart();
                IsSoundEffects = true;
            }
            else if (DelayClockO.getElapsedTime() >= TickBoxDelayO)
            {
                DelayClockO.restart();
                IsSoundEffects = false;
            }
        }

        if (MusicTickBoxO.getGlobalBounds().contains(mouse_pos) && Mouse::isButtonPressed(Mouse::Left))
        {
            if (!IsMusic && DelayClockO.getElapsedTime() >= TickBoxDelayO)
            {
                DelayClockO.restart();
                IsMusic = true;
            }
            else if (DelayClockO.getElapsedTime() >= TickBoxDelayO)
            {
                DelayClockO.restart();
                IsMusic = false;
            }
        }
    }
#pragma endregion
}

//draws the main menu
void DrawMainMenu(RenderWindow& window)
{
    window.draw(MainMenuBackGround);
    window.draw(StartButton);
    window.draw(OptionsButton);
    window.draw(QuitButton);
    window.draw(CreditButton);
    window.draw(BackTOMainMenuCreditsButton);
    window.draw(Level1Button);
    window.draw(Level2Button);
    window.draw(Level3Button);
    window.draw(Level4Button);
    window.draw(Level5Button);
    window.draw(BackTOMainMenuButtonLS);
    window.draw(Level2Lock);
    window.draw(Level3Lock);
    window.draw(Level4Lock);
    window.draw(Level5Lock);

    if (ShowOptions)
    {
        window.draw(OptionOpacityTex);
        window.draw(OptionsBlank);
        window.draw(BackFromOptions);
        window.draw(FullScreenTickBoxO);
        window.draw(SoundEffectTickBoxO);
        window.draw(MusicTickBoxO);
    }
}