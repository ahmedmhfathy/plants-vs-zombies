#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<string>
#include<vector>
using namespace std;
using namespace sf;

int currentMoney;

struct Grid
{
	RectangleShape shape;
	bool isPlanted = false;
}myGrid[46];

namespace plantNS {
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

	//all types of plants
	enum PlantType { PeaShooter, SnowPeaShooter, SunFlower, WallNut, EmptyPlant };

	struct PlantProjectile
	{
		//string type;
		PlantType type;
		Sprite shape;

		float damage; //<<<<<<<<---------------<<< to be used in the zombie system
		float slowMultiplier = 1; //<<<<<<<<---------------<<< to be used in the zombie system
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
				//projectileLifeSpan = seconds(5); //time to despawn
				speed = 5;
				damage = PlantDamage;
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
				slowMultiplier = 0.5;
			}
			else if (type == SunFlower)
			{
				shape.setTexture(SunFlowerSunTex);
				shape.setPosition(SpwanPos);
				shape.setOrigin({ shape.getLocalBounds().width / 2, shape.getLocalBounds().height / 2 });
				projectileLifeSpan = seconds(12); //time to despawn
				shape.setScale(1.25, 1.25);
				speed = 0;
				damage = PlantDamage;
				slowMultiplier = 1;
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
		}
	};

	vector<PlantProjectile> PlantProjectilesARR; // contains both the bullets and sun coins

	struct Plants {
		Sprite shape;
		PlantType type;

		int GridIndex;

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
		void update(RectangleShape zombie) //<<<<<<<<---------------<<< take the array of zombies and loop through them
		{
			if (!isDead) // if not dead will animate and execute action
			{
				//checks if a zombie is infront of the plant and on screen
				//will take the array of zombies instead in the future
				if ((type == PeaShooter || type == SnowPeaShooter) 
					&& ((shape.getGlobalBounds().top + shape.getGlobalBounds().height / 2) <= (zombie.getGlobalBounds().top + zombie.getGlobalBounds().height)
					&& ((shape.getGlobalBounds().top + shape.getGlobalBounds().height / 2) >= zombie.getGlobalBounds().top)
					&& (shape.getGlobalBounds().left <= zombie.getGlobalBounds().left))
					&& (zombie.getPosition().x <= 1000))
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

			if (type == EmptyPlant || health <=0)
			{
				myGrid[GridIndex].isPlanted = false;
				idle = false;
				doAction = false;
				isDead = true;

				type = EmptyPlant;
				setupPrefab();
			}
		}

		void takeDmg(float damage) { //<<<<<<<<---------------<<< to be used in the zombie system
			health -= damage;
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
					bullet.start(type, damage, shape.getPosition() + Vector2f({ 12 , -24 }));

					PlantProjectilesARR.push_back(bullet);
				}
				else if (type == SnowPeaShooter && zombieInFront) // shoot
				{
					doAction = true;
					idle = false;
					isDead = false;

					PlantProjectile bullet;
					bullet.start(type, damage, shape.getPosition() + Vector2f({ 12, -24 }));

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

				animationCol = rand() % 8;
				shape.setTextureRect(IntRect(animationCol * 30, 0, 30, 34));
				shape.setTexture(PeaShooterIdleTex);
				shape.setScale(3.5, 3.5);
			}
			else if (type == SnowPeaShooter) {
				health = 100;
				damage = 20;
				timeForAction = seconds(1.5); // time to shoot

				animationCol = rand() % 8;
				shape.setTextureRect(IntRect(animationCol * 32, 0, 32, 34));
				shape.setTexture(IcePeaShooterProjectileTex);
				shape.setScale(3.5, 3.5);
			}
			else if (type == SunFlower) {
				health = 100;
				damage = 0;
				timeForAction = seconds(24); // time to spawn sun 24

				animationCol = rand() % 6;
				shape.setTextureRect(IntRect(animationCol * 32, 0, 32, 34));
				shape.setTexture(SunFlowerIdleTex);
				shape.setScale(3.5, 3.5);
			}
			else if (type == WallNut) {
				health = 600;
				damage = 0;

				animationRow = 0;
				animationCol = rand() % 5;
				shape.setTextureRect(IntRect(animationCol * 28, animationRow * 31, 28, 31));
				shape.setTexture(WallNutIdleTex);
				shape.setScale(3.5, 3.5);
			}
		}
	}PlantsArray[45];

	void StartPlants() {
		PlantProjectilesARR.clear();
		//here we will set all positions of the 45 plants to each box in the grid and make them all empty gameobjects

		//testing will be removed soon
		for (int i = 1; i <= 45; i++)
		{
			PlantsArray[i - 1].shape.setPosition(myGrid[i].shape.getPosition());
			PlantsArray[i - 1].type = EmptyPlant;
			PlantsArray[i - 1].GridIndex = i;
			myGrid[i].isPlanted = false;
		}

		PlantsArray[0].type = PeaShooter;
		myGrid[1].isPlanted = true;
		//PlantsArray[0].shape.setPosition({ 200,100 });
		PlantsArray[1].type = SnowPeaShooter;
		myGrid[2].isPlanted = true;
		//PlantsArray[1].shape.setPosition({ 200,300 });
		PlantsArray[2].type = WallNut;
		myGrid[3].isPlanted = true;
		//PlantsArray[2].shape.setPosition({ 200,500 });
		PlantsArray[3].type = SunFlower;
		myGrid[4].isPlanted = true;
		//PlantsArray[3].shape.setPosition({ 200,600 });

		for (int i = 0; i < 45; i++)
		{
			PlantsArray[i].start();
		}
	}

	// this function will be used to update the plants and remove outdated projectiles 
	// it will be called every frame
	void UpdatePlants(RectangleShape zombiePH, Vector2f mousePos) {
		//deletes outdated projectiles
		for (int i = 0; i < PlantProjectilesARR.size(); i++)
		{
			if ((PlantProjectilesARR[i].type == PeaShooter || PlantProjectilesARR[i].type == SnowPeaShooter) && 
				PlantProjectilesARR[i].shape.getPosition().x > 1290) //enter despawn position
			{
				PlantProjectilesARR.erase(PlantProjectilesARR.begin() + i);
				i--;
			}
			else if ((PlantProjectilesARR[i].type == SunFlower) &&
					(!PlantProjectilesARR.empty() && PlantProjectilesARR[i].projectileLifeSpan <= PlantProjectilesARR[i].clock.getElapsedTime()))
			{
				PlantProjectilesARR.erase(PlantProjectilesARR.begin() + i);
				i--;
			}
		}

		for (int i = 0; i < PlantProjectilesARR.size(); i++)
		{
			PlantProjectilesARR[i].update();

			if (PlantProjectilesARR[i].type == SunFlower && PlantProjectilesARR[i].shape.getGlobalBounds().contains(mousePos)
				&& Mouse::isButtonPressed(Mouse::Left))
			{
				currentMoney += 25;
				PlantProjectilesARR.erase(PlantProjectilesARR.begin() + i);
				i--;
			}
		}

		for (int i = 0; i < 45; i++)
		{
			PlantsArray[i].update(zombiePH); // will take the zombie array in the update function
		}
	}

	void DrawPlantsAndProjectiles(RenderWindow& window) {
		for (int i = 0; i < PlantProjectilesARR.size(); i++)
		{
			window.draw(PlantProjectilesARR[i].shape);
		}
		for (int i = 0; i < 45; i++)
		{
			if (PlantsArray[i].type != EmptyPlant)
			{
				window.draw(PlantsArray[i].shape);
			}
		}
	}
}

