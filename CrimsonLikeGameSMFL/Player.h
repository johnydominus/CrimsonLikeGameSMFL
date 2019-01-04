#pragma once
#include "Object.h"
#include <Windows.h>

class Player :
	public Object
{
private:
	sf::Sprite mSprite;
	sf::Texture mTexture;

	aPOINT Position;
	aPOINT relatPosition;
	aPOINT prevPosition;
	aRECT shape;

	std::vector<float> size{ 25,25 };
	std::vector<float> mapSize{ 0,0 };
	std::vector<float> relatMovement{ 0,0 };

	float speed = 120.0;
	bool alive;

	bool leftPressed;
	bool rightPressed;
	bool upPressed;
	bool downPressed;

public:
	Player();
	~Player();

	sf::Sprite* getSprite();
	sf::Texture* getTexture();

	aPOINT* getPosition();
	aPOINT* getRelatPosition();
	aPOINT* getPrevPosition();
	aRECT* getShape();
	std::vector<float>* getRelatMovement();
	std::vector<float>* getSize();

	float* getSpeed();
	bool* isAlive();

	void setPosition(float x, float y);
	void setRelativePosition(float x, float y);
	void setSize(float x, float y);
	void setSpeed(float x);
	void setAlive(bool x);
	void setMapSize(float x, float y);

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void stopLeft();
	void stopRight();
	void stopUp();
	void stopDown();
	
	void update(float elapsedTime);
};

