#pragma once
#include "Object.h"
#include <Windows.h>

class Reticle :
	public Object
{
private:
	sf::Sprite mSprite;
	sf::Texture mTexture;

	POINT screenPosition;
	aPOINT relatPosition;
	aPOINT Position;
	std::vector<float> direction{ 0,0 };
	
	float pathLength;

public:
	Reticle();
	~Reticle();

	sf::Sprite* getSprite() override;

	POINT* getScreenPosition();
	aPOINT* getPosition() override;
	aPOINT* getRelatPosition() override;
	std::vector<float>* getDirection();

	void setPosition(float x, float y) override;
	void setRelativePosition(float x, float y) override;
	void setScreenPosition(float x, float y);

	void update(aPOINT* playerPosition, aPOINT* playerRelPosition);
};