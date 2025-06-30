#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <algorithm>
#include "Tools.h"
#include "Game Settings And Audio.h"
#include "Plants_Zombies.h"
#include "StartAnimation.h"
#include "Game Manager.h"
#include "Plants_Zombies.h"
#include<deque>
#include<vector>
using namespace std;
using namespace sf;

namespace boss
{
	deque<Plants_Zombies::Zombie> bosszombies;
	enum BossState {PlacingZombies, IceAttack, FireAttack, ThrowVan, HeadIdle, StandingIdle, EnteringLevel, None };

	Sprite Textlosegamesprite;
	Clock LoseGameClock;

	float zombieSpawnRate = 8;
	int zombiePlaceCounter = 0;
	int ballAttackCounter = 0;
	bool endAttackWave = true;

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
	Texture armtext;
	//==================lawn=========================//
	Texture lawntexture;

#pragma endregion

#pragma region boolean
	bool startBossfight = false;

	bool plantedIceAttack = false;
	bool plantedFireAttack = false;

	bool LevelIsOver = false;
	bool WinLevel = false;
	bool playLoseGameAnim = false;
#pragma endregion

#pragma region Sound
	SoundBuffer carsSoundBuffer;
	SoundBuffer LoseSoundBuffer;
#pragma endregion

#pragma region values
	//first is head position second is ball spawn position
	pair<Vector2f, Vector2f> ElementalAttacksSpawnPoints[4] = { {{495,-55},{710, 550}}
															   ,{{495,-165},{710,440}}
															   ,{{495,-275},{710,330}}
															   ,{{495,-385},{710,220}} };
	pair<Vector2f, Vector2f> randElementalAttackPos = ElementalAttacksSpawnPoints[rand() % 4];

	float x_axisplacingzombie[3] = { 770, 620,570 };
	float y_axisplacingzombie[5] = { -50, 70, 175, 280, 400 };

	float y_axisrandomplace = y_axisplacingzombie[rand() % 5];
	float x_axisrandomplace = x_axisplacingzombie[rand() % 3];

	float minscaletextlosegame = 1.17f;         // Min Scale For Text Lose Game
	float scalefactortextlosegame = 4.2f;      // First scale For Lose Game
#pragma endregion

#pragma region Structs
	struct cars
	{
		bool startsoundcar = true;
		bool intersection = false;
		float speed = 500;
		Sprite lawnsprite;

		void start(int i)
		{
			if (onRoof) {
				lawntexture.loadFromFile("Assets/Environment/Roof_Cleaner.png");
				lawnsprite.setTexture(lawntexture);
				lawnsprite.setTextureRect(IntRect(0, 0, lawntexture.getSize().x, lawntexture.getSize().y));
				lawnsprite.setScale(0.8, 0.8);
				lawnsprite.setPosition(-70, 50 + (i * 110));
			}
			else {
				lawntexture.loadFromFile("Assets/Environment/lawnmower.png");
				lawnsprite.setTexture(lawntexture);
				lawnsprite.setTextureRect(IntRect(0, 0, lawntexture.getSize().x, lawntexture.getSize().y));
				lawnsprite.setScale(0.8, 0.8);
				lawnsprite.setPosition(-90, 60 + (i * 130));
			}

		}

		void update()
		{
			if (!intersection)
			{
				if (lawnsprite.getPosition().x < -50 && onRoof)
				{
					lawnsprite.move(speed * 0.144f * deltaTime, 0);
				}
				else if (lawnsprite.getPosition().x < -65 && !onRoof)
				{
					lawnsprite.move(speed * 0.144f * deltaTime, 0);
				}
			}
			else
			{
				if (lawnsprite.getPosition().x < 960)
				{
					lawnsprite.move(speed * deltaTime, 0);

					if (startsoundcar)
					{
						PlaySoundEffect(carsSoundBuffer, false);
						startsoundcar = false;
					}
				}
				else
				{
					lawnsprite.setPosition(2000, 2000);
				}
			}
		}
	}car[5];

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

		float attackClock = 0;

	private:
		Time AnimationTime = seconds(0.2f);
		Clock moveBossAnimClock;

