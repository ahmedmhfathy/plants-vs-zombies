#pragma once
#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;
using namespace sf;


//namespace plantingSystem{
//enum Selection { PeaShooter, SnowPeaShooter, SunFlower, WallNut, Shovel, None }currentSelection;
//
//int currentIndex;
//
//struct Grid
//{
//	RectangleShape shape;
//	bool isPlanted = false;
//}myGrid[46];
//
//void startPlantingSystem() {
//	for (int i = 1, r=0, c=0; i <= 45; i++)
//	{
//		myGrid[i].shape.setSize({ 107, 130 });
//		myGrid[i].shape.setPosition(107 * c, 130 * r);
//
//		c++;
//		if (i%9==0)
//		{
//			c = 0;
//			r++;
//		}
//		if (i%2==0)
//		{
//			myGrid[i].shape.setFillColor(Color(255, 255, 255, 128));
//		}
//		else
//		{
//			myGrid[i].shape.setFillColor(Color(255, 255, 255, 64));
//		}
//	}
//}
//
//void updatePlantingSystem(Vector2f mousePos) {
//
//	if (currentSelection != None)
//	{
//		for (int i = 1; i < 46; i++)
//		{
//			if (myGrid[i].shape.getGlobalBounds().contains(mousePos) && Mouse::isButtonPressed(Mouse::Left))
//			{
//				if (currentSelection == Shovel)
//				{
//					cout << "Shovel " << i <<endl;
//					myGrid[i].isPlanted = false;
//					currentIndex = i;
//				}
//				else if (currentSelection == PeaShooter)
//				{
//					cout << "PeaShooter " << i << endl;
//					myGrid[i].isPlanted = true;
//					currentIndex = i;
//				}
//				else if (currentSelection == SnowPeaShooter)
//				{
//					cout << "SnowPeaShooter " << i << endl;
//					myGrid[i].isPlanted = true;
//					currentIndex = i;
//				}
//				else if (currentSelection == SunFlower)
//				{
//					cout << "SunFlower " << i << endl;
//					myGrid[i].isPlanted = true;
//					currentIndex = i;
//				}
//				else if (currentSelection == WallNut)
//				{
//					cout << "WallNut " << i << endl;
//					myGrid[i].isPlanted = true;
//					currentIndex = i;
//				}
//			}
//		}
//	}
//}
//
//void drawPlantingSystem(RenderWindow& window) {
//	for (int i = 1; i <= 45; i++)
//	{
//		window.draw(myGrid[i].shape);
//	}
//}
//
//}