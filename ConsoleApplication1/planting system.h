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

const int numGraves = 4;

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
Texture plantingpotAvailableTex;
Texture plantingpotUnavailableTex;
Texture potatomineAvaliableTex;
Texture potatomineUnavaliableTex;
Texture JalapenoAvaliableTex;
Texture JalapenoUnavaliableTex;
Texture iceshroomAvaliableTex;
Texture iceshroomUnavaliableTex;
///=============================
Texture emptySeedPacketTex;
Texture shoveltex;
Texture ShovelContainerAvailable;
Texture ShovelContainerEmpty;
Texture gradientopacitytex;
Texture sunContainerTex;
///=============================
Texture plantSelectionBlankTex;
Texture LetsRockTex;
Texture LetsRockHoverTex;
///=============================
Texture Textgraves;
#pragma endregion

#pragma region sprite declaration
Sprite shovelcontainer;
Sprite sunContainer;
Sprite gradientopacity;
Sprite SelectionHolograph;
//==================================
Sprite plantSelectionBlank;
Sprite LetsRockButton;
//===================================
Sprite graves[numGraves];
#pragma endregion

#pragma region clocks and time
float sunSpawnTimeClock = 0;
Time SunSpawnTime = seconds(14);

Time LongCoolDown = seconds(50);
Time MediumCoolDown = seconds(30);
Time ShortCoolDown = seconds(7);
Clock PlantSelectionAnimationClock;
#pragma endregion

#pragma region Sounds
SoundBuffer PlantingSoundBuffer;
SoundBuffer SelectingPlant;
SoundBuffer ShovelSoundBuffer;

SoundBuffer HoverButtonBuffer;
SoundBuffer ClickButtonBuffer;
#pragma endregion

Plants_Zombies::PlantType currentselection;

#pragma region struct declaration
struct grid;
struct PlantSelection;
struct SelectedSeedPacket;
#pragma endregion

#pragma region animation stuff
Vector2f animationCenter = { 0, 0 };
int opacityAnimation = 0;

Vector2f letsrockstartPos;
Vector2f shovelstartPos;
Vector2f sunContainerStartPos;
Vector2f moneytextStartPos;
Vector2f selectedPlantsStartPos[6];
Vector2f plantsToSelectStartPos[4][3];
#pragma endregion

#pragma region booleans
bool isNight;
bool onRoof;

bool isbossFight;

bool isHolding = false;
bool plantselectionMenu = true;
bool animatePlantSelection = false;
bool resetClocksAtStart = true;

bool PlaySelectionSound = false;
bool playHoverSound = false;
//from start animation
bool moveright = false;
bool moveleft = false;
#pragma endregion

int currentSelectionIndex = -1;

Font font;
Text moneytext;

#pragma region structs
struct grid {
	RectangleShape shape;
	bool isplanted = false;
	bool gravePlanted = false;
}mygrid[46];

struct SelectedSeedPacket {
	Plants_Zombies::PlantType type;
	Sprite shape;

	Texture AvailableTexture;
	Texture UnavailableTexture;

	//bool isAvailable = false;
	bool isAdded = false;
	int index;
	int price;

	float seedPacketClock;
	Time CoolDown;

	Vector2f offset;

	void SetSeedPacket(Plants_Zombies::PlantType type_, Texture& AvailavbleTex, Texture& UnAvailableTex, Vector2f offset_, Time coolDown_, int price_, int i)
	{
		index = i;
		type = type_;
		AvailableTexture = AvailavbleTex;
		UnavailableTexture = UnAvailableTex;
		price = price_;
		CoolDown = coolDown_;
		offset = offset_;

		shape.setTextureRect(IntRect(0, 0, AvailableTexture.getSize().x, AvailableTexture.getSize().y));
		shape.setTexture(AvailavbleTex);

		shape.setPosition(shape.getPosition().x + offset.x, shape.getPosition().y + offset.y);
		isAdded = true;
	}

	void update(Vector2f mousepos, PlantSelection arr[4][3]);

	void resetSeedPacket()
	{
		//isAvailable = false;
		seedPacketClock = 0;
		shape.setTexture(UnavailableTexture);
		isHolding = false;
		currentselection = Plants_Zombies::EmptyPlant;
		currentSelectionIndex = -1;
	}

}selectedPlantsArr[6];

struct PlantSelection {
	Plants_Zombies::PlantType type;
	Sprite shape;

	Texture AvailableTexture;
	Texture UnavailableTexture;

	Vector2f SeedPacketOffset;

	bool isAvailable = false;
	bool isAvailableAtNight = false;
	bool isAvailableAtDay = false;
	bool isAvailableAtRoof = false;
	Time CoolDown;

	int price;

	void start(Plants_Zombies::PlantType type_, Texture& availableTex, Texture unavailableTex, Vector2f offset, Time cooldown_, int price_, bool availableAtDay, bool availableAtNight, bool availableOnRoof) {
		type = type_;
		AvailableTexture = availableTex;
		UnavailableTexture = unavailableTex;
		price = price_;
		CoolDown = cooldown_;

		isAvailable = true;
		isAvailableAtNight = availableAtNight;
		isAvailableAtDay = availableAtDay;
		isAvailableAtRoof = availableOnRoof;

		shape.setPosition(shape.getPosition().x + offset.x, shape.getPosition().y + offset.y);
		SeedPacketOffset = offset;
	}

