#pragma once
#include "Object.h"
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
	bool shot;
	
	Reticle* theReticle;

public:
	Bullet();
	~Bullet();

	sf::Sprite* getSprite() override;

	aPOINT* getPosition() override;
	aPOINT* getRelatPosition() override;

	float* getSpeed();
	bool* isShot();

	void setPosition(float x, float y) override;
	void setRelativePosition(float x, float y) override;
	void setDirection(float x, float y);
	void setSpeed(float x);
	void setShot(bool x);

	void setReticle(Reticle* aReticle);
	void setMovement();
	void setMapSize(std::vector<float> aMapSize);

	void update(aPOINT playerPosition, aPOINT playerRelPosition, float elapsedTime);
};