		bool resetClock = false;

		float animationClock = 0;

		Vector2f StartPos, EndPos;
		Vector2f HeadOutOfScreenPos = { 800, -400 };
		Vector2f LegFrontOutOfScreenPos = { 900, -50 };
		Vector2f LegBackOutOfScreenPos = { 860, -250 };

	public:
		void Start()
		{
			currentState = EnteringLevel;
			//currentState = PlacingZombies;

			isAttacking = false;
			isSwitchingState = false;
			attackOnce = false;
			resetClock = false;

			attackClock = 0;
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
			//LegFront.setPosition({ 750, -50 });
			LegBack.setTextureRect(IntRect(animationCol * 140, 0, 140, 183));
			LegBack.setTexture(LegEnterTex);
			LegBack.setScale(3, 3);
			LegBack.setPosition({ 1000, -400 });
			//LegBack.setPosition({ 675, -250 });

			Arm.setTexture(armtext);
			Arm.setTextureRect(IntRect(animationCol * 266, 0, 266, 264));
			Arm.setScale(2.6, 2.6);
			Arm.setOrigin(40, 180);
			Arm.setPosition(1400, -500);
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

				isSwitchingState = false;
				isAttacking = false;
				attackOnce = false;
			}
			else if (currentState == IceAttack || currentState == FireAttack)
			{
				//cout << "entered elemental attack animation" << endl;

				Time animTime = seconds(3);

				if (!isAttacking)
				{
					//cout << " attack boolean = true in elemental" << endl;
					StartPos = Head.getPosition();
					EndPos = randElementalAttackPos.first;
					moveBossAnimClock.restart();

					isAttacking = true;
					attackOnce = false;
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
				if (!isAttacking)
				{
					isAttacking = true;
					attackOnce = false;
				}

				Time animspeed = seconds(3);
				Vector2f startFront = { 1100, -300 };

				if (Arm.getPosition().x != x_axisrandomplace && Arm.getPosition().y != y_axisrandomplace)
				{
					if (!resetClock)
					{
						moveBossAnimClock.restart();
						animationCol2 = 0;
						resetClock = true;
					}

					Arm.setTextureRect(IntRect(0 * 266, 0, 266, 264));
					Arm.setTexture(armtext);

					Arm.setPosition(easeInOut(ExpoEaseIn, startFront.x, x_axisrandomplace, moveBossAnimClock, animspeed),
									easeInOut(ExpoEaseIn, startFront.y, y_axisrandomplace, moveBossAnimClock, animspeed));
				}
				else if (animationClock >= seconds(0.45f).asSeconds())
				{
					if (!bosszombies.empty())
					{
						if (bosszombies.back().zombieCollider.getPosition() == Vector2f{0,0})
						{
							bosszombies.back().zombieCollider.setScale(0, 0);
						}
						else
						{
							bosszombies.back().zombieCollider.setScale(1, 1);
						}

						bosszombies.back().CurrentPlantIndex = 45;
						bosszombies.back().started = true;
					}

					resetClock = false;

					Arm.setTextureRect(IntRect(animationCol2 * 266, 0, 266, 264));
					Arm.setTexture(armtext);

					if (animationCol2 < 2)
					{
						animationCol2++;
					}
					else
					{
						zombiePlaceCounter++;
						animationCol2 = 2;
						attackOnce = false;
						isAttacking = false;
						Arm.setPosition(710, -100);
						currentState = StandingIdle;
					}
				}

				//animate leg too
				if (animationClock >= seconds(0.45f).asSeconds())
				{
					//cout << "animate idle leg \n";

					LegFront.setTextureRect(IntRect(animationCol * 140, 0, 140, 183));
					LegFront.setTexture(LegsIdleTex);

					LegBack.setTextureRect(IntRect(animationCol * 140, 0, 140, 183));
					LegBack.setTexture(LegsIdleTex);

					animationCol = (animationCol + 1) % 3;

					animationClock = 0;
				}
			}
			else if (currentState == EnteringLevel)
			{
				Time animspeed = seconds(2);
				Vector2f startFront = { 1100, -300 }, endFront = { 750, -50 };
				Vector2f startBack = { 1000, -400 }, endBack = { 675, -250 };

				if (moveleft)
				{
					if (!resetClock)
					{
						moveBossAnimClock.restart();
						resetClock = true;
					}

					if (animationClock >= AnimationTime.asSeconds())
					{
						//cout << "animate leg \n";
						LegFront.setTextureRect(IntRect(animationCol * 140, 0, 140, 183));
						LegFront.setTexture(LegEnterTex);

						LegBack.setTextureRect(IntRect(animationCol2 * 140, 0, 140, 183));
						LegBack.setTexture(LegEnterTex);

						//move front leg and when moved animate the sprite
						if (LegFront.getPosition() != endFront)
						{
							//cout << "MOVING FRONT LEG " << endl;
							LegFront.setPosition(easeInOut(ExpoEaseIn, startFront.x, endFront.x, moveBossAnimClock, animspeed),
												 easeInOut(ExpoEaseIn, startFront.y, endFront.y, moveBossAnimClock, animspeed));
						}
						else
						{
							if (animationCol < 6)
							{
								animationCol++;
							}
						}
						
						//if front leg is moved and on 2nd frame of animation move back leg
						if (animationCol >= 2)
						{
							if (LegBack.getPosition() != endBack)
							{
								//cout << "MOVING BACK LEG " << endl;
								LegBack.setPosition(easeInOut(ExpoEaseIn, startBack.x, endBack.x, moveBossAnimClock, seconds(3.4)),
													easeInOut(ExpoEaseIn, startBack.y, endBack.y, moveBossAnimClock, seconds(3.4)));
							}
							else
							{
								animationCol2++;

								LegFront.setTextureRect(IntRect(animationCol2 * 140, 0, 140, 183));
								LegFront.setTexture(LegBentEnterTex);
							}
						}

						//if both animations are finished transition to idle animation
						if (animationCol2 == 6 || animationCol == 6)
						{
							animationCol = 0;
							animationCol2 = 0;

							resetClock = false;
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
					//cout << "animate idle leg \n";

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
			attackClock += deltaTime;

			AnimationHandler();
			Attack();

			//if (Keyboard::isKeyPressed(Keyboard::F) && !isAttacking && !isSwitchingState)
			//{
			//	randElementalAttackPos = ElementalAttacksSpawnPoints[rand() % 4];
			//	BossOBJ.currentState = FireAttack;
			//	isSwitchingState = true;
			//	//cout << endl << endl << endl << "+==============================+" << endl;
			//}

			//if (Keyboard::isKeyPressed(Keyboard::G) && !isAttacking && !isSwitchingState)
			//{
			//	randElementalAttackPos = ElementalAttacksSpawnPoints[rand() % 4];
			//	BossOBJ.currentState = IceAttack;
			//	isSwitchingState = true;
			//	//cout << endl << endl << endl << "+==============================+" << endl;
			//}

			//if (Keyboard::isKeyPressed(Keyboard::L) && !isAttacking)
			//{
			//	currentState = StandingIdle;
			//}
			//if (Keyboard::isKeyPressed(Keyboard::A) && !isAttacking)
			//{
			//	currentState = PlacingZombies;
			//	animationCol2 = 0;
			//}
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

		void placeZombie() 
		{
			if (!isAttacking)
			{
				//cout << "Place zombie func" << endl;
				currentState = PlacingZombies;
				animationCol2 = 0;
			}
		}

		void ThrowElementalAttack(BossState attackType) 
		{
			if (!isAttacking && !isSwitchingState)
			{
				//cout << "Throw elemental attack func" << endl;

				randElementalAttackPos = ElementalAttacksSpawnPoints[rand() % 4];
				BossOBJ.currentState = static_cast<BossState>(IceAttack + rand() % FireAttack);;

				isSwitchingState = true;
			}
		}

		void drawBoss(RenderWindow& window)
		{
			if (moveleft)
			{
				if (currentState == EnteringLevel)
				{
					window.draw(LegBack);
					window.draw(LegFront);
				}
				else if (currentState == StandingIdle)
				{
					window.draw(LegBack);
					window.draw(LegFront);
				}
				else if (currentState == HeadIdle || currentState == FireAttack || currentState == IceAttack)
				{
					//cout << "HEAD" << endl;
					window.draw(Head);
				}
				else if (currentState == PlacingZombies)
				{
					window.draw(LegBack);
					window.draw(LegFront);
					window.draw(Arm);
				}
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
					//cout << endl << "ready is true " << endl;
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
					ballAttackCounter++;
					BossOBJ.currentState = HeadIdle;
					BossOBJ.animationCol = 0;
					BossOBJ.isAttacking = false;
					BossOBJ.attackOnce = false;

					BossOBJ.attackClock = 0;
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
					if (collider.getGlobalBounds().intersects(Plants_Zombies::PlantsArray[i].plantCollider.getGlobalBounds())
						&& !(Plants_Zombies::PlantsArray[i].type == Plants_Zombies::Jalapeno && Plants_Zombies::PlantsArray[i].Explosion))
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

	deque<ElementalAttack> elementalAttackArr;

	void Boss::Attack()
	{
		if (!isSwitchingState && isAttacking)
		{
			//cout << "Main attack func" << endl;
			if ((currentState == FireAttack || currentState == IceAttack) && !attackOnce)
			{
				//cout << "entered ball attack func" << endl;
				ElementalAttack projectile;
				projectile.start(currentState, randElementalAttackPos.second);

				elementalAttackArr.push_back(projectile);

				attackOnce = true;
			}
			else if (currentState == PlacingZombies && !attackOnce)
			{
				//cout << "entered zomb attack func" << endl;
				y_axisrandomplace = y_axisplacingzombie[rand() % 5];
				x_axisrandomplace = x_axisplacingzombie[rand() % 3];

				Plants_Zombies::Zombie zombieprefab;
				Plants_Zombies::zombieType randomzombietype = static_cast<Plants_Zombies::zombieType>(rand() % Plants_Zombies::Dead);

				zombieprefab.type = randomzombietype;
				//zombieprefab.type = randomzombietype;

				//adjust position based on zombie type
				if (randomzombietype == Plants_Zombies::gargantous)
				{
					zombieprefab.zombieCont.setPosition(x_axisrandomplace, y_axisrandomplace - 60);
				}
				else 
				{
					zombieprefab.zombieCont.setPosition(x_axisrandomplace, y_axisrandomplace);
				}

				//zombieprefab.zombieCont.setPosition(x_axisrandomplace, y_axisrandomplace);
				zombieprefab.CurrentPlantIndex = 45;
				zombieprefab.zombieCollider.setScale(0, 0);

				zombieprefab.start();

				zombieprefab.isAttacking = false;
				zombieprefab.isDead = false;
				zombieprefab.started = false;
				zombieprefab.PlantInfront = false;

				zombieprefab.isMoving = true;

				bosszombies.push_back(zombieprefab);

				attackOnce = true;
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

	armtext.loadFromFile("Assets/Boss Fight/final arms.png");

	IceBallTopTex.loadFromFile("Assets/Boss Fight/iceball-top.png");
	IceBallBottomTex.loadFromFile("Assets/Boss Fight/iceball-bottom.png");
	FireBallTopTex.loadFromFile("Assets/Boss Fight/fireball-top.png");
	FireBallBottomTex.loadFromFile("Assets/Boss Fight/fireball-bottom.png");
}

void SetupBossData()
{
	srand(time(0));
	elementalAttackArr.clear();
	bosszombies.clear();

	plantedIceAttack = false;
	plantedFireAttack = false;

	startBossfight = false;

	zombieSpawnRate = 8;
	zombiePlaceCounter = 0;
	ballAttackCounter = 0;
	endAttackWave = true;

	BossOBJ.Start();
}

BossState randomAttackType = static_cast<BossState>(rand() % ThrowVan);

void BossStateManager()
{
	if (startBossfight)
	{
		if (endAttackWave)
		{
			if (BossOBJ.currentState == HeadIdle)
			{
				randomAttackType = PlacingZombies;
			}
			else
			{
				//cout << "reset attack wave " << endl;
				randomAttackType = static_cast<BossState>(rand() % ThrowVan);
			}

			BossOBJ.attackClock = 0;
			ballAttackCounter = 0;
			zombiePlaceCounter = 0;
			endAttackWave = false;
		}

		if (randomAttackType == PlacingZombies)
		{
			if (BossOBJ.attackClock >= zombieSpawnRate)
			{
				//cout << "zomb" << endl;
				BossOBJ.placeZombie();
				BossOBJ.attackClock = 0;
			}

			if (zombiePlaceCounter == 5)
			{
				BossOBJ.isSwitchingState = false;
				endAttackWave = true;
			}
		}
		else if (randomAttackType == FireAttack || randomAttackType == IceAttack)
		{
			if (ballAttackCounter == 3)
			{
				//cout << " AAAAAAAAAAAAAAAAAAAALLLLLLLLLLLLLLLLLLOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOooo" << endl;
				endAttackWave = true;
				return;
			}

			if (BossOBJ.attackClock < 4)
			{
				//cout << "Head idle" << endl;
				BossOBJ.currentState = HeadIdle;
			}
			else if (!BossOBJ.isAttacking)
			{
				//cout << "throw ball" << endl;
				BossOBJ.ThrowElementalAttack(randomAttackType);
			}

			//cout << endl << endl << ballAttackCounter << endl << endl;
		}
	}
}

void UpdateBossLogic()
{
	BossStateManager();

#pragma region update elements
	//update elemental attacks and deactivation logic
	for (int i = 0; i < elementalAttackArr.size(); i++)
	{
		elementalAttackArr[i].update();

		for (int j = 0; j < 45; j++)
		{
			//deactivate the ice attacks
			if (Plants_Zombies::PlantsArray[j].type == Plants_Zombies::Jalapeno
				&& (elementalAttackArr[i].type == IceAttack)
				&& (Plants_Zombies::PlantsArray[j].plantCollider.getGlobalBounds().intersects(
				   elementalAttackArr[i].collider.getGlobalBounds()))
				&& elementalAttackArr[i].ready)
			{
				elementalAttackArr[i].active = false;
				break;
			}

			//deactivate the fire attacks
			if (Plants_Zombies::PlantsArray[j].type == Plants_Zombies::IceShroom
				&& Plants_Zombies::PlantsArray[j].ExplosionIce
				&& elementalAttackArr[i].type == FireAttack && elementalAttackArr[i].ready)
			{
				elementalAttackArr[i].active = false;
				break;
			}
		}
	}

	//delete elemental attacks
	elementalAttackArr.erase(remove_if(elementalAttackArr.begin(), elementalAttackArr.end(),
		[](const ElementalAttack& A)
		{
			return A.active == false;
		}), elementalAttackArr.end());

	//intersection of zombies and cars
	for (int i = 0; i < 5; i++)
	{
		FloatRect rect1 = car[i].lawnsprite.getGlobalBounds();

		for (int j = 0; j < bosszombies.size(); j++)
		{
			FloatRect rect2 = bosszombies[j].zombieCollider.getGlobalBounds();

			if (rect1.intersects(rect2) && bosszombies[j].started) {
				car[i].intersection = true;
				bosszombies[j].isSquished = true;
			}
		}
	}

	//update cars
	for (int i = 0; i < 5; i++) {
		car[i].update();
	}

	//update zombies
	for (int i = 0; i < bosszombies.size(); i++) {

		if (bosszombies[i].started && bosszombies[i].type != Plants_Zombies::Dead)
		{
			if (!IsPaused)
			{
				bosszombies[i].update(deltaTime);
			}
		}
	}

	//arrange zombies to be removed at the left then iterate through the dead zombies and removes them
	//leaving the alive zombies unaffected by vector shifting elements
	bosszombies.erase(remove_if(bosszombies.begin(), bosszombies.end(),
		[](const Plants_Zombies::Zombie& z)
		{
			return z.type == Plants_Zombies::Dead;
		}), bosszombies.end());
#pragma endregion

	BossOBJ.Update();
}

void DrawBoss(RenderWindow& window)
{
	//draw elemental attacks
	for (int i = 0; i < elementalAttackArr.size(); i++)
	{
		window.draw(elementalAttackArr[i].spriteBottom);
		window.draw(elementalAttackArr[i].spriteTop);
	}

	//draw zombies
	for (int i = 0; i < bosszombies.size(); i++) 
	{
		if (bosszombies[i].started) 
		{
			window.draw(bosszombies[i].zombieCont);
			window.draw(bosszombies[i].zombieCollider);
		}
	}

	//draw boss
	BossOBJ.drawBoss(window);

}

void endlevel() 
{
	for (int i = 0; i < bosszombies.size(); i++) 
	{
		if (bosszombies[i].zombieCollider.getPosition().x < -50 && bosszombies[i].started)
		{
			if (!playLoseGameAnim)
			{
				PlaySoundEffect(LoseSoundBuffer, false);
				LoseGameClock.restart();
				playLoseGameAnim = true;
			}
			else
			{
				Time animDuration_ = seconds(6);
				if (scalefactortextlosegame > minscaletextlosegame)
				{
					scalefactortextlosegame = easeInOut(linear, scalefactortextlosegame, minscaletextlosegame, LoseGameClock, animDuration_);
					Textlosegamesprite.setScale(scalefactortextlosegame, scalefactortextlosegame);
				}
				else
				{
					IsPaused = true;
					LevelIsOver = true;
					WinLevel = false;
				}
			}
			window.draw(Textlosegamesprite);
		}
	}
}

}

//the calling of this function is in the plants_Zombies header file
//update the plants with the zombie vector
void Plants_Zombies::Plants::updateBossPlantStruct()
{
	int lastZombieProximity = 0;
	if (!isDead) // if not dead will animate and execute action  
	{
		actionTimeClock += deltaTime;
		plantLifeTimeClock += deltaTime;

		//zombie in front checker
		for (int j = 0; j < boss::bosszombies.size(); j++)
		{
			if (!(boss::bosszombies[j].isDead || boss::bosszombies[j].type == Dead) && boss::bosszombies[j].started) // checks if zombie is dead or not to avoid shooting dead zombies
			{
				// checks if a zombie is in front of the plant  
				if ((type == PeaShooter || type == SnowPeaShooter || type == ScaredyShroom)
					&& ((shape.getGlobalBounds().top + shape.getGlobalBounds().height / 2) <= (boss::bosszombies[j].zombieCollider.getGlobalBounds().top + boss::bosszombies[j].zombieCollider.getGlobalBounds().height)
						&& ((shape.getGlobalBounds().top + shape.getGlobalBounds().height / 2) >= boss::bosszombies[j].zombieCollider.getGlobalBounds().top)
						&& (shape.getGlobalBounds().left <= boss::bosszombies[j].zombieCollider.getGlobalBounds().left))
					&& (boss::bosszombies[j].zombieCollider.getPosition().x < 960))
				{
					zombieInFront = true;
					break;
				}
				else if ((type == PuffShroom)
					&& ((shape.getGlobalBounds().top + shape.getGlobalBounds().height / 2) <= (boss::bosszombies[j].zombieCollider.getGlobalBounds().top + boss::bosszombies[j].zombieCollider.getGlobalBounds().height)
						&& ((shape.getGlobalBounds().top + shape.getGlobalBounds().height / 2) >= boss::bosszombies[j].zombieCollider.getGlobalBounds().top)
						&& (shape.getGlobalBounds().left <= boss::bosszombies[j].zombieCollider.getGlobalBounds().left))
					&& (boss::bosszombies[j].zombieCollider.getPosition().x < shape.getPosition().x + (107 * 4))
					&& (boss::bosszombies[j].zombieCollider.getPosition().x < 960))
				{
					zombieInFront = true;
					break;
				}
				else
				{
					zombieInFront = false;
				}
			}
			else
			{
				zombieInFront = false;
			}
		}

		//zombie proximity checker
		if (type == ScaredyShroom)
		{
			for (int j = 0; j < boss::bosszombies.size(); j++)
			{
				if (!(boss::bosszombies[j].isDead || boss::bosszombies[j].type == Dead) && boss::bosszombies[j].started) // checks if zombie is dead or not to avoid shooting dead zombies
				{
					if (((shape.getGlobalBounds().top + shape.getGlobalBounds().height / 2) <= (boss::bosszombies[j].zombieCollider.getGlobalBounds().top + boss::bosszombies[j].zombieCollider.getGlobalBounds().height)
						&& ((shape.getGlobalBounds().top + shape.getGlobalBounds().height / 2) >= boss::bosszombies[j].zombieCollider.getGlobalBounds().top))
						&& (boss::bosszombies[j].zombieCollider.getPosition().x < shape.getPosition().x + (107 * 3.5)))
					{
						//cout << "true \n";
						zombieProximityAction = true;
						lastZombieProximity = j;
						break;
					}
					else
					{
						zombieProximityAction = false;
					}
				}
				else if (lastZombieProximity == j)
				{
					zombieProximityAction = false;
				}
			}
		}
		else if (type == PotatoMine && !zombieProximityAction && GettingUp)
		{
			for (int j = 0; j < boss::bosszombies.size(); j++)
			{
				//!(zombie_array[j].isDead || zombie_array[j].type == Dead || !zombie_array[j].started)
				if (!(boss::bosszombies[j].isDead || boss::bosszombies[j].type == Dead) && boss::bosszombies[j].started) // checks if zombie is dead or not to avoid shooting dead zombies
				{
					if (((shape.getGlobalBounds().top + shape.getGlobalBounds().height / 2) <= (boss::bosszombies[j].zombieCollider.getGlobalBounds().top + boss::bosszombies[j].zombieCollider.getGlobalBounds().height)
						&& ((shape.getGlobalBounds().top + shape.getGlobalBounds().height / 2) >= boss::bosszombies[j].zombieCollider.getGlobalBounds().top)
						&& (shape.getGlobalBounds().left <= boss::bosszombies[j].zombieCollider.getGlobalBounds().left))
						&& (boss::bosszombies[j].zombieCollider.getPosition().x < shape.getPosition().x + (107))
						&& (boss::bosszombies[j].zombieCollider.getPosition().x < 960))

					{
						zombieProximityAction = true;
						animationCol = 0;
						boss::bosszombies[j].health -= damage;
					}
				}
			}
		}
		else if (type == Jalapeno && Explosion)
		{
			for (int j = 0; j < boss::bosszombies.size(); j++)
			{
				//!(zombie_array[j].isDead || zombie_array[j].type == Dead || !zombie_array[j].started)
				if (!(boss::bosszombies[j].isDead || boss::bosszombies[j].type == Dead) && boss::bosszombies[j].started) // checks if zombie is dead or not to avoid shooting dead zombies
				{
					if (plantCollider.getGlobalBounds().intersects(boss::bosszombies[j].zombieCollider.getGlobalBounds()))
					{
						boss::bosszombies[j].health -= damage;
					}
				}
			}
		}
		else if (type == IceShroom && ExplosionIce)
		{
			for (int j = 0; j < boss::bosszombies.size(); j++)
			{
				//!(zombie_array[j].isDead || zombie_array[j].type == Dead || !zombie_array[j].started)
				if (!(boss::bosszombies[j].isDead || boss::bosszombies[j].type == Dead) && boss::bosszombies[j].started) // checks if zombie is dead or not to avoid shooting dead zombies
				{
					boss::bosszombies[j].IsFrozen = true;
				}
			}
		}

		animationHandler();
		action();

		if (!Explosion)
		{
			plantCollider.setPosition(shape.getPosition());
		}
	}
	else if (!mygrid[gridIndex].gravePlanted && !deadPlantingPot)// else if there is not a grave planted there will turn the plant into an empty gameobject  
	{
		if (type == PlantingPot)
		{
			deadPlantingPot = true;
		}

		type = EmptyPlant;
		mygrid[gridIndex].isplanted = false;
		zombieProximityAction = false;
		setupPrefab();
	}

	if (health <= 0 || type == EmptyPlant)
	{
		isDead = true;
		idle = false;
		doAction = false;
		zombieProximityAction = false;
	}
}
