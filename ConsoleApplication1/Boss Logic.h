#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Tools.h"
#include "Game Settings And Audio.h"
#include "Plants_Zombies.h"
#include "StartAnimation.h"
using namespace std;
using namespace sf;

namespace boss
{
#pragma region Textures
	Texture HeadIdleTex;
	Texture HeadIceAttackTex;
	Texture HeadFireAttackTex;
	//===============leg=============================//
	Texture leg;

	//===============elemental attacks===============//
	Texture IceBallTopTex;
	Texture IceBallBottomTex;
	Texture FireBallTopTex;
	Texture FireBallBottomTex;
#pragma endregion

#pragma region sprites
	Sprite Head;
	Sprite Leg;
	Sprite Leg2;
#pragma endregion

	enum BossState{ StandingIdle, HeadIdle, PlacingZombies, IceAttack, FireAttack, ThrowVan, enteringLevel} CurrentState;

	int health = 10000;
	float StateClock = 0, animationClock = 0;
	Time IdleTime = seconds(10), PlacingZombiesTime = seconds(20), ElementalAttackTime = seconds(30);
	Time AnimationTime = seconds(0.5f);

	int animationCol = 0;

	bool startBossfight = false;

	bool plantedIceAttack = false;
	bool plantedFireAttack = false;
	bool doingAction = false;
	bool resetAction = false;

	pair<Vector2f, Vector2f> ElementalAttacksSpawnPoints[10];

	struct ElementalAttack 
	{
		BossState type;
		Sprite spriteTop;
		Sprite spriteBottom;
		Sprite spriteExplosion;

		RectangleShape collider;

		Vector2f pos;
		Vector2f scale;
		Vector2f finalScale = { 3.5f, 3.5f };

		bool active = true;
		bool ready = false;
		bool explode = false; 

		void start(BossState state, Vector2f spawnPos) 
		{
			doingAction = true;
			resetAction = false;

			type = state;
			ready = false;
			explode = false;
			active = true;

			collider.setSize({ 15, 40 });
			collider.setFillColor(Color(255, 0, 0, 100));

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
			collider.setOrigin(bottomBounds.width / 2, bottomBounds.height);

			collider.setPosition(pos + Vector2f{80,20});
			collider.setScale(scale);

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

				doingAction = true;
			}
			else
			{
				pos += Vector2f(-50, 0) * deltaTime;

				if (!resetAction)
				{
					CurrentState = HeadIdle;
					animationCol = 0;
					doingAction = false;
					resetAction = true;
				}
			}

			collider.setPosition(pos + Vector2f{ 80,20 });
			collider.setScale(scale);

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
				ready = false;
				explode = false;
			}

			//intersects plants and ball
			if (active)
			{
				for (int i = 0; i < 45; i++)
				{
					if (collider.getGlobalBounds().intersects(Plants_Zombies::PlantsArray[i].plantCollider.getGlobalBounds()))
					{
						Plants_Zombies::PlantsArray[i].takeDmg(9999999);
					}

					if (collider.getGlobalBounds().intersects(Plants_Zombies::PlantingPotArray[i].plantCollider.getGlobalBounds()))
					{
						Plants_Zombies::PlantingPotArray[i].takeDmg(9999999);
					}
				}
			}
		}
	}ElementalAttackOBJ;

void LoadBossTexturesAndAudio() 
{
	HeadIdleTex.loadFromFile("Assets/Boss Fight/boss-idle-1.png");
	HeadIceAttackTex.loadFromFile("Assets/Boss Fight/boss-iceattack-1.png");
	HeadFireAttackTex.loadFromFile("Assets/Boss Fight/boss-fireattack-1.png");
	
	leg.loadFromFile("Assets/Boss Fight/leg1.png");

	IceBallTopTex.loadFromFile("Assets/Boss Fight/iceball-top.png");
	IceBallBottomTex.loadFromFile("Assets/Boss Fight/iceball-bottom.png");
	FireBallTopTex.loadFromFile("Assets/Boss Fight/fireball-top.png");
	FireBallBottomTex.loadFromFile("Assets/Boss Fight/fireball-bottom.png");
}

void SetupBossData()
{
	StateClock = 0;
	animationClock = 0;
	animationCol = 0;

	plantedIceAttack = false;
	plantedFireAttack = false;
	doingAction = false;
	resetAction = false;

	startBossfight = true;
	CurrentState = StandingIdle;

	Head.setTexture(HeadIdleTex);
	Head.setTextureRect(IntRect(animationCol * 230, 0, 230, 200));
	Head.setScale(3.5, 3.5);
	Head.setPosition({ 445, -75 });

	Leg.setTexture(leg);
	Leg.setTextureRect(IntRect(animationCol * 140, 0, 140, 183));
	Leg.setScale(3, 3);
	Leg.setPosition({ 750, -50 });
	Leg2.setTexture(leg);
	Leg2.setTextureRect(IntRect(animationCol * 140, 0, 140, 183));
	Leg2.setScale(3, 3);
	Leg2.setPosition({ 710, -250 });
}

//void BossStateManager()
//{
//	if (!doingAction)
//	{
//		if (CurrentState == IceAttack || CurrentState == FireAttack)
//		{
//			ElementalAttackOBJ.start(CurrentState, { 600, 550 });
//		}
//	}
//}

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
		}
		else if (CurrentState == PlacingZombies)
		{

		}
		else if (CurrentState == StandingIdle)
		{
			cout << "animate leg \n";
			Leg.setTexture(leg);
			Leg.setTextureRect(IntRect(animationCol * 140, 0, 140, 183));

			Leg2.setTexture(leg);
			Leg2.setTextureRect(IntRect(animationCol * 140, 0, 140, 183));

			animationCol = (animationCol + 1) % 7;
		}

		animationClock = 0;
	}
}

void UpdateBossLogic()
{
	AnimatateBoss();
	//BossStateManager();

	/*if (ElementalAttackOBJ.active)
	{
		ElementalAttackOBJ.update();
	}

	if (Keyboard::isKeyPressed(Keyboard::F) && !doingAction)
	{
		CurrentState = FireAttack;
		animationCol = 0;
	}

	if (Keyboard::isKeyPressed(Keyboard::G) && !doingAction)
	{
		CurrentState = IceAttack;
		animationCol = 0;
	}*/

	if (CurrentState == HeadIdle)
	{
		cout << "Head Idle" << " - " << doingAction << endl;
	}
	else if (CurrentState == IceAttack)
	{
		cout << "Head ice" << " - " << doingAction << endl;
	}
	else if (CurrentState == FireAttack)
	{
		cout << "Head fire" << " - " << doingAction << endl;
	}
	else if(CurrentState == StandingIdle)
	{
		cout << "leg" << " - " << doingAction << endl;
	}
}

void DrawBoss(RenderWindow& window)
{
	/*if (ElementalAttackOBJ.active)
	{
		window.draw(ElementalAttackOBJ.spriteBottom);
		window.draw(ElementalAttackOBJ.spriteTop);
		window.draw(ElementalAttackOBJ.collider);
	}

	window.draw(Head);*/
	if (moveleft)
	{
		window.draw(Leg2);
		window.draw(Leg);
	}
	
}

}

