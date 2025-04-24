#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<string>
#include<vector>
using namespace std;
using namespace sf;


RectangleShape collider(Vector2f());
RectangleShape plant;

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
	RegularWalkText.loadFromFile("Assets/regular_walk.png");
}

enum zombieType{ regular, bucketHat, trafficCone, soccerGuy};
struct Zombie {
	Sprite zombieCont;
	zombieType type;
	int health;
	float speed;
	int damage;

private:
	int CollIndex = 0;
	int RowIndex = 0;
	bool isIdle = false;
	bool isMoving = false;
	bool isAttacking = false;
	bool isDead = false;
	bool PlantsinFront = false;

public:
	void start() {
		isIdle = false;
		isMoving = true;
		isAttacking = false;

		TextLoading();

		switch (type)
		{
		case regular:
			zombieCont.setTexture(RegularWalkText);
			health = 100;
			speed = 1.0;
			damage = 10;
			zombieCont.setPosition(200, 0);
			break;
		case trafficCone:
			zombieCont.setTexture(TrafficConeIdleText);
			health = 200;
			speed = 0.9;
			damage = 10;
			break;
		case bucketHat:
			zombieCont.setTexture(BucketHatIdleText);
			health = 300;
			speed = 0.8;
			damage = 15;
			break;
		case soccerGuy:
			zombieCont.setTexture(RegularIdleText);
			health = 150;
			speed = 2.0;
			damage = 20;
			break;
		default:
			break;
		}
	}
	void update(/*RectangleShape plant*/) { // will take plants array
		
		Animation();
		Movement();

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
		}else if (type == regular && isAttacking)
		{
		}else if (type == regular && isDead)
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
	void Movement() {
		if (health == 0) {
			isDead = 0;
		}
		/*else if (zombieCont.getGlobalBounds().intersects(plant.getGlobalBounds()) && !isDead) 
		{
			Attacking();
		}*/
		else {
			isMoving = true;
			zombieCont.move(-1 * speed, 0);
		}
		
	}

	void Attacking() {
		isMoving = false;
		isAttacking = true;
		//if (condition for batates) 
		//// takeDmg from plants.h
		// }
	}


}zombie[4];

void StartZombies() {
	zombie[0].type = regular;
	zombie[0].start();
}

void UpdateZ() {
	zombie[0].update();
}