	void update(Vector2f mousepos)
	{
		if (type != Plants_Zombies::Shovel && type != Plants_Zombies::EmptyPlant)
		{
			// check if available at day/night and determine availability
			if (isNight)
			{
				if (onRoof)
				{
					if (!isAvailableAtRoof || !isAvailableAtNight)
					{
						isAvailable = false;
					}
				}
				else
				{
					if (!isAvailableAtNight)
					{
						isAvailable = false;
					}
				}
			}
			else
			{
				if (onRoof)
				{
					if (!isAvailableAtRoof || !isAvailableAtDay)
					{
						isAvailable = false;
					}
				}
				else
				{
					if (!isAvailableAtDay)
					{
						isAvailable = false;
					}
				}
			}

			if (!onRoof && type == Plants_Zombies::PlantingPot)
			{
				isAvailable = false;
			}

			if (isAvailable)
			{
				shape.setTexture(AvailableTexture);
			}
			else
			{
				shape.setTexture(UnavailableTexture);
			}

			if (shape.getGlobalBounds().contains(mousepos) && Mouse::isButtonPressed(Mouse::Left) && isAvailable && animationCenter.x == 500)
			{
				for (int i = 0; i < 6; i++)
				{
					if (!selectedPlantsArr[i].isAdded)
					{
						//add plant
						cout << "Add plant again" << endl;
						PlaySoundEffect(SelectingPlant, true);
						selectedPlantsArr[i].SetSeedPacket(type, AvailableTexture, UnavailableTexture, SeedPacketOffset, CoolDown, price, i);
						isAvailable = false;
						break;
					}
					else
					{
						continue;
					}
				}
			}

		}
		else
		{
			shape.setTexture(emptySeedPacketTex);
			isAvailable = false;
		}
	}
}plantsToSelect[4][3];

void SelectedSeedPacket::update(Vector2f mousepos, PlantSelection arr[4][3])
{
	seedPacketClock += deltaTime;

	if (plantselectionMenu)
	{
		if (!(type == Plants_Zombies::EmptyPlant || type == Plants_Zombies::Shovel))
		{
			if (shape.getGlobalBounds().contains(mousepos) && Mouse::isButtonPressed(Mouse::Left))
			{
				isAdded = false;
				shape.setPosition(shape.getPosition().x - offset.x, shape.getPosition().y - offset.y);
				shape.setTextureRect(IntRect(0, 0, emptySeedPacketTex.getSize().x, emptySeedPacketTex.getSize().y));
				shape.setTexture(emptySeedPacketTex);

				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						if (arr[i][j].type == type)
						{
							arr[i][j].isAvailable = true;
							break;
						}
					}
				}

				PlaySoundEffect(SelectingPlant, true);
				type = Plants_Zombies::EmptyPlant; // reset the type to empty plant
			}
			else
			{
				isAdded = true;
				shape.setTextureRect(IntRect(0, 0, AvailableTexture.getSize().x, AvailableTexture.getSize().y));
				shape.setTexture(AvailableTexture);
			}
		}
		else
		{
			isAdded = false;
			shape.setTextureRect(IntRect(0, 0, emptySeedPacketTex.getSize().x, emptySeedPacketTex.getSize().y));
			shape.setTexture(emptySeedPacketTex);
		}
	}
	else
	{
		if (!(type == Plants_Zombies::EmptyPlant || type == Plants_Zombies::Shovel))
		{
			if ((seedPacketClock >= CoolDown.asSeconds() && Plants_Zombies::score >= price) || isbossFight)
			{
				shape.setTexture(AvailableTexture);

				if (shape.getGlobalBounds().contains(mousepos) && Mouse::isButtonPressed(Mouse::Left))
				{
					currentselection = type;
					currentSelectionIndex = index;
					isHolding = true;

					if (!PlaySelectionSound)
					{
						PlaySelectionSound = true;
						PlaySoundEffect(SelectingPlant, true);
					}
				}
			}
			else
			{
				shape.setTexture(UnavailableTexture);
			}
		}
		else
		{
			isAdded = false;
			shape.setTextureRect(IntRect(0, 0, emptySeedPacketTex.getSize().x, emptySeedPacketTex.getSize().y));
			shape.setTexture(emptySeedPacketTex);
		}
	}
}
#pragma endregion

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
	plantingpotAvailableTex.loadFromFile("Assets/Currency System and planting/New/planting-pot-available.png");	
	plantingpotUnavailableTex.loadFromFile("Assets/Currency System and planting/New/planting-pot-unavailable.png");
	potatomineAvaliableTex.loadFromFile("Assets/Currency System and planting/New/potatomine-available.png");
	potatomineUnavaliableTex.loadFromFile("Assets/Currency System and planting/New/potatomine-unavailable.png");
	JalapenoAvaliableTex.loadFromFile("Assets/Currency System and planting/New/jalapeno-avaliable.png");
	JalapenoUnavaliableTex.loadFromFile("Assets/Currency System and planting/New/jalapeno-unavaliable.png");
	iceshroomAvaliableTex.loadFromFile("Assets/Currency System and planting/New/ice shroom-avalialbe.png");
	iceshroomUnavaliableTex.loadFromFile("Assets/Currency System and planting/New/ice shroom-unavalialbe.png");
	//=============================
	plantSelectionBlankTex.loadFromFile("Assets/Currency System and Planting/New/plantselection-blank.png");
	LetsRockHoverTex.loadFromFile("Assets/Currency System and Planting/New/lets-rock-hover.png");
	LetsRockTex.loadFromFile("Assets/Currency System and Planting/New/lets-rock.png");
	//==============================
	Textgraves.loadFromFile("Assets/Environment/Graves-ST.png");
	//==============================
	HoverButtonBuffer.loadFromFile("Audio/bleep.ogg");
	ClickButtonBuffer.loadFromFile("Audio/buttonclick.ogg");
}

