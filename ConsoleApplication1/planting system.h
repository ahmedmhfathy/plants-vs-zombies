#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include "Tools.h"
#include "Plants_Zombies.h"
using namespace std;
using namespace sf;

#pragma region texture declaration
Texture sunflowerAvailableTex;
Texture sunflowerUnavailableTex;
Texture peashooterAvailableTex;
Texture peashooterUnavailableTex;
Texture snowpeaAvailableTex;
Texture snowpeaUnavailableTex;
Texture wallnutAvailableTex;
Texture wallnutUnavailableTex;
Texture sunshroomAvailableTex;
Texture sunshroomUnavailableTex;
Texture puffshroomAvailableTex;
Texture puffshroomUnavailableTex;
Texture scaredyshroomAvailableTex;
Texture scaredyshroomUnavailableTex;

Texture emptySeedPacketTex;
Texture shoveltex;
Texture ShovelContainerAvailable;
Texture ShovelContainerEmpty;
Texture gradientopacitytex;
Texture sunContainerTex;
///=============================
Texture Textgraves;
#pragma endregion

#pragma region sprite declaration
Sprite sunflowerSeedPacket;
Sprite peashooterSeedPacket;
Sprite snowpeashooterSeedPacket;
Sprite wallnutSeedPacket;
Sprite sunshroomSeedPacket;
Sprite puffshroomSeedPacket;
Sprite scaredyshroomSeedPacket;

Sprite emptySeedPacket1;
Sprite emptySeedPacket2;

Sprite shovelcontainer;
Sprite sunContainer;
Sprite gradientopacity;
Sprite SelectionHolograph;
//===================================
Sprite graves[4];
#pragma endregion

#pragma region clocks and time
float sunSpawnTimeClock = 0;
Time SunSpawnTime = seconds(14);

float SunFlowerClock = 0;
float PeaShooterClock = 0;
float SnowPeaClock = 0;
float WallNutClock = 0;
float SunShroomClock = 0;
float PuffShroomClock = 0;
float ScaredyShroomClock = 0;

Time LongCoolDown = seconds(50);
Time MediumCoolDown = seconds(30);
Time ShortCoolDown = seconds(7);
#pragma endregion

#pragma region Sounds
SoundBuffer PlantingSoundBuffer;
SoundBuffer SelectingPlant;
SoundBuffer ShovelSoundBuffer;
#pragma endregion

Font font;
Text moneytext;

enum Selection { peashooter, snowpeashooter, sunflower, wallnut, sunshroom, puffshroom, scaredyshroom, shovel, none }curruntselection;

bool PlaySelectionSound = false;
bool isHolding = false;
bool isNight;

struct grid {
	RectangleShape shape;
	bool isplanted = false;
	bool gravePlanted = false;
}mygrid[46];

