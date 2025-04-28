#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "Tools.h"

using namespace std;
using namespace sf;

namespace Environment{

View GameCamera(FloatRect(0, 0, 1280, 720));

#pragma region Texture Declaration
Texture gardenTex;
Texture LawnMowerTex;
Texture ReadyTex;
Texture SetTex;
Texture PlantTex;
#pragma endregion

#pragma region Sprite Declaration
Sprite Garden;
Sprite ReadySetPlant;
#pragma endregion

bool startAnimation = false;
bool finishedRight = false;
bool finishedLeft = false;
bool startRSP = false;
bool FinishedAllAimations = false;

Clock animationClock;

struct lawnMowers
{
	Sprite shape;
	float speed = 5;
	bool used = false;

	void start(int index) {
		shape.setTexture(LawnMowerTex);
		shape.setScale(0.8 , 0.8);
		shape.setPosition(-75, 45 + 130*index);
	}
	void update(bool hit) {
		if (hit)
		{
			if (shape.getPosition().x < 1100)
			{
				shape.move(speed, 0);
			}
			else
			{
				shape.setPosition(2000, 2000);
			}
		}
	}
}mowers[5];

void LoadEnvironmentTextures() {
	gardenTex.loadFromFile("Assets/Environment/Game-Environment.png");
	LawnMowerTex.loadFromFile("Assets/Environment/lawnmower.png");
	ReadyTex.loadFromFile("Assets/Environment/StartReady.png");
	SetTex.loadFromFile("Assets/Environment/StartSet.png");
	PlantTex.loadFromFile("Assets/Environment/StartPlant.png");
}

void startEnvironment() {
	GameCamera.setCenter({ 640, 360 });
	GameCamera.move(-300, -50);

	animationClock.restart();

	startAnimation = false;
	finishedRight = false;
	finishedLeft = false;
	startRSP = false;
	FinishedAllAimations = false;


	LoadEnvironmentTextures();
	Garden.setTexture(gardenTex);
	Garden.setPosition(-325, -265);
	Garden.setScale(0.65, 0.65);

	for (int i = 0; i < 5; i++)
	{
		mowers[i].start(i);
	}
}

void updateEnvironment(RenderWindow& window) {
	window.setView(GameCamera);

	//start animation
	if (!finishedRight)
	{
		if (GameCamera.getCenter().x < 850)
		{
			Time animationTime = seconds(3);
			float start = 340, end = 850;
			if (!startAnimation)
			{
				animationClock.restart();
				startAnimation = true;
			}

			GameCamera.setCenter(easeInOut(CubicEaseInOut, start, end, animationClock, animationTime), 360-50);
		}
		else
		{
			startAnimation = false;
			finishedRight = true;
		}
	}
	else if (!finishedLeft)
	{
		if (GameCamera.getCenter().x > 340)
		{
			Time animationTime_ = seconds(3);
			float start = 850, end = 340;
			if (!startAnimation)
			{
				animationClock.restart();
				startAnimation = true;
			}

			GameCamera.setCenter(easeInOut(CubicEaseInOut, start, end, animationClock, animationTime_), 360-50);
		}
		else
		{
			finishedLeft = true;
			startRSP = true;
		}
	}
	
	//READY SET PLANT ANIMATION
	if (finishedRight && finishedLeft && !FinishedAllAimations)
	{
		if (startRSP)
		{
			animationClock.restart();
			ReadySetPlant.setPosition(340, 310);
			startRSP = false;
		}

		if (animationClock.getElapsedTime() <= seconds(1))
		{
			ReadySetPlant.setTexture(ReadyTex);
			ReadySetPlant.setOrigin(ReadySetPlant.getGlobalBounds().width / 2, ReadySetPlant.getGlobalBounds().height / 2);
			ReadySetPlant.setPosition(340, 310);
		}
		else if (animationClock.getElapsedTime() <= seconds(2)) {
			ReadySetPlant.setTexture(SetTex);
			ReadySetPlant.setOrigin(ReadySetPlant.getGlobalBounds().width / 2, ReadySetPlant.getGlobalBounds().height / 2);
			ReadySetPlant.setPosition(340, 310);
		}
		else if (animationClock.getElapsedTime() <= seconds(3)) {
			ReadySetPlant.setTexture(PlantTex);
			ReadySetPlant.setOrigin(ReadySetPlant.getGlobalBounds().width / 2, ReadySetPlant.getGlobalBounds().height / 2);
			ReadySetPlant.setPosition(340, 310);
		}
		else if (animationClock.getElapsedTime() <= seconds(4.5)) {
			FinishedAllAimations = true;
		}
	}
	else
	{
		ReadySetPlant.setPosition(2000, 2000);
	}
}

void drawEnvironment(RenderWindow& window) {
	window.draw(Garden);

	for (int i = 0; i < 5; i++)
	{
		window.draw(mowers[i].shape);
	}

	if (!FinishedAllAimations)
	{
		window.draw(ReadySetPlant);
	}
}

}