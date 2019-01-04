#pragma once
#include "Object.h"
#include <Windows.h>

class Player :
	public Object
{
private:
	std::vector<float> mapSize{0,0};
	sf::Texture mTexture;

	float speed = 1.0;
	bool alive;

	POINT prevPosition;
	std::vector<float> relatMovement{ 0,0 };

	bool leftPressed;
	bool rightPressed;
	bool upPressed;
	bool downPressed;

public:
	Player();
	~Player();

	POINT Position;
	POINT relatPosition;
	sf::Sprite mSprite;
	std::vector<float> size{ 25,15 };
	RECT shape;

	POINT* getPosition();
	POINT* getRelatPosition();
	std::vector<float>* getSize();
	sf::Sprite getSprite();
	float* getSpeed();
	bool* isAlive();

	void setPosition(float x, float y);
	void setRelativePosition(float x, float y);
	void setSize(float x, float y);
	void setSpeed(float x);
	void setAlive(bool x);
	void setMapSize(float x, float y);

	std::vector<float>* getRelatMovement();

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

