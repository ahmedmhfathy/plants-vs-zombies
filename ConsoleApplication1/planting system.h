#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <iomanip>
#include<cstdlib> //for rand() and srand()
#include<ctime>//for time()
#include"Plants_Zombies.h"

using namespace std;
using namespace sf;

#pragma region texture declaration
Texture opacityGradientTex;
Texture sunscore;
Texture plant1;
Texture plant11;
Texture plant2;
Texture plant22;
Texture plant3;
Texture plant33;
Texture plant4;
Texture plant44;
Texture sun;
Font font;
Text scoretex;
#pragma endregion

#pragma region sprite declaration
Sprite opacityGradient;
Sprite sunscore1;
Sprite plants1;
Sprite plants2;
Sprite plants3;
Sprite plants4;
Sprite drop;
#pragma endregion

#pragma region clockandtime
Clock peashooterclock, sunflowerclock, wallnutclock, snowpeashooterclock, suncoinclock;
Time peashootertime = seconds(7);
Time sunflowertime = seconds(7);
Time  snowpeashootertime = seconds(7);
Time  wallnuttime = seconds(30);
#pragma endregion

bool ispeashooter = false;
bool issunflower = false;
bool iswallnut = false;
bool issnowpea = false;

void LoadSunDropTex() {
	opacityGradientTex.loadFromFile("Assets/Currency System and planting/Gradient-opacity-layer.png");
	sunscore.loadFromFile("Assets/Currency System and planting/sun-cointainer.png");
	plant1.loadFromFile("Assets/Currency System and planting/peashooter-seedpacket-2.png");
	plant11.loadFromFile("Assets/Currency System and planting/peashooter-seedpacket-1.png");
	plant2.loadFromFile("Assets/Currency System and planting/sunflower-seedpacket-2.png");
	plant22.loadFromFile("Assets/Currency System and planting/sunflower-seedpacket-1.png");
	plant3.loadFromFile("Assets/Currency System and planting/wallnut-seedpacket-2.png");
	plant33.loadFromFile("Assets/Currency System and planting/wallnut-seedpacket-1.png");
	plant4.loadFromFile("Assets/Currency System and planting/snowpea-seedpacket-2.png");
	plant44.loadFromFile("Assets/Currency System and planting/snowpea-seedpacket-1.png");
	sun.loadFromFile("Assets/Sun/sun-ST.png");
	font.loadFromFile("Assets/HouseofTerror Regular.otf");
}

void SetupSunDrop(Vector2f offset) {
	opacityGradient.setTexture(opacityGradientTex);
	opacityGradient.setPosition(offset.x, offset.y);

	sunscore1.setTexture(sunscore);
	sunscore1.setScale(1, 1);
	sunscore1.setPosition(30 + offset.x, 20 + offset.y);

	plants1.setTexture(plant1);
	plants1.setScale(1, 1);
	plants1.setPosition(27 + offset.x, 292 + offset.y);

	plants2.setTexture(plant2);
	plants2.setScale(1, 1);
	plants2.setPosition(27 + offset.x, 183 + offset.y);

	plants3.setTexture(plant3);
	plants3.setScale(1, 1);
	plants3.setPosition(27 + offset.x, 490 + offset.y);

	plants4.setTexture(plant4);
	plants4.setScale(1, 1);
	plants4.setPosition(27 + offset.x, 393 + offset.y);

	scoretex.setFont(font);
	scoretex.setString(to_string(Plants_Zombies::score));
	scoretex.setCharacterSize(56);
	scoretex.setFillColor(Color::White);
	scoretex.setOutlineThickness(3);
	scoretex.setOrigin(scoretex.getGlobalBounds().width / 2, scoretex.getGlobalBounds().height / 2);
	scoretex.setPosition(80 + offset.x, 138 + offset.y);
}

void updateSunDrop(Vector2f mousepos, Vector2f offset) {
	if (suncoinclock.getElapsedTime() >= seconds(17))
	{
		Vector2f sponposition = { (float)(0 + rand() % 780), (float)(-100 + offset.y) };
		Plants_Zombies::PlantProjectile suncoin;

		suncoin.start(Plants_Zombies::SunCoin, 0, sponposition, (200 + rand() % 300) + offset.y);
		Plants_Zombies::PlantProjectilesARR.push_back(suncoin);
		suncoinclock.restart();
	}

	scoretex.setString(to_string(Plants_Zombies::score));
	scoretex.setOrigin(scoretex.getGlobalBounds().width / 2, scoretex.getGlobalBounds().height / 2);
	scoretex.setPosition(80 + offset.x, 138 + offset.y);

	if (Plants_Zombies::score >= 50 && sunflowerclock.getElapsedTime() >= sunflowertime)
	{
		plants2.setTexture(plant22);
		issunflower = true;
	}
	else
	{
		plants2.setTexture(plant2);
	}

	if (Plants_Zombies::score >= 50 && wallnutclock.getElapsedTime() >= wallnuttime)
	{
		plants3.setTexture(plant33);
		iswallnut = true;
	}
	else
	{
		plants3.setTexture(plant3);
	}

	if (Plants_Zombies::score >= 100 && peashooterclock.getElapsedTime() >= peashootertime)
	{
		plants1.setTexture(plant11);
		ispeashooter = true;
	}
	else
	{
		plants1.setTexture(plant1);
	}

	if (Plants_Zombies::score >= 175 && snowpeashooterclock.getElapsedTime() >= snowpeashootertime)
	{
		plants4.setTexture(plant44);
		issnowpea = true;
	}
	else
	{
		plants4.setTexture(plant4);
	}

	if (plants1.getGlobalBounds().contains(mousepos) && Mouse::isButtonPressed(Mouse::Left) && ispeashooter)
	{
		Plants_Zombies::score = Plants_Zombies::score - 100;
		peashooterclock.restart();
		ispeashooter = false;
	}

	if (plants2.getGlobalBounds().contains(mousepos) && Mouse::isButtonPressed(Mouse::Left) && issunflower)
	{
		Plants_Zombies::score -= 50;
		sunflowerclock.restart();
		issunflower = false;
	}

	if (plants3.getGlobalBounds().contains(mousepos) && Mouse::isButtonPressed(Mouse::Left) && iswallnut)
	{

		Plants_Zombies::score -= 50;
		wallnutclock.restart();
		iswallnut = false;
	}

	if (plants4.getGlobalBounds().contains(mousepos) && Mouse::isButtonPressed(Mouse::Left) && issnowpea)
	{
		Plants_Zombies::score -= 175;
		snowpeashooterclock.restart();
		issnowpea = false;
	}
}

void DrawSunDrop(RenderWindow& window) {
	window.draw(opacityGradient);
	window.draw(scoretex);
	window.draw(sunscore1);
	window.draw(drop);
	window.draw(plants1);
	window.draw(plants2);
	window.draw(plants3);
	window.draw(plants4);
}
