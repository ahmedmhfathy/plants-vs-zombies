// eshta8al ya3am

#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<string>
#include<vector>
#include "Game Settings And Audio.h"
#include "Brightness Shader.h"
using namespace std;
using namespace sf;

namespace Plants_Zombies
{
	int score;
	bool onRoof;

#pragma region Forward Declaration for Structs
	struct Zombie;
	struct PlantProjectile;
	struct Plant;
	vector<PlantProjectile> PlantProjectilesARR;
#pragma endregion

#pragma region Plants and Zombies Types
	enum PlantType { PeaShooter, SnowPeaShooter, PlantingPot, Jalapeno, IceShroom, SunFlower, WallNut, PotatoMine, SunShroom, ScaredyShroom, PuffShroom, EmptyPlant, SunCoin, Shovel };
	enum zombieType { regular, bucketHat, trafficCone, soccerGuy, newsMan, jackInTheBox, screenDoor, gargantous, poleVault, Dead, imp };
#pragma endregion

#pragma region Declaring Texures
	//peashooter
	Texture PeaShooterIdleTex;
	Texture PeaShooterShootTex;
	Texture PeaShooterProjectileTex;
	//Sunflower
	Texture SunFlowerIdleTex;
	Texture SunFlowerProducingSunTex;
	Texture SunFlowerSunTex;
	//WallNut
	Texture WallNutIdleTex;
	//Potato Mine
	Texture PotatoMineTransitionTex;
	Texture PotatoMineIdelTex;
	Texture PotatoExplosionTex;
	//Jalapeno
	Texture JalapenoExplosionTex;
	Texture JalapenoFireTex;
	//Ice Shroom
	Texture IceShroomIdelTex;
	Texture IceShroomIceTex;
	//IcePeaShooter
	Texture IcePeaShooterIdleTex;
	Texture IcePeaShooterShootTex;
	Texture IcePeaShooterProjectileTex;
	//SunShroom
	Texture SunShroomIdleTex;
	Texture SunShroomProducingSunTex;
	//PuffShroom
	Texture PuffShroomTex;
	Texture PuffShroomBulletTex;
	//ScaredyShroom
	Texture ScaredyShroomIdleTex;
	Texture ScaredyShroomHideTex;
	Texture ScaredyShroomAttackTex;
	//planting pot
	Texture PlantingPotIdleTex;
#pragma endregion

#pragma region Sounds
	SoundBuffer SunCoinSoundBuffer;
	SoundBuffer PeaShootSoundBuffer;
	SoundBuffer SplatSoundBuffer[3];
	SoundBuffer ZombieEatSoundBuffer[3];
	SoundBuffer newsmanyellbuffer[2];
	SoundBuffer newsManPaperRipSoundBuffer;
	SoundBuffer BucketHatHitSoundBuffer[2];
	SoundBuffer jackSong;
	SoundBuffer jackBombSound;
	SoundBuffer jackSurprise;
	SoundBuffer GargantousDeathSound;
	SoundBuffer GargantousCrushSound;
	SoundBuffer ImpSpawnSound;
	SoundBuffer poleJumpSound;
	SoundBuffer JalapenoFireBuffer;
	SoundBuffer IceShroomFreezeBuffer;
	SoundBuffer PotatoMineBoomBuffer;
#pragma endregion

#pragma region Plants
	//will load all textures once
	void LoadPlantTexturesAndSounds() {
		//Audio
		SunCoinSoundBuffer.loadFromFile("Audio/points.ogg");
		//Ice shroom
		IceShroomFreezeBuffer.loadFromFile("Audio/Plants/frozen.ogg");
		//Jalapeno
		JalapenoFireBuffer.loadFromFile("Audio/Plants/jalapeno.ogg");
		//Potato mine
		PotatoMineBoomBuffer.loadFromFile("Audio/Plants/potato_mine.ogg");
		//SunCoinSound.setBuffer(SunCoinSoundBuffer);
		PeaShootSoundBuffer.loadFromFile("Audio/Plants/peaShoot1.ogg");
		//ShootSound.setBuffer(PeaShootSoundBuffer);
		SplatSoundBuffer[0].loadFromFile("Audio/Plants/splat1.ogg");
		SplatSoundBuffer[1].loadFromFile("Audio/Plants/splat2.ogg");
		SplatSoundBuffer[2].loadFromFile("Audio/Plants/splat3.ogg");
		ZombieEatSoundBuffer[0].loadFromFile("Audio/Zombies/eat1.ogg");
		ZombieEatSoundBuffer[1].loadFromFile("Audio/Zombies/eat2.ogg");
		ZombieEatSoundBuffer[2].loadFromFile("Audio/Zombies/eat3.ogg");
		newsmanyellbuffer[0].loadFromFile("Audio/Zombies/newspaper_rarrgh.ogg");
		newsmanyellbuffer[1].loadFromFile("Audio/Zombies/newspaper_rarrgh2.ogg");
		newsManPaperRipSoundBuffer.loadFromFile("Audio/Zombies/newspaper_rip.ogg");
		//newsManPaperRipSound.setBuffer(newsManPaperRipSoundBuffer);
		BucketHatHitSoundBuffer[0].loadFromFile("Audio/Zombies/shieldhit.ogg");
		BucketHatHitSoundBuffer[1].loadFromFile("Audio/Zombies/shieldhit2.ogg");
		// Jack in The box
		jackBombSound.loadFromFile("Audio/Zombies/jackBomb.ogg");
		jackSong.loadFromFile("Audio/Zombies/jackSong.ogg");
		jackSurprise.loadFromFile("Audio/Zombies/jackSuprise.ogg");
		// gargantous
		GargantousDeathSound.loadFromFile("Audio/Zombies/gargantousdeathsound.ogg");
		GargantousCrushSound.loadFromFile("Audio/Zombies/gargantouscrushsound.ogg");
		ImpSpawnSound.loadFromFile("Audio/Zombies/impVoice.ogg");
		// pole vault
		poleJumpSound.loadFromFile("Audio/Zombies/polevaultjump.ogg");
		//PeaShooter
		PeaShooterIdleTex.loadFromFile("Assets/Plants/PeaShooter/peashooter-idle-ST.png");
		PeaShooterShootTex.loadFromFile("Assets/Plants/PeaShooter/peashooter-shooting-ST.png");
		PeaShooterProjectileTex.loadFromFile("Assets/Plants/PeaShooter/peashooter-bullet.png");
		//sunflower
		SunFlowerIdleTex.loadFromFile("Assets/Plants/SunFlower/sunflower-idle-ST.png");
		SunFlowerProducingSunTex.loadFromFile("Assets/Plants/SunFlower/sunflower-producingsun_ST.png");
		SunFlowerSunTex.loadFromFile("Assets/Sun/sun-ST.png");
		//SnowPeaShooter
		IcePeaShooterIdleTex.loadFromFile("Assets/Plants/IcePeaShooter/icepeashooter-idle-ST2.png");
		IcePeaShooterShootTex.loadFromFile("Assets/Plants/IcePeaShooter/icepeashooter-shooting-ST.png");
		IcePeaShooterProjectileTex.loadFromFile("Assets/Plants/IcePeaShooter/icepeashooter-bullet.png");
		//wallnut
		WallNutIdleTex.loadFromFile("Assets/Plants/WallNut/wallnut-ST.png");
		//Potato Mine
		PotatoMineTransitionTex.loadFromFile("Assets/Plants/Potato Mine/Potato Transition.png");
		PotatoMineIdelTex.loadFromFile("Assets/Plants/Potato Mine/Potato Idel.png");
		PotatoExplosionTex.loadFromFile("Assets/Plants/Potato Mine/Explosion.png");
		//Jalapeno
		JalapenoExplosionTex.loadFromFile("Assets/Plants/Jalapeno/Explosion.png");
		JalapenoFireTex.loadFromFile("Assets/Plants/Jalapeno/Fire2.png");
		//Ice Shroom
		IceShroomIdelTex.loadFromFile("Assets/Plants/Ice shroom/Ice shroom idel.png");
		IceShroomIceTex.loadFromFile("Assets/Plants/Ice shroom/Ice boom2.png");
		

		//SunShroom
		SunShroomIdleTex.loadFromFile("Assets/Plants/SunShroom/SunShroom-idle-ST.png");
		SunShroomProducingSunTex.loadFromFile("Assets/Plants/SunShroom/SunShroom-producing-ST.png");
		//PuffShroom
		PuffShroomTex.loadFromFile("Assets/Plants/PuffShroom/puffshroom-idle-ST.png");
		PuffShroomBulletTex.loadFromFile("Assets/Plants/PuffShroom/puffshroom-bullet.png");
		//ScaredyShroom
		ScaredyShroomIdleTex.loadFromFile("Assets/Plants/ScaredyShroom/ScaredyShroom-idle-ST.png");
		ScaredyShroomHideTex.loadFromFile("Assets/Plants/ScaredyShroom/ScaredyShroom-hide-ST.png");
		ScaredyShroomAttackTex.loadFromFile("Assets/Plants/ScaredyShroom/ScaredyShroom-attack-ST.png");
		//planting pot
		PlantingPotIdleTex.loadFromFile("Assets/Plants/PlantingPot/plantingpot-idle-ST.png");
	}

	struct PlantProjectile
	{
		//string type;
		PlantType type;
		Sprite shape;

		float damage;
		float slowMultiplier = 1;
		float speed;

		Time projectileLifeSpan;
		float clockTime = 0;

		int sunCoinYLimt;
		int sunValue;

		void start(PlantType plantType, float PlantDamage, Vector2f SpwanPos, int yLimit, int sunValue_)
		{
			clockTime = 0;
			type = plantType;
			sunValue = sunValue_;

			if (type == PeaShooter)
			{
				shape.setTexture(PeaShooterProjectileTex);
				shape.setScale(3.5, 3.5);
				shape.setPosition(SpwanPos);

				speed = 350;
				damage = PlantDamage;
				slowMultiplier = 1; // wont affect anything
			}
			else if (type == SnowPeaShooter)
			{
				shape.setTexture(IcePeaShooterProjectileTex);
				shape.setScale(3.5, 3.5);
				shape.setPosition(SpwanPos);

				speed = 350;
				damage = PlantDamage;
				slowMultiplier = 0.3;
			}
			else if (type == PuffShroom || type == ScaredyShroom)
			{
				shape.setTexture(PuffShroomBulletTex);
				shape.setScale(3.5, 3.5);
				shape.setPosition(SpwanPos);

				speed = 350;
				damage = PlantDamage;
				slowMultiplier = 1; // wont affect anything
			}
			else if (type == SunFlower || type == SunCoin || type == SunShroom)
			{
				shape.setTexture(SunFlowerSunTex);
				shape.setPosition(SpwanPos);

				shape.setOrigin({ shape.getLocalBounds().width / 2, shape.getLocalBounds().height / 2 });
				projectileLifeSpan = seconds(12); //time to despawn

				if (sunValue == 25)
				{
					shape.setScale(1.25, 1.25);
				}
				else if (sunValue == 15)
				{
					shape.setScale(0.85, 0.85);
				}

				speed = 65;
				damage = PlantDamage;
				slowMultiplier = 1;
				sunCoinYLimt = yLimit;
			}
		}
		void update()
		{
			clockTime += deltaTime;
			if (type == PeaShooter || type == SnowPeaShooter || type == PuffShroom || type == ScaredyShroom)
			{
				shape.move(speed * deltaTime, 0);
			}
			else if (type == SunFlower || type == SunShroom)
			{
				shape.rotate(0.5);
			}
			else if (type == SunCoin)
			{
				if (shape.getPosition().y < sunCoinYLimt)
				{
					shape.move(0, speed * deltaTime);
				}
				shape.rotate(0.5);
			}
		}
	};

