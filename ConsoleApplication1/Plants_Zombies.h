
#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<string>
#include<vector>
using namespace std;
using namespace sf;

namespace Plants_Zombies {
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
	//IcePeaShooter
	Texture IcePeaShooterIdleTex;
	Texture IcePeaShooterShootTex;
	Texture IcePeaShooterProjectileTex;
#pragma endregion

	//will load all textures once
	void LoadPlantTextures() {
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
	}

	struct Zombie;
	struct PlantProjectile;
	struct Plant;
	vector<PlantProjectile> PlantProjectilesARR;

	// PLANTS =============================================
	//all types of plants & zombies
	enum PlantType { PeaShooter, SnowPeaShooter, SunFlower, WallNut, EmptyPlant };
	enum zombieType { regular, bucketHat, trafficCone, soccerGuy, Dead };


	struct PlantProjectile
	{
		PlantType type;
		Sprite shape;

		float damage; 
		float slowMultiplier = 1; 
		float speed;

		Time projectileLifeSpan;
		Clock clock;

		void start(PlantType plantType, float PlantDamage, Vector2f SpwanPos) {
			clock.restart();
			type = plantType;

			if (type == PeaShooter)
			{
				shape.setTexture(PeaShooterProjectileTex);
				shape.setScale(3.5, 3.5);
				shape.setPosition(SpwanPos);
				projectileLifeSpan = seconds(5); //time to despawn
				speed = 5;
				damage = PlantDamage;
				slowMultiplier = 1; // wont affect anything
			}
			else if (type == SnowPeaShooter)
			{
				shape.setTexture(IcePeaShooterProjectileTex);
				shape.setScale(3.5, 3.5);
				shape.setPosition(SpwanPos);
				projectileLifeSpan = seconds(5); //time to despawn
				speed = 5;
				damage = PlantDamage;
				slowMultiplier = 0.5;
			}
			else if (type == SunFlower)
			{
				shape.setTexture(SunFlowerSunTex);
				shape.setPosition(SpwanPos);
				shape.setOrigin({ shape.getLocalBounds().width / 2, shape.getLocalBounds().height / 2 });
				projectileLifeSpan = seconds(17.5); //time to despawn
				shape.setScale(3.5, 3.5);
				speed = 0;
				damage = PlantDamage;
				slowMultiplier = 1;
			}
		}
		void update(bool isPaused) {

			if (type == PeaShooter || type == SnowPeaShooter)
			{
				shape.move(speed, 0);
			}
			else if (type == SunFlower)
			{
				shape.rotate(0.5);
			}
		}
	};

	

	struct Plants {
		Sprite shape;
		PlantType type;

		int row, col; //<<<<<<<<---------------<<< for the grid system
		
		bool isDead = false;
		bool zombieInFront = false;

		float damage;

		float health;
	private:

		int animationCol = 0;
		int animationRow = 0;

		bool doAction = false;
		bool idle = true;

		Clock actionClock, animationClock;
		Time timeForAction, animationSpeed = seconds(0.2); // time for each frame

	public:
		// calls function when you spawn the plant
		void start() {
			setupPrefab();
		}
		void updatePlantStruct(Zombie* zombie_array, bool isPaused);

		void takeDmg(float damage) { //<<<<<<<<---------------<<< to be used in the zombie system
			health -= damage;

			if (health <= 0)
			{
				idle = false;
				doAction = false;
				isDead = true;
			}
		}

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
				timeForAction = seconds(1.5); // time to shoot

