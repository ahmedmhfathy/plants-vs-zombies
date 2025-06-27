#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Tools.h"
#include "Game Settings And Audio.h"
#include "Plants_Zombies.h"
#include "StartAnimation.h"
#include<vector>
using namespace std;
using namespace sf;

namespace boss
{
#pragma region Textures
	Texture HeadIdleTex;
	Texture HeadIceAttackTex;
	Texture HeadFireAttackTex;
	//======================legs=====================//
	Texture LegEnterTex;
	Texture LegBentEnterTex;
	Texture LegsIdleTex;
	//===============elemental attacks===============//
	Texture IceBallTopTex;
	Texture IceBallBottomTex;
	Texture FireBallTopTex;
	Texture FireBallBottomTex;
	//=====================Arms======================//
#pragma endregion

	enum BossState{ StandingIdle, EnteringLevel, PlacingZombies, HeadIdle, IceAttack, FireAttack, ThrowVan, None};

	bool startBossfight = false;

	bool plantedIceAttack = false;
	bool plantedFireAttack = false;

	//first is head position second is ball spawn position
	pair<Vector2f, Vector2f> ElementalAttacksSpawnPoints[4] = { {{495,-55},{710, 550}}
															   ,{{495,-165},{710,440}}
															   ,{{495,-275},{710,330}}
															   ,{{495,-385},{710,220}} };

	pair<Vector2f, Vector2f> randElementalAttackPos = ElementalAttacksSpawnPoints[rand() % 4];

#pragma region Structs
	struct Boss {
		Sprite Head;
		Sprite LegFront;
		Sprite LegBack;
		Sprite Arm;

		BossState currentState, previousState;

		int Health = 10000;

		bool isAttacking = false;
		bool isSwitchingState = false;
		bool attackOnce = false;

		int animationCol = 0;
		int animationCol2 = 0;

	private:
		Time AnimationTime = seconds(0.2f);
		Clock moveBossAnimClock;

		bool resetClock = false;

		float animationClock = 0;

		Vector2f StartPos, EndPos;
		Vector2f HeadOutOfScreenPos = { 800, -400 };
		Vector2f LegFrontOutOfScreenPos = {900, -50};
		Vector2f LegBackOutOfScreenPos = {860, -250};

	public:
		void Start()
		{
			currentState = EnteringLevel;

			isAttacking = false;
			isSwitchingState = false;
			attackOnce = false;
			resetClock = false;

			animationCol = 0;
			Health = 10000;

			Head.setTexture(HeadIdleTex);
			Head.setTextureRect(IntRect(animationCol * 230, 0, 230, 200));
			Head.setScale(3.5, 3.5);
			Head.setPosition({ 495, -165 });

			LegFront.setTextureRect(IntRect(animationCol * 140, 0, 140, 183));
			LegFront.setTexture(LegEnterTex);
			LegFront.setScale(3, 3);
			LegFront.setPosition({ 900, -175 });
			LegBack.setTextureRect(IntRect(animationCol * 140, 0, 140, 183));
			LegBack.setTexture(LegEnterTex);
			LegBack.setScale(3, 3);
			LegBack.setPosition({ 710, -250 });
		}

