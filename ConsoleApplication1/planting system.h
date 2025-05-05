#pragma once
#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include<time.h>
#include"Plants_Zombies.h"

using namespace std;
using namespace sf;

#pragma region texture declaration
Texture peashootertex;
Texture peashooteruntex;
Texture sunflowertex;
Texture sunfloweruntex;
Texture wallnuttex;
Texture wallnutuntex;
Texture snowpeashootertex;
Texture snowpeashooteruntex;
Texture shoveltex;
Texture shovelcontainertex;
Texture shovelcontaineruntex;
Texture gradientopacitytex;
Texture suncountertex;
#pragma endregion

#pragma region sprite declaration
Sprite peashootercontainer;
Sprite snowpeashootercontainer;
Sprite wallnutcontainer;
Sprite sunflowercontainer;
Sprite shovelcontainer;
Sprite suncounter;
Sprite gradientopacity;
Sprite SelectionHolograph;
#pragma endregion

#pragma region clocks and time
Clock PeaShooterClock, SnowPeaClock, WallNutClock, SunFlowerClock, SunCoinClock;
Time SunSpawnTime = seconds(17);

Time SunFlowerCoolDown = seconds(7);
Time PeaShooterCoolDown = seconds(7);
Time SnowPeaCoolDown = seconds(7);
Time WallNutCoolDown = seconds(30);
#pragma endregion

Font font;
Text moneytext;

enum Selection { peashooter, snowpeashooter, sunflower, shovel, wallnut, none }curruntselection;

bool isHolding = false;

struct grid {
	RectangleShape shape;
	bool isplanted = false;
}mygrid[46];

void LoadSelectionTexture() {
	peashootertex.loadFromFile("Assets/Currency System and planting/peashooter-seedpacket-1.png");
	peashooteruntex.loadFromFile("Assets/Currency System and planting/peashooter-seedpacket-2.png");

	sunflowertex.loadFromFile("Assets/Currency System and planting/sunflower-seedpacket-1.png");
	sunfloweruntex.loadFromFile("Assets/Currency System and planting/sunflower-seedpacket-2.png");

	wallnuttex.loadFromFile("Assets/Currency System and planting/wallnut-seedpacket-1.png");
	wallnutuntex.loadFromFile("Assets/Currency System and planting/wallnut-seedpacket-2.png");

	snowpeashootertex.loadFromFile("Assets/Currency System and planting/snowpea-seedpacket-1.png");
	snowpeashooteruntex.loadFromFile("Assets/Currency System and planting/snowpea-seedpacket-2.png");

	shoveltex.loadFromFile("Assets/Currency System and planting/shovel.png");
	shovelcontainertex.loadFromFile("Assets/Currency System and planting/container-with-shovel.png");
	shovelcontaineruntex.loadFromFile("Assets/Currency System and planting/empty-container.png");

	gradientopacitytex.loadFromFile("Assets/Currency System and planting/Gradient-opacity-layer.png");

	suncountertex.loadFromFile("Assets/Currency System and planting/sun-cointainer.png");

	font.loadFromFile("Assets/HouseofTerror Regular.otf");
}

void SetupSelectionUI(Vector2f offset) {

	gradientopacity.setTexture(gradientopacitytex);
	gradientopacity.setPosition(0 + offset.x, 0 + offset.y);

	suncounter.setTexture(suncountertex);
	suncounter.setPosition(30 + offset.x, 20 + offset.y);

	sunflowercontainer.setTexture(sunflowertex);
	sunflowercontainer.setPosition(23 + offset.x, 183 + offset.y);

	peashootercontainer.setTexture(peashootertex);
	peashootercontainer.setPosition(27 + offset.x, 292 + offset.y);

	snowpeashootercontainer.setTexture(snowpeashootertex);
	snowpeashootercontainer.setPosition(27 + offset.x, 393 + offset.y);

	wallnutcontainer.setTexture(wallnuttex);
	wallnutcontainer.setPosition(27 + offset.x, 490 + offset.y);

	shovelcontainer.setTexture(shovelcontainertex);
	shovelcontainer.setPosition(27 + offset.x, 595 + offset.y);

	moneytext.setFont(font);
	moneytext.setString(to_string(Plants_Zombies::score));
	moneytext.setCharacterSize(56);
	moneytext.setFillColor(Color::White);
	moneytext.setOutlineThickness(3);
	moneytext.setOrigin(moneytext.getGlobalBounds().width / 2, moneytext.getGlobalBounds().height / 2);
	moneytext.setPosition(80 + offset.x, 138 + offset.y);
}


