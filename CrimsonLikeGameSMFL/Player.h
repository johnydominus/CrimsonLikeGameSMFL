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

	std::vector<float> mapSize{ 0,0 };
	std::vector<float> relatMovement{ 0,0 };
	std::vector<sf::IntRect> rectTextures;
	std::vector<sf::IntRect>::iterator sprtIter;
	
	Bullet* bullets;

	float speed = 120.0;
	bool alive;
	int cntr = 0;

	bool leftPressed;
	bool rightPressed;
	bool upPressed;
	bool downPressed;

public:
	Player();
	~Player();

	typedef std::chrono::high_resolution_clock Clock;
	typedef std::chrono::milliseconds milliseconds;
	Clock::time_point previous_shot;
	Clock::time_point current_shot;
	milliseconds ms;
	int ammoNumber, bulletNumber, bulletMax;
	bool mouseButtonPressed;
	bool wasFire;

	sf::Sprite* getSprite() override;
	sf::Texture* getTexture();
	aPOINT* getPosition() override;
	aPOINT* getRelatPosition() override;
	aPOINT* getPrevPosition();
	std::vector<float>* getRelatMovement();
	Bullet* getBullet(int i);
	float* getSpeed();
	bool* isAlive();
	
	void setPosition(float x, float y) override;
	void setRelativePosition(float x, float y) override;
	void setSpeed(float x);
	void setAlive(bool x);
	void setMapSize(float x, float y);

	void fillAmmo();
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