	struct Plants {
		RectangleShape plantCollider;

		Sprite shape;
		PlantType type;

		int gridIndex; //<<<<<<<<---------------<<< for the grid system
		bool deadPlantingPot;

		float health;
		float damage;

		bool ExplosionIce = false;
		bool Explosion = false;

	private:
		bool zombieInFront = false;
		bool zombieProximityAction = false;
		bool isHiding = false;
		bool GettingUp = false;
		bool checkdeathpos = false;

		int animationCol = 0;
		int animationRow = 0;

		bool doAction = false;
		bool idle = true;
		bool isDead = false;

		bool playActionSound = true;

		Clock animationClock;
		Time timeForAction, animationSpeed = seconds(0.2); // time for each frame
		float actionTimeClock, plantLifeTimeClock = 0;

	public:
		// calls function when you spawn the plant
		void start() {
			setupPrefab();
		}

		void takeDmg(float damage) {
			health -= damage;
			//cout << "Plant Health = " << health << endl;
			if (health <= 0)
			{
				idle = false;
				doAction = false;
				isDead = true;
			}
		}

		void updatePlantStruct(Zombie* zombie_array); // Defined at the planting system
		void updateBossPlantStruct(); // Defined at the boss system system

	private:
		void animationHandler() {
			if (animationSpeed <= animationClock.getElapsedTime() && type != EmptyPlant)
			{
				if (type == PeaShooter)
				{
					if (idle)
					{
						shape.setTextureRect(IntRect(animationCol * 30, 0, 30, 34));
						shape.setTexture(PeaShooterIdleTex);
						animationCol = (animationCol + 1) % 8;
					}
					else if (doAction) 
					{
						if (animationCol + 1 == 3)
						{
							doAction = false;
							idle = true;
							isDead = false;
						}

						shape.setTextureRect(IntRect(animationCol * 30, 0, 30, 34));
						shape.setTexture(PeaShooterShootTex);
						animationCol = (animationCol + 1) % 3;

						if (playActionSound)
						{
							PlaySoundEffect(PeaShootSoundBuffer, true);
							playActionSound = false;
						}
					}
				}
				else if (type == SnowPeaShooter) 
				{
					if (idle)
					{
						shape.setTextureRect(IntRect(animationCol * 32, 0, 32, 34));
						shape.setTexture(IcePeaShooterIdleTex);

						animationCol = (animationCol + 1) % 8;
					}
					else if (doAction) 
					{
						if (animationCol + 1 == 3)
						{
							doAction = false;
							idle = true;
							isDead = false;
						}
						shape.setTextureRect(IntRect(animationCol * 31, 0, 31, 34));
						shape.setTexture(IcePeaShooterShootTex);

						animationCol = (animationCol + 1) % 3;

						if (playActionSound)
						{
							PlaySoundEffect(PeaShootSoundBuffer, true);
							playActionSound = false;
						}
					}
				}
				else if (type == SunFlower) 
				{
					if (idle)
					{
						shape.setTextureRect(IntRect(animationCol * 32, 0, 32, 34));
						shape.setTexture(SunFlowerIdleTex);

						animationCol = (animationCol + 1) % 6;
					}
					else if (doAction) 
					{
						if (animationCol + 1 == 6)
						{
							doAction = false;
							idle = true;
							isDead = false;
						}

						shape.setTextureRect(IntRect(animationCol * 32, 0, 32, 34));
						shape.setTexture(SunFlowerProducingSunTex);
					
						animationCol = (animationCol + 1) % 6;
					}
				}
				else if (type == WallNut) { //always idle
					if (health >= 1000)
					{
						animationRow = 0;
						shape.setTextureRect(IntRect(animationCol * 28, animationRow * 31, 28, 31));
						animationCol = (animationCol + 1) % 5;
					}
					else if (health >= 500) {
						animationRow = 1;
						shape.setTextureRect(IntRect(animationCol * 28, animationRow * 31, 28, 31));
						animationCol = (animationCol + 1) % 5;
					}
					else
					{
						animationRow = 2;
						shape.setTextureRect(IntRect(animationCol * 28, animationRow * 31, 28, 31));
						animationCol = (animationCol + 1) % 5;
					}
				}
				else if (type == PotatoMine)
				{
					if (!GettingUp)
					{
						if (timeForAction.asSeconds() <= plantLifeTimeClock)
						{

							shape.setTextureRect(IntRect(animationCol * 30, 0, 30, 26));
							animationCol++;
							if (animationCol == 3)
							{
								GettingUp = true;
								animationCol = 0;
							}
						}
						else
						{
							shape.setTextureRect(IntRect(0, 0, 30, 26));
							shape.setTexture(PotatoMineTransitionTex);
						}
					}
					else if (GettingUp)
					{
						if (!zombieProximityAction)
						{
							shape.setTexture(PotatoMineIdelTex);
							shape.setTextureRect(IntRect(29 * animationCol, 0, 29, 26));
							animationCol = (animationCol + 1) % 5;
						}
						else if (zombieProximityAction)
						{
							if (checkdeathpos == false) {
								shape.setPosition(shape.getPosition().x - 90, shape.getPosition().y - 130);
								checkdeathpos = true;
								PlaySoundEffect(PotatoMineBoomBuffer, false);
							}
							shape.setTextureRect(IntRect(animationCol * 80, 0, 80, 70));
							shape.setTexture(PotatoExplosionTex);
							animationCol++;
							if (animationCol == 8)
							{
								isDead = true;
							}
						}
					}

				}
				else if (type == Jalapeno)
				{
					if (!Explosion)
					{
						shape.setTextureRect(IntRect(animationCol * 32, 0, 32, 36));
						shape.setTexture(JalapenoExplosionTex);
						animationCol++;

						if (animationCol == 6)
						{
							plantCollider.setSize({ 2920, 39 });

							plantCollider.setPosition(shape.getPosition().x - 1100, shape.getPosition().y);

							animationCol = 0;
							Explosion = true;
							PlaySoundEffect(JalapenoFireBuffer,false);
						}
					}
					else if (Explosion)
					{ 
						shape.setTextureRect(IntRect(0, animationRow * 54, 2920, 54));
						shape.setTexture(JalapenoFireTex);

						shape.setScale(1, 1);
						plantCollider.setOrigin(plantCollider.getGlobalBounds().width / 2, plantCollider.getGlobalBounds().height / 2);
						shape.setOrigin(shape.getGlobalBounds().width / 2, shape.getGlobalBounds().height / 2);

						if (animationRow == 3)
						{
							shape.setPosition(shape.getPosition().x, shape.getPosition().y + 50);
							plantCollider.setSize({ 0,0 });
						}
						else if (animationRow == 2)
						{
							shape.setPosition(shape.getPosition().x, shape.getPosition().y);
						}
						else if (animationRow == 1)
						{
							shape.setPosition(shape.getPosition().x, shape.getPosition().y - 25);
							plantCollider.setSize({ 0,0 });
						}
						else if (animationRow == 0)
						{
							shape.setPosition(shape.getPosition().x, shape.getPosition().y - 10);
							plantCollider.setSize({ 0,0 });
						}
						else if (animationRow < 0)
						{
							plantCollider.setOrigin(0, 0);
							shape.setOrigin(0, 0);
							
							Explosion = false;
							isDead = true;
						}

						animationRow--;
					}
				}
				else if (type == IceShroom)
				{
					if (!ExplosionIce)
					{
						shape.setTextureRect(IntRect(animationCol * 39, 0, 39, 34));
						shape.setTexture(IceShroomIdelTex);

						animationCol++;

						if (animationCol == 4)
						{
							animationCol = 0;

							shape.setTextureRect(IntRect(animationCol * 200, 0, 200, 170));
							shape.setTexture(IceShroomIceTex);
	
							shape.setScale(3.5, 3.5);
							shape.setPosition(shape.getPosition().x -300, shape.getPosition().y - 85*3);

							plantCollider.setSize({0,0});

							ExplosionIce = true;
							PlaySoundEffect(IceShroomFreezeBuffer, false);
						} 
					}
					else if (ExplosionIce)
					{
						//shape.setTextureRect(IntRect(animationCol * 196, 0, 196, 164));
						shape.setTextureRect(IntRect(animationCol * 200, 0, 200, 170));
						shape.setTexture(IceShroomIceTex);
						animationCol++;

						if (animationCol == 6)
						{
							cout << "Nigaaaa";
							isDead = true;
							ExplosionIce = false;
						}
					}
				}
				else if (type == SunShroom)
				{
					if (plantLifeTimeClock >= seconds(120).asSeconds())
					{
						animationRow = 1;
					}

					if (idle)
					{
						shape.setTextureRect(IntRect(animationCol * 28, animationRow * 31, 28, 31));
						shape.setTexture(SunShroomIdleTex);
						animationCol = (animationCol + 1) % 5;
					}
					else if (doAction)
					{
						if (animationCol + 1 == 5)
						{
							doAction = false;
							idle = true;
							isDead = false;
						}
						shape.setTextureRect(IntRect(animationCol * 28, animationRow * 31, 28, 31));
						shape.setTexture(SunShroomProducingSunTex);

						animationCol = (animationCol + 1) % 5;
					}
				}
				else if (type == PuffShroom)
				{
					if (idle)
					{
						shape.setTextureRect(IntRect(animationCol * 28, 0, 28, 31));
						shape.setTexture(PuffShroomTex);

						animationCol = (animationCol + 1) % 5;
					}
					else if (doAction)
					{
						if (animationCol + 1 == 5)
						{
							doAction = false;
							idle = true;
							isDead = false;
						}

						shape.setTextureRect(IntRect(animationCol * 28, 0, 28, 31));
						shape.setTexture(PuffShroomTex);

						animationCol = (animationCol + 1) % 5;

						if (playActionSound)
						{
							PlaySoundEffect(PeaShootSoundBuffer, true);
							playActionSound = false;
						}
					}
				}
				else if (type == ScaredyShroom)
				{
					//cout << zombieProximityAction << endl;
					shape.setTextureRect(IntRect(animationCol * 28, 0, 28, 31));

					if (!zombieProximityAction)
					{
						if (isHiding)
						{
							animationCol--;
							if (animationCol == 0)
							{
								shape.setTexture(ScaredyShroomIdleTex);
								isHiding = false;
							}
						}
						else if (idle)
						{
							//shape.setTextureRect(IntRect(animationCol * 28, 0, 28, 31));
							shape.setTexture(ScaredyShroomIdleTex);

							animationCol = (animationCol + 1) % 4;
						}
						else if (doAction)
						{
							if (animationCol + 1 == 3)
							{
								doAction = false;
								idle = true;
								isDead = false;
							}

							//shape.setTextureRect(IntRect(animationCol * 28, 0, 28, 31));
							shape.setTexture(ScaredyShroomAttackTex);

							animationCol = (animationCol + 1) % 3;

							if (playActionSound)
							{
								PlaySoundEffect(PeaShootSoundBuffer, true);
								playActionSound = false;
							}
						}
					}
					else
					{
						if (!isHiding)
						{
							animationCol = 0;
							isHiding = true;
						}
						else
						{
							//shape.setTextureRect(IntRect(animationCol * 28, 0, 28, 31));
							shape.setTexture(ScaredyShroomHideTex);

							if (animationCol < 2)
							{
								doAction = false;
								idle = true;
								isDead = false;
								animationCol++;
							}
						}
					}
				}

				animationClock.restart();
			}
		}