namespace plantingSystem {

#pragma region PlantSelection Texture Declaration
	Texture SunContainerTex;
	Texture ShovelContainerBlankTex;
	Texture ShovelContainerTex;
	Texture ShovelTex;

	Texture GradientOpacityTex;

	Texture PeaShooterSeedPacketTex;
	Texture	PeaShooterSeedPacketUnavailableTex;

	Texture SnowPeaShooterSeedPacketTex;
	Texture SnowPeaShooterSeedPacketUnavailableTex;

	Texture SunFlowerSeedPacketTex;
	Texture SunFlowerSeedPacketUnavailableTex;

	Texture WallNutSeedPacketTex;
	Texture WallNutSeedPacketUnavailableTex;
#pragma endregion

#pragma region Plant Selection Sprite Declaration
	Sprite SunContainer;
	Sprite ShovelContainer;
	Sprite SelectionHolograph;
	Sprite GradientOpacity;

	Sprite peaShooterSeedPacket;
	Sprite SnowPeaShooterSeedPacket;
	Sprite SunFlowerSeedPacket;
	Sprite WallNutSeedPacket;
#pragma endregion

#pragma region Clocks and timers
	Clock PeaShooterClock, SnowPeaShooterClock, SunFlowerClock, WallNutClock;
	Time PeaShooterTime = seconds(7);
	Time SnowPeaShooterTime = seconds(7);
	Time SunFlowerTime = seconds(7);
	Time WallNutTime = seconds(30);
#pragma endregion

