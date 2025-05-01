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
Texture ground;
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
Sprite backg;
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

float speed = 0.1;
Vector2i mouseposition;
Vector2f mouseworldposition;
//RectangleShape rect(Vector2f(10, 20));//mouse
//Mouse ms;

void LoadSunDropTex() {
	ground.loadFromFile("SunDropSystem/background.jpg");
	sunscore.loadFromFile("SunDropSystem/sun-cointainer.jpg");
	plant1.loadFromFile("SunDropSystem/peashooter-seedpacket-2.jpg");
	plant11.loadFromFile("SunDropSystem/peashooter-seedpacket-1.jpg");
	plant2.loadFromFile("SunDropSystem/sunflower-seedpacket-2.jpg");
	plant22.loadFromFile("SunDropSystem/sunflower-seedpacket-1.jpg");
	plant3.loadFromFile("SunDropSystem/wallnut-seedpacket-2.jpg");
	plant33.loadFromFile("SunDropSystem/wallnut-seedpacket-1.jpg");
	plant4.loadFromFile("SunDropSystem/snowpea-seedpacket-2.jpg");
	plant44.loadFromFile("SunDropSystem/snowpea-seedpacket-1.jpg");
	sun.loadFromFile("SunDropSystem/sun-ST.png");
	font.loadFromFile("SunDropSystem/HouseofTerror Regular.otf");
}

void SetupSunDrop() {
	sunscore1.setTexture(sunscore);
	sunscore1.setTextureRect(IntRect(0, 0, 100, 92));
	sunscore1.setScale(1, 1);
	sunscore1.setPosition(30, 20);

	backg.setTexture(ground);

	plants1.setTexture(plant1);
	plants1.setTextureRect(IntRect(0, 0, 100, 92));
	plants1.setScale(1, 1);
	plants1.setPosition(27, 292);

	plants2.setTexture(plant2);
	plants2.setTextureRect(IntRect(0, 0, 100, 92));
	plants2.setScale(1, 1);
	plants2.setPosition(27, 183);

	plants3.setTexture(plant3);
	plants3.setTextureRect(IntRect(0, 0, 100, 92));
	plants3.setScale(1, 1);
	plants3.setPosition(27, 490);

	plants4.setTexture(plant4);
	plants4.setTextureRect(IntRect(0, 0, 100, 92));
	plants4.setScale(1, 1);
	plants4.setPosition(27, 393);

	//drop.setTexture(sun);
	//drop.setTextureRect(IntRect(0, 0, 26, 26));
	//drop.setScale(5, 5);
	//drop.setPosition(300+ (rand() % 700), -100);

	scoretex.setFont(font);
	scoretex.setString(to_string(Plants_Zombies::score));
	scoretex.setCharacterSize(56);
	scoretex.setFillColor(Color::White);
	scoretex.setOutlineThickness(3);
	scoretex.setOrigin(scoretex.getGlobalBounds().width / 2, scoretex.getGlobalBounds().height / 2);
	scoretex.setPosition(77, 135);

}

void updateSunDrop(Vector2f mousepos) {
	if (suncoinclock.getElapsedTime() >= seconds(17))
	{

		Vector2f sponposition = { (float)(300 + rand() % 700), (float)(-100) };
		Plants_Zombies::PlantProjectile suncoin;

		suncoin.start(Plants_Zombies::SunCoin, 0, sponposition);
		Plants_Zombies::PlantProjectilesARR.push_back(suncoin);
		suncoinclock.restart();
	}

	//rect.setPosition(ms.getPosition().x - 330, ms.getPosition().y - 220);
	scoretex.setString(to_string(Plants_Zombies::score));
	scoretex.setOrigin(scoretex.getGlobalBounds().width / 2, scoretex.getGlobalBounds().height / 2);
	scoretex.setPosition(77, 135);
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

		Plants_Zombies::score -=  50;
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
	//window.draw(backg);
	window.draw(scoretex);
	window.draw(sunscore1);
	window.draw(drop);
	window.draw(plants1);
	window.draw(plants2);
	window.draw(plants3);
	window.draw(plants4);

}