		void AnimationHandler()
		{
			animationClock += deltaTime;

			if (currentState == HeadIdle)
			{
				if (animationClock >= AnimationTime.asSeconds()) {
					Head.setTextureRect(IntRect(animationCol * 230, 0, 230, 200));
					Head.setTexture(HeadIdleTex);

					animationCol = (animationCol + 1) % 5;

					animationClock = 0;
				}

				isAttacking = false;
			}
			else if (currentState == IceAttack || currentState == FireAttack)
			{
				Time animTime = seconds(3);

				if (!isAttacking)
				{
					StartPos = Head.getPosition();
					EndPos = randElementalAttackPos.first;
					moveBossAnimClock.restart();

					isAttacking = true;
				}

				//move head to rand position
				if (Head.getPosition().y != EndPos.y)
				{
					//animate idle till reaches target position
					if (animationClock >= AnimationTime.asSeconds())
					{
						Head.setTextureRect(IntRect(animationCol * 230, 0, 230, 200));
						Head.setTexture(HeadIdleTex);

						animationCol = (animationCol + 1) % 5;

						animationClock = 0;
					}

					Head.setPosition(495, easeInOut(CubicEaseInOut, StartPos.y, EndPos.y, moveBossAnimClock, animTime));
				}
				//animate elemental attack
				else
				{
					if (isSwitchingState)
					{
						animationCol = 0;
						isSwitchingState = false;
					}

					if (animationClock >= AnimationTime.asSeconds())
					{
						if (currentState == IceAttack)
						{
							if (animationCol == 5)
							{
								animationCol = 3;
							}

							Head.setTextureRect(IntRect(animationCol * 230, 0, 230, 200));
							Head.setTexture(HeadIceAttackTex);

							animationCol++;
						}
						else if (currentState == FireAttack)
						{
							if (animationCol == 5)
							{
								animationCol = 3;
							}

							Head.setTextureRect(IntRect(animationCol * 230, 0, 230, 200));
							Head.setTexture(HeadFireAttackTex);

							animationCol++;
						}

						animationClock = 0;
					}
				}
			}
			else if (currentState == PlacingZombies)
			{
				isAttacking = true;
			}
			else if (currentState == EnteringLevel)
			{
				Time animspeed = seconds(2);
				Vector2f startFront = {1100, -300}, endFront = { 750, -50 };
				Vector2f startBack = {1100, -300}, endBack = { 750, -50 };

				if (moveleft)
				{
					if (LegFront.getPosition() != endFront)
					{
						if (!resetClock)
						{
							moveBossAnimClock.restart();
							resetClock = true;
						}

						cout << "MOVING LEG " << endl;
						LegFront.setPosition(easeInOut(ExpoEaseIn, startFront.x, endFront.x, moveBossAnimClock, animspeed),
											 easeInOut(ExpoEaseIn, startFront.y, endFront.y, moveBossAnimClock, animspeed));
					}
					else if (animationClock >= AnimationTime.asSeconds())
					{
						resetClock = false;

						cout << "animate leg \n";
						LegFront.setTextureRect(IntRect(animationCol * 140, 0, 140, 183));
						LegFront.setTexture(LegEnterTex);

						LegBack.setTextureRect(IntRect(animationCol2 * 140, 0, 140, 183));
						LegBack.setTexture(LegEnterTex);

						animationCol++;

						if (animationCol >= 4)
						{
							animationCol2++;
							LegFront.setTextureRect(IntRect(animationCol2 * 140, 0, 140, 183));
							LegFront.setTexture(LegBentEnterTex);
						}

						if (animationCol2 == 6 || animationCol == 6)
						{
							animationCol = 0;
							animationCol2 = 0;

							currentState = StandingIdle;
						}

						animationClock = 0;
					}
				}

				isAttacking = false;
			}
			else if (currentState == StandingIdle)
			{
				if (animationClock >= seconds(0.45f).asSeconds())
				{
					cout << "animate idle leg \n";

					LegFront.setTextureRect(IntRect(animationCol * 140, 0, 140, 183));
					LegFront.setTexture(LegsIdleTex);

					LegBack.setTextureRect(IntRect(animationCol * 140, 0, 140, 183));
					LegBack.setTexture(LegsIdleTex);

					animationCol = (animationCol + 1) % 3;

					animationClock = 0;

					if (animationCol + 1 == 3)
					{
						startBossfight = true;
						//cout << endl << endl << endl << "start boss fight" << endl;
					}
				}

				isAttacking = false;
			}
		}

		void SwitchStates() {

		}

		void Attack();

		void Update()
		{
			AnimationHandler();
			Attack();

			if (Keyboard::isKeyPressed(Keyboard::F) && !isAttacking && !isSwitchingState)
			{
				randElementalAttackPos = ElementalAttacksSpawnPoints[rand() % 4];
				BossOBJ.currentState = FireAttack;

				isSwitchingState = true;

				cout << endl << endl << endl << "+==============================+" << endl;
			}

			if (Keyboard::isKeyPressed(Keyboard::G) && !isAttacking && !isSwitchingState)
			{
				randElementalAttackPos = ElementalAttacksSpawnPoints[rand() % 4];
				BossOBJ.currentState = IceAttack;

				isSwitchingState = true;

				cout << endl << endl << endl << "+==============================+" << endl;
			}

			if (Keyboard::isKeyPressed(Keyboard::L) && !isAttacking)
			{
				currentState = StandingIdle;
			}

			//if (currentState == HeadIdle)
			//{
			//	cout << "Head Idle" << " -isattacking: " << isAttacking << " Attack1: " << attackOnce << " switch: " << isSwitchingState << endl;
			//}
			//else if (currentState == IceAttack)
			//{
			//	cout << "Head ice" << " -isattacking: " << isAttacking << " Attack1: " << attackOnce << " switch: " << isSwitchingState << endl;
			//}
			//else if (currentState == FireAttack)
			//{
			//	cout << "Head fire" << " -isattacking: " << isAttacking << " Attack1: " << attackOnce << " switch: " << isSwitchingState << endl;
			//}
			//else if (currentState == StandingIdle)
			//{
			//	cout << "leg" << " - " << isAttacking << endl;
			//}
		}