void LoadSelectionTexture() {
	PlantingSoundBuffer.loadFromFile("Audio/plant.ogg");
	ShovelSoundBuffer.loadFromFile("Audio/shovel.ogg");
	SelectingPlant.loadFromFile("Audio/seedlift.ogg");

	shoveltex.loadFromFile("Assets/Currency System and planting/shovel.png");
	ShovelContainerAvailable.loadFromFile("Assets/Currency System and planting/container-with-shovel.png");
	ShovelContainerEmpty.loadFromFile("Assets/Currency System and planting/empty-container.png");

	gradientopacitytex.loadFromFile("Assets/Currency System and planting/Gradient-opacity-layer.png");
	sunContainerTex.loadFromFile("Assets/Currency System and planting/sun-cointainer.png");
	emptySeedPacketTex.loadFromFile("Assets/Currency System and planting/New/seedpacket-container.png");

	font.loadFromFile("Assets/HouseofTerror Regular.otf");

	sunflowerAvailableTex.loadFromFile("Assets/Currency System and planting/New/sunflower-available.png");
	sunflowerUnavailableTex.loadFromFile("Assets/Currency System and planting/New/sunflower-unavailable.png");
	peashooterAvailableTex.loadFromFile("Assets/Currency System and planting/New/peashooter-available.png");
	peashooterUnavailableTex.loadFromFile("Assets/Currency System and planting/New/peashooter-unavailable.png");
	snowpeaAvailableTex.loadFromFile("Assets/Currency System and planting/New/snowpea-available.png");
	snowpeaUnavailableTex.loadFromFile("Assets/Currency System and planting/New/snowpea-unavailable.png");
	wallnutAvailableTex.loadFromFile("Assets/Currency System and planting/New/wallnut-available.png");
	wallnutUnavailableTex.loadFromFile("Assets/Currency System and planting/New/wallnut-unavailable.png");
	sunshroomAvailableTex.loadFromFile("Assets/Currency System and planting/New/sunshroom-available.png");
	sunshroomUnavailableTex.loadFromFile("Assets/Currency System and planting/New/sunshroom-unavailable.png");
	puffshroomAvailableTex.loadFromFile("Assets/Currency System and planting/New/puffshroom-available.png");
	puffshroomUnavailableTex.loadFromFile("Assets/Currency System and planting/New/puffshroom-unavailable.png");
	scaredyshroomAvailableTex.loadFromFile("Assets/Currency System and planting/New/scaredy-available.png");
	scaredyshroomUnavailableTex.loadFromFile("Assets/Currency System and planting/New/scaredy-unavailable.png");
	//==============================
	Textgraves.loadFromFile("Assets/Environment/Graves-ST.png");
}

void SetupSelectionUI(Vector2f offset)
{
	if (isNight)
	{
		sunshroomSeedPacket.setTexture(sunshroomUnavailableTex);
		sunshroomSeedPacket.setPosition(29 + offset.x, 15 + offset.y);

		scaredyshroomSeedPacket.setTexture(scaredyshroomUnavailableTex);
		scaredyshroomSeedPacket.setPosition(29 + offset.x, 119 + offset.y);

		puffshroomSeedPacket.setTexture(puffshroomUnavailableTex);
		puffshroomSeedPacket.setPosition(29 + offset.x, 243 + offset.y);

		peashooterSeedPacket.setTexture(peashooterUnavailableTex);
		peashooterSeedPacket.setPosition(29 + offset.x, 357 + offset.y);

		snowpeashooterSeedPacket.setTexture(snowpeaUnavailableTex);
		snowpeashooterSeedPacket.setPosition(29 + offset.x, 476 + offset.y);

		wallnutSeedPacket.setTexture(wallnutUnavailableTex);
		wallnutSeedPacket.setPosition(29 + offset.x, 580 + offset.y);
	}
	else
	{
		sunflowerSeedPacket.setTexture(sunflowerUnavailableTex);
		sunflowerSeedPacket.setPosition(24 + offset.x, 5 + offset.y);

		peashooterSeedPacket.setTexture(peashooterUnavailableTex);
		peashooterSeedPacket.setPosition(29 + offset.x, 129 + offset.y);

		snowpeashooterSeedPacket.setTexture(snowpeaUnavailableTex);
		snowpeashooterSeedPacket.setPosition(29 + offset.x, 248 + offset.y);

		wallnutSeedPacket.setTexture(wallnutUnavailableTex);
		wallnutSeedPacket.setPosition(29 + offset.x, 352 + offset.y);

		emptySeedPacket1.setTexture(emptySeedPacketTex);
		emptySeedPacket1.setPosition(29 + offset.x, 481 + offset.y);

		emptySeedPacket2.setTexture(emptySeedPacketTex);
		emptySeedPacket2.setPosition(29 + offset.x, 595 + offset.y);
	}

	gradientopacity.setTexture(gradientopacitytex);
	gradientopacity.setPosition(0 + offset.x, 0 + offset.y);

	shovelcontainer.setTexture(ShovelContainerAvailable);
	shovelcontainer.setPosition(170 + offset.x, 595 + offset.y);

	sunContainer.setTexture(sunContainerTex);
	sunContainer.setPosition(170 + offset.x, 25 + offset.y);

	moneytext.setFont(font);
	moneytext.setString(to_string(Plants_Zombies::score));
	moneytext.setCharacterSize(56);
	moneytext.setFillColor(Color::White);
	moneytext.setOutlineThickness(3);
	moneytext.setOrigin(moneytext.getGlobalBounds().width / 2, moneytext.getGlobalBounds().height / 2);
	moneytext.setPosition(170 + 53 + offset.x, 145 + offset.y);
}

