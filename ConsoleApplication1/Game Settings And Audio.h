#pragma once
#include<SFML\Graphics.hpp>
#include<SFML\Audio.hpp>
#include<vector>
#include<deque>
#include<algorithm>
using namespace std;
using namespace sf;

RenderWindow window(VideoMode(1280, 720), "Plants VS Zombies");
enum State { MainMenu, Level1, Level2, Level3 } CurrentState, MaxLevelWon;

Clock DeltaTimeClock;
float deltaTime;

bool IsPaused = false;
bool wasPausedLastFrame = IsPaused;

bool IsFullScreen = false;
bool IsSoundEffects = true;
bool IsMusic = true;
bool changeFullScreenState = true;

deque<Sound> soundEffects;
SoundBuffer GameMusicBuffer;
Sound GameMusic;

//should be called in the update function
void DeltaTimeManager()
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

	GameMusicBuffer.loadFromFile("Audio/Plants vs. Zombies BackGround.wav");
	GameMusic.setBuffer(GameMusicBuffer);
	GameMusic.setVolume(5);
	GameMusic.setLoop(true);
	GameMusic.play();
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

void PlaySoundEffect(SoundBuffer& buffer, bool Pitch) 
{
	float randPitch[5] = {0.75, 0.85, 1, 1.15, 1.25 };

	if (IsSoundEffects) {
		Sound sound;
		sound.setBuffer(buffer);

		if (Pitch)
		{
			sound.setPitch(randPitch[rand() % 5]);
		}
		else
		{
			sound.setPitch(1.0f);
		}

		soundEffects.push_back(sound);
		soundEffects.back().play();
	}
}

void PlaySoundEffect(SoundBuffer buffer[], bool Pitch , int size, int volume = 100) 
{
	float randPitch[5] = { 0.75, 0.85, 1, 1.15, 1.25 };

	if (IsSoundEffects) {
		Sound sound;
		sound.setBuffer(buffer[rand()%size]);
		sound.setVolume(volume);

		if (Pitch)
		{
			sound.setPitch(randPitch[rand() % 5]);
		}
		else
		{
			sound.setPitch(1.0f);
		}

		soundEffects.push_back(sound);
		soundEffects.back().play();
	}
}

void SoundsUpdate() 
{
	if (IsMusic)
	{
		GameMusic.setVolume(5);
	}
	else
	{
		GameMusic.setVolume(0);
	}

	if (IsSoundEffects)
	{
		//cout << soundEffects.size() << endl;

		if (!soundEffects.empty() && (soundEffects.front().getStatus() == SoundSource::Status::Stopped))
		{
			soundEffects.pop_front();
		}
	}
}