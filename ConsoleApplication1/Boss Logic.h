#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Tools.h"
#include "Game Settings And Audio.h"
#include "Plants_Zombies.h"
using namespace std;
using namespace sf;

namespace boss
{
	enum BossState{ Idle, PlacingZombies, IceAttack, FireAttack, ThrowVan};

	int health = 10000;
	float StateClock = 0;
	Time IdleTime = seconds(10), PlacingZombiesTime = seconds(20), ElementalAttackTime = seconds(30);

	bool startBossfight = false;
void LoadBossTexturesAndAudio() 
{

}

void SetupBossData()
{
	startBossfight = false;
}

void UpdateBossLogic()
{
	
}

void DrawBoss(RenderWindow& window)
{
	
}

}