void SetupSelectionUI(Vector2f offset)
{
#pragma region plant selection
	plantSelectionBlank.setTexture(plantSelectionBlankTex);
	plantSelectionBlank.setPosition(0 + offset.x, 0 + offset.y);

	//setup the empty selections packets
	for (int i = 0; i < 6; i++)
	{
		selectedPlantsArr[i].type = Plants_Zombies::EmptyPlant;
		selectedPlantsArr[i].shape.setPosition(29 + offset.x, 25 + (i * (100 + 14)) + offset.y);
	}

	//for the seed bank
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			plantsToSelect[i][j].type = Plants_Zombies::EmptyPlant;
			plantsToSelect[i][j].shape.setPosition(318 + offset.x + (j * (120 + 21)), 117 + offset.y + (i * (100 + 19)));
		}
	}

	//setup plants on selection screen
	plantsToSelect[0][0].start(Plants_Zombies::SunFlower, sunflowerAvailableTex, sunflowerUnavailableTex, Vector2f{ -5, -20 }, ShortCoolDown, 50, true, false,true);
	plantsToSelect[0][1].start(Plants_Zombies::PeaShooter, peashooterAvailableTex, peashooterUnavailableTex, Vector2f{ 0, -10 }, ShortCoolDown, 100, true, true, true);
	plantsToSelect[0][2].start(Plants_Zombies::SnowPeaShooter, snowpeaAvailableTex, snowpeaUnavailableTex, Vector2f{ 0, -5 }, ShortCoolDown, 175, true, true, true);

	plantsToSelect[1][0].start(Plants_Zombies::WallNut, wallnutAvailableTex, wallnutUnavailableTex, Vector2f{ 0, -15 }, MediumCoolDown, 50, true, true, true);
	plantsToSelect[1][1].start(Plants_Zombies::SunShroom, sunshroomAvailableTex, sunshroomUnavailableTex, Vector2f{ 0, -10 }, ShortCoolDown, 25, false, true, true);
	plantsToSelect[1][2].start(Plants_Zombies::ScaredyShroom, scaredyshroomAvailableTex, scaredyshroomUnavailableTex, Vector2f{ 0, -20 }, ShortCoolDown, 25, false, true, true);

	plantsToSelect[2][0].start(Plants_Zombies::PuffShroom, puffshroomAvailableTex, puffshroomUnavailableTex, Vector2f{ 0, -10 }, ShortCoolDown, 0, false, true, true);
	plantsToSelect[2][1].start(Plants_Zombies::PlantingPot, plantingpotAvailableTex, plantingpotUnavailableTex, Vector2f{ 0, -25 }, ShortCoolDown, 25, true, true, true);
	plantsToSelect[2][2].start(Plants_Zombies::PotatoMine, potatomineAvaliableTex, potatomineUnavaliableTex, Vector2f{ 0, -15 }, ShortCoolDown, 25, true, true,true);
	plantsToSelect[3][0].start(Plants_Zombies::Jalapeno, JalapenoAvaliableTex, JalapenoUnavaliableTex, Vector2f{ 0, -10 }, ShortCoolDown, 125, true, true, true);
	plantsToSelect[3][1].start(Plants_Zombies::IceShroom, iceshroomAvaliableTex, iceshroomUnavaliableTex, Vector2f{ 0, -20 }, ShortCoolDown, 75, true, true, true);
	
	//start game button
	LetsRockButton.setTexture(LetsRockTex);
	LetsRockButton.setPosition(796 + offset.x, 613 + offset.y);
#pragma endregion

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

#pragma region for animation
	letsrockstartPos = LetsRockButton.getPosition();
	shovelstartPos = shovelcontainer.getPosition();
	sunContainerStartPos = sunContainer.getPosition();

	for (int i = 0; i < 6; i++)
	{
		selectedPlantsStartPos[i] = selectedPlantsArr[i].shape.getPosition();
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			plantsToSelectStartPos[i][j] = plantsToSelect[i][j].shape.getPosition();
		}
	}

	moneytextStartPos = moneytext.getPosition();
#pragma endregion

}