void StartPlantingAndCurrencySystem(Vector2f offset, bool isNight_)
{
	isNight = isNight_;
	SetupSelectionUI(offset);
	Plants_Zombies::PlantProjectilesARR.clear();

	SunFlowerClock = 0;
	PeaShooterClock = 0;
	SnowPeaClock = 0;
	WallNutClock = 0;
	SunShroomClock = 0;
	PuffShroomClock = 0;
	ScaredyShroomClock = 0;

	Plants_Zombies::score = 50000;

	//setup the grid
	for (int i = 1, r = 0, c = 0; i <= 45; i++) {
		mygrid[i].shape.setSize({ 107,130 });
		mygrid[i].shape.setPosition(107 * c, 130 * r);

		c++;
		if (i % 9 == 0)
		{
			c = 0;
			r++;
		}
		
		//colours the grid
		if (i % 2 == 0) {
			mygrid[i].shape.setFillColor(Color(255, 255, 255, 64));
		}
		else {
			mygrid[i].shape.setFillColor(Color(255, 255, 255, 32));
		}

		//sets up the plants and sets them all to empty gameobjects
		Plants_Zombies::PlantsArray[i - 1].shape.setPosition(mygrid[i].shape.getPosition());
		Plants_Zombies::PlantsArray[i - 1].type = Plants_Zombies::EmptyPlant;
		Plants_Zombies::PlantsArray[i - 1].gridIndex = i;
		Plants_Zombies::PlantsArray[i - 1].start();
		mygrid[i].isplanted = false;
		mygrid[i].gravePlanted = false;
	}

	if (isNight)
	{
		int plantgraveson[20] = { 6, 7, 8, 9, 15, 16, 17, 18, 24, 25, 26, 27, 33, 34, 35, 36, 42, 43, 44, 45 };

		for (int x = 0; x < 4; x++)
		{
			int randindex = plantgraveson[rand() % 20];

			graves[x].setTexture(Textgraves);
			graves[x].setTextureRect(IntRect((4 + x) * 34, 0, 34, 38));
			graves[x].setScale(3, 3.1);
			graves[x].setPosition(mygrid[randindex].shape.getPosition());
			mygrid[randindex].isplanted = true;
			mygrid[randindex].gravePlanted = true;
		}
	}
}

