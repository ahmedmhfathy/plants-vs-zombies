#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<string>
#include<vector>
using namespace std;
using namespace sf;

namespace khalid {
#pragma region Declaring Texures
	//peashooter
	Texture PeaShooterIdleTex;
	Texture PeaShooterShootTex;
	Texture PeaShooterProjectileTex;
	//Sunflower
	Texture SunFlowerIdleTex;
	Texture SunFlowerProducingSunTex;
	Texture SunFlowerSunTex;
	//sun coin 2
	Texture sunCoin1;
	Texture sunCoin2;
	Texture sunCoin3;
	//WallNut
	Texture WallNutIdleTex;
	//IcePeaShooter
	Texture IcePeaShooterIdleTex;
	Texture IcePeaShooterShootTex;
	Texture IcePeaShooterProjectileTex;
#pragma endregion

	//will load all textures once
	void LoadPlantTextures() {
		//peashooter
		PeaShooterIdleTex.loadFromFile("Assets/Plants/PeaShooter/peashooter-idle-ST.png");
		PeaShooterShootTex.loadFromFile("Assets/Plants/PeaShooter/peashooter-shooting-ST.png");
		PeaShooterProjectileTex.loadFromFile("Assets/Plants/PeaShooter/peashooter-bullet.png");
		//sunflower
		SunFlowerIdleTex.loadFromFile("Assets/Plants/SunFlower/sunflower-idle-ST.png");
		SunFlowerProducingSunTex.loadFromFile("Assets/Plants/SunFlower/sunflower-producingsun_ST.png");
		SunFlowerSunTex.loadFromFile("Assets/sun-ST.png");
		//SunCoin
		sunCoin1.loadFromFile("Assets/Sun1.png");
		sunCoin2.loadFromFile("Assets/Sun2.png");
		sunCoin3.loadFromFile("Assets/Sun3.png");
		//icepeashooter
		IcePeaShooterIdleTex.loadFromFile("Assets/Plants/IcePeaShooter/icepeashooter-idle-ST2.png");
		IcePeaShooterShootTex.loadFromFile("Assets/Plants/IcePeaShooter/icepeashooter-shooting-ST.png");
		IcePeaShooterProjectileTex.loadFromFile("Assets/Plants/IcePeaShooter/icepeashooter-bullet.png");
		//wallnut
		WallNutIdleTex.loadFromFile("Assets/Plants/WallNut/wallnut-ST.png");
	}

	//all types of plants
	enum PlantType { PeaShooter, SnowPeaShooter, SunFlower, WallNut, EmptyPlant };

	struct PlantProjectile
	{
		//string type;
		PlantType type;

		//these are used for the other projectiles
		Sprite shape;

		//these are only used for the sun coin
		Sprite SunCoinShape1;
		Sprite SunCoinShape2;
		Sprite SunCoinShape3;

		float damage; //<<<<<<<<---------------<<< to be used in the zombie system
		float slowMultiplier = 1; //<<<<<<<<---------------<<< to be used in the zombie system
		float speed;

		Time projectileLifeSpan;
		Clock clock;

		void start(PlantType plantType, float PlantDamage, Vector2f SpwanPos) {
			clock.restart();
			type = plantType;
			//damage = PlantDamage;
			//shape.setPosition(SpwanPos);

			if (type == PeaShooter)
			{
				shape.setTexture(PeaShooterProjectileTex);
				shape.setScale(3.5, 3.5);
				shape.setPosition(SpwanPos);
				projectileLifeSpan = seconds(10); //time to despawn
				speed = 5;
				damage = PlantDamage;
				slowMultiplier = 1; // wont affect anything
			}
			else if (type == SnowPeaShooter)
			{
				shape.setTexture(IcePeaShooterProjectileTex);
				shape.setScale(3.5, 3.5);
				shape.setPosition(SpwanPos);
				projectileLifeSpan = seconds(10); //time to despawn
				speed = 5;
				damage = PlantDamage;
				slowMultiplier = 0.5;
			}
			else if (type == SunFlower)
			{
				SunCoinShape1.setTexture(sunCoin1);
				SunCoinShape2.setTexture(sunCoin2);
				SunCoinShape3.setTexture(sunCoin3);

				SunCoinShape1.setPosition(SpwanPos);
				SunCoinShape2.setPosition(SpwanPos);
				SunCoinShape3.setPosition(SpwanPos);

				SunCoinShape1.setOrigin({ SunCoinShape1.getLocalBounds().width / 2, SunCoinShape1.getLocalBounds().height / 2 });
				SunCoinShape2.setOrigin({ SunCoinShape2.getLocalBounds().width / 2, SunCoinShape2.getLocalBounds().height / 2 });
				SunCoinShape3.setOrigin({ SunCoinShape3.getLocalBounds().width / 2, SunCoinShape3.getLocalBounds().height / 2 });

				//SunCoinShape1.setScale(3.5, 3.5);
				//SunCoinShape2.setScale(3.5, 3.5);
				//SunCoinShape3.setScale(3.5, 3.5);

				projectileLifeSpan = seconds(12);

				speed = 0;
				damage = PlantDamage;
				slowMultiplier = 1;

				//shape.setTexture(SunFlowerSunTex);
				//shape.setTextureRect(IntRect(0, 0, 26, 26));
				//shape.setPosition(SpwanPos);
				//shape.setOrigin({ shape.getLocalBounds().width / 2, shape.getLocalBounds().height / 2 });
				//projectileLifeSpan = seconds(17.5); //time to despawn
				//shape.setScale(3.5, 3.5);
				//speed = 0;
				//damage = PlantDamage;
				//slowMultiplier = 1;
			}
		}
		void update(bool isPaused) {

			if (type == PeaShooter || type == SnowPeaShooter)
			{
				shape.move(speed, 0);
			}
			else if (type == SunFlower)
			{
				//SunCoinShape1.rotate(1);
				SunCoinShape2.rotate(-0.5);
				SunCoinShape3.rotate(0.5);
			}
		}
	};

