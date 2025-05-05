#pragma once
#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<string>
#include<vector>
using namespace std;
using namespace sf;

namespace Plants_Zombies {
	int score;
#pragma region Forward Declaration for Structs
	struct Zombie;
	struct PlantProjectile;
	struct Plant;
	vector<PlantProjectile> PlantProjectilesARR;
#pragma endregion

#pragma region Plants and Zombies Types
	enum PlantType { PeaShooter, SnowPeaShooter, SunFlower, WallNut, EmptyPlant, SunCoin };
	enum zombieType { regular, bucketHat, trafficCone, newsMan, Dead };
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

	struct PlantProjectile
	{
		//string type;
		PlantType type;
		Sprite shape;

		float damage;
		float slowMultiplier = 1;
		float speed;

		Time projectileLifeSpan;
		Clock clock;

		int sunCoinYLimt;

		void start(PlantType plantType, float PlantDamage, Vector2f SpwanPos, int yLimit) {
			clock.restart();
			type = plantType;

			if (type == PeaShooter)
			{
				shape.setTexture(PeaShooterProjectileTex);
				shape.setScale(3.5, 3.5);
				shape.setPosition(SpwanPos);
				//projectileLifeSpan = seconds(5); //time to despawn
				speed = 5;
				damage = 60;
				slowMultiplier = 1; // wont affect anything
			}
			else if (type == SnowPeaShooter)
			{
				shape.setTexture(IcePeaShooterProjectileTex);
				shape.setScale(3.5, 3.5);
				shape.setPosition(SpwanPos);
				//projectileLifeSpan = seconds(5); //time to despawn
				speed = 5;
				damage = PlantDamage;
				slowMultiplier = 0.3;
			}
			else if (type == SunFlower || type == SunCoin)
			{
				shape.setTexture(SunFlowerSunTex);
				shape.setPosition(SpwanPos);
				shape.setOrigin({ shape.getLocalBounds().width / 2, shape.getLocalBounds().height / 2 });
				projectileLifeSpan = seconds(12); //time to despawn
				shape.setScale(1.25, 1.25);
				speed = 1;
				damage = PlantDamage;
				slowMultiplier = 1;
				sunCoinYLimt = yLimit;
			}
		}
		void update() {

			if (type == PeaShooter || type == SnowPeaShooter)
			{
				shape.move(speed, 0);
			}
			else if (type == SunFlower)
			{
				shape.rotate(0.5);
			}
			else if (type == SunCoin)
			{
				if (shape.getPosition().y < sunCoinYLimt)
				{
					shape.move(0, speed);
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

		bool zombieInFront = false;

		float health;
		float damage;
	private:

		int animationCol = 0;
		int animationRow = 0;

		bool doAction = false;
		bool idle = true;
		bool isDead = false;

		Clock actionClock, animationClock;
		Time timeForAction, animationSpeed = seconds(0.2); // time for each frame

	public:
		// calls function when you spawn the plant
		void start() {
			setupPrefab();
		}

		void takeDmg(float damage) {
			health -= damage;
			cout << "Plant Health = " << health << endl;
			if (health <= 0)
			{
				idle = false;
				doAction = false;
				isDead = true;
			}
		}
		void updatePlantStruct(Zombie* zombie_array); // Defined at the bottom of the code

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
					bullet.start(type, damage, shape.getPosition() + Vector2f({ 12 , -24 }), 0);

					PlantProjectilesARR.push_back(bullet);
				}
				else if (type == SnowPeaShooter && zombieInFront) // shoot
				{
					doAction = true;
					idle = false;
					isDead = false;

					PlantProjectile bullet;
					bullet.start(type, damage, shape.getPosition() + Vector2f({ 12, -24 }), 0);

					PlantProjectilesARR.push_back(bullet);
				}
				else if (type == SunFlower) //spawn sun
				{
					doAction = true;
					idle = false;
					isDead = false;

					PlantProjectile sunCoin;
					sunCoin.start(type, damage, shape.getPosition() + Vector2f({ 0, 0 }), 0);

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

				plantCollider.setSize({ 30, 34 });

				shape.setTexture(PeaShooterIdleTex);
				shape.setScale(3.5, 3.5);
				animationCol = rand() % 8;
			}
			else if (type == SnowPeaShooter) {
				health = 100;
				damage = 20;
				timeForAction = seconds(1.5); // time to shoot

				plantCollider.setSize({ 31, 34 });

				shape.setTexture(IcePeaShooterProjectileTex);
				shape.setScale(3.5, 3.5);
				animationCol = rand() % 8;
			}
			else if (type == SunFlower) {
				health = 100;
				damage = 0;
				timeForAction = seconds(24); // time to spawn sun 24

				plantCollider.setSize({ 32, 34 });

				shape.setTexture(SunFlowerIdleTex);
				shape.setScale(3.5, 3.5);
				animationCol = rand() % 6;
			}
			else if (type == WallNut) {
				health = 1400;
				damage = 0;

				plantCollider.setSize({ 28, 31 });

				shape.setTexture(WallNutIdleTex);
				shape.setScale(3.5, 3.5);
				animationCol = rand() % 5;
			}

			plantCollider.setScale(2.9, 2);
			plantCollider.setFillColor(Color(252, 186, 3, 180));
			/*plantCollider.setPosition(shape.getPosition().x + 50, shape.getPosition().y + 20);*/
		}
	}PlantsArray[45];

