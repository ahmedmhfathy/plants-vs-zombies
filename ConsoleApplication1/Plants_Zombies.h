#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<string>
#include<vector>
#include "Game Settings And Audio.h"
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
	enum PlantType { PeaShooter, SnowPeaShooter, SunFlower, WallNut, SunShroom, PuffShroom, ScaredyShroom, PlantingPot, PotatoMine, EmptyPlant, SunCoin, Shovel };
	enum zombieType { regular, bucketHat, trafficCone, newsMan, jackInTheBox, soccerGuy, screenDoor, gargantous, Dead, imp , poleVault};
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
#pragma endregion

#pragma region Plants
	//will load all textures once
	void LoadPlantTexturesAndSounds() {
		//Audio
		SunCoinSoundBuffer.loadFromFile("Audio/points.ogg");
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

	void DrawPlantsAndProjectiles(RenderWindow& window) {
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
				window.draw(PlantingPotArray[i].plantCollider);
				window.draw(PlantingPotArray[i].shape);
			}

			if (!(PlantsArray[i].type == EmptyPlant || PlantsArray[i].health <= 0))
			{
				window.draw(PlantsArray[i].plantCollider);
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

		zombieType type;
		#pragma region booleans
		bool hasJumped = false;
		bool started = false;
		bool isSlowed = false;
		//bool moved = false;
		int health;
		float speed;
		float damage;
		float Extra_damage;

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
		bool isGargantousCrush = false;
		#pragma endregion

		Clock Zclock, Deathclock;
		float EatClock, CrushedZombieClock,  jackClock, gargantousCrushClock;
		Time EatTimer = seconds(1), CrushedTimer =seconds(1.5), jackTimer = seconds(22), gargantousCrushTimer = seconds(10);

	private:
		int CollIndex = 0;

		bool isIdle = false;
		bool PlantsinFront = false;
		bool deathOfZombie = false;
		bool jackBomb = false;
		bool checkdeathpos = false;


	public:

		int CurrentPlantIndex;
		bool PlantInfront = false;

		void start() {
			Deathclock.restart();
			Zclock.restart();
			EatClock = 0;
			CrushedZombieClock = 0;
			jackClock = 0;
			gargantousCrushClock = 0;

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
			isGargantousCrush = false;
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
				zombieCollider.setScale(1.4, 1);
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
				zombieCollider.setScale(1.4, 1);
				zombieCont.setScale(3, 3);
				break;
			case poleVault: 
				zombieCont.setTexture(PVWalkText);
				health = 1000;
				speed = 15;
				damage = 20;
				zombieCollider.setSize({ 50, 40 });
				zombieCollider.setScale(1.4, 1);
				zombieCont.setScale(3, 3);
				break;
			case imp:
				zombieCont.setTexture(PVWalkText);
				health = 800;
				speed = 40;
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

		}

		void update(float deltaTime) 
		{
			EatClock += deltaTime;
			CrushedZombieClock += deltaTime;
			jackClock += deltaTime;
			gargantousCrushClock += deltaTime;

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

				zombieCollider.setScale(0, 0);
				jackCollider.setScale(0, 0);
			}

			//normal update
			if (type != Dead)
			{
				Movement(deltaTime);
				CollisionZombies(PlantProjectilesARR, PlantsArray);
				Animation();

				if (type == trafficCone && health < 320 && !isDamaged)
					isDamaged = true;
				else if (type == bucketHat && health < 650 && !isDamaged)
					isDamaged = true;
				else if (type == newsMan && health < 800 && !isDamaged && !isDead) {
					isDamaged = true;
					if (!wassoundplayed) {
						PlaySoundEffect(newsManPaperRipSoundBuffer, true);
						PlaySoundEffect(newsmanyellbuffer, false, 2, 25);
						wassoundplayed = true;
					}
					speed = 120;
					damage = 30;
				}
				else if (type == screenDoor && health < 800 && !isDamaged && !isDead)
					isDamaged = true;
				else if (type == gargantous && health < 2500 && !isDamaged && !isDead )
				{
					isDamaged = true;
				}
				else if (type == soccerGuy && health < 800 && !isDamaged && !isDead) {
					{
						isDamaged = true;
						speed = 10;
					}
				}

				//set slow color 
				if (isSlowed && !jackBomb)
				{
					zombieCont.setColor(Color(120, 120, 255, 255));
				}
				else if (type == soccerGuy)
				{
					//zombieCont.setColor(Color(255, 105, 180, 255)); // pink
				}
				else if (type == gargantous)
				{
					//zombieCont.setColor(Color(44, 44, 44, 255)); // black
				}
				else
				{
					zombieCont.setColor(Color(255, 255, 255, 255));
				}
			}

			if (type == jackInTheBox && jackBomb && !isDead) {
				isDead = true;
				isMoving = false;
				isAttacking = false;
				health = 0;
			}

			jackCollider.setPosition(zombieCont.getPosition().x -75, zombieCont.getPosition().y -100);
			zombieCollider.setPosition(zombieCont.getPosition().x + 50, zombieCont.getPosition().y + 75);
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
							isSlowed = true;
						}

						if (type == bucketHat)
						{
							PlaySoundEffect(BucketHatHitSoundBuffer, true, 2);
						}

						PlaySoundEffect(SplatSoundBuffer, true ,3, 25);

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
					if (!isDead || type == Dead)
					{
						if ((!(PlantsArray[i].type == EmptyPlant || PlantsArray[i].health <= 0)
							&& zombieCollider.getGlobalBounds().intersects(PlantsArray[i].plantCollider.getGlobalBounds()))
							|| (!(PlantingPotArray[i].type == EmptyPlant || PlantingPotArray[i].health <= 0)
								&& zombieCollider.getGlobalBounds().intersects(PlantingPotArray[i].plantCollider.getGlobalBounds())))
						{
							CurrentPlantIndex = i;
							PlantInfront = true;
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
					isMoving = false;
					isAttacking = true;
					//attack clock
					if (EatTimer.asSeconds() <= EatClock)
					{
						if (PlantsArray[CurrentPlantIndex].type != EmptyPlant)
						{
							PlantsArray[CurrentPlantIndex].takeDmg(damage);
						}
						else if (PlantingPotArray[CurrentPlantIndex].type != EmptyPlant)
						{
							PlantingPotArray[CurrentPlantIndex].takeDmg(damage);
						}
						/*else if (type == gargantous && (PlantsArray[CurrentPlantIndex].type != EmptyPlant && PlantingPotArray[CurrentPlantIndex].type != EmptyPlant))
						{
							
							
							PlantsArray[CurrentPlantIndex].shape.setScale(3.5, 0.7);
							PlantingPotArray[CurrentPlantIndex].shape.setScale(3.5, 0.7);
							isGargantousCrush = true;
							
							if (isGargantousCrush && gargantousCrushTimer.asSeconds() <= gargantousCrushClock)
							{
								PlantsArray[CurrentPlantIndex].takeDmg(damage);
								PlantingPotArray[CurrentPlantIndex].takeDmg(damage);
								cout << "fa3as\n";
								isGargantousCrush = false;
								gargantousCrushClock = 0;
							}

						}*/
						
						PlaySoundEffect(ZombieEatSoundBuffer, false, 3, 25);
						EatClock = 0;
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
				if (started && !jackBomb && jackTimer.asSeconds() <= jackClock)
				{
					cout << "-----------------------ALLAHO AKBAAARRR-----------------------" << endl;
					zombieCont.setColor(Color(255, 255, 255, 255));
					jackBomb = true;
					jackClock = 0;
					PlaySoundEffect(jackBombSound, true);

				}

				//Jack in The Box
				if (jackBomb)
				{
					for (int i = 0; i < 45; i++)
					{
						if (!(PlantsArray[i].type == EmptyPlant || PlantsArray[i].health <= 0)
							&& jackCollider.getGlobalBounds().intersects(PlantsArray[i].plantCollider.getGlobalBounds()))
						{
							PlantsArray[i].takeDmg(Extra_damage);
						}

						if (!(PlantingPotArray[i].type == EmptyPlant || PlantingPotArray[i].health <= 0)
							&& jackCollider.getGlobalBounds().intersects(PlantingPotArray[i].plantCollider.getGlobalBounds()))
						{
							PlantingPotArray[i].takeDmg(Extra_damage);
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
				if (isMoving && !isSquished)
				{
					zombieCont.setTexture(JackWalkText);
					zombieCont.setTextureRect(IntRect(CollIndex * 42, 0, 42, 58));

					if (Zclock.getElapsedTime().asMilliseconds() > 150) {
						CollIndex = (CollIndex + 1) % 6;
						Zclock.restart();
					}
				}
				else if (isAttacking)
				{
					zombieCont.setTextureRect(IntRect(CollIndex * 42, 0, 42, 58));
					zombieCont.setTexture(JackEatText);

					if (Zclock.getElapsedTime().asMilliseconds() > 150) {
						CollIndex = (CollIndex + 1) % 6;
						Zclock.restart();
					}

				}
				else if (isDead)
				{
					if (jackBomb)
					{
						//removes coloring
						zombieCont.setColor(Color(255, 255, 255, 255));

						if (Zclock.getElapsedTime().asMilliseconds() > 200 && CollIndex != 11)
						{
							if (checkdeathpos == false) {
								zombieCont.setPosition(zombieCont.getPosition().x - 75, zombieCont.getPosition().y - 10);
								checkdeathpos = true;
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
						}
					}
					else
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
			}
			//Football

			if (type == soccerGuy && !isSquished)
			{
				if (isMoving && !isDamaged)
				{
					zombieCont.setTexture(FBWalkText);
					if (Zclock.getElapsedTime().asMilliseconds() > 150) {
						zombieCont.setTextureRect(IntRect(CollIndex * 64, 0, 64, 59));
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

			//Gargatnous
			if (type == gargantous && !isSquished) {
				if (isMoving)
				{
					zombieCont.setTexture(GiantWalkText);
					if (Zclock.getElapsedTime().asMilliseconds() > 300) {
						zombieCont.setTextureRect(IntRect(CollIndex * 72, 0, 72, 79));
						CollIndex = (CollIndex + 1) % 4;
						Zclock.restart();
					}
				}
				else if (isAttacking)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 300) {
						zombieCont.setTextureRect(IntRect(CollIndex * 86, 0, 86, 92));
						zombieCont.setTexture(GiantEatText);
						CollIndex = (CollIndex + 1) % 6;
						Zclock.restart();
					}

				}
				else if (isDead)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 200 && CollIndex != 7) {
						zombieCont.setTextureRect(IntRect(CollIndex * 115, 0, 115, 80));
						zombieCont.setTexture(GiantDeathText);
						CollIndex++;
						Zclock.restart();
					}
					if (CollIndex == 7) {

						zombieCont.setTextureRect(IntRect(7 * 115, 0, 115, 80));
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
			//imp >:)
			if (type == imp && !isSquished) {
				if (isMoving)
				{
					zombieCont.setTexture(ImpWalkText);
					if (Zclock.getElapsedTime().asMilliseconds() > 150) {
						zombieCont.setTextureRect(IntRect(CollIndex * 29, 0, 29, 35));
						CollIndex = (CollIndex + 1) % 8;
						Zclock.restart();
					}
				}
				else if (isAttacking)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 150) {
						zombieCont.setTextureRect(IntRect(CollIndex * 50, 0, 50, 40));
						zombieCont.setTexture(ImpEatText);
						CollIndex = (CollIndex + 1) % 8;
						Zclock.restart();
					}

				}
				else if (isDead)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 200 && CollIndex != 5) {
						zombieCont.setTextureRect(IntRect(CollIndex * 60, 0, 60, 40));
						zombieCont.setTexture(ImpDeathText);
						CollIndex++;
						Zclock.restart();
					}
					if (CollIndex == 5) {

						zombieCont.setTextureRect(IntRect(8 * 60, 0, 60, 40));
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
			if (isMoving)
			{
				zombieCont.move(-1 * speed * 2 * deltaTime, 0);
			}
		}
	}zombie_array[100];

	//gives zombies random types
	// 	enum zombieType { regular, bucketHat, trafficCone, newsMan, jackInTheBox, soccerGuy, screenDoor, Dead };
	void StartZombies(int numerzombieinwave, int numberlevel, bool onRoof_) 
	{
		onRoof = onRoof_;

		if (numberlevel == 1) {
			for (int i = 0; i < numerzombieinwave; i++) {
				zombieType randomzombietype = static_cast<zombieType>(rand() % jackInTheBox);
				zombie_array[i].type = randomzombietype;
				zombie_array[i].start();
			}
		}
		else if (numberlevel == 2) {
			for (int i = 0; i < numerzombieinwave; i++) {
				zombieType randomzombietype = static_cast<zombieType>(rand() % Dead);
				zombie_array[i].type = randomzombietype;
				zombie_array[i].start();
			}
		}
		else if (numberlevel == 3) {
			for (int i = 0; i < numerzombieinwave; i++) {
				zombieType randomzombietype = static_cast<zombieType>(rand() % Dead);
				zombie_array[i].type = randomzombietype;
				zombie_array[i].start();
			}
		}

	}
#pragma endregion
}