		void action() {

			if (timeForAction.asSeconds() <= actionTimeClock && type != EmptyPlant)
			{
				if (type == PeaShooter && zombieInFront) //shoot
				{
					animationCol = 0;
					doAction = true;
					playActionSound = true;
					idle = false;
					isDead = false;

					PlantProjectile bullet;
					bullet.start(type, damage, shape.getPosition() + Vector2f({ 12 , -24 }), 0, 0);

					PlantProjectilesARR.push_back(bullet);
				}
				else if (type == SnowPeaShooter && zombieInFront) // shoot
				{
					animationCol = 0;
					doAction = true;
					playActionSound = true;
					idle = false;
					isDead = false;

					PlantProjectile bullet;
					bullet.start(type, damage, shape.getPosition() + Vector2f({ 12, -24 }), 0, 0);

					PlantProjectilesARR.push_back(bullet);
				}
				else if (type == SunFlower) //spawn sun
				{
					int sunValue = 25;
					doAction = true;
					idle = false;
					isDead = false;

					PlantProjectile sunCoin;
					sunCoin.start(type, damage, shape.getPosition() + Vector2f({ 0, 0 }), 0, sunValue);

					PlantProjectilesARR.push_back(sunCoin);
				}
				else if (type == SunShroom)
				{
					int sunValue;
					if (plantLifeTimeClock >= seconds(120).asSeconds())
					{
						sunValue = 25;
					}
					else
					{
						sunValue = 15;
					}

					doAction = true;
					idle = false;
					isDead = false;

					PlantProjectile sunCoin;
					sunCoin.start(type, damage, shape.getPosition() + Vector2f({ 0, 0 }), 0, sunValue);

					PlantProjectilesARR.push_back(sunCoin);
				}
				else if (type == PuffShroom && zombieInFront)
				{
					doAction = true;
					playActionSound = true;
					idle = false;
					isDead = false;

					PlantProjectile bullet;
					bullet.start(type, damage, shape.getPosition() + Vector2f({ 12 , 25 }), 0, 0);

					PlantProjectilesARR.push_back(bullet);
				}
				else if (type == ScaredyShroom && zombieInFront && !isHiding)
				{
					animationCol = 0;
					doAction = true;
					playActionSound = true;
					idle = false;
					isDead = false;

					PlantProjectile bullet;
					bullet.start(type, damage, shape.getPosition() + Vector2f({ 30 , 10 }), 0, 0);

					PlantProjectilesARR.push_back(bullet);
				}
				actionTimeClock = 0;
			}
		}

		//setup all the plants
		void setupPrefab() {
			srand(time(0)); //gives random time for the animation to be random

			actionTimeClock = 0;
			plantLifeTimeClock = 0;

			animationRow = 0;
			animationCol = 0;

			//setup the current state of the plants
			doAction = false;
			idle = true;
			isDead = false;
			playActionSound = true;
			zombieProximityAction = false;
			isHiding = false;
			GettingUp = false;
			checkdeathpos = false;
			Explosion = false;
			ExplosionIce = false;
			//isPlantingPotArray = false;

			if (type == EmptyPlant) {
				doAction = false;
				idle = false;
				isDead = true;

				health = 0;
				damage = 0;
				shape.setScale(0, 0);
			}
			else if (type == PeaShooter)
			{
				health = 100;
				damage = 20;
				timeForAction = seconds(1.5); // time to shoot

				//ActionSound.setBuffer(PeaShootSoundBuffer);
				plantCollider.setSize({ 30, 34 });

				animationCol = rand() % 8;
				shape.setTextureRect(IntRect(animationCol * 30, 0, 30, 34));
				shape.setTexture(PeaShooterIdleTex);
				shape.setScale(3.5, 3.5);
			}
			else if (type == SnowPeaShooter)
			{
				health = 100;
				damage = 20;
				timeForAction = seconds(1.5); // time to shoot

				plantCollider.setSize({ 31, 34 });

				animationCol = rand() % 8;
				shape.setTextureRect(IntRect(animationCol * 32, 0, 32, 34));
				shape.setTexture(IcePeaShooterProjectileTex);
				shape.setScale(3.5, 3.5);
			}
			else if (type == SunFlower) {
				health = 100;
				damage = 0;
				timeForAction = seconds(14); // time to spawn sun 24

				plantCollider.setSize({ 32, 34 });

				animationCol = rand() % 6;
				shape.setTextureRect(IntRect(animationCol * 32, 0, 32, 34));
				shape.setTexture(SunFlowerIdleTex);
				shape.setScale(3.5, 3.5);
			}
			else if (type == WallNut) {
				health = 1400;
				damage = 0;

				animationCol = rand() % 5;
				plantCollider.setSize({ 28, 31 });
				shape.setTextureRect(IntRect(animationCol * 28, animationRow * 31, 28, 31));
				shape.setTexture(WallNutIdleTex);
				shape.setScale(3.5, 3.5);
			}
			else if (type == PotatoMine)
			{
				health = 100;
				damage = 9999;

				timeForAction = seconds(14); // time to transition

				plantCollider.setSize({ 32,34 });


				shape.setTextureRect(IntRect(0, 0, 30, 26));
				shape.setTexture(PotatoMineTransitionTex);
				shape.setScale(3.5, 3.5);
			}
			else if (type == Jalapeno)
			{
				health = 1000;
				damage = 99999;

				timeForAction = seconds(0.5);

				plantCollider.setSize({ 25,25 });

				shape.setTextureRect(IntRect(0, 0, 32, 36));
				shape.setTexture(JalapenoExplosionTex);
				shape.setScale(3.5, 3.5);
				animationRow = 3;

			}
			else if (type == IceShroom)
			{
				health = 1000;
				damage = 20;

				timeForAction = seconds(0.5);

				plantCollider.setSize({ 25,25 });

				shape.setTextureRect(IntRect(0,0,39,34));
				shape.setTexture(IceShroomIdelTex);
				shape.setScale(3.5, 3.5);
			}
			else if (type == SunShroom)
			{
				health = 50;
				damage = 0;
				timeForAction = seconds(10);

				plantCollider.setSize({ 22, 27 });

				animationCol = rand() % 5;
				shape.setTextureRect(IntRect(animationCol * 28, animationRow * 31, 28, 31));
				shape.setTexture(SunShroomIdleTex);
				shape.setScale(3.5, 3.5);
				animationRow = 0;
			}
			else if (type == PuffShroom)
			{
				health = 50;
				damage = 20;
				timeForAction = seconds(1.5);

				plantCollider.setSize({ 22, 27 });

				animationCol = rand() % 5;
				shape.setTextureRect(IntRect(animationCol * 28, 0, 28, 31));
				shape.setTexture(SunShroomIdleTex);
				shape.setScale(3.5, 3.5);
			}
			else if (type == ScaredyShroom)
			{
				health = 100;
				damage = 20;
				timeForAction = seconds(1.5);

				plantCollider.setSize({ 22, 27 });
				animationCol = rand() % 4;
				shape.setTextureRect(IntRect(animationCol * 28, 0, 28, 31));
				shape.setTexture(ScaredyShroomIdleTex);
				shape.setScale(3.5, 3.5);
			}
			else if (type == PlantingPot)
			{
				health = 100;
				damage = 0;

				deadPlantingPot = true; // this is a planting pot, not a plant

				plantCollider.setSize({ 25, 30 });
				shape.setTextureRect(IntRect(0, 0, 27, 30));
				shape.setTexture(PlantingPotIdleTex);
				shape.setScale(3, 2.85);
			}

			plantCollider.setScale(2.9, 2);
			plantCollider.setFillColor(Color(252, 186, 3, 180));
		}
	}PlantsArray[45], PlantingPotArray[45];

	void UpdatePlants(Zombie* zombie_array, Vector2f mousepos)
	{
		//deletes outdated projectiles
		for (int i = 0; i < PlantProjectilesARR.size(); i++)
		{
			if (!PlantProjectilesARR.empty()
				&& (PlantProjectilesARR[i].type == PeaShooter || PlantProjectilesARR[i].type == SnowPeaShooter || PlantProjectilesARR[i].type == PuffShroom)
				&& PlantProjectilesARR[i].shape.getPosition().x > 1000) //enter despawn position
			{
				PlantProjectilesARR.erase(PlantProjectilesARR.begin() + i);
				i--;
			}
			else if (!PlantProjectilesARR.empty()
				&& (PlantProjectilesARR[i].type == SunFlower || PlantProjectilesARR[i].type == SunCoin || PlantProjectilesARR[i].type == SunShroom)
				&& (PlantProjectilesARR[i].projectileLifeSpan.asSeconds() <= PlantProjectilesARR[i].clockTime))
			{
				PlantProjectilesARR.erase(PlantProjectilesARR.begin() + i);
				i--;
			}
		}

		for (int i = 0; i < PlantProjectilesARR.size(); i++)
		{
			PlantProjectilesARR[i].update();
			if ((PlantProjectilesARR[i].type == SunFlower || PlantProjectilesARR[i].type == SunCoin || PlantProjectilesARR[i].type == SunShroom)
				&& PlantProjectilesARR[i].shape.getGlobalBounds().contains(mousepos)
				&& Mouse::isButtonPressed(Mouse::Left))
			{
				PlaySoundEffect(SunCoinSoundBuffer, true);
				score += PlantProjectilesARR[i].sunValue;
				PlantProjectilesARR.erase(PlantProjectilesARR.begin() + i);
				i--;
			}
		}

		for (int i = 0; i < 45; i++)
		{
			PlantsArray[i].updatePlantStruct(zombie_array);
			PlantingPotArray[i].updatePlantStruct(zombie_array);
		}
	}

