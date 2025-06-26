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
#pragma region Textures
	Texture HeadIdleTex;
	Texture HeadIceAttackTex;
	Texture HeadFireAttackTex;

	//===============elemental attacks===============//
	Texture IceBallTopTex;
	Texture IceBallBottomTex;
	Texture FireBallTopTex;
	Texture FireBallBottomTex;
#pragma endregion

#pragma region sprites
	Sprite Head;
#pragma endregion

	enum BossState{ StandingIdle, HeadIdle, PlacingZombies, IceAttack, FireAttack, ThrowVan} CurrentState;

	int health = 10000;
	float StateClock = 0, animationClock = 0;
	Time IdleTime = seconds(10), PlacingZombiesTime = seconds(20), ElementalAttackTime = seconds(30);
	Time AnimationTime = seconds(0.35f);

	int animationCol = 0;

	bool startBossfight = false;

	bool plantedIceAttack = false;
	bool plantedFireAttack = false;
	bool doingAction = false;

	struct ElementalAttack 
	{
		BossState type;
		Sprite spriteTop;
		Sprite spriteBottom;
		Sprite spriteExplosion;

		Vector2f pos;
		Vector2f scale;
		Vector2f finalScale = { 3.5f, 3.5f };

		bool active = true;
		bool ready = false;
		bool explode = false; 
		bool resetOrigin = false;

		void start(BossState state, Vector2f spawnPos) 
		{
			type = state;
			ready = false;
			explode = false;
			active = true;
			resetOrigin = false;

			pos = spawnPos;
			scale = { 0, 0 };

			if (type == IceAttack)
			{
				spriteTop.setTextureRect(IntRect(0, 0, 60, 60));
				spriteBottom.setTextureRect(IntRect(0, 0, 60, 60));
				spriteTop.setTexture(IceBallTopTex);
				spriteBottom.setTexture(IceBallBottomTex);
			}
			else if(type == FireAttack)
			{
				spriteTop.setTextureRect(IntRect(0, 0, 60, 60));
				spriteBottom.setTextureRect(IntRect(0, 0, 60, 60));
				spriteTop.setTexture(FireBallTopTex);
				spriteBottom.setTexture(FireBallBottomTex);
			}

			IntRect topBounds = spriteTop.getTextureRect();
			IntRect bottomBounds = spriteBottom.getTextureRect();

			spriteTop.setOrigin(topBounds.width / 2, topBounds.height);
			spriteBottom.setOrigin(bottomBounds.width / 2, bottomBounds.height);

			spriteTop.setPosition(pos);
			spriteBottom.setPosition(pos);
			spriteTop.setScale(scale);
			spriteBottom.setScale(scale);
		}

		void update() 
		{
			if (!ready)
			{
				if (scale.x < finalScale.x)
				{
					scale += Vector2f(1, 1) * deltaTime;
				}
				else
				{
					scale = finalScale;
					ready = true;
				}
			}
			else
			{
				pos += Vector2f(-50, 0) * deltaTime;
			}

			spriteTop.setPosition(pos);
			spriteBottom.setPosition(pos);
			spriteTop.setScale(scale);
			spriteBottom.setScale(scale);

			if (plantedIceAttack && type == FireAttack)
			{
				spriteTop.scale({ 0,0 });
				spriteBottom.scale({ 0,0 });

				explode = true;
				active = false;
			}
			else if (plantedFireAttack && type == IceAttack)
			{
				spriteTop.scale({ 0,0 });
				spriteBottom.scale({ 0,0 });

				explode = true;
				active = false;
			}

			if (pos.x <= -200)
			{
				active = false;
			}
		}
	}ElementalAttackOBJ;

void LoadBossTexturesAndAudio() 
{
	HeadIdleTex.loadFromFile("Assets/Boss Fight/boss-idle-1.png");
	HeadIceAttackTex.loadFromFile("Assets/Boss Fight/boss-iceattack-1.png");
	HeadFireAttackTex.loadFromFile("Assets/Boss Fight/boss-fireattack-1.png");

	IceBallTopTex.loadFromFile("Assets/Boss Fight/iceball-top.png");
	IceBallBottomTex.loadFromFile("Assets/Boss Fight/iceball-bottom.png");
	FireBallTopTex.loadFromFile("Assets/Boss Fight/fireball-top.png");
	FireBallBottomTex.loadFromFile("Assets/Boss Fight/fireball-bottom.png");
}

void SetupBossData()
{
	//ElementalAttackOBJ.setup();

	StateClock = 0;
	animationClock = 0;
	animationCol = 0;

	plantedIceAttack = false;
	plantedFireAttack = false;
	doingAction = false;

	startBossfight = true;
	CurrentState = FireAttack;

	Head.setTexture(HeadIdleTex);
	Head.setTextureRect(IntRect(animationCol * 230, 0, 230, 200));
	Head.setScale(3.5, 3.5);
	Head.setPosition({ 445, -75 });

	ElementalAttackOBJ.start(FireAttack, { 600, 550 });
}

void BossStateManager()
{

}

void AnimatateBoss() 
{
	animationClock += deltaTime;

	if (animationClock >= AnimationTime.asSeconds())
	{
		if (CurrentState == HeadIdle)
		{
			Head.setTextureRect(IntRect(animationCol * 230, 0, 230, 200));
			Head.setTexture(HeadIdleTex);

			animationCol = (animationCol + 1) % 5;
		}
		else if (CurrentState == IceAttack)
		{
			if (animationCol == 5)
			{
				animationCol = 3;
			}

			Head.setTextureRect(IntRect(animationCol * 230, 0, 230, 200));
			Head.setTexture(HeadIceAttackTex);

			animationCol++;

			if (ElementalAttackOBJ.ready)
			{
				CurrentState = HeadIdle;
				doingAction = false;
				animationCol = 0;
			}
		}
		else if (CurrentState == FireAttack)
		{
			if (animationCol == 5)
			{
				animationCol = 3;
			}

			Head.setTextureRect(IntRect(animationCol * 230, 0, 230, 200));
			Head.setTexture(HeadFireAttackTex);

			animationCol++;

			if (ElementalAttackOBJ.ready)
			{
				CurrentState = HeadIdle;
				doingAction = false;
				animationCol = 0;
			}
		}
		else if (CurrentState == PlacingZombies)
		{

		}
		animationClock = 0;
	}
}

void UpdateBossLogic()
{
	AnimatateBoss();

	if (ElementalAttackOBJ.active)
	{
		ElementalAttackOBJ.update();
	}
}

void DrawBoss(RenderWindow& window)
{
	if (ElementalAttackOBJ.active)
	{
		window.draw(ElementalAttackOBJ.spriteBottom);
		window.draw(ElementalAttackOBJ.spriteTop);
	}

	window.draw(Head);
}

}