	void UpdatePlants(Zombie* zombie_array, Vector2f mousepos) {
		//deletes outdated projectiles
		for (int i = 0; i < PlantProjectilesARR.size(); i++)
		{
			if (!PlantProjectilesARR.empty()
				&& (PlantProjectilesARR[i].type == PeaShooter || PlantProjectilesARR[i].type == SnowPeaShooter)
				&& PlantProjectilesARR[i].shape.getPosition().x > 1290) //enter despawn position
			{
				PlantProjectilesARR.erase(PlantProjectilesARR.begin() + i);
				i--;
			}
			else if (!PlantProjectilesARR.empty()
				&& (PlantProjectilesARR[i].type == SunFlower || PlantProjectilesARR[i].type == SunCoin)
				&& (PlantProjectilesARR[i].projectileLifeSpan <= PlantProjectilesARR[i].clock.getElapsedTime()))
			{
				PlantProjectilesARR.erase(PlantProjectilesARR.begin() + i);
				i--;
			}
		}

		for (int i = 0; i < PlantProjectilesARR.size(); i++)
		{
			PlantProjectilesARR[i].update();
			if ((PlantProjectilesARR[i].type == SunFlower || PlantProjectilesARR[i].type == SunCoin)
				&& PlantProjectilesARR[i].shape.getGlobalBounds().contains(mousepos)
				&& Mouse::isButtonPressed(Mouse::Left))
			{
				//SunCoinSound.play();
				score += 25;
				PlantProjectilesARR.erase(PlantProjectilesARR.begin() + i);
				i--;
			}
		}

		for (int i = 0; i < 45; i++)
		{
			PlantsArray[i].updatePlantStruct(zombie_array);
		}
	}

	void DrawPlantsAndProjectiles(RenderWindow& window) {
		for (int i = 0; i < PlantProjectilesARR.size(); i++)
		{
			if (PlantProjectilesARR[i].type == PeaShooter || PlantProjectilesARR[i].type == SnowPeaShooter)
			{
				window.draw(PlantProjectilesARR[i].shape);
			}
		}
		for (int i = 0; i < 45; i++)
		{
			if (!(PlantsArray[i].type == EmptyPlant || PlantsArray[i].health <= 0))
			{
				window.draw(PlantsArray[i].plantCollider);
				window.draw(PlantsArray[i].shape);
			}
		}
		for (int i = 0; i < PlantProjectilesARR.size(); i++)
		{
			if (PlantProjectilesARR[i].type == SunFlower || PlantProjectilesARR[i].type == SunCoin)
			{
				window.draw(PlantProjectilesARR[i].shape);
			}
		}
	}

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
	}

