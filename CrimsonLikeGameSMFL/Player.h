#pragma once
#include "Object.h"
#include "Bullet.h"
#include <Windows.h>
#include <ctime>
#include <chrono>

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
	std::vector<sf::IntRect> rectTextures;
	std::vector<sf::IntRect>::iterator sprtIter;

	float speed = 120.0;
	bool alive;
	int i, j, cntr = 0;

	bool leftPressed;
	bool rightPressed;
	bool upPressed;
	bool downPressed;

public:
	Player();
	~Player();

	sf::Sprite* getSprite() override;
	sf::Texture* getTexture();

	aPOINT* getPosition() override;
	aPOINT* getRelatPosition() override;
	aPOINT* getPrevPosition();
	aRECT* getShape();

	Bullet* bullets;

	typedef std::chrono::high_resolution_clock Clock;
	typedef std::chrono::milliseconds milliseconds;
	Clock::time_point previous_shot;
	Clock::time_point current_shot;
	milliseconds ms;

	std::vector<float>* getRelatMovement();
	std::vector<float>* getSize();

	int ammoNumber, bulletNumber, bulletMax;
	bool mouseButtonPressed;
	bool wasFire;

	float* getSpeed();
	bool* isAlive();


	void setPosition(float x, float y) override;
	void setRelativePosition(float x, float y) override;
	void setSize(float x, float y);
	void setSpeed(float x);
	void setAlive(bool x);
	void setMapSize(float x, float y);

	void shoot();
	void fire();
	void stopFire();
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