void UpdatePlantingAndCurrencySystem(Vector2f mousepos, Vector2f offset)
{
	//Update Time
	sunSpawnTimeClock += deltaTime;
	SunFlowerClock += deltaTime;
	PeaShooterClock += deltaTime;
	SnowPeaClock += deltaTime;
	WallNutClock += deltaTime;
	SunShroomClock += deltaTime;
	PuffShroomClock += deltaTime;
	ScaredyShroomClock += deltaTime;

	//sun spawn system
	if (!isNight && sunSpawnTimeClock >= SunSpawnTime.asSeconds())
	{
		int sunValue = 25;
		Vector2f spawnposition = { (float)(0 + rand() % 780), (float)(-100 + offset.y) };
		Plants_Zombies::PlantProjectile suncoin;

		suncoin.start(Plants_Zombies::SunCoin, 0, spawnposition, (200 + rand() % 300) + offset.y, sunValue);
		Plants_Zombies::PlantProjectilesARR.push_back(suncoin);
		sunSpawnTimeClock = 0;
	}

	//score text updater
	moneytext.setString(to_string(Plants_Zombies::score));
	moneytext.setOrigin(moneytext.getGlobalBounds().width / 2, moneytext.getGlobalBounds().height / 2);
	moneytext.setPosition(170 + 53 + offset.x, 145 + offset.y);

	float randPitch[3] = { 0.85, 1, 1.15 };

	//plant select UI logic
	if (isNight)
	{
		if (SunShroomClock > ShortCoolDown.asSeconds() && Plants_Zombies::score >= 25)
		{
			sunshroomSeedPacket.setTexture(sunshroomAvailableTex);

			if (sunshroomSeedPacket.getGlobalBounds().contains(mousepos) && Mouse::isButtonPressed(Mouse::Left))
			{
				if (!PlaySelectionSound)
				{
					PlaySelectionSound = true;
					PlaySoundEffect(SelectingPlant, true);
				}
				isHolding = true;
				curruntselection = sunshroom;
			}
		}
		else
		{
			sunshroomSeedPacket.setTexture(sunshroomUnavailableTex);
		}

		if (PuffShroomClock > ShortCoolDown.asSeconds())
		{
			puffshroomSeedPacket.setTexture(puffshroomAvailableTex);

			if (puffshroomSeedPacket.getGlobalBounds().contains(mousepos) && Mouse::isButtonPressed(Mouse::Left))
			{
				if (!PlaySelectionSound)
				{
					PlaySelectionSound = true;
					PlaySoundEffect(SelectingPlant, true);
				}
				isHolding = true;
				curruntselection = puffshroom;
			}
		}
		else
		{
			puffshroomSeedPacket.setTexture(puffshroomUnavailableTex);
		}

		if (ScaredyShroomClock > ShortCoolDown.asSeconds() && Plants_Zombies::score >= 25)
		{
			scaredyshroomSeedPacket.setTexture(scaredyshroomAvailableTex);

			if (scaredyshroomSeedPacket.getGlobalBounds().contains(mousepos) && Mouse::isButtonPressed(Mouse::Left))
			{
				if (!PlaySelectionSound)
				{
					PlaySelectionSound = true;
					PlaySoundEffect(SelectingPlant, true);
				}
				isHolding = true;
				curruntselection = scaredyshroom;
			}
		}
		else
		{
			scaredyshroomSeedPacket.setTexture(scaredyshroomUnavailableTex);
		}

		if (PeaShooterClock > ShortCoolDown.asSeconds() && Plants_Zombies::score >= 100)
		{
			peashooterSeedPacket.setTexture(peashooterAvailableTex);

			if (peashooterSeedPacket.getGlobalBounds().contains(mousepos) && Mouse::isButtonPressed(Mouse::Left))
			{
				if (!PlaySelectionSound)
				{
					PlaySelectionSound = true;
					PlaySoundEffect(SelectingPlant, true);
				}
				isHolding = true;
				curruntselection = peashooter;
			}
		}
		else
		{
			peashooterSeedPacket.setTexture(peashooterUnavailableTex);
		}

		if (SnowPeaClock > ShortCoolDown.asSeconds() && Plants_Zombies::score >= 175)
		{
			snowpeashooterSeedPacket.setTexture(snowpeaAvailableTex);

			if (snowpeashooterSeedPacket.getGlobalBounds().contains(mousepos) && Mouse::isButtonPressed(Mouse::Left))
			{
				if (!PlaySelectionSound)
				{
					PlaySelectionSound = true;
					PlaySoundEffect(SelectingPlant, true);
				}
				isHolding = true;
				curruntselection = snowpeashooter;
			}
		}
		else
		{
			snowpeashooterSeedPacket.setTexture(snowpeaUnavailableTex);
		}

		if (WallNutClock > MediumCoolDown.asSeconds() && Plants_Zombies::score >= 50)
		{
			wallnutSeedPacket.setTexture(wallnutAvailableTex);

			if (wallnutSeedPacket.getGlobalBounds().contains(mousepos) && Mouse::isButtonPressed(Mouse::Left))
			{
				if (!PlaySelectionSound)
				{
					PlaySelectionSound = true;
					PlaySoundEffect(SelectingPlant, true);
				}
				isHolding = true;
				curruntselection = wallnut;
			}
		}
		else
		{
			wallnutSeedPacket.setTexture(wallnutUnavailableTex);
		}
	}
	else
	{
		if (SunFlowerClock > ShortCoolDown.asSeconds() && Plants_Zombies::score >= 50)
		{
			sunflowerSeedPacket.setTexture(sunflowerAvailableTex);

			if (sunflowerSeedPacket.getGlobalBounds().contains(mousepos) && Mouse::isButtonPressed(Mouse::Left))
			{
				if (!PlaySelectionSound)
				{
					PlaySelectionSound = true;
					PlaySoundEffect(SelectingPlant, true);
				}
				isHolding = true;
				curruntselection = sunflower;
			}
		}
		else
		{
			sunflowerSeedPacket.setTexture(sunflowerUnavailableTex);
		}

		if (PeaShooterClock > ShortCoolDown.asSeconds() && Plants_Zombies::score >= 100)
		{
			peashooterSeedPacket.setTexture(peashooterAvailableTex);

			if (peashooterSeedPacket.getGlobalBounds().contains(mousepos) && Mouse::isButtonPressed(Mouse::Left))
			{
				if (!PlaySelectionSound)
				{
					PlaySelectionSound = true;
					PlaySoundEffect(SelectingPlant, true);
				}
				isHolding = true;
				curruntselection = peashooter;
			}
		}
		else
		{
			peashooterSeedPacket.setTexture(peashooterUnavailableTex);
		}

		if (SnowPeaClock > ShortCoolDown.asSeconds() && Plants_Zombies::score >= 175)
		{
			snowpeashooterSeedPacket.setTexture(snowpeaAvailableTex);

			if (snowpeashooterSeedPacket.getGlobalBounds().contains(mousepos) && Mouse::isButtonPressed(Mouse::Left))
			{
				if (!PlaySelectionSound)
				{
					PlaySelectionSound = true;
					PlaySoundEffect(SelectingPlant, true);
				}
				isHolding = true;
				curruntselection = snowpeashooter;
			}
		}
		else
		{
			snowpeashooterSeedPacket.setTexture(snowpeaUnavailableTex);
		}

		if (WallNutClock > MediumCoolDown.asSeconds() && Plants_Zombies::score >= 50)
		{
			wallnutSeedPacket.setTexture(wallnutAvailableTex);

			if (wallnutSeedPacket.getGlobalBounds().contains(mousepos) && Mouse::isButtonPressed(Mouse::Left))
			{
				if (!PlaySelectionSound)
				{
					PlaySelectionSound = true;
					PlaySoundEffect(SelectingPlant, true);
				}
				isHolding = true;
				curruntselection = wallnut;
			}
		}
		else
		{
			wallnutSeedPacket.setTexture(wallnutUnavailableTex);
		}
	}

	if (shovelcontainer.getGlobalBounds().contains(mousepos) && Mouse::isButtonPressed(Mouse::Left))
	{
		if (!PlaySelectionSound)
		{
			PlaySelectionSound = true;
			PlaySoundEffect(ShovelSoundBuffer, true);
		}
		isHolding = true;
		curruntselection = shovel;
	}

	//deselects
	if (Mouse::isButtonPressed(Mouse::Right)) {
		isHolding = false;
	}

	//selection hologram logic
	if (isHolding)
	{
		if (curruntselection == shovel)
		{
			shovelcontainer.setTexture(ShovelContainerEmpty);
			SelectionHolograph.setTextureRect(IntRect(0, 0, 100, 100));
			SelectionHolograph.setTexture(shoveltex);
			SelectionHolograph.setScale(1, 1);
			SelectionHolograph.setOrigin({ SelectionHolograph.getLocalBounds().width / 2,SelectionHolograph.getLocalBounds().height / 2 });
			SelectionHolograph.setColor(Color(255, 255, 255, 255));
		}
		else if (curruntselection == sunflower)
		{
			SelectionHolograph.setTextureRect(IntRect(0, 0, 32, 34));
			SelectionHolograph.setTexture(Plants_Zombies::SunFlowerIdleTex);
			SelectionHolograph.setScale(3.5, 3.5);
			SelectionHolograph.setOrigin({ SelectionHolograph.getLocalBounds().width / 2,SelectionHolograph.getLocalBounds().height / 2 });
			SelectionHolograph.setColor(Color(255, 255, 255, 175));
		}
		else if (curruntselection == peashooter)
		{
			SelectionHolograph.setTextureRect(IntRect(0, 0, 30, 34));
			SelectionHolograph.setTexture(Plants_Zombies::PeaShooterIdleTex);
			SelectionHolograph.setScale(3.5, 3.5);
			SelectionHolograph.setOrigin({ SelectionHolograph.getLocalBounds().width / 2,SelectionHolograph.getLocalBounds().height / 2 });
			SelectionHolograph.setColor(Color(255, 255, 255, 175));
		}
		else if (curruntselection == snowpeashooter)
		{
			SelectionHolograph.setTextureRect(IntRect(0, 0, 32, 34));
			SelectionHolograph.setTexture(Plants_Zombies::IcePeaShooterIdleTex);
			SelectionHolograph.setScale(3.5, 3.5);
			SelectionHolograph.setOrigin({ SelectionHolograph.getLocalBounds().width / 2,SelectionHolograph.getLocalBounds().height / 2 });
			SelectionHolograph.setColor(Color(255, 255, 255, 175));
		}
		else if (curruntselection == wallnut)
		{
			SelectionHolograph.setTextureRect(IntRect(0, 0, 28, 31));
			SelectionHolograph.setTexture(Plants_Zombies::WallNutIdleTex);
			SelectionHolograph.setScale(3.5, 3.5);
			SelectionHolograph.setOrigin({ SelectionHolograph.getLocalBounds().width / 2,SelectionHolograph.getLocalBounds().height / 2 });
			SelectionHolograph.setColor(Color(255, 255, 255, 175));
		}
		else if (curruntselection == sunshroom)
		{
			SelectionHolograph.setTextureRect(IntRect(0, 0, 28, 31));
			SelectionHolograph.setTexture(Plants_Zombies::SunShroomIdleTex);
			SelectionHolograph.setScale(3.5, 3.5);
			SelectionHolograph.setOrigin({ SelectionHolograph.getLocalBounds().width / 2,SelectionHolograph.getLocalBounds().height / 2 });
			SelectionHolograph.setColor(Color(255, 255, 255, 175));
		}
		else if (curruntselection == puffshroom)
		{
			SelectionHolograph.setTextureRect(IntRect(0, 0, 28, 31));
			SelectionHolograph.setTexture(Plants_Zombies::PuffShroomTex);
			SelectionHolograph.setScale(3.5, 3.5);
			SelectionHolograph.setOrigin({ SelectionHolograph.getLocalBounds().width / 2,SelectionHolograph.getLocalBounds().height / 2 });
			SelectionHolograph.setColor(Color(255, 255, 255, 175));
		}
		else if (curruntselection == scaredyshroom)
		{
			SelectionHolograph.setTextureRect(IntRect(0, 0, 28, 31));
			SelectionHolograph.setTexture(Plants_Zombies::ScaredyShroomIdleTex);
			SelectionHolograph.setScale(3.5, 3.5);
			SelectionHolograph.setOrigin({ SelectionHolograph.getLocalBounds().width / 2,SelectionHolograph.getLocalBounds().height / 2 });
			SelectionHolograph.setColor(Color(255, 255, 255, 175));
		}

		if (curruntselection != shovel)
		{
			shovelcontainer.setTexture(ShovelContainerAvailable);
		}

		SelectionHolograph.setPosition(mousepos);
	}
	else
	{
		shovelcontainer.setTexture(ShovelContainerAvailable);
		PlaySelectionSound = false;
		curruntselection = none;
	}

	//planting system
	if (curruntselection != none && isHolding)
	{
		for (int i = 1; i <= 45; i++)
		{
			if (mygrid[i].shape.getGlobalBounds().contains(mousepos) && Mouse::isButtonPressed(Mouse::Left))
			{
				if (curruntselection == shovel)
				{
					if (mygrid[i].isplanted && !mygrid[i].gravePlanted)
					{
						PlaySoundEffect(PlantingSoundBuffer, true);
						//cout << "shovel " << i << endl;
						mygrid[i].isplanted = false;
						Plants_Zombies::PlantsArray[i - 1].type = Plants_Zombies::EmptyPlant;
						Plants_Zombies::PlantsArray[i - 1].start();

						isHolding = false;
					}
				}
				else if (curruntselection == peashooter)
				{
					if (!mygrid[i].isplanted)
					{
						PlaySoundEffect(PlantingSoundBuffer, true);
						//cout << "peashooter " << i << endl;

						Plants_Zombies::PlantsArray[i - 1].type = Plants_Zombies::PeaShooter;
						Plants_Zombies::PlantsArray[i - 1].start();
						mygrid[i].isplanted = true;

						Plants_Zombies::score -= 100;
						PeaShooterClock = 0;

						isHolding = false;
						curruntselection = none;
					}
				}
				else if (curruntselection == snowpeashooter)
				{
					if (!mygrid[i].isplanted)
					{
						PlaySoundEffect(PlantingSoundBuffer, true);
						//cout << "SnowPeaShooter " << i << endl;

						Plants_Zombies::PlantsArray[i - 1].type = Plants_Zombies::SnowPeaShooter;
						Plants_Zombies::PlantsArray[i - 1].start();
						mygrid[i].isplanted = true;

						Plants_Zombies::score -= 175;
						SnowPeaClock = 0;

						isHolding = false;
						curruntselection = none;
					}
				}
				else if (curruntselection == sunflower)
				{
					if (!mygrid[i].isplanted)
					{
						PlaySoundEffect(PlantingSoundBuffer, true);
						//cout << "SunFlower " << i << endl;

						Plants_Zombies::PlantsArray[i - 1].type = Plants_Zombies::SunFlower;
						Plants_Zombies::PlantsArray[i - 1].start();
						mygrid[i].isplanted = true;

						Plants_Zombies::score -= 50;
						SunFlowerClock = 0;

						isHolding = false;
						curruntselection = none;
					}
				}
				else if (curruntselection == wallnut)
				{
					if (!mygrid[i].isplanted)
					{
						PlaySoundEffect(PlantingSoundBuffer, true);
						//cout << "WallNut " << i << endl;

						Plants_Zombies::PlantsArray[i - 1].type = Plants_Zombies::WallNut;
						Plants_Zombies::PlantsArray[i - 1].start();
						mygrid[i].isplanted = true;

						Plants_Zombies::score -= 50;
						WallNutClock = 0;

						isHolding = false;
						curruntselection = none;
					}
				}
				else if (curruntselection == sunshroom)
				{
					if (!mygrid[i].isplanted)
					{
						PlaySoundEffect(PlantingSoundBuffer, true);
						//cout << "SunShroom " << i << endl;

						Plants_Zombies::PlantsArray[i - 1].type = Plants_Zombies::SunShroom;
						Plants_Zombies::PlantsArray[i - 1].start();
						mygrid[i].isplanted = true;

						Plants_Zombies::score -= 25;
						SunShroomClock = 0;

						isHolding = false;
						curruntselection = none;
					}
				}
				else if (curruntselection == puffshroom)
				{
					if (!mygrid[i].isplanted)
					{
						PlaySoundEffect(PlantingSoundBuffer, true);
						//cout << "PuffShroom " << i << endl;

						Plants_Zombies::PlantsArray[i - 1].type = Plants_Zombies::PuffShroom;
						Plants_Zombies::PlantsArray[i - 1].start();
						mygrid[i].isplanted = true;

						Plants_Zombies::score -= 0;
						PuffShroomClock = 0;

						isHolding = false;
						curruntselection = none;
					}
				}
				else if (curruntselection == scaredyshroom)
				{
					if (!mygrid[i].isplanted)
					{
						PlaySoundEffect(PlantingSoundBuffer, true);
						//cout << "ScaredyShroom " << i << endl;

						Plants_Zombies::PlantsArray[i - 1].type = Plants_Zombies::ScaredyShroom;
						Plants_Zombies::PlantsArray[i - 1].start();
						mygrid[i].isplanted = true;

						Plants_Zombies::score -= 25;
						ScaredyShroomClock = 0;

						isHolding = false;
						curruntselection = none;
					}
				}
			}
		}
	}
}

