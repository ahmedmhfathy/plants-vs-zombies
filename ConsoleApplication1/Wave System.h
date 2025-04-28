#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "Tools.h"

namespace Waves{

struct Wave {
	int numberOfZombies;
	Time DelayBetweenWaves;
};

Clock waveClock;

void startWaves(Wave wavesData[], int numberOfWaves) {
	for (int i = 0; i < numberOfWaves; i++)
	{

	}
}

void UpdateWaves() {
	Time StartDelay = seconds(5);
	if (waveClock.getElapsedTime()>= StartDelay)
	{

	}
}

}