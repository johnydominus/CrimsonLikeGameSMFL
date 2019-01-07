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
	sf::Sprite mSprite;
	sf::Texture mTexture;

	aPOINT Position;
	aPOINT relatPosition;
	aPOINT reticlePosition;
	aPOINT playerPosition;
	aPOINT playerRelatPosition;
	std::vector<float> vSpeed{ 0,0 };
	std::vector<float> mapSize{ 0,0 };
	std::vector<float> direction{ 0,0 };

	float speed = 500.0;
	float theAngle = 0;
	float pathLength;
	bool shot;
	
	Player* thePlayer;
	Map* theMap;
	Reticle* theReticle;

public:
	Bullet();
	~Bullet();

	sf::Sprite* getSprite();

	aPOINT* getPosition();
	aPOINT* getRelatPosition();

	float* getSpeed();
	bool* isShot();

	void setPosition(float x, float y);
	void setRelativePosition(float x, float y);
	void setSpeed(float x);
	void setShot(bool x);

	void setPlayer(Player* aPlayer);
	void setMap(Map* aMap);
	void setReticle(Reticle* aReticle);
	void shoot();
	void setMapSize(std::vector<float> aMapSize);

	void update(float elapsedTime);
};