	vector<PlantProjectile> PlantProjectilesARR; // contains both the bullets and sun coins

	struct Plants {
		//string type;
		Sprite shape;
		PlantType type;

	private:
		float health;
		float damage;

		int animationCol = 0;
		int animationRow = 0;

		bool doAction = false;
		bool idle = true;
		bool isDead = false;
		bool zombieInFront = false;

		Clock actionClock, animationClock;
		Time timeForAction, animationSpeed = seconds(0.2); // time for each frame

	public:
		// calls function when you spawn the plant
		void start() {
			setupPrefab();
		}
		void update(RectangleShape zombie, bool isPaused) //<<<<<<<<---------------<<< take the array of zombies and loop through them
		{
			if (!isDead) // if not dead will animate and execute action
			{
				//checks if a zombie is infront of the plant
				//will take the array of zombies instead in the future
				if ((type == PeaShooter || type == SnowPeaShooter) &&
					((shape.getPosition().y <= zombie.getGlobalBounds().top + zombie.getGlobalBounds().height &&
						shape.getPosition().y >= zombie.getGlobalBounds().top) &&
						shape.getPosition().x <= zombie.getGlobalBounds().left))
				{
					zombieInFront = true;
				}
				else
				{
					zombieInFront = false;
				}

				animationHandler();
				action();
			}
			else // else will turn the plant into an empty gameobject
			{
				type = EmptyPlant;
				setupPrefab();

				// and remove the plant from the garden
			}
		}

		void takeDmg(float damage) { //<<<<<<<<---------------<<< to be used in the zombie system
			health -= damage;

			if (health <= 0)
			{
				idle = false;
				doAction = false;
				isDead = true;
			}
		}

	private:
		void animationHandler() {
			if (animationSpeed <= animationClock.getElapsedTime() && type != EmptyPlant)
			{
				if (type == PeaShooter)
				{
					if (idle)
					{
						shape.setTexture(PeaShooterIdleTex);
						animationCol = (animationCol + 1) % 8;
						shape.setTextureRect(IntRect(animationCol * 30, 0, 30, 34));
					}
					else if (doAction) {
						if (animationCol + 1 == 3)
						{
							doAction = false;
							idle = true;
							isDead = false;
						}
						shape.setTexture(PeaShooterShootTex);
						animationCol = (animationCol + 1) % 3;

						shape.setTextureRect(IntRect(animationCol * 30, 0, 30, 34));
					}
				}
				else if (type == SnowPeaShooter) {
					if (idle)
					{
						shape.setTexture(IcePeaShooterIdleTex);
						animationCol = (animationCol + 1) % 8;

						shape.setTextureRect(IntRect(animationCol * 32, 0, 32, 34));
					}
					else if (doAction) {
						if (animationCol + 1 == 3)
						{
							doAction = false;
							idle = true;
							isDead = false;
						}
						shape.setTexture(IcePeaShooterShootTex);
						animationCol = (animationCol + 1) % 3;

						shape.setTextureRect(IntRect(animationCol * 31, 0, 31, 34));

					}
				}
				else if (type == SunFlower) {
					if (idle)
					{
						shape.setTexture(SunFlowerIdleTex);
						animationCol = (animationCol + 1) % 6;

						shape.setTextureRect(IntRect(animationCol * 32, 0, 32, 34));
					}
					else if (doAction) {
						if (animationCol + 1 == 6)
						{
							doAction = false;
							idle = true;
							isDead = false;
						}
						shape.setTexture(SunFlowerProducingSunTex);
						animationCol = (animationCol + 1) % 6;

						shape.setTextureRect(IntRect(animationCol * 32, 0, 32, 34));
					}
				}
				else if (type == WallNut) { //always idle
					if (health >= 400)
					{
						animationRow = 0;
						animationCol = (animationCol + 1) % 5;
						shape.setTextureRect(IntRect(animationCol * 28, animationRow * 31, 28, 31));
					}
					else if (health >= 200) {
						animationRow = 1;
						animationCol = (animationCol + 1) % 5;
						shape.setTextureRect(IntRect(animationCol * 28, animationRow * 31, 28, 31));
					}
					else
					{
						animationRow = 2;
						animationCol = (animationCol + 1) % 5;
						shape.setTextureRect(IntRect(animationCol * 28, animationRow * 31, 28, 31));
					}
				}

				animationClock.restart();
			}
		}

