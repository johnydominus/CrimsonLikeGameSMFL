#pragma once
#include "Object.h"
#include "Player.h"
#include <iterator>
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

	std::vector<float> playerRelatMovement{ 0,0 };
	std::vector<float> direction{ 0,0 };
	std::vector<float> vSpeed{ 0,0 };
	std::vector<sf::IntRect> rectTextures;
	std::vector<sf::IntRect>::iterator sprtIter;

	float speed, angle;
	bool alive;
	int cntr=0;

	Player* thePlayer;

public:
	Monster();
	~Monster();

	float pathLength;

	sf::Sprite* getSprite() override;
	float * getAngle();
	aPOINT* getPosition() override;
	aPOINT* getRelatPosition() override;
	aPOINT* getPlayerPosition();
	std::vector<float>* getDirection();

	float* getSpeed();
	bool* isAlive();

	aPOINT setMovement();
	void setMovement(Node goal);
	
	void setPosition(float x, float y) override;
	void setRelativePosition(float x, float y) override;
	void setPlayerPosition();
	void setDirection(float x, float y);
	void setSpeed(float x);
	void setAlive(bool x);
	void setPlayer(Player* aPlayer);
	void killPlayer();

	void updateRelativePosition();
	
	void update();
};