		void drawBoss(RenderWindow& window)
		{
			if (moveleft)
			{
				window.draw(Head);
				window.draw(LegBack);
				window.draw(LegFront);
				window.draw(Arm);
			}
		}
	}BossOBJ;

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

		bool active = false;
		bool ready = false;
		bool explode = false;

		bool resetBossState = false;

		void start(BossState state, Vector2f spawnPos)
		{
			resetBossState = false;

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
			else if (type == FireAttack)
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

			collider.setPosition(pos + Vector2f{ 80,20 });
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
					scale += Vector2f(2, 2) * deltaTime;
				}
				else
				{
					cout << endl << "ready is true " << endl;
					scale = finalScale;
					ready = true;
				}

				BossOBJ.isAttacking = true;
			}
			else
			{
				pos += Vector2f(-50, 0) * deltaTime;

				if (!resetBossState)
				{
					BossOBJ.currentState = HeadIdle;
					BossOBJ.animationCol = 0;
					BossOBJ.isAttacking = false;
					BossOBJ.attackOnce = false;

					resetBossState = true;
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
	};

	vector<ElementalAttack> elementalAttackArr;

	void Boss::Attack()
	{
		if (!isSwitchingState && isAttacking)
		{
			if ((currentState == FireAttack || currentState == IceAttack) && !attackOnce)
			{
				ElementalAttack projectile;
				projectile.start(currentState, randElementalAttackPos.second);

				elementalAttackArr.push_back(projectile);

				attackOnce = true;
			}
			else if (currentState == PlacingZombies)
			{

			}
			else if (currentselection == ThrowVan)
			{

			}
		}
	}
#pragma endregion

void LoadBossTexturesAndAudio() 
{
	HeadIdleTex.loadFromFile("Assets/Boss Fight/boss-idle-1.png");
	HeadIceAttackTex.loadFromFile("Assets/Boss Fight/boss-iceattack-1.png");
	HeadFireAttackTex.loadFromFile("Assets/Boss Fight/boss-fireattack-1.png");
	
	LegEnterTex.loadFromFile("Assets/Boss Fight/leg-entering.png");
	LegBentEnterTex.loadFromFile("Assets/Boss Fight/leg-bent-entering.png");
	LegsIdleTex.loadFromFile("Assets/Boss Fight/leg-idle.png");

	IceBallTopTex.loadFromFile("Assets/Boss Fight/iceball-top.png");
	IceBallBottomTex.loadFromFile("Assets/Boss Fight/iceball-bottom.png");
	FireBallTopTex.loadFromFile("Assets/Boss Fight/fireball-top.png");
	FireBallBottomTex.loadFromFile("Assets/Boss Fight/fireball-bottom.png");
}

void SetupBossData()
{
	srand(time(0));
	elementalAttackArr.empty();

	plantedIceAttack = false;
	plantedFireAttack = false;

	startBossfight = false;

	BossOBJ.Start();
}

void BossStateManager()
{

}

void UpdateBossLogic()
{
	BossStateManager();

	//update elemental attacks
	for (int i = 0; i < elementalAttackArr.size(); i++)
	{
		if (elementalAttackArr[i].active)
		{
			elementalAttackArr[i].update();
		}
	}

	//delete elemental attacks
	if (!elementalAttackArr.empty())
	{
		for (int i = 0; i < elementalAttackArr.size(); i++)
		{
			if (!elementalAttackArr.empty() && !elementalAttackArr[i].active)
			{
				elementalAttackArr.erase(elementalAttackArr.begin(), elementalAttackArr.begin() + i);

				if (i<0)
				{
					i--;
				}
			}
		}
	}

	BossOBJ.Update();
}

void DrawBoss(RenderWindow& window)
{
	for (int i = 0; i < elementalAttackArr.size(); i++)
	{
		if (elementalAttackArr[i].active)
		{
			window.draw(elementalAttackArr[i].spriteBottom);
			window.draw(elementalAttackArr[i].spriteTop);
		}
	}

	BossOBJ.drawBoss(window);
}

}