	Font font;
	Text moneyText;

	bool isHolding = false;

	void LoadPlantSelectionTextures() {
		font.loadFromFile("Assets/HouseofTerror Regular.otf");

		SunContainerTex.loadFromFile("Assets/Currency system and planting/sun-cointainer.png");
		ShovelContainerBlankTex.loadFromFile("Assets/Currency system and planting/empty-container.png");
		ShovelContainerTex.loadFromFile("Assets/Currency system and planting/container-with-shovel.png");
		ShovelTex.loadFromFile("Assets/Currency system and planting/shovel.png");

		GradientOpacityTex.loadFromFile("Assets/Currency system and planting/Gradient-opacity-layer.png");

		PeaShooterSeedPacketTex.loadFromFile("Assets/Currency system and planting/peashooter-seedpacket-1.png");
		PeaShooterSeedPacketUnavailableTex.loadFromFile("Assets/Currency system and planting/peashooter-seedpacket-2.png");

		SnowPeaShooterSeedPacketTex.loadFromFile("Assets/Currency system and planting/snowpea-seedpacket-1.png");
		SnowPeaShooterSeedPacketUnavailableTex.loadFromFile("Assets/Currency system and planting/snowpea-seedpacket-2.png");

		SunFlowerSeedPacketTex.loadFromFile("Assets/Currency system and planting/sunflower-seedpacket-1.png");
		SunFlowerSeedPacketUnavailableTex.loadFromFile("Assets/Currency system and planting/sunflower-seedpacket-2.png");

		WallNutSeedPacketTex.loadFromFile("Assets/Currency system and planting/wallnut-seedpacket-1.png");
		WallNutSeedPacketUnavailableTex.loadFromFile("Assets/Currency system and planting/wallnut-seedpacket-2.png");
	}



	void SetupPlantSelectionUI(Vector2f offset) {
		GradientOpacity.setTexture(GradientOpacityTex);
		GradientOpacity.setPosition(0 + offset.x, 0 + offset.y);

		SunContainer.setTexture(SunContainerTex);
		SunContainer.setPosition(30 + offset.x, 20 + offset.y);

		moneyText.setFont(font);
		moneyText.setCharacterSize(56);
		moneyText.setOutlineColor(Color::Black);
		moneyText.setOutlineThickness(3);
		moneyText.setPosition(55 + offset.x, 117 + offset.y);

		SunFlowerSeedPacket.setTexture(SunFlowerSeedPacketTex);
		SunFlowerSeedPacket.setPosition(23 + offset.x, 183 + offset.y);

		peaShooterSeedPacket.setTexture(PeaShooterSeedPacketTex);
		peaShooterSeedPacket.setPosition(27 + offset.x, 292 + offset.y);

		SnowPeaShooterSeedPacket.setTexture(SnowPeaShooterSeedPacketTex);
		SnowPeaShooterSeedPacket.setPosition(27 + offset.x, 393 + offset.y);

		WallNutSeedPacket.setTexture(WallNutSeedPacketTex);
		WallNutSeedPacket.setPosition(27 + offset.x, 490 + offset.y);

		ShovelContainer.setTexture(ShovelContainerTex);
		ShovelContainer.setPosition(27 + offset.x, 595 + offset.y);
	}

	enum Selection { PeaShooter, SnowPeaShooter, SunFlower, WallNut, Shovel, None }currentSelection;

	void startPlantingSystem(Vector2f offset) {
		LoadPlantSelectionTextures();
		SetupPlantSelectionUI(offset);

		SunFlowerClock.restart();
		PeaShooterClock.restart();
		SnowPeaShooterClock.restart();
		WallNutClock.restart();

		currentMoney = 50;
		currentSelection = SnowPeaShooter;

		//setup the grid
		for (int i = 1, r = 0, c = 0; i <= 45; i++)
		{
			myGrid[i].shape.setSize({ 107, 130 });
			myGrid[i].shape.setPosition(107 * c, 130 * r);

			c++;
			if (i % 9 == 0)
			{
				c = 0;
				r++;
			}
			if (i % 2 == 0)
			{
				myGrid[i].shape.setFillColor(Color(255, 255, 255, 64));
			}
			else
			{
				myGrid[i].shape.setFillColor(Color(255, 255, 255, 32));
			}
		}
	}