	void UpdateBossPlants(Vector2f mousepos)
	{
		//deletes outdated projectiles
		for (int i = 0; i < PlantProjectilesARR.size(); i++)
		{
			if (!PlantProjectilesARR.empty()
				&& (PlantProjectilesARR[i].type == PeaShooter || PlantProjectilesARR[i].type == SnowPeaShooter || PlantProjectilesARR[i].type == PuffShroom)
				&& PlantProjectilesARR[i].shape.getPosition().x > 1000) //enter despawn position
			{
				PlantProjectilesARR.erase(PlantProjectilesARR.begin() + i);
				i--;
			}
			else if (!PlantProjectilesARR.empty()
				&& (PlantProjectilesARR[i].type == SunFlower || PlantProjectilesARR[i].type == SunCoin || PlantProjectilesARR[i].type == SunShroom)
				&& (PlantProjectilesARR[i].projectileLifeSpan.asSeconds() <= PlantProjectilesARR[i].clockTime))
			{
				PlantProjectilesARR.erase(PlantProjectilesARR.begin() + i);
				i--;
			}
		}

		for (int i = 0; i < PlantProjectilesARR.size(); i++)
		{
			PlantProjectilesARR[i].update();
			if ((PlantProjectilesARR[i].type == SunFlower || PlantProjectilesARR[i].type == SunCoin || PlantProjectilesARR[i].type == SunShroom)
				&& PlantProjectilesARR[i].shape.getGlobalBounds().contains(mousepos)
				&& Mouse::isButtonPressed(Mouse::Left))
			{
				PlaySoundEffect(SunCoinSoundBuffer, true);
				score += PlantProjectilesARR[i].sunValue;
				PlantProjectilesARR.erase(PlantProjectilesARR.begin() + i);
				i--;
			}
		}

		for (int i = 0; i < 45; i++)
		{
			PlantsArray[i].updateBossPlantStruct();
			PlantingPotArray[i].updateBossPlantStruct();
		}
	}

	void DrawPlantsAndProjectiles(RenderWindow& window) 
	{
		for (int i = 0; i < PlantProjectilesARR.size(); i++)
		{
			if (PlantProjectilesARR[i].type == PeaShooter || PlantProjectilesARR[i].type == SnowPeaShooter ||
				PlantProjectilesARR[i].type == PuffShroom || PlantProjectilesARR[i].type == ScaredyShroom)
			{
				window.draw(PlantProjectilesARR[i].shape);
			}
		}

		for (int i = 0; i < 45; i++)
		{
			if (!(PlantingPotArray[i].type == EmptyPlant || PlantingPotArray[i].health <= 0))
			{
				//window.draw(PlantingPotArray[i].plantCollider);
				window.draw(PlantingPotArray[i].shape);
			}

			if (!(PlantsArray[i].type == EmptyPlant || PlantsArray[i].health <= 0))
			{
				//window.draw(PlantsArray[i].plantCollider);
				window.draw(PlantsArray[i].shape);
			}
		}

		for (int i = 0; i < PlantProjectilesARR.size(); i++)
		{
			if (PlantProjectilesARR[i].type == SunFlower || PlantProjectilesARR[i].type == SunCoin || PlantProjectilesARR[i].type == SunShroom)
			{
				window.draw(PlantProjectilesARR[i].shape);
			}
		}
	}
#pragma endregion

#pragma region Zombies
	// ZOMBIES =============================================

#pragma region Texture Decalration
	//Regular
	Texture RegularWalkText;
	Texture RegularIdleText;
	Texture RegularAttackText;
	Texture RegularDeathText;
	// TrafficCone
	Texture TrafficConeWalkText;
	Texture TrafficConeIdleText;
	Texture TrafficConeAttackText;
	Texture DamegedTrafficConeWalkText;
	Texture DamegedTrafficConeAttackText;
	Texture ConeDeathText;
	//BucketHat
	Texture BucketHatWalkText;
	Texture BucketHatIdleText;
	Texture BucketHatAttackText;
	Texture DamegedBucketHatWalkText;
	Texture DamegedBucketHatAttackText;
	Texture BucketDeathText;
	//NewsMan
	Texture NewsManWalkText;
	Texture NewsManAttackText;
	Texture DamegedNewsManWalkText;
	Texture DamegedNewsManAttackText;
	Texture SurpriseText;
	Texture NewsManDeath;
	//jack
	Texture JackWalkText;
	Texture JackEatText;
	Texture JackDeathText;
	Texture JackExplosionText;
	Texture jackSurprisedText;
	//screendoor
	Texture ScreenDoorWalkText;
	Texture ScreenDoorEatText;
	Texture ScreenDoorDeathText;
	Texture ScreenDoorDamagedWalkText;
	Texture ScreenDoorDamagedEatText;
	//Football
	Texture FBWalkText;
	Texture FBEatText;
	Texture DamagedFBWalkText;
	Texture DamegedFBEatText;
	Texture FBDeathText;
	//Gargantuar
	Texture GiantWalkText;
	Texture GiantEatText;
	Texture GiantDeathText;
	//PoleVault 
	Texture PVRunWithPoleText;
	Texture PVWalkText;
	Texture PVJumpText;
	Texture PVEatText;
	Texture PvDeathText;
	// Imp AKA Ali Omar when he was 5
	Texture ImpWalkText;
	Texture ImpEatText;
	Texture ImpDeathText;
#pragma endregion

	void LoadZombieTextures() {
		//regular
		RegularWalkText.loadFromFile("Assets/Zombies/Default/walkregular.png");
		RegularAttackText.loadFromFile("Assets/Zombies/Default/eatregular.png");
		RegularDeathText.loadFromFile("Assets/Zombies/Default/regular_death.png");
		//traffic cone
		TrafficConeWalkText.loadFromFile("Assets/Zombies/conehead/walkconehead.png");
		TrafficConeAttackText.loadFromFile("Assets/Zombies/conehead/eatconehead.png");
		DamegedTrafficConeWalkText.loadFromFile("Assets/Zombies/conehead/walkconeheaddameged.png");
		DamegedTrafficConeAttackText.loadFromFile("Assets/Zombies/conehead/eatconeheaddameged.png");
		ConeDeathText.loadFromFile("Assets/Zombies/conehead/conedeath.png");
		//bucket
		BucketHatWalkText.loadFromFile("Assets/Zombies/buckethead/walkBuckethead.png");
		BucketHatAttackText.loadFromFile("Assets/Zombies/buckethead/eatbuckethead.png");
		DamegedBucketHatWalkText.loadFromFile("Assets/Zombies/buckethead/walkbucketheaddmged.png");
		DamegedBucketHatAttackText.loadFromFile("Assets/Zombies/buckethead/eatbucketheaddmged.png");
		BucketDeathText.loadFromFile("Assets/Zombies/buckethead/bucketdeath.png");
		//news man
		NewsManWalkText.loadFromFile("Assets/Zombies/newspaper/newspaperwalk.png");
		NewsManAttackText.loadFromFile("Assets/Zombies/newspaper/newspapereat.png");
		DamegedNewsManWalkText.loadFromFile("Assets/Zombies/newspaper/damegednewspaperwalk.png");
		DamegedNewsManAttackText.loadFromFile("Assets/Zombies/newspaper/damegednewspapereat.png");
		NewsManDeath.loadFromFile("Assets/Zombies/newspaper/newspaperdeath.png");
		SurpriseText.loadFromFile("Assets/Zombies/newspaper/surprised.png");
		//jack
		JackExplosionText.loadFromFile("Assets/Zombies/jackinthebox/jack-explosion-ST.png");
		JackWalkText.loadFromFile("Assets/Zombies/jackinthebox/jack-default-walk-ST.png");
		JackEatText.loadFromFile("Assets/Zombies/jackinthebox/jack-default-eat-ST.png");
		JackDeathText.loadFromFile("Assets/Zombies/jackinthebox/jack-default-death-ST.png");
		jackSurprisedText.loadFromFile("Assets/Zombies/jackinthebox/jacksurprised.png");
		//screendoor
		ScreenDoorWalkText.loadFromFile("Assets/Zombies/screendoor/screendoor-walk-ST.png");
		ScreenDoorEatText.loadFromFile("Assets/Zombies/screendoor/screendoor-eat-ST.png");
		ScreenDoorDeathText.loadFromFile("Assets/Zombies/screendoor/screendoor-death-ST.png");
		ScreenDoorDamagedWalkText.loadFromFile("Assets/Zombies/screendoor/screendoor-walk-damaged2-ST.png");
		ScreenDoorDamagedEatText.loadFromFile("Assets/Zombies/screendoor/screendoor-eat-damaged2-ST.png");
		// FootBall siuuuuuuu
		FBWalkText.loadFromFile("Assets/Zombies/FootBall/walkfb.png");
		FBEatText.loadFromFile("Assets/Zombies/FootBall/eatfb.png");
		DamagedFBWalkText.loadFromFile("Assets/Zombies/FootBall/dmgwalkfb.png");
		DamegedFBEatText.loadFromFile("Assets/Zombies/FootBall/dmgeatfb.png");
		FBDeathText.loadFromFile("Assets/Zombies/FootBall/deathfb.png");
		//Gargantuar AKA giant AKA Elkebeer awy gedan 5ales fash5 very much  
		GiantWalkText.loadFromFile("Assets/Zombies/giant/giantwalk.png");
		GiantEatText.loadFromFile("Assets/Zombies/giant/gianteat.png");
		GiantDeathText.loadFromFile("Assets/Zombies/giant/deathgiant.png");
		//polevault
		PVRunWithPoleText.loadFromFile("Assets/Zombies/pole vaulting/runwithpolePV.png");
		PVJumpText.loadFromFile("Assets/Zombies/pole vaulting/jumpPV.png");
		PVWalkText.loadFromFile("Assets/Zombies/pole vaulting/walkPV.png");
		PVEatText.loadFromFile("Assets/Zombies/pole vaulting/eatPV.png");
		PvDeathText.loadFromFile("Assets/Zombies/pole vaulting/deathPV.png");
		//Imp (Little Ali Omar)
		ImpWalkText.loadFromFile("Assets/Zombies/imp/walkimp.png");
		ImpEatText.loadFromFile("Assets/Zombies/imp/eatimp.png");
		ImpDeathText.loadFromFile("Assets/Zombies/imp/deathimp.png");
	}