		void action() {

			if (timeForAction <= actionClock.getElapsedTime() && type != EmptyPlant)
			{
				if (type == PeaShooter && zombieInFront) //shoot
				{
					doAction = true;
					idle = false;
					isDead = false;

					PlantProjectile bullet;
					bullet.start(type, damage, shape.getPosition() + Vector2f({ 7 , -23 }));

					PlantProjectilesARR.push_back(bullet);
				}
				else if (type == SnowPeaShooter && zombieInFront) // shoot
				{
					doAction = true;
					idle = false;
					isDead = false;

					PlantProjectile bullet;
					bullet.start(type, damage, shape.getPosition() + Vector2f({ 7, -23 }));

					PlantProjectilesARR.push_back(bullet);
				}
				else if (type == SunFlower) //spawn sun
				{
					doAction = true;
					idle = false;
					isDead = false;

					PlantProjectile sunCoin;
					sunCoin.start(type, damage, shape.getPosition() + Vector2f({ 0, 0 }));

					PlantProjectilesARR.push_back(sunCoin);
				}
				actionClock.restart();
			}
		}

		//setup all the plants
		void setupPrefab() {
			srand(time(0));		   //gives random time for the animation to be random
			actionClock.restart(); //starts the countdown right when they are planted

			//setup the current state of the plants
			doAction = false;
			idle = true;
			isDead = false;

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
				timeForAction = seconds(2); // time to shoot

				shape.setTexture(PeaShooterIdleTex);
				shape.setScale(3.5, 3.5);
				animationCol = rand() % 8;
			}
			else if (type == SnowPeaShooter) {
				health = 100;
				damage = 20;
				timeForAction = seconds(2); // time to shoot

				shape.setTexture(IcePeaShooterProjectileTex);
				shape.setScale(3.5, 3.5);
				animationCol = rand() % 8;
			}
			else if (type == SunFlower) {
				health = 100;
				damage = 0;
				timeForAction = seconds(24); // time to spawn sun 24

				shape.setTexture(SunFlowerIdleTex);
				shape.setScale(3.5, 3.5);
				animationCol = rand() % 6;
			}
			else if (type == WallNut) {
				health = 600;
				damage = 0;

				shape.setTexture(WallNutIdleTex);
				shape.setScale(3.5, 3.5);
				animationCol = rand() % 5;
			}
		}
	}PlantsArray[4];


	// we will have 45 plants in the game all set to null at the start of the game
	// ###### ahmed ibrahim & marawan ###### will set the position of the 45 plants on each box of the garden
	// and when the player decides to plant it will change from NULL to which ever plant they choose
	// and if the plant dies it will be NULL as well

	// this will be used for
	// loading textures
	// setting up the plants
	// calling the start function of each plant
	void StartPlants() {
		LoadPlantTextures(); //we could remove this and call it once in the main start function
		PlantProjectilesARR.clear();

		//testing will be removed soon
		PlantsArray[0].type = PeaShooter;
		PlantsArray[0].shape.setPosition({ 200,100 });
		PlantsArray[1].type = SnowPeaShooter;
		PlantsArray[1].shape.setPosition({ 200,300 });
		PlantsArray[2].type = WallNut;
		PlantsArray[2].shape.setPosition({ 200,500 });
		PlantsArray[3].type = SunFlower;
		PlantsArray[3].shape.setPosition({ 200,600 });

		for (int i = 0; i < 4; i++)
		{
			PlantsArray[i].start();
		}
	}

	// this function will be used to update the plants and remove outdated projectiles 
	// it will be called every frame
	void UpdatePlants(RectangleShape zombiePH, bool isPaused) {

		//deletes outdated projectiles
		if (!PlantProjectilesARR.empty() && PlantProjectilesARR.front().projectileLifeSpan <= PlantProjectilesARR.front().clock.getElapsedTime())
		{
			PlantProjectilesARR.erase(PlantProjectilesARR.begin());
		}

		for (int i = 0; i < PlantProjectilesARR.size(); i++)
		{
			PlantProjectilesARR[i].update(isPaused);
		}

		for (int i = 0; i < 4; i++)
		{
			PlantsArray[i].update(zombiePH, isPaused); // will take the zombie array in the update function
		}
	}

	void DrawPlantsAndProjectiles(RenderWindow& window) {
		for (int i = 0; i < PlantProjectilesARR.size(); i++)
		{
			if (PlantProjectilesARR[i].type == SunFlower)
			{
				window.draw(PlantProjectilesARR[i].SunCoinShape3);
				window.draw(PlantProjectilesARR[i].SunCoinShape2);
				window.draw(PlantProjectilesARR[i].SunCoinShape1);
			}
			else
			{
				window.draw(PlantProjectilesARR[i].shape);
			}
		}
		for (int i = 0; i < 4; i++)
		{
			window.draw(PlantsArray[i].shape);
		}
	}
}