void SetupPlants() {
	Plants_Zombies::PlantProjectilesARR.clear();

	for (int i = 1; i <= 45; i++)
	{
		Plants_Zombies::PlantsArray[i - 1].type = Plants_Zombies::EmptyPlant;
		Plants_Zombies::PlantsArray[i - 1].gridIndex = i;
		Plants_Zombies::PlantsArray[i - 1].shape.setPosition(mygrid[i].shape.getPosition());
		Plants_Zombies::PlantsArray[i - 1].start();
	}
}

void StartPlantingAndCurrencySystem(Vector2f offset) {
	SetupSelectionUI(offset);

	SunCoinClock.restart();
	PeaShooterClock.restart();
	SnowPeaClock.restart();
	WallNutClock.restart();
	SunFlowerClock.restart();

	Plants_Zombies::score = 10000;

	//setup the grid
	for (int i = 1, r = 0, c = 0; i <= 45; i++) {
		mygrid[i].shape.setSize({ 107,130 });
		mygrid[i].shape.setPosition(107 * c, 130 * r);

		mygrid[i].isplanted = false;

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
	}
	SetupPlants();
}

void UpdatePlantingAndCurrencySystem(Vector2f mousepos, Vector2f offset) {
	if (SunCoinClock.getElapsedTime() >= SunSpawnTime)
	{
		Vector2f sponposition = { (float)(0 + rand() % 780), (float)(-100 + offset.y) };
		Plants_Zombies::PlantProjectile suncoin;

		suncoin.start(Plants_Zombies::SunCoin, 0, sponposition, (200 + rand() % 300) + offset.y);
		Plants_Zombies::PlantProjectilesARR.push_back(suncoin);
		SunCoinClock.restart();
	}

	moneytext.setString(to_string(Plants_Zombies::score));
	moneytext.setOrigin(moneytext.getGlobalBounds().width / 2, moneytext.getGlobalBounds().height / 2);
	moneytext.setPosition(80 + offset.x, 138 + offset.y);

	if (PeaShooterClock.getElapsedTime() > PeaShooterCoolDown && Plants_Zombies::score >= 100)
	{
		peashootercontainer.setTexture(peashootertex);

		if (peashootercontainer.getGlobalBounds().contains(mousepos) && Mouse::isButtonPressed(Mouse::Left))
		{
			isHolding = true;
			curruntselection = peashooter;
		}
	}
	else
	{
		peashootercontainer.setTexture(peashooteruntex);
	}

	if (SnowPeaClock.getElapsedTime() > SnowPeaCoolDown && Plants_Zombies::score >= 175)
	{
		snowpeashootercontainer.setTexture(snowpeashootertex);

		if (snowpeashootercontainer.getGlobalBounds().contains(mousepos) && Mouse::isButtonPressed(Mouse::Left))
		{
			isHolding = true;
			curruntselection = snowpeashooter;
		}
	}
	else
	{
		snowpeashootercontainer.setTexture(snowpeashooteruntex);
	}

	if (SunFlowerClock.getElapsedTime() > SunFlowerCoolDown && Plants_Zombies::score >= 50)
	{
		sunflowercontainer.setTexture(sunflowertex);

		if (sunflowercontainer.getGlobalBounds().contains(mousepos) && Mouse::isButtonPressed(Mouse::Left))
		{
			isHolding = true;
			curruntselection = sunflower;
		}
	}
	else
	{
		sunflowercontainer.setTexture(sunfloweruntex);
	}

	if (WallNutClock.getElapsedTime() > WallNutCoolDown && Plants_Zombies::score >= 50)
	{
		wallnutcontainer.setTexture(wallnuttex);

		if (wallnutcontainer.getGlobalBounds().contains(mousepos) && Mouse::isButtonPressed(Mouse::Left))
		{
			isHolding = true;
			curruntselection = wallnut;
		}
	}
	else
	{
		wallnutcontainer.setTexture(wallnutuntex);
	}

	if (shovelcontainer.getGlobalBounds().contains(mousepos) && Mouse::isButtonPressed(Mouse::Left))
	{
		isHolding = true;
		curruntselection = shovel;
	}

	//deselects
	if (Mouse::isButtonPressed(Mouse::Right)) {
		isHolding = false;
	}

	if (isHolding)
	{
		if (curruntselection == shovel)
		{
			shovelcontainer.setTexture(shovelcontaineruntex);
			SelectionHolograph.setTextureRect(IntRect(0, 0, 100, 100));
			SelectionHolograph.setTexture(shoveltex);
			SelectionHolograph.setScale(1, 1);
			SelectionHolograph.setOrigin({ SelectionHolograph.getLocalBounds().width / 2,SelectionHolograph.getLocalBounds().height / 2 });
		}
		else if (curruntselection == peashooter)
		{
			SelectionHolograph.setTextureRect(IntRect(0, 0, 30, 34));
			SelectionHolograph.setTexture(Plants_Zombies::PeaShooterIdleTex);
			SelectionHolograph.setScale(3.5, 3.5);
			SelectionHolograph.setOrigin({ SelectionHolograph.getLocalBounds().width / 2,SelectionHolograph.getLocalBounds().height / 2 });
		}
		else if (curruntselection == snowpeashooter)
		{
			SelectionHolograph.setTextureRect(IntRect(0, 0, 32, 34));
			SelectionHolograph.setTexture(Plants_Zombies::IcePeaShooterIdleTex);
			SelectionHolograph.setScale(3.5, 3.5);
			SelectionHolograph.setOrigin({ SelectionHolograph.getLocalBounds().width / 2,SelectionHolograph.getLocalBounds().height / 2 });
		}
		else if (curruntselection == sunflower)
		{
			SelectionHolograph.setTextureRect(IntRect(0, 0, 32, 34));
			SelectionHolograph.setTexture(Plants_Zombies::SunFlowerIdleTex);
			SelectionHolograph.setScale(3.5, 3.5);
			SelectionHolograph.setOrigin({ SelectionHolograph.getLocalBounds().width / 2,SelectionHolograph.getLocalBounds().height / 2 });
		}
		else if (curruntselection == wallnut)
		{
			SelectionHolograph.setTextureRect(IntRect(0, 0, 28, 31));
			SelectionHolograph.setTexture(Plants_Zombies::WallNutIdleTex);
			SelectionHolograph.setScale(3.5, 3.5);
			SelectionHolograph.setOrigin({ SelectionHolograph.getLocalBounds().width / 2,SelectionHolograph.getLocalBounds().height / 2 });
		}

		SelectionHolograph.setPosition(mousepos);
	}
	else
	{
		shovelcontainer.setTexture(shovelcontainertex);
		curruntselection = none;
	}

	if (curruntselection != none)
	{
		for (int i = 1; i <= 45; i++)
		{
			if (mygrid[i].shape.getGlobalBounds().contains(mousepos) && Mouse::isButtonPressed(Mouse::Left))
			{
				if (curruntselection == shovel && isHolding)
				{
					cout << "shovel " << i << endl;

					mygrid[i].isplanted = false;
					Plants_Zombies::PlantsArray[i - 1].type = Plants_Zombies::EmptyPlant;
					Plants_Zombies::PlantsArray[i - 1].start();

					isHolding = false;
				}
				else if (curruntselection == peashooter && isHolding)
				{
					if (!mygrid[i].isplanted)
					{
						cout << "peashooter " << i << endl;

						mygrid[i].isplanted = true;
						Plants_Zombies::score -= 100;
						PeaShooterClock.restart();

						Plants_Zombies::PlantsArray[i - 1].type = Plants_Zombies::PeaShooter;
						Plants_Zombies::PlantsArray[i - 1].start();

						isHolding = false;
						curruntselection = none;
					}
				}
				else if (curruntselection == snowpeashooter && isHolding)
				{
					if (!mygrid[i].isplanted)
					{
						cout << "SnowPeaShooter " << i << endl;

						mygrid[i].isplanted = true;
						Plants_Zombies::score -= 175;
						SnowPeaClock.restart();

						Plants_Zombies::PlantsArray[i - 1].type = Plants_Zombies::SnowPeaShooter;
						Plants_Zombies::PlantsArray[i - 1].start();

						isHolding = false;
						curruntselection = none;
					}
				}

				else if (curruntselection == sunflower && isHolding)
				{
					if (!mygrid[i].isplanted)
					{
						cout << "SunFlower " << i << endl;

						mygrid[i].isplanted = true;
						Plants_Zombies::score -= 50;
						SunFlowerClock.restart();

						Plants_Zombies::PlantsArray[i - 1].type = Plants_Zombies::SunFlower;
						Plants_Zombies::PlantsArray[i - 1].start();

						isHolding = false;
						curruntselection = none;
					}
				}
				else if (curruntselection == wallnut && isHolding)
				{
					if (!mygrid[i].isplanted)
					{
						cout << "WallNut " << i << endl;

						mygrid[i].isplanted = true;
						Plants_Zombies::score -= 50;
						WallNutClock.restart();

						Plants_Zombies::PlantsArray[i - 1].type = Plants_Zombies::WallNut;
						Plants_Zombies::PlantsArray[i - 1].start();

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
	/*for (int i = 1; i <= 45; i++) {
		window.draw(mygrid[i].shape);
	}*/

	window.draw(gradientopacity);
	window.draw(moneytext);
	window.draw(suncounter);
	window.draw(peashootercontainer);
	window.draw(snowpeashootercontainer);
	window.draw(sunflowercontainer);
	window.draw(wallnutcontainer);
	window.draw(shovelcontainer);

	if (isHolding)
	{
		window.draw(SelectionHolograph);
	}
}

//plants_Zombies function
void Plants_Zombies::Plants::updatePlantStruct(Zombie zombie_array[]) {
	if (!isDead) // if not dead will animate and execute action  
	{
		for (int j = 0; j < 100; j++)
		{
			if (!(zombie_array[j].isDead || zombie_array[j].type == Dead)) // checks if zombie is dead or not to avoid shooting dead zombies
			{
				// checks if a zombie is in front of the plant  
				if ((type == PeaShooter || type == SnowPeaShooter)
					&& ((shape.getGlobalBounds().top + shape.getGlobalBounds().height / 2) <= (zombie_array[j].zombieCont.getGlobalBounds().top + zombie_array[j].zombieCont.getGlobalBounds().height)
					&& ((shape.getGlobalBounds().top + shape.getGlobalBounds().height / 2) >= zombie_array[j].zombieCont.getGlobalBounds().top)
					&& (shape.getGlobalBounds().left <= zombie_array[j].zombieCont.getGlobalBounds().left))
					&& (zombie_array[j].zombieCollider.getPosition().x < 960))
				{
					if (!(zombie_array[j].type == Dead || zombie_array[j].health <= 0))
					{
						zombieInFront = true;
						break;
					}
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

		animationHandler();
		action();

		plantCollider.setPosition(shape.getPosition());
	}
	else // else will turn the plant into an empty gameobject  
	{
		type = EmptyPlant;
		mygrid[gridIndex].isplanted = false;
		setupPrefab();
	}

	if (health <= 0 || type == EmptyPlant)
	{
		isDead = true;
		idle = false;
		doAction = false;
	}
}