void DrawPlantingAndCurrencySystem(RenderWindow& window)
{
	//for (int i = 1; i <= 45; i++) {
	//	window.draw(mygrid[i].shape);
	//}

	window.draw(gradientopacity);
	
	if (isNight)
	{
		window.draw(scaredyshroomSeedPacket);
		window.draw(sunshroomSeedPacket);
		window.draw(puffshroomSeedPacket);
		window.draw(peashooterSeedPacket);
		window.draw(snowpeashooterSeedPacket);
		window.draw(wallnutSeedPacket);

		for (int i = 0; i < 4; i++) 
		{
			window.draw(graves[i]);
		}
	}
	else
	{
		window.draw(sunflowerSeedPacket);
		window.draw(peashooterSeedPacket);
		window.draw(snowpeashooterSeedPacket);
		window.draw(wallnutSeedPacket);
		window.draw(emptySeedPacket1);
		window.draw(emptySeedPacket2);
	}

	window.draw(sunContainer);
	window.draw(moneytext);
	window.draw(shovelcontainer);

	if (isHolding)
	{
		window.draw(SelectionHolograph);
	}
}

void Plants_Zombies::Plants::updatePlantStruct(Zombie zombie_array[]) {
	int lastZombieProximity = 0;
	if (!isDead) // if not dead will animate and execute action  
	{
		actionTimeClock += deltaTime;
		plantLifeTimeClock += deltaTime;

		for (int j = 0; j < 100; j++)
		{
			if (!(zombie_array[j].isDead || zombie_array[j].type == Dead || !zombie_array[j].started)) // checks if zombie is dead or not to avoid shooting dead zombies
			{
				// checks if a zombie is in front of the plant  
				if ((type == PeaShooter || type == SnowPeaShooter || type == ScaredyShroom)
					&& ((shape.getGlobalBounds().top + shape.getGlobalBounds().height / 2) <= (zombie_array[j].zombieCont.getGlobalBounds().top + zombie_array[j].zombieCont.getGlobalBounds().height)
						&& ((shape.getGlobalBounds().top + shape.getGlobalBounds().height / 2) >= zombie_array[j].zombieCont.getGlobalBounds().top)
						&& (shape.getGlobalBounds().left <= zombie_array[j].zombieCont.getGlobalBounds().left))
					&& (zombie_array[j].zombieCollider.getPosition().x < 960))
				{
					zombieInFront = true;
					break;
				}
				else if ((type == PuffShroom)
					&& ((shape.getGlobalBounds().top + shape.getGlobalBounds().height / 2) <= (zombie_array[j].zombieCont.getGlobalBounds().top + zombie_array[j].zombieCont.getGlobalBounds().height)
						&& ((shape.getGlobalBounds().top + shape.getGlobalBounds().height / 2) >= zombie_array[j].zombieCont.getGlobalBounds().top)
						&& (shape.getGlobalBounds().left <= zombie_array[j].zombieCont.getGlobalBounds().left))
					&& (zombie_array[j].zombieCollider.getPosition().x < shape.getPosition().x + (107 * 4))
					&& (zombie_array[j].zombieCollider.getPosition().x < 960))
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

		if (type == ScaredyShroom)
		{
			for (int j = 0; j < 100; j++)
			{
				if (!(zombie_array[j].isDead || zombie_array[j].type == Dead || !zombie_array[j].started)) // checks if zombie is dead or not to avoid shooting dead zombies
				{
					if (((shape.getGlobalBounds().top + shape.getGlobalBounds().height / 2) <= (zombie_array[j].zombieCont.getGlobalBounds().top + zombie_array[j].zombieCont.getGlobalBounds().height)
						&& ((shape.getGlobalBounds().top + shape.getGlobalBounds().height / 2) >= zombie_array[j].zombieCont.getGlobalBounds().top))
						&& (zombie_array[j].zombieCollider.getPosition().x < shape.getPosition().x + (107 * 4.5)))
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

		animationHandler();
		action();

		plantCollider.setPosition(shape.getPosition());
	}
	else if(!mygrid[gridIndex].gravePlanted)// else if there is not a grave planted there will turn the plant into an empty gameobject  
	{
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