void StartPlantingAndCurrencySystem(Vector2f offset, bool isNight_, bool onRoof_, bool isBossFight_)
{
	isNight = isNight_;
	onRoof = onRoof_;
	isbossFight = isBossFight_;

	Plants_Zombies::score = 50000;

	SetupSelectionUI(offset);
	Plants_Zombies::PlantProjectilesARR.clear();

	sunSpawnTimeClock = 0;

	currentselection = Plants_Zombies::EmptyPlant;
	currentSelectionIndex = -1;

	opacityAnimation = 0;
	animationCenter = { 0, 0 };

	isHolding = false;
	plantselectionMenu = true;
	animatePlantSelection = false;
	resetClocksAtStart = true;

	PlaySelectionSound = false;
	playHoverSound = false;
	//from start animation
	moveright = false;
	moveleft = false;

	//setup the grid
	int indexes[30] = {4, 5 ,6 ,7 ,8, 9
		, 13, 14 ,15 ,16, 17, 18
		, 22, 23, 24, 25, 26, 27
		, 31, 32, 33, 34 ,35, 36
		, 40, 41, 42 ,43, 44 ,45};
	int potIndexes[15] = { 1, 2, 3,
						10, 11, 12,
						19, 20, 21,
						28, 29, 30,
						37, 38, 39 };
	for (int i = 1, r = 0, c = 0; i <= 45; i++) 
	{
		if (onRoof)
		{
			bool smaller = false;
			for (int j = 0; j < 30; j++)
			{
				if (i == indexes[j]) {
					smaller = true;
					break;
				}
			}

			if (smaller) {
				mygrid[i].shape.setSize({ 100,110 });
				mygrid[i].shape.setPosition(45 + 100 * c, 110 * r);
			}
			else
			{
				mygrid[i].shape.setSize({ 115,110 });
				mygrid[i].shape.setPosition(115 * c, 110 * r);
			}
		}
		else
		{
			mygrid[i].shape.setSize({ 107,130 });
			mygrid[i].shape.setPosition(107 * c, 130 * r);
		}
		
		c++;
		if (i % 9 == 0)
		{
			c = 0;
			r++;
		}

		//colours the grid
		if (i % 2 == 0) {
			mygrid[i].shape.setFillColor(Color(255, 255, 0, 64));
		}
		else {
			mygrid[i].shape.setFillColor(Color(255, 255, 0, 48));
		}

		Plants_Zombies::PlantingPotArray[i - 1].shape.setPosition(mygrid[i].shape.getPosition() + Vector2f{ 17, 25 });
		Plants_Zombies::PlantingPotArray[i - 1].type = Plants_Zombies::EmptyPlant;
		Plants_Zombies::PlantingPotArray[i - 1].gridIndex = i;
		Plants_Zombies::PlantingPotArray[i - 1].start();
		Plants_Zombies::PlantingPotArray[i - 1].deadPlantingPot = true;

		if (onRoof)
		{
			for (int j = 0; j < 15; j++)
			{
				if (i == potIndexes[j])
				{
					Plants_Zombies::PlantingPotArray[i - 1].shape.setPosition(mygrid[i].shape.getPosition() + Vector2f{ 17, 25 });
					Plants_Zombies::PlantingPotArray[i - 1].type = Plants_Zombies::PlantingPot;
					Plants_Zombies::PlantingPotArray[i - 1].gridIndex = i;
					Plants_Zombies::PlantingPotArray[i - 1].start();
					Plants_Zombies::PlantingPotArray[i - 1].deadPlantingPot = false;
				}
			}

			Plants_Zombies::PlantsArray[i - 1].shape.setPosition(mygrid[i].shape.getPosition() + Vector2f{ 0, -15 });
		}
		else
		{
			Plants_Zombies::PlantsArray[i - 1].shape.setPosition(mygrid[i].shape.getPosition());
		}
		
		//sets up the plants and sets them all to empty gameobjects
		Plants_Zombies::PlantsArray[i - 1].type = Plants_Zombies::EmptyPlant;
		Plants_Zombies::PlantsArray[i - 1].gridIndex = i;
		Plants_Zombies::PlantsArray[i - 1].start();
		Plants_Zombies::PlantsArray[i - 1].deadPlantingPot = false;

		mygrid[i].isplanted = false;
		mygrid[i].gravePlanted = false;
	}

	// adding graves randomly when it is a night level
	if (isNight && !onRoof)
	{
		int plantgraveson[20] = { 6, 7, 8, 9, 15, 16, 17, 18, 24, 25, 26, 27, 33, 34, 35, 36, 42, 43, 44, 45 };

		for (int x = 0; x < numGraves; x++)
		{
			int randindex = plantgraveson[rand() % 20];

			while (mygrid[randindex].gravePlanted == true) // so no two graves will be on top of eachother
			{
				randindex = plantgraveson[rand() % 20];
			}

			graves[x].setTexture(Textgraves);
			graves[x].setTextureRect(IntRect((rand() % 8) * 34, 0, 34, 38));
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

	//sun spawn system
	if (!isNight && sunSpawnTimeClock >= SunSpawnTime.asSeconds() && moveleft)
	{
		int sunValue = 25;
		Vector2f spawnposition = { (float)(0 + rand() % 780), (float)(-100 + offset.y) };
		Plants_Zombies::PlantProjectile suncoin;

		suncoin.start(Plants_Zombies::SunCoin, 0, spawnposition, (200 + rand() % 300) + offset.y, sunValue);
		Plants_Zombies::PlantProjectilesARR.push_back(suncoin);
		sunSpawnTimeClock = 0;
	}

#pragma region animation
	if (!isbossFight)
	{
		//moves ui from left to right
		if (animationCenter.x < 500 && moveright && plantselectionMenu)
		{
			float start = -300, end = 500;
			Time Duration = seconds(2);
			float startOpacity = 0, endOpacity = 255;
			if (moveright && !animatePlantSelection)
			{
				PlantSelectionAnimationClock.restart();
				animatePlantSelection = true;
			}

			animationCenter = { easeInOut(ExpoEaseOut, start, end, PlantSelectionAnimationClock, Duration), 0 };
			opacityAnimation = easeInOut(ExpoEaseOut, startOpacity, endOpacity, PlantSelectionAnimationClock, seconds(2));

			gradientopacity.setPosition(offset.x + animationCenter.x, offset.y + animationCenter.y);
			plantSelectionBlank.setPosition(animationCenter.x + offset.x, animationCenter.y + offset.y);
			plantSelectionBlank.setColor(Color(255, 255, 255, opacityAnimation));
			LetsRockButton.setPosition(letsrockstartPos.x + animationCenter.x, letsrockstartPos.y + animationCenter.y);
			LetsRockButton.setColor(Color(255, 255, 255, opacityAnimation));
			shovelcontainer.setPosition(shovelstartPos.x + animationCenter.x, shovelstartPos.y + animationCenter.y);
			shovelcontainer.setColor(Color(255, 255, 255, opacityAnimation));
			sunContainer.setPosition(sunContainerStartPos.x + animationCenter.x, sunContainerStartPos.y + animationCenter.y);
			sunContainer.setColor(Color(255, 255, 255, opacityAnimation));

			for (int i = 0; i < 6; i++)
			{
				selectedPlantsArr[i].shape.setPosition(selectedPlantsStartPos[i].x + animationCenter.x, selectedPlantsStartPos[i].y + animationCenter.y);
				selectedPlantsArr[i].shape.setColor(Color(255, 255, 255, opacityAnimation));
			}

			//for the seed bank
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					plantsToSelect[i][j].shape.setPosition(plantsToSelectStartPos[i][j].x + animationCenter.x, plantsToSelectStartPos[i][j].y + animationCenter.y);
					plantsToSelect[i][j].shape.setColor(Color(255, 255, 255, opacityAnimation));
				}
			}

			moneytext.setPosition(moneytextStartPos.x + animationCenter.x, moneytextStartPos.y + animationCenter.y);
			moneytext.setFillColor(Color(255, 255, 255, opacityAnimation));
		}
		else if (animationCenter.x < 500 && !moveright && plantselectionMenu)
		{
			//start all user interfaces with opacity 0 then fades in
			plantSelectionBlank.setColor(Color(255, 255, 255, opacityAnimation));
			LetsRockButton.setColor(Color(255, 255, 255, opacityAnimation));
			shovelcontainer.setColor(Color(255, 255, 255, opacityAnimation));
			sunContainer.setColor(Color(255, 255, 255, opacityAnimation));

			for (int i = 0; i < 6; i++)
			{
				selectedPlantsArr[i].shape.setColor(Color(255, 255, 255, opacityAnimation));
			}

			//for the seed bank
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					plantsToSelect[i][j].shape.setColor(Color(255, 255, 255, opacityAnimation));
				}
			}

			moneytext.setFillColor(Color(255, 255, 255, opacityAnimation));
		}

		//moves ui from right to left
		if (animationCenter.x > 0 && !plantselectionMenu)
		{
			float start = 500, end = 0;
			Time Duration = seconds(2);
			if (animatePlantSelection)
			{
				PlantSelectionAnimationClock.restart();
				animatePlantSelection = false;
			}

			animationCenter = { easeInOut(ExpoEaseOut, start, end, PlantSelectionAnimationClock, Duration), 0 };

			gradientopacity.setPosition(offset.x + animationCenter.x, offset.y + animationCenter.y);
			plantSelectionBlank.setPosition(animationCenter.x + offset.x, animationCenter.y + offset.y);
			LetsRockButton.setPosition(letsrockstartPos.x + animationCenter.x, letsrockstartPos.y + animationCenter.y);
			shovelcontainer.setPosition(shovelstartPos.x + animationCenter.x, shovelstartPos.y + animationCenter.y);
			sunContainer.setPosition(sunContainerStartPos.x + animationCenter.x, sunContainerStartPos.y + animationCenter.y);

			for (int i = 0; i < 6; i++)
			{
				selectedPlantsArr[i].shape.setPosition(selectedPlantsStartPos[i].x + animationCenter.x, selectedPlantsStartPos[i].y + animationCenter.y);
			}

			//for the seed bank
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					plantsToSelect[i][j].shape.setPosition(plantsToSelectStartPos[i][j].x + animationCenter.x, plantsToSelectStartPos[i][j].y + animationCenter.y);
				}
			}

			moneytext.setPosition(moneytextStartPos.x + animationCenter.x, moneytextStartPos.y + animationCenter.y);

			//reset all clocks after clicking the lets rock button
			if (resetClocksAtStart)
			{
				for (int i = 0; i < 6; i++)
				{
					//cout << selectedPlantsArr[i].seedPacketClock << " - " << i << endl;
					selectedPlantsArr[i].seedPacketClock = 0;
				}
				resetClocksAtStart = false;
			}
		}
	}
