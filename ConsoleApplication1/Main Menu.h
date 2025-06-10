#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "Game Manager.h"
#include "Tools.h"
#include "Game Settings And Audio.h"

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
Texture Level1Tex;
Texture Level1HoverTex;
Texture Level2Tex;
Texture Level2HoverTex;
Texture Level3Tex;
Texture Level3HoverTex;
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
Sprite BackTOMainMenuButton;
Sprite Level1Button;
Sprite Level2Button;
Sprite Level3Button;
Sprite Level2Lock;
Sprite Level3Lock;
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
Sound HoverMainMenuSound;
SoundBuffer CreditsTran;
SoundBuffer ButtonSoundBuffer;
Sound ButtonSound;
Sound CreditsTranSound;
SoundBuffer ClickBuffer;
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
Time TickBoxDelayO=seconds(.25);

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

    MainMenuBackGroundTex.loadFromFile("Assets/Main Menu/pvz main menu new.png");
    StartButtonTex.loadFromFile("Assets/Main Menu/startbutton-default.png");
    StartButtonHoverTex.loadFromFile("Assets/Main Menu/startbutton-hover.png");
    CreditButtonTex.loadFromFile("Assets/Main Menu/creditsbutton-default-2.png");
    CreditButtonHoverTex.loadFromFile("Assets/Main Menu/creditsbutton-hover-2.png");
    QuitButtonTex.loadFromFile("Assets/Main Menu/quitbutton-default.png");
    QuitButtonHoverTex.loadFromFile("Assets/Main Menu/quitbutton-hover.png");
    BackTOMainMenuTex.loadFromFile("Assets/Main Menu/back to main menu button-default.png");
    BackTOMainMenuHoverTex.loadFromFile("Assets/Main Menu/back to main menu button-hover.png");
    OptionsButtonTex.loadFromFile("Assets/Main Menu/optionsbutton-default.png");
    OptionsButtonHoverTex.loadFromFile("Assets/Main Menu/optionsbutton-hover.png");

    //Level Selection 
    Level1Tex.loadFromFile("Assets/Main Menu/Level 1.png");
    Level1HoverTex.loadFromFile("Assets/Main Menu/Level 1 hover.png");
    Level2Tex.loadFromFile("Assets/Main Menu/Level 2.png");
    Level2HoverTex.loadFromFile("Assets/Main Menu/Level 2 hover.png");
    Level3Tex.loadFromFile("Assets/Main Menu/Level 3.png");
    Level3HoverTex.loadFromFile("Assets/Main Menu/Level 3 hover.png");
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
    MaxLevelWon = Level3;
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
    OptionsButton.setTexture(OptionsButtonTex);
    //set up the back to main menu button
    BackTOMainMenuButton.setPosition(2185, 436);
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
    //Back to main menu 
    BackTOMainMenuButtonLS.setTexture(BackTOMainMenuTex);
    BackTOMainMenuButtonLS.setOrigin({ BackTOMainMenuButtonLS.getLocalBounds().width / 2, BackTOMainMenuButtonLS.getLocalBounds().height / 2 });
    BackTOMainMenuButtonLS.setPosition(978, 1096);
    //locks
    Level2Lock.setTexture(LevelLockTex);
    Level2Lock.setPosition(375, 965);
    Level3Lock.setTexture(LevelLockTex);
    Level3Lock.setPosition(375, 1087);
    //Options set up
    OptionsBlank.setTexture(OptionsBlankTex);
    OptionsBlank.setOrigin(OptionsBlank.getGlobalBounds().width / 2, OptionsBlank.getGlobalBounds().height / 2);
    OptionsBlank.setScale(2, 2);
    OptionsBlank.setPosition(640,360);
    OptionOpacityTex.setTexture(OpacityOPtions);
    OptionOpacityTex.setPosition(0, 0);
    BackFromOptions.setTexture(BackFromOptionsTex);
    BackFromOptions.setOrigin(BackFromOptions.getGlobalBounds().width / 2, BackFromOptions.getGlobalBounds().height / 2);
    BackFromOptions.setScale(2.25, 2.25);
    BackFromOptions.setPosition(629, 497);

    FullScreenTickBoxO.setTexture(TickBoxBlankTexO);
    FullScreenTickBoxO.setOrigin(FullScreenTickBoxO.getGlobalBounds().width / 2, FullScreenTickBoxO.getGlobalBounds().height / 2);
    FullScreenTickBoxO.setScale(2, 2);
    FullScreenTickBoxO.setPosition(750,335);

   SoundEffectTickBoxO.setTexture(TickBoxSelectedTexO);
   SoundEffectTickBoxO.setOrigin(SoundEffectTickBoxO.getGlobalBounds().width / 2, SoundEffectTickBoxO.getGlobalBounds().height / 2);
   SoundEffectTickBoxO.setScale(2, 2);
   SoundEffectTickBoxO.setPosition(750, 385);

    MusicTickBoxO.setTexture(TickBoxSelectedTexO);
    MusicTickBoxO.setOrigin(MusicTickBoxO.getGlobalBounds().width / 2, MusicTickBoxO.getGlobalBounds().height / 2);
    MusicTickBoxO.setScale(2, 2);
    MusicTickBoxO.setPosition(750, 435);