	void updatePlantingSystem(Vector2f mousePos) {

		moneyText.setString(to_string(currentMoney));

		#pragma region selection logic
		if (PeaShooterClock.getElapsedTime() >= PeaShooterTime && currentMoney >= 100)
		{
			peaShooterSeedPacket.setTexture(PeaShooterSeedPacketTex);
			if (peaShooterSeedPacket.getGlobalBounds().contains(mousePos) && Mouse::isButtonPressed(Mouse::Left))
			{
				isHolding = true;
				currentSelection = PeaShooter;
			}
		}
		else
		{
			peaShooterSeedPacket.setTexture(PeaShooterSeedPacketUnavailableTex);
		}

		if (SnowPeaShooterClock.getElapsedTime() >= SnowPeaShooterTime && currentMoney >= 175)
		{
			SnowPeaShooterSeedPacket.setTexture(SnowPeaShooterSeedPacketTex);
			if (SnowPeaShooterSeedPacket.getGlobalBounds().contains(mousePos) && Mouse::isButtonPressed(Mouse::Left)) {
				isHolding = true;
				currentSelection = SnowPeaShooter;
			}
		}
		else
		{
			SnowPeaShooterSeedPacket.setTexture(SnowPeaShooterSeedPacketUnavailableTex);
		}

		if (SunFlowerClock.getElapsedTime() >= SunFlowerTime && currentMoney >= 50)
		{
			SunFlowerSeedPacket.setTexture(SunFlowerSeedPacketTex);
			if (SunFlowerSeedPacket.getGlobalBounds().contains(mousePos) && Mouse::isButtonPressed(Mouse::Left)) {
				isHolding = true;
				currentSelection = SunFlower;
			}
		}
		else
		{
			SunFlowerSeedPacket.setTexture(SunFlowerSeedPacketUnavailableTex);
		}

		if (WallNutClock.getElapsedTime() >= WallNutTime && currentMoney >= 50)
		{
			WallNutSeedPacket.setTexture(WallNutSeedPacketTex);
			if (WallNutSeedPacket.getGlobalBounds().contains(mousePos) && Mouse::isButtonPressed(Mouse::Left)) {
				isHolding = true;
				currentSelection = WallNut;
			}
		}
		else
		{
			WallNutSeedPacket.setTexture(WallNutSeedPacketUnavailableTex);
		}

		if (ShovelContainer.getGlobalBounds().contains(mousePos) && Mouse::isButtonPressed(Mouse::Left)) {
			isHolding = true;
			currentSelection = Shovel;
		}

		//cancel holding when you right click
		if (Mouse::isButtonPressed(Mouse::Right))
		{
			isHolding = false;
		}

		// if holding an item show the holograph of it
		if (isHolding)
		{
			if (currentSelection == Shovel)
			{
				ShovelContainer.setTexture(ShovelContainerBlankTex);

				SelectionHolograph.setTextureRect(IntRect(0, 0, 100, 100));
				SelectionHolograph.setTexture(ShovelTex);
				SelectionHolograph.setOrigin({ SelectionHolograph.getGlobalBounds().width / 2, SelectionHolograph.getGlobalBounds().height / 2 });
				SelectionHolograph.setScale(1, 1);
			}
			else if (currentSelection == PeaShooter)
			{
				SelectionHolograph.setTextureRect(IntRect(0 * 30, 0, 30, 34));
				SelectionHolograph.setTexture(plantNS::PeaShooterIdleTex);
				SelectionHolograph.setOrigin({ SelectionHolograph.getLocalBounds().width / 2, SelectionHolograph.getLocalBounds().height / 2 });
				SelectionHolograph.setScale(3.5, 3.5);
			}
			else if (currentSelection == SnowPeaShooter)
			{
				SelectionHolograph.setTextureRect(IntRect(0 * 32, 0, 32, 34));
				SelectionHolograph.setTexture(plantNS::IcePeaShooterIdleTex);
				SelectionHolograph.setOrigin({ SelectionHolograph.getLocalBounds().width / 2, SelectionHolograph.getLocalBounds().height / 2 });
				SelectionHolograph.setScale(3.5, 3.5);
			}
			else if (currentSelection == SunFlower)
			{
				SelectionHolograph.setTextureRect(IntRect(0 * 32, 0, 32, 34));
				SelectionHolograph.setTexture(plantNS::SunFlowerIdleTex);
				SelectionHolograph.setOrigin({ SelectionHolograph.getLocalBounds().width / 2, SelectionHolograph.getLocalBounds().height / 2 });
				SelectionHolograph.setScale(3.5, 3.5);
			}
			else if (currentSelection == WallNut)
			{
				SelectionHolograph.setTextureRect(IntRect(0 * 28, 0 * 31, 28, 31));
				SelectionHolograph.setTexture(plantNS::WallNutIdleTex);
				SelectionHolograph.setOrigin({ SelectionHolograph.getLocalBounds().width / 2, SelectionHolograph.getLocalBounds().height / 2 });
				SelectionHolograph.setScale(3.5, 3.5);
			}

			SelectionHolograph.setPosition(mousePos);
		}
		else
		{
			ShovelContainer.setTexture(ShovelContainerTex);
			currentSelection = None;
		}
		#pragma endregion

		//planting logic
		if (currentSelection != None)
		{
			for (int i = 1; i < 46; i++)
			{
				if (myGrid[i].shape.getGlobalBounds().contains(mousePos) && Mouse::isButtonPressed(Mouse::Left))
				{
					if (currentSelection == Shovel && isHolding)
					{
						cout << "Shovel " << i << endl;
						
						plantNS::PlantsArray[i - 1].type = plantNS::EmptyPlant;
						plantNS::PlantsArray[i - 1].start();
						myGrid[i].isPlanted = false;

						isHolding = false;
						currentSelection = None;
					}
					else if (currentSelection == PeaShooter && isHolding)
					{
						if (!myGrid[i].isPlanted)
						{
							cout << "PeaShooter " << i << endl;

							plantNS::PlantsArray[i - 1].type = plantNS::PeaShooter;
							plantNS::PlantsArray[i - 1].start();
							myGrid[i].isPlanted = true;

							currentMoney -= 100;
							PeaShooterClock.restart();

							isHolding = false;
							currentSelection = None;
						}
					}
					else if (currentSelection == SnowPeaShooter && isHolding)
					{
						if (!myGrid[i].isPlanted)
						{
							cout << "SnowPeaShooter " << i << endl;

							plantNS::PlantsArray[i - 1].type = plantNS::SnowPeaShooter;
							plantNS::PlantsArray[i - 1].start();
							myGrid[i].isPlanted = true;

							currentMoney -= 175;
							SnowPeaShooterClock.restart();

							isHolding = false;
							currentSelection = None;
						}
					}
					else if (currentSelection == SunFlower && isHolding)
					{
						if (!myGrid[i].isPlanted)
						{
							cout << "SunFlower " << i << endl;

							plantNS::PlantsArray[i - 1].type = plantNS::SunFlower;
							plantNS::PlantsArray[i - 1].start();
							myGrid[i].isPlanted = true;

							currentMoney -= 50;
							SunFlowerClock.restart();

							isHolding = false;
							currentSelection = None;
						}
					}
					else if (currentSelection == WallNut && isHolding)
					{
						if (!myGrid[i].isPlanted)
						{
							cout << "WallNut " << i << endl;

							plantNS::PlantsArray[i - 1].type = plantNS::WallNut;
							plantNS::PlantsArray[i - 1].start();
							myGrid[i].isPlanted = true;

							currentMoney -= 50;
							WallNutClock.restart();

							isHolding = false;
							currentSelection = None;
						}
					}
				}
			}
		}
	}

	////draws the grid
	//void drawPlantingSystem(RenderWindow& window) {
	//	for (int i = 1; i <= 45; i++)
	//	{
	//		window.draw(myGrid[i].shape);
	//	}
	//}

	void drawPlantSelectionUI(RenderWindow& window) {
		window.draw(GradientOpacity);
		window.draw(SunContainer);
		window.draw(moneyText);
		window.draw(peaShooterSeedPacket);
		window.draw(SnowPeaShooterSeedPacket);
		window.draw(SunFlowerSeedPacket);
		window.draw(WallNutSeedPacket);
		window.draw(ShovelContainer);

		if (isHolding)
		{
			window.draw(SelectionHolograph);
		}
	}
}