	struct Zombie {
		Sprite zombieCont;
		RectangleShape zombieCollider;
		RectangleShape jackCollider;

		Vector2f GargantousPos, JackPos, PolePos;

		zombieType type;
		FlashState flashData;

		#pragma region booleans
		bool started = false;
		bool isSlowed = false;
		bool IsFrozen = false;
		//bool moved = false;
		int health;
		float speed;
		float damage;
		float Extra_damage;
		float PreSpeed = speed;

		bool isDead = false;
		bool deathstart = false;
		bool resetColIndex = false;

		bool isDamaged = false;
		bool isAttacking = false;
		bool isMoving = false;
		bool isslowmultiply = false;
		bool isSquished = false;
		bool SquishEffect = false;
		bool wassoundplayed = false;
		bool startJackClock = true;
		bool isGargantousCrushPlant = false;
		bool isGargantousCrushPot = false;
		bool isGargantousDead = false;
		bool hasJumped = false;
		bool isJumping = false;
		bool isJackSurprised = false;
		bool StopJackMusic = false;
		#pragma endregion

		Clock Zclock, Deathclock;
		float EatClock, CrushedZombieClock,  jackClock, gargantousCrushClock, gargantousAnimationClock, FrozenClock, PoleJumpClock;
		Time EatTimer = seconds(1), CrushedTimer =seconds(1.5), jackTimer = seconds(22);

	private:
		int CollIndex = 0;

		bool isIdle = false;
		bool PlantsinFront = false;
		bool deathOfZombie = false;
		bool jackBomb = false;
		bool checkdeathpos = false;

	public:

		int CurrentPlantIndex = 45;
		bool PlantInfront = false;

		void start() {
			Deathclock.restart();
			Zclock.restart();
			EatClock = 0;
			CrushedZombieClock = 0;
			jackClock = 0;
			gargantousCrushClock = 0;
			FrozenClock = 0;
			PoleJumpClock = 0;
			gargantousAnimationClock = 0;

			flashData.isFlashing = false;
			flashData.currentBrightness = flashData.normalBrightness;

			#pragma region Booleans
			started = false;
			isSlowed = false;
			isDead = false;
			deathstart = false;
			resetColIndex = false;
			isDamaged = false;
			isAttacking = false;
			isMoving = false;
			isslowmultiply = false;
			isSquished = false;
			SquishEffect = false;
			wassoundplayed = false;
			isIdle = false;
			PlantsinFront = false;
			deathOfZombie = false;
			PlantInfront = false;
			jackBomb = false;
			startJackClock = true;
			isGargantousCrushPlant = false;
			isGargantousCrushPot = false;
			IsFrozen = false;
			isGargantousDead = false;
			isJumping = false;
			hasJumped = false;
			isJackSurprised = false;
			StopJackMusic = false;
			#pragma endregion

			switch (type)
			{

			case regular:
				zombieCont.setTexture(RegularWalkText);
				health = 200;
				speed = 7.0;
				damage = 20;

				zombieCollider.setSize({ 42, 47 });

				zombieCollider.setScale(1.4, 1);
				zombieCont.setScale(3, 3);
				// zombieCont.setPosition(1300,row[rand() % 5]); // sets random spawn position 
				break;
			case trafficCone:
				zombieCont.setTexture(TrafficConeWalkText);
				health = 640;
				speed = 7.4;
				damage = 20;

				zombieCollider.setSize({ 44, 57 });
				zombieCollider.setScale(1.4, 1);
				zombieCont.setScale(3, 3);
				break;
			case bucketHat:
				zombieCont.setTexture(BucketHatWalkText);
				health = 1300;
				speed = 7.4;
				damage = 20;

				zombieCollider.setSize({ 37, 56 });
				zombieCollider.setScale(1.4, 1);
				zombieCont.setScale(3, 3);
				break;
			case newsMan:
				zombieCont.setTexture(RegularWalkText);
				health = 1000;
				speed = 7.4;
				damage = 20;

				zombieCollider.setSize({ 50, 57 });
				zombieCollider.setScale(1.4, 1);
				zombieCont.setScale(3, 3);
				break;
			case Dead:
				isDead = true;
				isAttacking = false;
				isMoving = false;
				isDamaged = false;
				health = 0;
				speed = 0;
				damage = 0;
				break;
			case jackInTheBox:
				zombieCont.setTexture(JackWalkText);
				health = 500;
				speed = 20.4;
				damage = 20;
				Extra_damage = 9999999;

				zombieCollider.setSize({ 50, 40 });
				zombieCollider.setScale(1.4, 1.4);
				jackCollider.setSize({ 280,330 });
				jackCollider.setScale(1, 1);
				zombieCont.setScale(3, 3);
				break;
			case soccerGuy:
				zombieCont.setTexture(FBWalkText);
				health = 1400;
				speed = 17.4;
				damage = 20;

				zombieCollider.setSize({ 50, 40 });
				zombieCollider.setScale(1.4, 1.3);
				zombieCont.setScale(3, 3);
				break;
			case screenDoor:
				zombieCont.setTexture(ScreenDoorWalkText);
				health = 1400;
				speed = 9.4;
				damage = 20;
				zombieCollider.setSize({ 50, 40 });
				zombieCollider.setScale(1.4, 1);
				zombieCont.setScale(3, 3);
				break;
			case gargantous: // zombie zengy
				zombieCont.setTexture(GiantWalkText);
				health = 3000;
				speed = 7.4;
				damage = 20000;
				zombieCollider.setSize({ 50, 40 });
				zombieCollider.setScale(1., 1);
				zombieCont.setScale(2.7, 2.7);
				break;
			case poleVault: 
				zombieCont.setTexture(PVWalkText);
				health = 1000;
				speed = 15;
				damage = 20;
				zombieCollider.setSize({ 50, 40 });
				zombieCollider.setScale(1, 1);
				zombieCont.setScale(2.8, 2.8);
				break;
			case imp:
				zombieCont.setTexture(PVWalkText);
				health = 80;
				speed = 20;
				damage = 10;
				zombieCollider.setSize({ 50, 40 });
				zombieCollider.setScale(1.4, 1);
				zombieCont.setScale(3, 3);

			default:
				break;
			}

			zombieCollider.setFillColor(Color(255, 0, 0, 180));
			jackCollider.setFillColor(Color(150, 150, 150, 120));
			zombieCont.setColor(Color(255, 255, 255, 255));
			PreSpeed = speed;
		}

		void update(float deltaTime) 
		{
			EatClock += deltaTime;
			CrushedZombieClock += deltaTime;
			jackClock += deltaTime;
			gargantousCrushClock += deltaTime;
			FrozenClock += deltaTime;
			PoleJumpClock += deltaTime;
			gargantousAnimationClock += deltaTime;

			//setup death animation data
			if (health <= 0)
			{
				isDead = true;
				isIdle = false;
				isAttacking = false;
				isDamaged = false;
				isMoving = false;
				PlantsinFront = false;

				if (!resetColIndex)
				{
					CollIndex = 0;
					resetColIndex
						= true;
				}

				if (type == gargantous && isDead && !wassoundplayed)
				{
					PlaySoundEffect(GargantousDeathSound, false);
					//cout << "play\n";
					wassoundplayed = true;
				}

				zombieCollider.setScale(0, 0);
				/*if (jackBomb && isJackSurprised)
				{
					jackCollider.setScale(0, 0);
				}*/
			}

			//normal update
			if (type != Dead)
			{
				Movement(deltaTime);
				CollisionZombies(PlantProjectilesARR, PlantsArray);
				Animation();

				#pragma region damaged states
				if (type == trafficCone && health < 320 && !isDamaged)
					isDamaged = true;
				else if (type == bucketHat && health < 650 && !isDamaged)
					isDamaged = true;
				else if (type == newsMan && health < 800 && !isDamaged && !isDead && !IsFrozen) {
					isDamaged = true;
					if (!wassoundplayed) {
						PlaySoundEffect(newsManPaperRipSoundBuffer, true);
						PlaySoundEffect(newsmanyellbuffer, false, 2, 25);
						wassoundplayed = true;
					}
					speed = 120;
					PreSpeed = speed;
					damage = 30;
				}
				else if (type == screenDoor && health < 800 && !isDamaged && !isDead)
					isDamaged = true;
				else if (type == gargantous && health < 2500 && !isDamaged && !isDead)
				{
					isDamaged = true;
				}
				else if (type == soccerGuy && health < 800 && !isDamaged && !isDead && !IsFrozen) {
					isDamaged = true;
					speed = 10;
					PreSpeed = speed;
				}
				else if (type == gargantous && isGargantousDead)
				{
					// imp spawn
					type = imp;
					start();
					started = true;
					PlaySoundEffect(ImpSpawnSound, false);
					zombieCont.setPosition(GargantousPos.x, GargantousPos.y + 70);
					isGargantousDead = false;
					cout << "egry ya imp ya gaaaammemeddddd\n";
				}
				#pragma endregion

				if (IsFrozen && !(isDead || health <= 0))
				{
					FrozenClock = 0;
					Zclock.restart();
					EatClock = 0;
					zombieCont.setColor(Color(120, 120, 255, 255));
					speed = 0;
					IsFrozen = false;
				}
				else if (speed == 0 && !(isDead || health <= 0))
				{
					Zclock.restart();
					EatClock = 0;
					zombieCont.setColor(Color(120, 120, 255, 255));
					//cout << " blue NIgga";

					if (FrozenClock >= 5)
					{
						speed = PreSpeed;

						if (!isSlowed)
						{
							zombieCont.setColor(Color(255, 255, 255, 255));
						}
					}
				}

				//set slow color 
				if (isSlowed && !jackBomb)
				{
					zombieCont.setColor(Color(120, 120, 255, 255));
				}
				else if(speed != 0)
				{
					zombieCont.setColor(Color(255, 255, 255, 255));
				}

				if (flashData.isFlashing)
				{
					if (flashData.flashClock.getElapsedTime() <= flashData.flashDuration)
					{
						flashData.currentBrightness = flashData.flashBrightness;
					}
					else
					{
						flashData.currentBrightness = flashData.normalBrightness;
						flashData.isFlashing = false;
					}
				}

				if (type == gargantous && !PlantsinFront && !isAttacking) 
				{
					GargantousPos = zombieCont.getPosition();
				}
				else if (type == jackInTheBox)
				{
					JackPos = jackCollider.getPosition();
				}
				else if (type == poleVault)
				{
					PolePos = zombieCollider.getPosition();
				}
			}

			/*if (type == jackInTheBox && jackBomb && isJackSurprised && !isDead) {
				isDead = true;
				isMoving = false;
				isAttacking = false;
				health = 0;
			}*/

			if (type == jackInTheBox && !jackBomb && !isJackSurprised)
			{
				jackCollider.setPosition(zombieCont.getPosition().x -75, zombieCont.getPosition().y -100);
			}
			else if (type == jackInTheBox && jackBomb && isJackSurprised)
			{
				jackCollider.setPosition(JackPos.x, JackPos.y );
				//cout << "ana sabet makanie\n";
			}

			if (type == gargantous)
			{
				zombieCollider.setPosition(zombieCont.getPosition().x + 70, zombieCont.getPosition().y + 135);
			}
			else if (type == imp) {
				zombieCollider.setPosition(zombieCont.getPosition().x + 25, zombieCont.getPosition().y + 55);
			}
			else if (type == poleVault )
			{
				
				if (!hasJumped)
					zombieCollider.setPosition(zombieCont.getPosition().x + 70, zombieCont.getPosition().y + 55);
				else
					zombieCollider.setPosition(zombieCont.getPosition().x + 20, zombieCont.getPosition().y + 55);
				
				
			}
			else {
				zombieCollider.setPosition(zombieCont.getPosition().x + 50, zombieCont.getPosition().y + 75);
			}
		}