	int numberofdeadzombie = 0;
	struct Zombie {
		Sprite zombieCont;
		RectangleShape zombieCollider;

		zombieType type;
		bool started = false;
		bool stoped;
		bool isSlowed = false;

		int health;
		float speed;
		float damage;

		bool isActivated = false;
		bool isDamaged = false;
		bool isAttacking = false;
		bool isDead = false;
		bool isMoving = false;
		bool isslowmultiply = false;

		Clock Zclock, EatClock;

	private:
		int CollIndex = 0;
		int RowIndex = 0;

		bool isIdle = false;
		bool PlantsinFront = false;
		bool deathOfZombie = false;

		int CurrentPlantIndex;
		bool PlantInfront = false;

	public:
		void start() {
			isIdle = false;
			isMoving = true;
			isAttacking = false;
			isDamaged = false;
			isSlowed = false;
			PlantInfront = false;

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
				// zombieCont.setPosition(1300, row[rand() % 5]); // sets random spawn position 
				break;
			case bucketHat:
				zombieCont.setTexture(BucketHatWalkText);
				health = 1300;
				speed = 7.4;
				damage = 20;

				zombieCollider.setSize({ 37, 56 });
				zombieCollider.setScale(1.4, 1);
				zombieCont.setScale(3, 3);
				// zombieCont.setPosition(1300, row[rand() % 5]); // sets random spawn position 
				break;
			case newsMan:
				zombieCont.setTexture(RegularWalkText);
				health = 1000;
				speed = 7.4;
				damage = 20;

				zombieCollider.setSize({ 50, 57 });
				zombieCollider.setScale(1.4, 1);
				zombieCont.setScale(3, 3);
				// zombieCont.setPosition(1300, row[rand() % 5]); // sets random spawn position 
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

			zombieCollider.setFillColor(Color(252, 3, 3, 180));
			zombieCont.setColor(Color(255, 255, 255, 255));
		}
		void update(float deltaTime) {

			if (!deathOfZombie || type != Dead)
			{
				Movement(deltaTime);
				CollisionZombies(PlantProjectilesARR, PlantsArray);
				Animation();
				if (type == trafficCone && health < 320 && !isDamaged)
					isDamaged = true;
				else if (type == bucketHat && health < 650 && !isDamaged)
					isDamaged = true;
				else if (type == newsMan && health < 800 && !isDamaged) {
					isDamaged = true;
					speed = 120;
					damage = 30;
				}

				if (isSlowed)
				{
					zombieCont.setColor(Color(120, 120, 255, 255));
				}
				else
				{
					zombieCont.setColor(Color(255, 255, 255, 255));
				}
			}

			if (health <= 0 || type == Dead)
			{
				deathOfZombie = true;
				isDead = true;
				isIdle = false;
				isAttacking = false;
				isDamaged = false;
				isMoving = false;

				zombieCont.setPosition(2000, 2000);
			}

			zombieCollider.setPosition(zombieCont.getPosition().x + 50, zombieCont.getPosition().y + 60);
		}

