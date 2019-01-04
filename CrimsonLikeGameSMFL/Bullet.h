#pragma once
#include "Object.h"
#include "Player.h"
#include "Map.h"
#include "Reticle.h"
#include <cmath>
#include <Windows.h>

class Bullet :
	public Object
{
private:
	sf::Texture mTexture;
	int speed = 3;
	float theAngle = 0;
	bool shot;
	
	Player* thePlayer;
	Map* theMap;
	Reticle* theReticle;
	POINT reticlePosition;
	POINT playerPosition;
	POINT playerRelatPosition;
	std::vector<float> vSpeed{0,0};


public:
	Bullet();
	~Bullet();

	POINT Position;
	POINT relatPosition;
	sf::Sprite mSprite;

	POINT* getPosition();
	POINT* getRelatPosition();
	std::vector<float> mapSize{ 0,0 };
	sf::Sprite getSprite();
	int* getSpeed();
	bool* isShot();

	void setPosition(float x, float y);
	void setRelativePosition(float x, float y);
	void setSpeed(float x);
	void setShot(bool x);

	void setPlayer(Player* aPlayer);
	void setMap(Map* aMap);
	void setReticle(Reticle* aReticle);
	void shoot();

	void update(float elapsedTime);
};

