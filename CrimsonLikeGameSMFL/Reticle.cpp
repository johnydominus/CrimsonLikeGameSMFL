#include "pch.h"
#include "Reticle.h"


Reticle::Reticle()
{
	mTexture.loadFromFile("img/reticle.png");
	mSprite.setTexture(mTexture);
	mSprite.setOrigin(mSprite.getTexture()->getSize().x*0.5, mSprite.getTexture()->getSize().y*0.5);
	ShowCursor(false);
}


Reticle::~Reticle()
{
	ShowCursor(true);
}

POINT * Reticle::getScreenPosition()
{
	return &screenPosition;
}

aPOINT* Reticle::getPosition()
{
	return &Position;
}

aPOINT* Reticle::getRelatPosition()
{
	return &relatPosition;
}

std::vector<float>* Reticle::getDirection()
{
	return &direction;
}

sf::Sprite* Reticle::getSprite()
{
	return &mSprite;
}

void Reticle::setPosition(float x, float y)
{
	Position.x = x;
	Position.y = y;
}

void Reticle::setRelativePosition(float x, float y)
{
	relatPosition.x = x;
	relatPosition.y = y;
}

void Reticle::setScreenPosition(float x, float y)
{
	screenPosition.x = x;
	screenPosition.y = y;
}

void Reticle::update(aPOINT* playerPosition, aPOINT* playerRelPosition)
{
	GetCursorPos(&screenPosition);

	Position.x = playerPosition->x + (screenPosition.x - playerRelPosition->x);
	Position.y = playerPosition->y + (screenPosition.y - playerRelPosition->y);

	direction[0] = screenPosition.x - playerRelPosition->x;
	direction[1] = screenPosition.y - playerRelPosition->y;

	auto pathLength = sqrt(pow(direction[0], 2) + pow(direction[1], 2));

	direction[0] /= pathLength;
	direction[1] /= pathLength;
}