#pragma endregion

	//update score text
	if (moveleft && !plantselectionMenu && !isbossFight)
	{
		moneytext.setString(to_string(Plants_Zombies::score));
		moneytext.setOrigin(moneytext.getGlobalBounds().width / 2, moneytext.getGlobalBounds().height / 2);
		moneytext.setPosition(170 + 53 + offset.x, 145 + offset.y);
	}

	if (plantselectionMenu && !isbossFight)
	{
		//update the seed packets to select
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				plantsToSelect[i][j].update(mousepos);
			}
		}

		//update selected plants
		for (int i = 0; i < 6; i++)
		{
			selectedPlantsArr[i].update(mousepos, plantsToSelect);
		}

		//lets rock button logic
		if (LetsRockButton.getGlobalBounds().contains(mousepos))
		{
			LetsRockButton.setTexture(LetsRockHoverTex);

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				plantselectionMenu = false;

				for (int i = 0; i < 6; i++)
				{
					selectedPlantsStartPos[i] = { selectedPlantsStartPos[i].x + selectedPlantsArr[i].offset.x,
												  selectedPlantsStartPos[i].y + selectedPlantsArr[i].offset.y };
				}

				PlaySoundEffect(ClickButtonBuffer, true);
			}

			if (!playHoverSound)
			{
				PlaySoundEffect(HoverButtonBuffer, true);
				playHoverSound = true;
			}
		}
		else
		{
			LetsRockButton.setTexture(LetsRockTex);
			playHoverSound = false;
		}
	}
	else
	{
		//updated selected plants
		for (int i = 0; i < 6; i++)
		{
			selectedPlantsArr[i].update(mousepos, plantsToSelect);
		}

		//select shovel
		if (shovelcontainer.getGlobalBounds().contains(mousepos) && Mouse::isButtonPressed(Mouse::Left))
		{
			if (!PlaySelectionSound)
			{
				PlaySelectionSound = true;
				PlaySoundEffect(ShovelSoundBuffer, true);
			}
			isHolding = true;
			currentselection = Plants_Zombies::Shovel;
			currentSelectionIndex = -1;
		}

		//deselects
		if (Mouse::isButtonPressed(Mouse::Right)) {
			isHolding = false;
		}

		//selection hologram logic
		if (isHolding)
		{
			if (currentselection == Plants_Zombies::Shovel)
			{
				shovelcontainer.setTexture(ShovelContainerEmpty);
				SelectionHolograph.setTextureRect(IntRect(0, 0, 100, 100));
				SelectionHolograph.setTexture(shoveltex);
				SelectionHolograph.setScale(1, 1);
				SelectionHolograph.setOrigin({ SelectionHolograph.getLocalBounds().width / 2,SelectionHolograph.getLocalBounds().height / 2 });
				SelectionHolograph.setColor(Color(255, 255, 255, 255));
			}
			else if (currentselection == Plants_Zombies::SunFlower)
			{
				SelectionHolograph.setTextureRect(IntRect(0, 0, 32, 34));
				SelectionHolograph.setTexture(Plants_Zombies::SunFlowerIdleTex);
				SelectionHolograph.setScale(3.5, 3.5);
				SelectionHolograph.setOrigin({ SelectionHolograph.getLocalBounds().width / 2,SelectionHolograph.getLocalBounds().height / 2 });
				SelectionHolograph.setColor(Color(255, 255, 255, 175));
			}
			else if (currentselection == Plants_Zombies::PeaShooter)
			{
				SelectionHolograph.setTextureRect(IntRect(0, 0, 30, 34));
				SelectionHolograph.setTexture(Plants_Zombies::PeaShooterIdleTex);
				SelectionHolograph.setScale(3.5, 3.5);
				SelectionHolograph.setOrigin({ SelectionHolograph.getLocalBounds().width / 2,SelectionHolograph.getLocalBounds().height / 2 });
				SelectionHolograph.setColor(Color(255, 255, 255, 175));
			}
			else if (currentselection == Plants_Zombies::SnowPeaShooter)
			{
				SelectionHolograph.setTextureRect(IntRect(0, 0, 32, 34));
				SelectionHolograph.setTexture(Plants_Zombies::IcePeaShooterIdleTex);
				SelectionHolograph.setScale(3.5, 3.5);
				SelectionHolograph.setOrigin({ SelectionHolograph.getLocalBounds().width / 2,SelectionHolograph.getLocalBounds().height / 2 });
				SelectionHolograph.setColor(Color(255, 255, 255, 175));
			}
			else if (currentselection == Plants_Zombies::WallNut)
			{
				SelectionHolograph.setTextureRect(IntRect(0, 0, 28, 31));
				SelectionHolograph.setTexture(Plants_Zombies::WallNutIdleTex);
				SelectionHolograph.setScale(3.5, 3.5);
				SelectionHolograph.setOrigin({ SelectionHolograph.getLocalBounds().width / 2,SelectionHolograph.getLocalBounds().height / 2 });
				SelectionHolograph.setColor(Color(255, 255, 255, 175));
			}
			else if (currentselection == Plants_Zombies::PotatoMine)
			{
				SelectionHolograph.setTextureRect(IntRect(0, 0, 29, 26));
				SelectionHolograph.setTexture(Plants_Zombies::PotatoMineIdelTex);
				SelectionHolograph.setScale(3.5, 3.5);
				SelectionHolograph.setOrigin({ SelectionHolograph.getLocalBounds().width / 2,SelectionHolograph.getLocalBounds().height / 2 });
				SelectionHolograph.setColor(Color(255, 255, 255, 175));
			}
			else if (currentselection == Plants_Zombies::Jalapeno)
			{
				SelectionHolograph.setTextureRect(IntRect(0, 0, 32, 36));
				SelectionHolograph.setTexture(Plants_Zombies::JalapenoExplosionTex);
				SelectionHolograph.setScale(3.5, 3.5);
				SelectionHolograph.setOrigin({ SelectionHolograph.getLocalBounds().width / 2,SelectionHolograph.getLocalBounds().height / 2 });
				SelectionHolograph.setColor(Color(255, 255, 255, 175));
			}
			else if (currentselection == Plants_Zombies::IceShroom)
			{
				SelectionHolograph.setTextureRect(IntRect(0, 0, 39, 32));
				SelectionHolograph.setTexture(Plants_Zombies::IceShroomIdelTex);
				SelectionHolograph.setScale(3.5, 3.5);
				SelectionHolograph.setOrigin({ SelectionHolograph.getLocalBounds().width / 2,SelectionHolograph.getLocalBounds().height / 2 });
				SelectionHolograph.setColor(Color(255, 255, 255, 175));
			}
			else if (currentselection == Plants_Zombies::SunShroom)
			{
				SelectionHolograph.setTextureRect(IntRect(0, 0, 28, 31));
				SelectionHolograph.setTexture(Plants_Zombies::SunShroomIdleTex);
				SelectionHolograph.setScale(3.5, 3.5);
				SelectionHolograph.setOrigin({ SelectionHolograph.getLocalBounds().width / 2,SelectionHolograph.getLocalBounds().height / 2 });
				SelectionHolograph.setColor(Color(255, 255, 255, 175));
			}
			else if (currentselection == Plants_Zombies::PuffShroom)
			{
				SelectionHolograph.setTextureRect(IntRect(0, 0, 28, 31));
				SelectionHolograph.setTexture(Plants_Zombies::PuffShroomTex);
				SelectionHolograph.setScale(3.5, 3.5);
				SelectionHolograph.setOrigin({ SelectionHolograph.getLocalBounds().width / 2,SelectionHolograph.getLocalBounds().height / 2 });
				SelectionHolograph.setColor(Color(255, 255, 255, 175));
			}
			else if (currentselection == Plants_Zombies::ScaredyShroom)
			{
				SelectionHolograph.setTextureRect(IntRect(0, 0, 28, 31));
				SelectionHolograph.setTexture(Plants_Zombies::ScaredyShroomIdleTex);
				SelectionHolograph.setScale(3.5, 3.5);
				SelectionHolograph.setOrigin({ SelectionHolograph.getLocalBounds().width / 2,SelectionHolograph.getLocalBounds().height / 2 });
				SelectionHolograph.setColor(Color(255, 255, 255, 175));
			}
			else if (currentselection == Plants_Zombies::PlantingPot)
			{
				SelectionHolograph.setTextureRect(IntRect(0, 0, 27, 30));
				SelectionHolograph.setTexture(Plants_Zombies::PlantingPotIdleTex);
				SelectionHolograph.setScale(3.5, 3.5);
				SelectionHolograph.setOrigin({ SelectionHolograph.getLocalBounds().width / 2,SelectionHolograph.getLocalBounds().height / 2 });
				SelectionHolograph.setColor(Color(255, 255, 255, 175));
			}

			if (currentselection != Plants_Zombies::Shovel)
			{
				shovelcontainer.setTexture(ShovelContainerAvailable);
			}

			SelectionHolograph.setPosition(mousepos);
		}
		else
		{
			shovelcontainer.setTexture(ShovelContainerAvailable);
			PlaySelectionSound = false;
			currentSelectionIndex = -1;
			currentselection = Plants_Zombies::EmptyPlant;
		}

		//planting on the grid
		if (currentselection != Plants_Zombies::EmptyPlant && isHolding)
		{
			for (int i = 1; i <= 45; i++)
			{
				if (mygrid[i].shape.getGlobalBounds().contains(mousepos) && Mouse::isButtonPressed(Mouse::Left))
				{
					if (onRoof)
					{
						if (currentselection == Plants_Zombies::Shovel)
						{
							//delete normal plants
							if (mygrid[i].isplanted && !mygrid[i].gravePlanted)
							{
								PlaySoundEffect(PlantingSoundBuffer, true);
								//cout << "shovel " << i << endl;
								mygrid[i].isplanted = false;
								Plants_Zombies::PlantsArray[i - 1].type = Plants_Zombies::EmptyPlant;
								Plants_Zombies::PlantsArray[i - 1].start();

								isHolding = false;
								break;
							}
							//delete planting pots
							else if (Plants_Zombies::PlantingPotArray[i - 1].type != Plants_Zombies::EmptyPlant)
							{
								PlaySoundEffect(PlantingSoundBuffer, true);
								//cout << "shovel " << i << endl;
								mygrid[i].isplanted = false;
								Plants_Zombies::PlantingPotArray[i - 1].type = Plants_Zombies::EmptyPlant;
								Plants_Zombies::PlantingPotArray[i - 1].start();

								isHolding = false;
								break;
							}
						}
						else if(!mygrid[i].isplanted)
						{
							//plant the pot
							if (currentselection == Plants_Zombies::PlantingPot
								&& Plants_Zombies::PlantingPotArray[i - 1].type == Plants_Zombies::EmptyPlant)
							{
								PlaySoundEffect(PlantingSoundBuffer, true);
								//mygrid[i].isplanted = true;
								Plants_Zombies::score -= selectedPlantsArr[currentSelectionIndex].price;
								Plants_Zombies::PlantingPotArray[i - 1].type = selectedPlantsArr[currentSelectionIndex].type;
								Plants_Zombies::PlantingPotArray[i - 1].start();
								selectedPlantsArr[currentSelectionIndex].resetSeedPacket();
								Plants_Zombies::PlantingPotArray[i - 1].deadPlantingPot = false;
								break;
							}
							//if not planting pot and pot is already present plant normally
							else if (Plants_Zombies::PlantingPotArray[i - 1].type == Plants_Zombies::PlantingPot
								&& currentselection != Plants_Zombies::PlantingPot)
							{
								PlaySoundEffect(PlantingSoundBuffer, true);
								mygrid[i].isplanted = true;
								Plants_Zombies::score -= selectedPlantsArr[currentSelectionIndex].price;
								Plants_Zombies::PlantsArray[i - 1].type = selectedPlantsArr[currentSelectionIndex].type;
								Plants_Zombies::PlantsArray[i - 1].start();
								Plants_Zombies::PlantsArray[i - 1].shape.setPosition(mygrid[i].shape.getPosition() + Vector2f{ 0, -15 });
								selectedPlantsArr[currentSelectionIndex].resetSeedPacket();
								break;
							}
						}
					}
					else
					{
						if (currentselection == Plants_Zombies::Shovel)
						{
							cout << "deleteeee 1" << endl;
							cout << Plants_Zombies::PlantsArray[i - 1].deadPlantingPot << " --- " << Plants_Zombies::PlantingPotArray[i-1].deadPlantingPot <<endl;
							if (mygrid[i].isplanted && !mygrid[i].gravePlanted)
							{
								cout << "deleteeee 2" << endl;
								PlaySoundEffect(PlantingSoundBuffer, true);
								//cout << "shovel " << i << endl;
								mygrid[i].isplanted = false;
								Plants_Zombies::PlantsArray[i - 1].type = Plants_Zombies::EmptyPlant;
								Plants_Zombies::PlantsArray[i - 1].start();

								isHolding = false;
								break;
							}
						}
						else if(!mygrid[i].isplanted)
						{
							PlaySoundEffect(PlantingSoundBuffer, true);
							mygrid[i].isplanted = true;
							Plants_Zombies::score -= selectedPlantsArr[currentSelectionIndex].price;
							Plants_Zombies::PlantsArray[i - 1].type = selectedPlantsArr[currentSelectionIndex].type;
							Plants_Zombies::PlantsArray[i - 1].start();
							Plants_Zombies::PlantsArray[i - 1].shape.setPosition(mygrid[i].shape.getPosition());
							selectedPlantsArr[currentSelectionIndex].resetSeedPacket();
							break;
						}
					}
				}
			}
		}
	}
}

