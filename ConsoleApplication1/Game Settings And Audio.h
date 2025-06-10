#pragma once
#include<SFML\Graphics.hpp>
#include<SFML\Audio.hpp>
using namespace std;
using namespace sf;

RenderWindow window(VideoMode(1280, 720), "Plants VS Zombies");

Clock DeltaTimeClock;
float deltaTime;

bool IsPaused = false;
bool wasPausedLastFrame = IsPaused;

bool IsFullScreen = false;
bool IsSoundEffects = true;
bool IsMusic = true;
bool changeFullScreenState = true;

//should be called in the update function
void DeltaTimeManager(bool IsPaused)
{
	// Check if the game just switched FROM paused TO unpaused
	if (wasPausedLastFrame && !IsPaused)
	{
		DeltaTimeClock.restart();
		deltaTime = 0.0f;
		wasPausedLastFrame = false;
	}
	else if (!IsPaused)
	{
		deltaTime = DeltaTimeClock.restart().asSeconds();
	}
	else
	{
		deltaTime = 0.0f;
		wasPausedLastFrame = true;
	}
	//cout << deltaTime << endl;
}

void SetupGameSettings() 
{
	IsFullScreen = false;
	IsSoundEffects = true;
	IsMusic = true;
	changeFullScreenState = true;

	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
}

View lastCameraPos;
void GameSettingsUpdate() 
{
	lastCameraPos = window.getView();

	if (changeFullScreenState)
	{
		if (IsFullScreen)
		{
			window.create(VideoMode(1280, 720), "Plants VS Zombies", Style::Fullscreen);
		}
		else
		{
			window.create(VideoMode(1280, 720), "Plants VS Zombies");
		}

		window.setFramerateLimit(60);
		window.setVerticalSyncEnabled(true);

		window.setView(lastCameraPos);

		changeFullScreenState = false;
	}
}