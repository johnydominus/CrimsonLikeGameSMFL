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
	sf::Sprite mSprite;
	sf::Texture mTexture;

	aPOINT Position;
	aPOINT relatPosition;
	aPOINT playerPosition;
	aPOINT playerRelatPosition;
	aPOINT nextStep;
	aRECT shape;
	aRECT nextShape;

	std::vector<float> size{ 30,30 };
	std::vector<float> playerRelatMovement{ 0,0 };
	std::vector<float> direction{ 0,0 };
	std::vector<float> vSpeed{ 0,0 };

	float speed;
	float pathLength;
	bool alive;
	bool collide;

	time_t since_collide;
	time_t now;

	Player* thePlayer;
	Map* theMap;

public:
	Monster();
	~Monster();

	aPOINT* getPosition();
	aPOINT* getRelatPosition();
	aRECT* getShape();
	std::vector<float>* getSize();
	std::vector<float>* getDirection();
	sf::Sprite* getSprite();
	float* getSpeed();
	time_t * getSinceCollide();
	bool* isAlive();

	void setCollide(bool collision);

	void setPosition(aPOINT newPosition);
	void setRelativePosition(float x, float y);
	void setSize(float x, float y);
	void setSpeed(float x);
	void setAlive(bool x);

	void setPlayer(Player* aPlayer);
	void setMap(Map* aMap);

	//void occupyNode();
	//void occupyNextNode();

	aPOINT checkUpdate(float elapsedTime);
	void update(float elapsedTime, aPOINT position);
};