		void CollisionZombies(vector<PlantProjectile>& PlantProjectilesARR, Plants PlantsArray[]) 
		{
			// Projectiles // remove collision with sun coins
			for (int j = 0; j < PlantProjectilesARR.size(); j++) 
			{
				if (!PlantProjectilesARR.empty()) 
				{
					if (!(PlantProjectilesARR[j].type == SunCoin || PlantProjectilesARR[j].type == SunFlower || PlantProjectilesARR[j].type == SunShroom)
						&& (PlantProjectilesARR[j].shape.getGlobalBounds().intersects(zombieCollider.getGlobalBounds()))) {

						//cout << "Zombie Health = " << health << endl;
						health -= PlantProjectilesARR[j].damage;

						if (PlantProjectilesARR[j].type == SnowPeaShooter && !isSlowed)
						{
							speed = (speed * PlantProjectilesARR[j].slowMultiplier);
							PreSpeed = speed;
							isSlowed = true;
						}

						if (type == bucketHat)
						{
							PlaySoundEffect(BucketHatHitSoundBuffer, true, 2);
						}

						PlaySoundEffect(SplatSoundBuffer, true ,3, 25);

						flashData.isFlashing = true;
						flashData.flashClock.restart();

						PlantProjectilesARR.erase(PlantProjectilesARR.begin() + j);
						j--;
						break;
					}
				}
			}

			// Plants
			if (!PlantInfront)
			{
				//if not a plant infront the zombie will loop on all 45 plants and check if he collides with anyone
				for (int i = 0; i < 45; i++)
				{
					if ((!isDead || type == Dead) && started)
					{
						if ((!(PlantsArray[i].type == EmptyPlant || PlantsArray[i].health <= 0)
							&& zombieCollider.getGlobalBounds().intersects(PlantsArray[i].plantCollider.getGlobalBounds()))
							|| (!(PlantingPotArray[i].type == EmptyPlant || PlantingPotArray[i].health <= 0)
								&& zombieCollider.getGlobalBounds().intersects(PlantingPotArray[i].plantCollider.getGlobalBounds())))
						{

							if (type == poleVault && !hasJumped && !PlantsArray[i].Explosion) 
							{
								isJumping = true;
								PlantsinFront = false;
								cout << "ana mesh a7wal la ana a3ma\n";
								PoleJumpClock = 0;
								zombieCollider.setScale(0, 0);
								zombieCont.move(0, -30);
								CollIndex = 0;
								speed *= 0.6;
							}
							
							else {
								CurrentPlantIndex = i;
								PlantInfront = true;
								cout << "plants in front\n";
								if (type == gargantous && !isDead && !PlantsArray[i].Explosion)
								{
									gargantousCrushClock = 0;
									gargantousAnimationClock = 0;
									isGargantousCrushPlant = false;
									isGargantousCrushPot = false;
									zombieCont.setPosition(GargantousPos.x, GargantousPos.y - 15);
									cout << "zew\n";
								}
								

							}

							break;
						}
						else
						{			
							isMoving = true;
							isAttacking = false;
							
						}
					}
				}
			}
			else
			{
				if (health > 0)
				{
					isAttacking = true;
					isMoving = false;
					//attack clock
					if (EatTimer.asSeconds() <= EatClock && type != gargantous)
					{
						if (PlantsArray[CurrentPlantIndex].type != EmptyPlant && type != gargantous)
						{
								PlantsArray[CurrentPlantIndex].takeDmg(damage);	
								cout << "ana bakol\n";
						}
						else if (PlantingPotArray[CurrentPlantIndex].type != EmptyPlant && type != gargantous)
						{
							PlantingPotArray[CurrentPlantIndex].takeDmg(damage);
							cout << "ana bakol\n";
						}
						
						
						
						
						PlaySoundEffect(ZombieEatSoundBuffer, false, 3, 25);
						EatClock = 0;
					}
					else if (PlantsArray[CurrentPlantIndex].type != EmptyPlant && type == jackInTheBox && jackBomb && isJackSurprised)
					{
						PlantsArray[CurrentPlantIndex].takeDmg(Extra_damage);

					}
					else if (PlantingPotArray[CurrentPlantIndex].type != EmptyPlant && type == jackInTheBox && jackBomb && isJackSurprised)
					{
						PlantingPotArray[CurrentPlantIndex].takeDmg(Extra_damage);
					}
					else if (PlantsArray[CurrentPlantIndex].type != EmptyPlant && type == gargantous  && isGargantousCrushPlant && !isDead  )
					{
						PlantsArray[CurrentPlantIndex].takeDmg(damage);
						PlaySoundEffect(GargantousCrushSound, false);
						isGargantousCrushPlant = false;
						//zombieCont.setScale(2.8, 2.8);
						gargantousCrushClock = 0;
						zombieCont.setPosition(GargantousPos.x, GargantousPos.y + 15);
						//cout << "bat7arak men take dmg\n";


					}
					else if (PlantingPotArray[CurrentPlantIndex].type != EmptyPlant && type == gargantous && isGargantousCrushPot && gargantousCrushClock >= 0.2 && CollIndex == 5)
					{
						PlantingPotArray[CurrentPlantIndex].takeDmg(damage);
						PlaySoundEffect(GargantousCrushSound, false);
						isGargantousCrushPot = false;
						gargantousCrushClock = 0;
						//zombieCont.setPosition(GargantousPos.x + 35, GargantousPos.y + 25);
					}
				}
				else
				{
					PlantInfront = false;
					isMoving = true;
					isAttacking = false;
				}
			}

			// if the plant the zombie is eating died or is removed reset the zombie state
			if ((PlantsArray[CurrentPlantIndex].type == EmptyPlant || PlantsArray[CurrentPlantIndex].health <= 0)
				&& (PlantingPotArray[CurrentPlantIndex].type == EmptyPlant || PlantingPotArray[CurrentPlantIndex].health <= 0))
			{
				if (!(isDead || type == Dead || health <= 0))
				{
					PlantInfront = false;
					isMoving = true;
					isAttacking = false;
				}
				else
				{
					PlantInfront = false;
					isMoving = false;
					isAttacking = false;
				}
			}

			// Collision with Cars
			if (isSquished && type != Dead)
			{
				if (!SquishEffect) {

					SquishEffect = true;
					zombieCollider.setScale(0, 0);
					zombieCont.setScale(3.5, 0.7);
					zombieCont.setPosition(zombieCont.getPosition().x, (zombieCont.getPosition().y) + 100);
					speed = 0;
					CrushedZombieClock = 0;
				}
				if (CrushedTimer.asSeconds() <= CrushedZombieClock)
				{
					zombieCont.setScale(0, 0);
					zombieCont.setPosition(2000, 2000);
					type = Dead;
				}
			}

			// Jack in the box
			if (type == jackInTheBox && !isDead && health > 0)
			{
				if (started && !isJackSurprised && !jackBomb && jackTimer.asSeconds() <= jackClock)
				{
					zombieCont.setColor(Color(255, 255, 255, 255));
					isJackSurprised = true;
					isMoving = false;
					//isDead = true;
					jackClock = 0;
					PlaySoundEffect(jackSurprise, true);
					cout << "-----------------------ALLAHO AKBAAARRR-----------------------" << endl;
					//PlaySoundEffect(jackBombSound, true);

				}
				//Jack in The Box
				if (jackBomb && isJackSurprised || isAttacking && isJackSurprised)
				{
					for (int i = 0; i < 45; i++)
					{
						isMoving = false;
						if ((PlantsArray[i].type != EmptyPlant || PlantsArray[i].health > 0)
							&& jackCollider.getGlobalBounds().intersects(PlantsArray[i].plantCollider.getGlobalBounds()))
						{
							/*cout << "looking for things to bomb\n";*/
							if (jackBomb)
							{
								PlantsArray[i].takeDmg(Extra_damage);
								cout << "bomb plant\n";

							}
						}

						if (!(PlantingPotArray[i].type == EmptyPlant || PlantingPotArray[i].health <= 0)
							&& jackCollider.getGlobalBounds().intersects(PlantingPotArray[i].plantCollider.getGlobalBounds()))
						{
							if (jackBomb && CollIndex == 11)
							{
								PlantingPotArray[i].takeDmg(Extra_damage);

							}
						}
					}
				}
			}
		}

