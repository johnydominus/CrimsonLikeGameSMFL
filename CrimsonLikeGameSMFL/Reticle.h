#pragma once
#include "Object.h"
#include "Player.h"
#include <Windows.h>

class Reticle :
	public Object
{
private:
	sf::Texture mTexture;
	Player* thePlayer;
	POINT playerPosition;
	POINT playerRelatPosition;

public:
	Reticle();
	~Reticle();

	POINT Position;
	POINT relatPosition;
	std::vector<float> direction{ 0,0 };
	float pathLength;
	sf::Sprite mSprite;

	POINT* getPosition();
	POINT* getRelatPosition();
	sf::Sprite getSprite();

	void setPosition(float x, float y);
	void setRelativePosition(float x, float y);
	void setPlayer(Player* aPlayer);

	void update();
};