				shape.setTexture(PeaShooterIdleTex);
				shape.setScale(3.5, 3.5);
				animationCol = rand() % 8;
			}
			else if (type == SnowPeaShooter) {
				health = 100;
				damage = 20;
				timeForAction = seconds(1.5); // time to shoot

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

	void StartPlants() {
		PlantProjectilesARR.clear();
		//here we will set all positions of the 45 plants to each box in the grid and make them all empty gameobjects
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
	void UpdatePlants(Zombie* zombie_array, bool isPaused) {

		//deletes outdated projectiles
		for (int i = 0; i < PlantProjectilesARR.size(); i++)
		{
			if (!PlantProjectilesARR.empty() && PlantProjectilesARR[i].projectileLifeSpan <= PlantProjectilesARR[i].clock.getElapsedTime())
			{
				PlantProjectilesARR.erase(PlantProjectilesARR.begin() + i);
				i--;
			}
		}

		for (int i = 0; i < PlantProjectilesARR.size(); i++)
		{
			PlantProjectilesARR[i].update(isPaused);
		}

		for (int i = 0; i < 4; i++)
		{
			PlantsArray[i].updatePlantStruct(zombie_array, isPaused); 
		}

		
	}

	void DrawPlantsAndProjectiles(RenderWindow& window) {
		for (int i = 0; i < PlantProjectilesARR.size(); i++)
		{
			window.draw(PlantProjectilesARR[i].shape);
		}
		for (int i = 0; i < 4; i++)
		{
			window.draw(PlantsArray[i].shape);
		}
	}

// ZOMBIES =============================================

#pragma region Texture Decalration
	//Regular
	Texture RegularWalkText;
	Texture RegularIdleText;
	Texture RegularAttackText;
	// TrafficCone
	Texture TrafficConeWalkText;
	Texture TrafficConeIdleText;
	Texture TrafficConeAttackText;
	//BucketHat
	Texture BucketHatWalkText;
	Texture BucketHatIdleText;
	Texture BucketHatAttackText;
	//SoccerGuy
	Texture SoccerGuyWalkText;
	Texture SoccerGuyIdleText;
	Texture SoccerGuyAttackText;
#pragma endregion

	void TextLoading() {

	}

	struct Zombie {
		RectangleShape zombieSquare; // instead of sprite for now
		Sprite zombieCont;
		zombieType type;

		int health;
		float speed;
		float damage;

		bool isDamaged = false;
		bool isAttacking = false;

	private:
		int CollIndex = 0;
		int RowIndex = 0;

		bool isIdle = false;
		bool isMoving = false;
		bool isDead = false;
		bool PlantsinFront = false;

	public:
		void start() {
			isIdle = false;
			isMoving = true;
			isAttacking = false;
			isDamaged = false;

			TextLoading();

			switch (type)
			{
			case regular:
				//zombieCont.setTexture(RegularWalkText);
				health = 100;
				speed = 10.0;
				damage = 10;
				zombieSquare.setPosition(1000, 100); // will be changed to the sprite
				break;
			case trafficCone:
				//zombieCont.setTexture(TrafficConeIdleText);
				health = 300;
				speed = 9.9;
				damage = 5;
				zombieSquare.setPosition(1000, 300); // will be changed to the sprite
				break;
			case bucketHat:
				//zombieCont.setTexture(BucketHatIdleText);
				health = 300;
				speed = 9.8;
				damage = 10;
				zombieSquare.setPosition(1000, 500); // will be changed to the sprite
				break;
			case soccerGuy:
				//zombieCont.setTexture(RegularIdleText);
				health = 150;
				speed = 15.0;
				damage = 5;
				zombieSquare.setPosition(1000, 600); // will be changed to the sprite
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
			default:
				break;
			}
		}
		void update(float deltaTime) { 

			if (!isDead || type != Dead)
			{
				//Animation(); will be used when sprites sheets are available (ammar)
				Movement(deltaTime);
				CollisionZombies(PlantProjectilesARR, PlantsArray);
			}

		}
		void CollisionZombies(vector<PlantProjectile>& PlantProjectilesARR, Plants* PlantsArray) {

			// Projectiles
			if (!PlantProjectilesARR.empty())
			{
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < PlantProjectilesARR.size(); j++) {
						if (!PlantProjectilesARR.empty()) {
							if (PlantProjectilesARR[j].shape.getGlobalBounds().intersects(zombie_array[i].zombieSquare.getGlobalBounds())) {
								zombie_array[i].health -= PlantProjectilesARR[j].damage;
								zombie_array[i].isDamaged = true;
								zombie_array[i].zombieSquare.setFillColor(Color::Red);
								if (PlantProjectilesARR[j].type == SnowPeaShooter)
								{
									zombie_array[i].speed = (speed * PlantProjectilesARR[j].slowMultiplier);
								}
								else if (PlantProjectilesARR[j].type == SunFlower) {
									zombie_array[i].health -= PlantProjectilesARR[j].damage;
								}
								PlantProjectilesARR.erase(PlantProjectilesARR.begin() + j);
								j--;
								break;
							}
						}
					}
				}
			}


			// Plants
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (Plants_Zombies::PlantsArray[i].shape.getGlobalBounds().intersects(Plants_Zombies::zombie_array[j].zombieSquare.getGlobalBounds()))
					{
						zombie_array[j].zombieSquare.setFillColor(Color::White);
						PlantsArray[i].takeDmg(Plants_Zombies::zombie_array[j].damage);
						cout << PlantsArray[i].health << endl;
						zombie_array[j].health -= PlantsArray[j].damage;
						zombie_array[j].isMoving = false;
						zombie_array[j].isAttacking = true;

					}
				}
			}
			

		}

	private:
		void Animation() {
			// regular
			if (type == regular && isIdle)
			{
			}
			else if (type == regular && isMoving)
			{
				zombieCont.setTexture(RegularWalkText);
				zombieCont.setTextureRect(IntRect(CollIndex * 42, 50, 42, 50));
				CollIndex = (CollIndex + 1) % 7;
			}
			else if (type == regular && isAttacking)
			{
			}
			else if (type == regular && isDead)
			{
			}

			// Traffic Cone
			if (type == trafficCone && isIdle)
			{

			}
			else if (type == trafficCone && isMoving)
			{

			}
			else if (type == trafficCone && isAttacking)
			{

			}
			else if (type == trafficCone && isDead)
			{

			}

			// Bucket Hat
			if (type == bucketHat && isIdle)
			{

			}
			else if (type == bucketHat && isMoving)
			{

			}
			else if (type == bucketHat && isAttacking)
			{

			}
			else if (type == bucketHat && isDead)
			{

			}

			// Soccer Guy
			if (type == soccerGuy && isIdle)
			{

			}
			else if (type == soccerGuy && isMoving)
			{

			}
			else if (type == soccerGuy && isAttacking)
			{

			}
			else if (type == soccerGuy && isDead)
			{

			}
		}
		void Movement(float deltaTime) {
			if (health <= 0)
			{
				isDead == true;
				zombieSquare.setScale(Vector2f(0, 0));
			}
			else if (isMoving)
			{
			zombieSquare.move(-1 * speed * deltaTime, 0);
			}
			
		}

	}zombie_array[4];

	void StartZombies() {
#pragma region regular
		zombie_array[0].type = regular;
		zombie_array[0].zombieSquare.setSize(Vector2f(100.f, 100.f));
		zombie_array[0].start();
#pragma endregion

#pragma region trafficCone 
		zombie_array[1].type = trafficCone;
		zombie_array[1].zombieSquare.setSize(Vector2f(100.f, 100.f));
		zombie_array[1].start();
#pragma endregion

#pragma region bucketHat
		zombie_array[2].type = bucketHat;
		zombie_array[2].zombieSquare.setSize(Vector2f(100.f, 100.f));
		zombie_array[2].start();
#pragma endregion

#pragma region soccerGuy
		zombie_array[3].type = soccerGuy;
		zombie_array[3].zombieSquare.setSize(Vector2f(100.f, 100.f));
		zombie_array[3].start();
#pragma endregion
	}

	void UpdateZombies(float deltaTime) {
		for (int i = 0; i < 4; i++)
		{
			if (zombie_array[i].type != Dead)
			{
				// Blue
				zombie_array[0].zombieSquare.setFillColor(Color::Blue);
				zombie_array[0].update(deltaTime);
				//Cyan
				zombie_array[1].zombieSquare.setFillColor(Color::Cyan);
				zombie_array[1].update(deltaTime);
				#pragma endregion
				// Yellow
				zombie_array[2].zombieSquare.setFillColor(Color::Yellow);
				zombie_array[2].update(deltaTime);
				// Magnetta
				zombie_array[3].zombieSquare.setFillColor(Color::Magenta);
				zombie_array[3].update(deltaTime);
			}
		}

	}

	void DrawZombies(RenderWindow& window) {
		for (int i = 0; i < 4; i++)
		{
			if (zombie_array[i].type != Dead)
			{
				
				window.draw(zombie_array[i].zombieSquare);

			}
		}
	}






	void Plants::updatePlantStruct(Zombie* zombie_array, bool isPaused) {
		for (int i = 0; i < 4; i++)
		{
			if (!PlantsArray[i].isDead) // if not dead will animate and execute action  
			{
				for (int j = 0; j < 4; j++)
				{
					// checks if a zombie is in front of the plant  
					if ((PlantsArray[i].type == PeaShooter || PlantsArray[i].type == SnowPeaShooter)
						&& ((PlantsArray[i].shape.getGlobalBounds().top + PlantsArray[i].shape.getGlobalBounds().height / 2) <= (zombie_array[j].zombieSquare.getGlobalBounds().top + zombie_array[j].zombieSquare.getGlobalBounds().height)
							&& ((PlantsArray[i].shape.getGlobalBounds().top + PlantsArray[i].shape.getGlobalBounds().height / 2) >= zombie_array[j].zombieSquare.getGlobalBounds().top)
							&& (PlantsArray[i].shape.getGlobalBounds().left <= zombie_array[j].zombieSquare.getGlobalBounds().left)))
					{
						PlantsArray[i].zombieInFront = true;
						break;
					}
					else
					{
						PlantsArray[i].zombieInFront = false;
					}
				}

				PlantsArray[i].animationHandler();
				PlantsArray[i].action();
			}
			else // else will turn the plant into an empty gameobject  
			{
				PlantsArray[i].type = EmptyPlant;
				PlantsArray[i].setupPrefab();
			}
		}
	}


}




