#pragma once
#include "Object.h"
#include "Map.h"
#include "Player.h"
#include <ctime>
#include <Windows.h>

class Monster :
	public Object
{
private:
	std::vector<float> size{30,20};
	sf::Texture mTexture;
	int speed=4;
	bool alive;
	float pathLength;
	Player* thePlayer;
	Map* theMap;
	POINT playerPosition;
	POINT playerRelatPosition;
	POINT nextStep;
	std::vector<float> playerRelatMovement{0,0};
	std::vector<float> direction{ 0,0 };
	std::vector<float> vSpeed{ 0,0 };

public:
	Monster();
	~Monster();

	POINT Position;
	POINT relatPosition;
	sf::Sprite mSprite;
	RECT shape;

	POINT* getPosition();
	POINT* getRelatPosition();
	std::vector<float>* getSize();
	sf::Sprite getSprite();
	int* getSpeed();
	bool* isAlive();

	void setPosition(POINT newPosition);
	void setRelativePosition(float x, float y);
	void setSize(float x, float y);
	void setSpeed(int x);
	void setAlive(bool x);

	void setPlayer(Player* aPlayer);
	void setMap(Map* aMap);

	POINT checkUpdate(float elapsedTime);
	void update(float elapsedTime, POINT position);
};

