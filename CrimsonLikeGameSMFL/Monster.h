#pragma once
#include "Object.h"
#include "Map.h"
#include "Player.h"
#include <iterator>
#include <ctime>
#include <cmath>
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

	std::vector<float> size{ 30,30 };
	std::vector<float> playerRelatMovement{ 0,0 };
	std::vector<float> direction{ 0,0 };
	std::vector<float> vSpeed{ 0,0 };
	std::vector<sf::IntRect> rectTextures;
	std::vector<sf::IntRect>::iterator sprtIter;

	float speed;
	float pathLength;
	bool alive;
	bool collide;
	int cntr=0;
	int i;

	time_t since_collide;
	time_t now;

	Player* thePlayer;
	Map* theMap;

	aPOINT mNode;
	aPOINT mNextNode;

public:
	Monster();
	~Monster();

	aPOINT* getPosition() override;
	aPOINT* getRelatPosition() override;
	sf::Sprite* getSprite() override;
	aRECT* getShape();
	std::vector<float>* getSize();
	std::vector<float>* getDirection();

	float* getSpeed();
	time_t * getSinceCollide();
	bool* isAlive();

	void setCollide(bool collision);
	void setPosition(float x, float y) override;
	void setPosition(aPOINT newPosition);
	void setRelativePosition(float x, float y) override;
	void setSize(float x, float y);
	void setSpeed(float x);
	void setAlive(bool x);

	void setPlayer(Player* aPlayer);
	void setMap(Map* aMap);

	void occupyNode();

	void update();
};