#pragma endregion
}

void MainMenuUpdate(Vector2f mouse_pos, RenderWindow& window)
{
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
                HoverMainMenuSound.setPitch(randPitch[rand() % 3]);
                HoverMainMenuSound.play();
                SoundStart = false;
            }
            if (!startAnim && Mouse::isButtonPressed(Mouse::Left) && !startAnimLevel)
            {
                Click.setPitch(randPitch[rand() % 3]);
                Click.play();
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
                HoverMainMenuSound.setPitch(randPitch[rand() % 3]);
                HoverMainMenuSound.play();
                SoundOptions = false;
            }
            if (!startAnim && Mouse::isButtonPressed(Mouse::Left) && !startAnimLevel)
            {
                Click.setPitch(randPitch[rand() % 3]);
                Click.play();
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
                HoverMainMenuSound.setPitch(randPitch[rand() % 3]);
                HoverMainMenuSound.play();
                SoundQuit = false;
            }
            if (!startAnim && Mouse::isButtonPressed(Mouse::Left) && !startAnimLevel)
            {
                Click.setPitch(randPitch[rand() % 3]);
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

        if (CreditButton.getGlobalBounds().contains(mouse_pos) && !ShowOptions)
        {
            CreditButton.setTexture(CreditButtonHoverTex);
            if (SoundCredit)
            {
                ButtonSound.setPitch(randPitch[rand() % 3]);
                ButtonSound.play();
                SoundCredit = false;
            }
            if (!startAnim && Mouse::isButtonPressed(Mouse::Left) && !startAnimLevel)
            {
                Click.setPitch(randPitch[rand() % 3]);
                Click.play();
                //CreditsTranSound.play();
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
        if (BackTOMainMenuButton.getGlobalBounds().contains(mouse_pos))
        {
            if (SoundButton)
            {
                ButtonSound.setPitch(randPitch[rand() % 3]);
                ButtonSound.play();
                SoundButton = false;
            }
            BackTOMainMenuButton.setTexture(BackTOMainMenuHoverTex);
            if (!startAnim && Mouse::isButtonPressed(Mouse::Left))
            {
                Click.setPitch(randPitch[rand() % 3]);
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
                ButtonSound.setPitch(randPitch[rand() % 3]);
                ButtonSound.play();
                SoundButton = false;
            }
            BackTOMainMenuButtonLS.setTexture(BackTOMainMenuHoverTex);
            if (!startAnim && Mouse::isButtonPressed(Mouse::Left) && !startAnimLevel)
            {
                Click.setPitch(randPitch[rand() % 3]);
                Click.play();
                //CreditsTranSound.play();
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
                ButtonSound.setPitch(randPitch[rand() % 3]);
                ButtonSound.play();
                SoundLevel1Button = false;
            }
            Level1Button.setTexture(Level1HoverTex);
            if (!startAnim && Mouse::isButtonPressed(Mouse::Left) && !startAnimLevel)
            {
                Click.setPitch(randPitch[rand() % 3]);
                Click.play();
                //CreditsTranSound.play();
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
                ButtonSound.setPitch(randPitch[rand() % 3]);
                ButtonSound.play();
                SoundLevel2Button = false;
            }

            Level2Button.setTexture(Level2HoverTex);
            Level2Lock.setScale(0, 0);

            if (!startAnim && Mouse::isButtonPressed(Mouse::Left) && !startAnimLevel)
            {
                Click.setPitch(randPitch[rand() % 3]);
                Click.play();
                //CreditsTranSound.play();
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
                ButtonSound.setPitch(randPitch[rand() % 3]);
                ButtonSound.play();
                SoundLevel3Button = false;
            }

            Level3Button.setTexture(Level3HoverTex);
            Level3Lock.setScale(0, 0);

            if (!startAnim && Mouse::isButtonPressed(Mouse::Left) && !startAnimLevel)
            {
                Click.setPitch(randPitch[rand() % 3]);
                Click.play();
                //CreditsTranSound.play();
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
            cout << 1 << endl;
            if (BackFromOptionsSound)
            {
                ButtonSound.setPitch(randPitch[rand() % 3]);
                ButtonSound.play();
                BackFromOptionsSound = false;
            }

            if (Mouse::isButtonPressed(Mouse::Left))
            {
                Click.setPitch(randPitch[rand() % 3]);
                Click.play();
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
    window.draw(BackTOMainMenuButton);
    window.draw(Level1Button);
    window.draw(Level2Button);
    window.draw(Level3Button);
    window.draw(BackTOMainMenuButtonLS);
    window.draw(Level2Lock);
    window.draw(Level3Lock);
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