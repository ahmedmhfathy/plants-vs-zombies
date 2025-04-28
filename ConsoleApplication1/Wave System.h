#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include"time.h"
#include "Tools.h"

namespace Waves{


Texture zombTex;
struct zombies {
	Sprite shape;
	float speed = 10;

	bool idle = true;
	bool moving = false;
	bool isdead = false;

	void start() {
		bool idle = true;
		bool moving = false;
		bool isdead = false;
		shape.setTexture(zombTex);
		shape.setPosition(1100 + rand() % 300, 130*(rand() % 5));
	}
	void update() {
		if (moving)
		{
			shape.move(-speed, 0);
		}
	}
}AllZombies[100];
struct Wave {
	int numberOfZombies;
	Time DelayBetweenWaves;
};

Clock waveClock;

void startWaves(Wave wavesData[], int numberOfWaves) {
	srand(time(0));
	zombTex.loadFromFile("rectangle.png");

	for (int i = 0; i < numberOfWaves; i++)
	{
		for (int j = 0; j < wavesData[i].numberOfZombies; j++)
		{
			AllZombies[j].start();
		}
	}
}

void UpdateWaves(Wave wavesData[], int numberOfWaves) {
	Time StartDelay = seconds(5);
	if (waveClock.getElapsedTime()>= StartDelay)
	{

	}
}

void SpawnZombie() {

}

void DrawWavesAndZombies(Wave wavesData[], int numberOfWaves, RenderWindow& window) {
	for (int i = 0; i < numberOfWaves; i++)
	{
		for (int j = 0; j < wavesData[i].numberOfZombies; j++)
		{
			window.draw(AllZombies[j].shape);
		}
	}
}

}