void DrawPlantingAndCurrencySystem(RenderWindow& window)
{
	window.draw(gradientopacity);

	//for (int i = 1; i <= 45; i++)
	//{
	//	window.draw(mygrid[i].shape);
	//}
	
	//draw graves
	if (isNight && !onRoof)
	{
		for (int i = 0; i < numGraves; i++)
		{
			window.draw(graves[i]);
		}
	}

	if (moveright)
	{
		// draw plant selection menu
		if (plantselectionMenu && !isbossFight)
		{
			window.draw(plantSelectionBlank);

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					window.draw(plantsToSelect[i][j].shape);
				}
			}

			window.draw(LetsRockButton);
		}

		//draw selected plants
		for (int i = 5; i >= 0; i--)
		{
			window.draw(selectedPlantsArr[i].shape);
		}


		if (!isbossFight)
		{
			window.draw(sunContainer);
			window.draw(moneytext);
		}

		window.draw(shovelcontainer);
	}

	// draw selection hologram
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
			if (!(zombie_array[j].isDead || zombie_array[j].type == Dead) && zombie_array[j].started) // checks if zombie is dead or not to avoid shooting dead zombies
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
				if (!(zombie_array[j].isDead || zombie_array[j].type == Dead) && zombie_array[j].started) // checks if zombie is dead or not to avoid shooting dead zombies
				{
					if (((shape.getGlobalBounds().top + shape.getGlobalBounds().height / 2) <= (zombie_array[j].zombieCont.getGlobalBounds().top + zombie_array[j].zombieCont.getGlobalBounds().height)
						&& ((shape.getGlobalBounds().top + shape.getGlobalBounds().height / 2) >= zombie_array[j].zombieCont.getGlobalBounds().top))
						&& (zombie_array[j].zombieCollider.getPosition().x < shape.getPosition().x + (107 * 3.5)))
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
			for (int j = 0; j < 100; j++)
			{
				//!(zombie_array[j].isDead || zombie_array[j].type == Dead || !zombie_array[j].started)
				if (!(zombie_array[j].isDead || zombie_array[j].type == Dead) && zombie_array[j].started) // checks if zombie is dead or not to avoid shooting dead zombies
				{
					if (((shape.getGlobalBounds().top + shape.getGlobalBounds().height / 2) <= (zombie_array[j].zombieCont.getGlobalBounds().top + zombie_array[j].zombieCont.getGlobalBounds().height)
						&& ((shape.getGlobalBounds().top + shape.getGlobalBounds().height / 2) >= zombie_array[j].zombieCont.getGlobalBounds().top)
						&& (shape.getGlobalBounds().left <= zombie_array[j].zombieCont.getGlobalBounds().left))
						&& (zombie_array[j].zombieCollider.getPosition().x < shape.getPosition().x + (107))
						&& (zombie_array[j].zombieCollider.getPosition().x < 960))

					{
						zombieProximityAction = true;
						animationCol = 0;
						zombie_array[j].health -= damage;
					}
				}
			}
		}
		else if (type == PotatoMine && !zombieProximityAction && GettingUp)
		{
			for (int j = 0; j < 100; j++)
			{
				//!(zombie_array[j].isDead || zombie_array[j].type == Dead || !zombie_array[j].started)
				if (!(zombie_array[j].isDead || zombie_array[j].type == Dead) && zombie_array[j].started) // checks if zombie is dead or not to avoid shooting dead zombies
				{
					if (((shape.getGlobalBounds().top + shape.getGlobalBounds().height / 2) <= (zombie_array[j].zombieCont.getGlobalBounds().top + zombie_array[j].zombieCont.getGlobalBounds().height)
						&& ((shape.getGlobalBounds().top + shape.getGlobalBounds().height / 2) >= zombie_array[j].zombieCont.getGlobalBounds().top)
						&& (shape.getGlobalBounds().left <= zombie_array[j].zombieCont.getGlobalBounds().left))
						&& (zombie_array[j].zombieCollider.getPosition().x < shape.getPosition().x + (107))
						&& (zombie_array[j].zombieCollider.getPosition().x < 960))

					{
						zombieProximityAction = true;
						animationCol = 0;
						zombie_array[j].health -= damage;
					}
				}
			}
		}
		else if (type == Jalapeno && Explosion)
		{
			for (int j = 0; j < 100; j++)
			{
				//!(zombie_array[j].isDead || zombie_array[j].type == Dead || !zombie_array[j].started)
				if (!(zombie_array[j].isDead || zombie_array[j].type == Dead) && zombie_array[j].started) // checks if zombie is dead or not to avoid shooting dead zombies
				{
					if (plantCollider.getGlobalBounds().intersects(zombie_array[j].zombieCollider.getGlobalBounds()))
					{
						zombie_array[j].health -= damage;
					}
				}
			}
		}
		else if (type == IceShroom && ExplosionIce)
		{
			for (int j = 0; j < 100; j++)
			{
				//!(zombie_array[j].isDead || zombie_array[j].type == Dead || !zombie_array[j].started)
				if (!(zombie_array[j].isDead || zombie_array[j].type == Dead) && zombie_array[j].started) // checks if zombie is dead or not to avoid shooting dead zombies
				{
					zombie_array[j].IsFrozen = true;
				}
			}
		}
		animationHandler();
		action();

		plantCollider.setPosition(shape.getPosition());
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