		void CollisionZombies(vector<PlantProjectile>& PlantProjectilesARR, Plants PlantsArray[]) {
			// Projectiles
			for (int j = 0; j < PlantProjectilesARR.size(); j++) {
				if (!PlantProjectilesARR.empty()) {
					if (PlantProjectilesARR[j].shape.getGlobalBounds().intersects(zombieCollider.getGlobalBounds())) {
						cout << "Zombie Health = " << health << endl;
						health -= PlantProjectilesARR[j].damage;

						if (PlantProjectilesARR[j].type == SnowPeaShooter && !isSlowed)
						{
							isSlowed = true;

							speed = (speed * PlantProjectilesARR[j].slowMultiplier);
						}

						PlantProjectilesARR.erase(PlantProjectilesARR.begin() + j);
						j--;
						break;
					}
				}
			}

			// Plants
			if (!PlantInfront)
			{
				for (int i = 0; i < 45; i++) {
					if (!isDead || type == Dead) {
						if (!(PlantsArray[i].type == EmptyPlant || PlantsArray[i].health <= 0)
							&& zombieCollider.getGlobalBounds().intersects(PlantsArray[i].plantCollider.getGlobalBounds())) {
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
				if (!(isDead || type == Dead || health <= 0))
				{
					isMoving = false;
					isAttacking = true;
					//attack clock
					if (EatClock.getElapsedTime() >= seconds(1))
					{
						PlantsArray[CurrentPlantIndex].takeDmg(damage);
						EatClock.restart();
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
			if (PlantsArray[CurrentPlantIndex].type == EmptyPlant || PlantsArray[CurrentPlantIndex].health <= 0)
			{
				PlantInfront = false;
				isMoving = true;
				isAttacking = false;
			}
		}

	private:
		void Animation() {

			// regular
			if (type == regular) {
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
					if (Zclock.getElapsedTime().asMilliseconds() > 200) {
						zombieCont.setTextureRect(IntRect(CollIndex * 100, 0, 100, 34));
						zombieCont.setTexture(RegularDeathText);
						CollIndex = (CollIndex + 1) % 8;
						Zclock.restart();

						if (CollIndex == 7)
						{
							deathOfZombie = true;
						}
					}
				}

			}

			// Traffic Cone
			if (type == trafficCone) {
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
					if (Zclock.getElapsedTime().asMilliseconds() > 200) {
						zombieCont.setTextureRect(IntRect(CollIndex * 100, 0, 100, 34));
						zombieCont.setTexture(ConeDeathText);
						CollIndex = (CollIndex + 1) % 8;
						Zclock.restart();

						if (CollIndex == 7)
						{
							deathOfZombie = true;
						}
					}
				}
			}

			// Bucket Hat
			if (type == bucketHat)
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
						zombieCont.setTexture(BucketHatAttackText);
						CollIndex = (CollIndex + 1) % 6;
						Zclock.restart();
					}
				}
				else if (isDead)
				{
					if (Zclock.getElapsedTime().asMilliseconds() > 200) {
						zombieCont.setTextureRect(IntRect(CollIndex * 100, 0, 100, 34));
						zombieCont.setTexture(BucketDeathText);
						CollIndex = (CollIndex + 1) % 8;
						Zclock.restart();
					}
					if (CollIndex == 7)
					{
						deathOfZombie = true;
					}
				}
			}

			// news man
			if (type == newsMan) {
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
					if (Zclock.getElapsedTime().asMilliseconds() > 150) {
						zombieCont.setTextureRect(IntRect(CollIndex * 58, 0, 58, 45));
						zombieCont.setTexture(NewsManDeath);
						CollIndex = (CollIndex + 1) % 6;
						Zclock.restart();
					}
					if (CollIndex == 6)
					{
						deathOfZombie = true;
					}
				}
			}
		}

		void Movement(float deltaTime)
		{
			if (health <= 0)
			{
				numberofdeadzombie++;
				isDead = true;
				isMoving = false;
				isAttacking = false;
				isDamaged = false;

				// waits until zombie is dead to remove it
				if (deathOfZombie)
				{
					/*if (Zclock.getElapsedTime().asSeconds()>2.5) {*/
					//zombieCont.setScale(Vector2f(0, 0));
					zombieCont.setPosition(2000, 2000);
					Zclock.restart();
					type = Dead;
				}
			}
			else if (isMoving)
			{
				zombieCont.move(-1 * speed * 400000 * deltaTime, 0);
			}
		}
	}zombie_array[100];

	void StartZombies(int numerzombieinwave) {
		for (int i = 0; i < numerzombieinwave; i++) {
			zombieType randomzombietype = static_cast<zombieType>(rand() % Dead);
			zombie_array[i].type = randomzombietype;
			zombie_array[i].start();
		}
	}
}