	private:
		void Animation() {

			// regular
			if (type == regular && !isSquished) {
				if (isMoving)
				{
					zombieCont.setTexture(RegularWalkText);
					if (Zclock.getElapsedTime().asMilliseconds() > 150) {
						zombieCont.setTextureRect(IntRect(CollIndex * 42, 0, 42, 47));
						CollIndex = (CollIndex + 1) % 6;
						Zclock.restart();
					}
				}
				else if (isAttacking)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 150) {
						zombieCont.setTextureRect(IntRect(CollIndex * 42, 0, 42, 50));
						zombieCont.setTexture(RegularAttackText);
						CollIndex = (CollIndex + 1) % 6;
						Zclock.restart();
					}

				}
				else if (isDead)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 200 && CollIndex != 8) {
						zombieCont.setTextureRect(IntRect(CollIndex * 100, 0, 100, 58));
						zombieCont.setTexture(RegularDeathText);
						CollIndex++;
						Zclock.restart();
					}
					if (CollIndex == 8) {

						zombieCont.setTextureRect(IntRect(8 * 100, 0, 100, 58));
						if (deathstart == false) {
							Deathclock.restart();
							deathstart = true;
						}
						else if (Deathclock.getElapsedTime().asSeconds() >= 1.5)
						{
							zombieCont.setPosition(2000, 2000);
							type = Dead;

						}
					}
				}

			}

			// Traffic Cone
			if (type == trafficCone && !isSquished) {
				if (isMoving && !isDamaged)
				{
					zombieCont.setTexture(TrafficConeWalkText);
					if (Zclock.getElapsedTime().asMilliseconds() > 150) {
						zombieCont.setTextureRect(IntRect(CollIndex * 44, 0, 44, 58));
						CollIndex = (CollIndex + 1) % 6;
						Zclock.restart();
					}
				}
				else if (isAttacking && !isDamaged)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 150) {
						zombieCont.setTextureRect(IntRect(CollIndex * 37, 0, 37, 57));
						zombieCont.setTexture(TrafficConeAttackText);
						CollIndex = (CollIndex + 1) % 6;
						Zclock.restart();
					}
				}
				else if (isMoving && isDamaged)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 150) {
						zombieCont.setTextureRect(IntRect(CollIndex * 44, 0, 44, 58));
						zombieCont.setTexture(DamegedTrafficConeWalkText);
						CollIndex = (CollIndex + 1) % 6;
						Zclock.restart();
					}
				}
				else if (isAttacking && isDamaged)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 150) {
						zombieCont.setTextureRect(IntRect(CollIndex * 37, 0, 37, 57));
						zombieCont.setTexture(DamegedTrafficConeAttackText);
						CollIndex = (CollIndex + 1) % 6;
						Zclock.restart();
					}
				}
				else if (isDead)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 200 && CollIndex != 8) {
						zombieCont.setTextureRect(IntRect(CollIndex * 100, 0, 100, 58));
						zombieCont.setTexture(ConeDeathText);
						CollIndex++;
						Zclock.restart();

					}
					if (CollIndex == 8) {

						zombieCont.setTextureRect(IntRect(8 * 100, 0, 100, 58));
						if (deathstart == false) {
							Deathclock.restart();
							deathstart = true;
						}
						else if (Deathclock.getElapsedTime().asSeconds() >= 1.5)
						{
							zombieCont.setScale(0, 0);
							zombieCont.setPosition(2000, 2000);
							type = Dead;
						}
					}
				}
			}

			// Bucket Hat
			if (type == bucketHat && !isSquished)
			{
				if (isMoving && !isDamaged)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 150) {

						zombieCont.setTextureRect(IntRect(CollIndex * 42, 0, 42, 57));
						zombieCont.setTexture(BucketHatWalkText);
						CollIndex = (CollIndex + 1) % 6;
						Zclock.restart();
					}
				}
				else if (isAttacking && !isDamaged)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 150) {
						zombieCont.setTextureRect(IntRect(CollIndex * 37, 0, 37, 57));
						zombieCont.setTexture(BucketHatAttackText);
						CollIndex = (CollIndex + 1) % 6;
						Zclock.restart();
					}
				}
				else if (isMoving && isDamaged)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 150) {
						zombieCont.setTextureRect(IntRect(CollIndex * 44, 0, 44, 56));
						zombieCont.setTexture(DamegedBucketHatWalkText);
						CollIndex = (CollIndex + 1) % 6;
						Zclock.restart();
					}
				}
				else if (isAttacking && isDamaged)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 150) {
						zombieCont.setTextureRect(IntRect(CollIndex * 37, 0, 37, 57));
						zombieCont.setTexture(DamegedBucketHatAttackText);
						CollIndex = (CollIndex + 1) % 6;
						Zclock.restart();
					}
				}
				else if (isDead)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 200 && CollIndex != 8) {
						zombieCont.setTextureRect(IntRect(CollIndex * 100, 0, 100, 58));
						zombieCont.setTexture(BucketDeathText);
						CollIndex++;
						Zclock.restart();
					}
					if (CollIndex == 8) {

						zombieCont.setTextureRect(IntRect(8 * 100, 0, 100, 58));
						if (deathstart == false) {
							Deathclock.restart();
							deathstart = true;
						}
						else if (Deathclock.getElapsedTime().asSeconds() >= 1.5)
						{
							zombieCont.setScale(0, 0);
							zombieCont.setPosition(2000, 2000);
							type = Dead;

						}
					}
				}
			}

			// news man
			if (type == newsMan && !isSquished) {
				if (isMoving && !isDamaged)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 150) {
						zombieCont.setTextureRect(IntRect(CollIndex * 50, 0, 50, 57));
						zombieCont.setTexture(NewsManWalkText);
						CollIndex = (CollIndex + 1) % 6;
						Zclock.restart();
					}
				}
				else if (isAttacking && !isDamaged)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 150) {
						zombieCont.setTextureRect(IntRect(CollIndex * 57, 0, 57, 57));
						zombieCont.setTexture(NewsManAttackText);
						CollIndex = (CollIndex + 1) % 6;
						Zclock.restart();
					}
				}
				else if (isMoving && isDamaged)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 150) {
						zombieCont.setTextureRect(IntRect(CollIndex * 50, 0, 50, 57));
						zombieCont.setTexture(DamegedNewsManWalkText);
						CollIndex = (CollIndex + 1) % 6;
						Zclock.restart();
					}
				}
				else if (isAttacking && isDamaged)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 150) {
						zombieCont.setTextureRect(IntRect(CollIndex * 57, 0, 57, 57));
						zombieCont.setTexture(DamegedNewsManAttackText);
						CollIndex = (CollIndex + 1) % 6;
						Zclock.restart();
					}
				}
				else if (isDead)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 150 && CollIndex != 5) {
						zombieCont.setTextureRect(IntRect(CollIndex * 58, 0, 58, 52));
						zombieCont.setTexture(NewsManDeath);
						CollIndex++;
						Zclock.restart();
					}
					if (CollIndex == 5) {

						zombieCont.setTextureRect(IntRect(5 * 58, 0, 58, 52));
						if (deathstart == false) {
							Deathclock.restart();
							deathstart = true;
						}
						else if (Deathclock.getElapsedTime().asSeconds() >= 1.5)
						{
							zombieCont.setScale(0, 0);
							zombieCont.setPosition(2000, 2000);
							type = Dead;
						}
					}
				}
			}

			//jack in the box  
			if (type == jackInTheBox)
			{
				if (isMoving && !isSquished && !isJackSurprised)
				{
					zombieCont.setTextureRect(IntRect(CollIndex * 42, 0, 42, 58));
					zombieCont.setTexture(JackWalkText);

					if (Zclock.getElapsedTime().asMilliseconds() > 150) {
						CollIndex = (CollIndex + 1) % 6;
						Zclock.restart();
					}
				}
				else if (isAttacking && !isJackSurprised)
				{
					zombieCont.setTextureRect(IntRect(CollIndex * 42, 0, 42, 58));
					zombieCont.setTexture(JackEatText);

					if (Zclock.getElapsedTime().asMilliseconds() > 150) {
						CollIndex = (CollIndex + 1) % 6;
						Zclock.restart();
					}

				} else if (isJackSurprised && !jackBomb)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 150 && CollIndex != 9)
					{
						zombieCont.setTextureRect(IntRect(CollIndex * 45, 0, 45, 62));
						zombieCont.setTexture(jackSurprisedText);

						CollIndex++;
						Zclock.restart();
					}
					if (CollIndex == 9)
					{
						//isJackSurprised = false;
						jackBomb = true;
						CollIndex = 0;
					}
				}else if (jackBomb && isJackSurprised)
				{
					//removes coloring
					zombieCont.setColor(Color(255, 255, 255, 255));

					if (Zclock.getElapsedTime().asMilliseconds() > 200 && CollIndex != 11)
					{
						if (checkdeathpos == false) {
							zombieCont.setPosition(zombieCont.getPosition().x - 75, zombieCont.getPosition().y - 10);
							checkdeathpos = true;
							PlaySoundEffect(jackBombSound, true);
						}

						zombieCont.setTextureRect(IntRect(CollIndex * 95, 0, 95, 66));
						zombieCont.setTexture(JackExplosionText);

						CollIndex++;
						Zclock.restart();
					}
					if (CollIndex == 11)
					{
						zombieCont.setPosition(2000, 2000);
						type = Dead;
						jackCollider.setScale(0, 0);
						cout << "type is dead\n";
					}
				}
				else if (isDead)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 150 && CollIndex != 7)
					{
						if (checkdeathpos == false)
						{
							zombieCont.setPosition(zombieCont.getPosition().x - 75, zombieCont.getPosition().y - 10);
							checkdeathpos = true;
						}

						zombieCont.setTextureRect(IntRect(CollIndex * 95, 0, 95, 58));
						zombieCont.setTexture(JackDeathText);

						CollIndex++;
						Zclock.restart();
					}
					if (CollIndex == 7) {

						zombieCont.setTextureRect(IntRect(6 * 95, 0, 95, 58));

						if (deathstart == false) {
							Deathclock.restart();
							deathstart = true;
						}
						else if (Deathclock.getElapsedTime().asSeconds() >= 1.5)
						{
							zombieCont.setScale(0, 0);
							zombieCont.setPosition(2000, 2000);
							type = Dead;
						}
					}
				}
			}

			//Football
			if (type == soccerGuy && !isSquished)
			{
				if (isMoving && !isDamaged)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 150) {
						zombieCont.setTextureRect(IntRect(CollIndex * 64, 0, 64, 59));
						zombieCont.setTexture(FBWalkText);
						CollIndex = (CollIndex + 1) % 8;
						Zclock.restart();
					}
				}
				else if (isAttacking && !isDamaged)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 150) {
						zombieCont.setTextureRect(IntRect(CollIndex * 63, 0, 63, 59));
						zombieCont.setTexture(FBEatText);
						CollIndex = (CollIndex + 1) % 6;
						Zclock.restart();
					}
				}
				else if (isMoving && isDamaged)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 150) {
						zombieCont.setTextureRect(IntRect(CollIndex * 64, 0, 64, 59));
						zombieCont.setTexture(DamagedFBWalkText);
						CollIndex = (CollIndex + 1) % 8;
						Zclock.restart();
					}
				}
				else if (isAttacking && isDamaged)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 150) {
						zombieCont.setTextureRect(IntRect(CollIndex * 62, 0, 62, 59));
						zombieCont.setTexture(DamegedFBEatText);
						CollIndex = (CollIndex + 1) % 6;
						Zclock.restart();
					}
				}
				else if (isDead)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 200 && CollIndex != 6) {
						zombieCont.setTextureRect(IntRect(CollIndex * 200, 0, 200, 58));
						zombieCont.setTexture(FBDeathText);
						CollIndex++;
						Zclock.restart();
					}
					if (CollIndex == 6) {

						zombieCont.setTextureRect(IntRect(6 * 200, 0, 200, 58));
						if (deathstart == false) {
							Deathclock.restart();
							deathstart = true;
						}
						else if (Deathclock.getElapsedTime().asSeconds() >= 1.5)
						{
							zombieCont.setPosition(2000, 2000);
							type = Dead;

						}
					}
				}
			}

			// Screen Door 
			if (type == screenDoor && !isSquished)
			{
				if (isMoving)
				{
					if (isDamaged)
					{
						if (Zclock.getElapsedTime().asMilliseconds() > 150) {
							zombieCont.setTextureRect(IntRect(CollIndex * 42, 0, 42, 52));
							zombieCont.setTexture(ScreenDoorDamagedWalkText);
							CollIndex = (CollIndex + 1) % 7;
							Zclock.restart();
						}
					}
					else
					{
						if (Zclock.getElapsedTime().asMilliseconds() > 150) {
							zombieCont.setTextureRect(IntRect(CollIndex * 42, 0, 42, 52));
							zombieCont.setTexture(ScreenDoorWalkText);
							CollIndex = (CollIndex + 1) % 7;
							Zclock.restart();
						}
					}

				}
				else if (isAttacking)
				{
					if (isDamaged)
					{
						if (Zclock.getElapsedTime().asMilliseconds() > 150) {
							zombieCont.setTextureRect(IntRect(CollIndex * 42, 0, 42, 52));
							zombieCont.setTexture(ScreenDoorDamagedEatText);
							CollIndex = (CollIndex + 1) % 7;
							Zclock.restart();
						}
					}
					else
					{
						if (Zclock.getElapsedTime().asMilliseconds() > 150) {
							zombieCont.setTextureRect(IntRect(CollIndex * 42, 0, 42, 52));
							zombieCont.setTexture(ScreenDoorEatText);
							CollIndex = (CollIndex + 1) % 7;
							Zclock.restart();
						}
					}


				}
				else if (isDead)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 200 && CollIndex != 8)
					{
						if (checkdeathpos == false)
						{
							zombieCont.setPosition(zombieCont.getPosition().x - 100, zombieCont.getPosition().y - 2);
							checkdeathpos = true;
						}

						zombieCont.setTextureRect(IntRect(CollIndex * 100, 0, 100, 50));
						zombieCont.setTexture(ScreenDoorDeathText);
						CollIndex++;
						Zclock.restart();
					}
					if (CollIndex == 8) {

						zombieCont.setTextureRect(IntRect(8 * 100, 0, 100, 50));
						if (deathstart == false) {
							Deathclock.restart();
							deathstart = true;
						}
						else if (Deathclock.getElapsedTime().asSeconds() >= 1.5)
						{
							zombieCont.setPosition(2000, 2000);
							type = Dead;
						}
					}
				}
			}

			// polevault
			if (type == poleVault && !isSquished) {
				if (isMoving && !isJumping)
				{
					if (!hasJumped)
					{
						if (Zclock.getElapsedTime().asMilliseconds() > 150) {
						zombieCont.setTextureRect(IntRect(CollIndex * 73, 0, 73, 58));
							zombieCont.setTexture(PVRunWithPoleText);
							CollIndex = (CollIndex + 1) % 6;
							Zclock.restart();
						}
					}
					else
					{
						if (Zclock.getElapsedTime().asMilliseconds() > 150) {
							zombieCont.setTextureRect(IntRect(CollIndex * 34, 0, 34, 57));
						zombieCont.setTexture(PVWalkText);
							CollIndex = (CollIndex + 1) % 6;
							Zclock.restart();
						}
					}

				}
				else if (isJumping)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 150 && CollIndex != 6) {
						zombieCont.setTextureRect(IntRect(CollIndex * 67, 0, 67, 71));
						zombieCont.setTexture(PVJumpText);
						CollIndex++;
						if (CollIndex == 5)
						{
							hasJumped == true;
							PlaySoundEffect(poleJumpSound, false);
							zombieCont.move(-130, 0);
							cout << "7arakt el collider wel sprite\n";

						}
						if (CollIndex == 6)
						{
							zombieCont.setTextureRect(IntRect(5 * 67, 0, 67, 71));
							if (PoleJumpClock >= 0.5)
							{
								isJumping = false;
								hasJumped = true;
								isMoving = true;
								cout << "not yasta\n";
								zombieCollider.setScale(1, 1);
								CollIndex = 0;
								zombieCont.move(0, 30);
								zombieCollider.setPosition(zombieCont.getPosition().x + 50, zombieCont.getPosition().y + 75);

							}
						}
						Zclock.restart();
					}
				}
				else if (isAttacking)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 150) {
						zombieCont.setTextureRect(IntRect(CollIndex * 33, 0, 33, 55));
						zombieCont.setTexture(PVEatText);
						CollIndex = (CollIndex + 1) % 6;
						Zclock.restart();
					}

				}
				else if (isDead)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 200 && CollIndex != 10) {
						zombieCont.setTextureRect(IntRect(CollIndex * 50, 0, 50, 58));
						zombieCont.setTexture(PvDeathText);
						CollIndex++;
						Zclock.restart();
					}
					if (CollIndex == 10) {

						zombieCont.setTextureRect(IntRect(10 * 50, 0, 50, 58));
						if (deathstart == false) {
							Deathclock.restart();
							deathstart = true;
						}
						else if (Deathclock.getElapsedTime().asSeconds() >= 1.5)
						{
							zombieCont.setPosition(2000, 2000);
							type = Dead;

						}
					}
				}

			}

			//Gargatnous
			if (type == gargantous && !isSquished) {
				if (isMoving )
				{
					zombieCont.setTextureRect(IntRect(CollIndex * 72, 0, 72, 79));
					if (Zclock.getElapsedTime().asMilliseconds() > 300) {
						zombieCont.setTexture(GiantWalkText);
						CollIndex = (CollIndex + 1) % 4;
						Zclock.restart();
					}
				}
				else if (isAttacking)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 150 && CollIndex != 5) {
					cout << CollIndex <<  endl;
						zombieCont.setTextureRect(IntRect(CollIndex * 95, 0, 95, 95));
						zombieCont.setTexture(GiantEatText);
						CollIndex++;
						if (CollIndex == 5)
						{
							zombieCont.setTextureRect(IntRect(5 * 95, 0, 95, 95));
							cout << "ana mesh mawgood\n";
								isGargantousCrushPlant = true;
								isGargantousCrushPot = true;
								isAttacking = false;
								isMoving = true;	
								CollIndex= 0;
								cout << "edrab ya gargantooooooooo\n";
								gargantousCrushClock = 0;

						}
						Zclock.restart();
					}

				}
				else if (isDead)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 200 && CollIndex != 6) {
						zombieCont.setTextureRect(IntRect(CollIndex * 115, 0, 115, 80));
						zombieCont.setTexture(GiantDeathText);
						CollIndex++;
						Zclock.restart();
						//cout << CollIndex << endl;
					}
					if (CollIndex == 6) {

						zombieCont.setTextureRect(IntRect(6 * 115, 0, 115, 80));
						if (deathstart == false) {
							Deathclock.restart();
							deathstart = true;
						}
						else if (Deathclock.getElapsedTime().asSeconds() >= 1.5)
						{
							zombieCont.setPosition(2000, 2000);
							isGargantousDead = true;
							//type = Dead;
							wassoundplayed = false;
							//zombieCont.setPosition(GargantousPos.x - 35, GargantousPos.y - 65);
						}
					}
				}

			}

			//imp >:)
			if (type == imp && !isSquished) {
				if (isMoving)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 150) {
						zombieCont.setTextureRect(IntRect(CollIndex * 29, 0, 29, 35));
					zombieCont.setTexture(ImpWalkText);
						CollIndex = (CollIndex + 1) % 8;
						Zclock.restart();
					}
				}
				else if (isAttacking)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 150) {
						zombieCont.setTextureRect(IntRect(CollIndex * 25, 0, 25, 40));
						zombieCont.setTexture(ImpEatText);
						CollIndex = (CollIndex + 1) % 8;
						Zclock.restart();
					}

				}
				else if (isDead)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 200 && CollIndex != 6) {
						zombieCont.setTextureRect(IntRect(CollIndex * 50, 0, 50, 40));
						zombieCont.setTexture(ImpDeathText);
						CollIndex++;
						Zclock.restart();
					}
					if (CollIndex == 6) {

						zombieCont.setTextureRect(IntRect(6 * 50, 0, 50, 40));
						if (deathstart == false) {
							Deathclock.restart();
							deathstart = true;
						}
						else if (Deathclock.getElapsedTime().asSeconds() >= 1.5)
						{
							zombieCont.setPosition(2000, 2000);
							type = Dead;

						}
					}
				}

			}
		}

		void Movement(float deltaTime)
		{
			if (isMoving && !isSquished)
			{
				zombieCont.move(-1 * speed * 2 * deltaTime, 0);
			}
		}
	}zombie_array[100];

	//gives zombies random types
	// 	enum zombieType { regular, bucketHat, trafficCone, newsMan, jackInTheBox, soccerGuy, screenDoor, Dead };
	// 	enum zombieType { regular, bucketHat, trafficCone, newsMan, jackInTheBox, soccerGuy, screenDoor, gargantous, poleVault,dead, imp};
	void StartZombies(int numerzombieinwave, int numberlevel, bool onRoof_) 
	{
		onRoof = onRoof_;

		if (numberlevel == 1) {
			for (int i = 0; i < numerzombieinwave; i++) {
				zombieType randomzombietype = static_cast<zombieType>(rand() % newsMan);
				zombie_array[i].type = randomzombietype;
				zombie_array[i].start();
			}
		}
		else if (numberlevel == 2) {
			for (int i = 0; i < numerzombieinwave; i++) {
				zombieType randomzombietype = static_cast<zombieType>(rand() % gargantous);
				zombie_array[i].type = randomzombietype;
				zombie_array[i].start();
			}
		}
		else if (numberlevel == 3) {
			for (int i = 0; i < numerzombieinwave; i++) {
				zombieType randomzombietype = static_cast<zombieType>(rand() % poleVault);
				zombie_array[i].type = randomzombietype;
				zombie_array[i].start();
			}
		}
		else if (numberlevel == 4) 
		{
			for (int i = 0; i < numerzombieinwave; i++) {
				zombieType randomzombietype = static_cast<zombieType>(rand() % Dead);
				zombie_array[i].type = randomzombietype;
				zombie_array[i].start();
			}
		}
	
	}
#pragma endregion
}