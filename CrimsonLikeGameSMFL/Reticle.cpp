#include "pch.h"
#include "Reticle.h"


Reticle::Reticle()
{
	mTexture.loadFromFile("img/reticle.png");
	mSprite.setTexture(mTexture);
	ShowCursor(false);
}


Reticle::~Reticle()
{
	ShowCursor(true);
}

POINT* Reticle::getPosition()
{
	return &Position;
}

POINT* Reticle::getRelatPosition()
{
	return &relatPosition;
}

sf::Sprite Reticle::getSprite()
{
	return mSprite;
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

void Reticle::setPlayer(Player * aPlayer)
{
	thePlayer = aPlayer;
}

void Reticle::update()
{
	GetCursorPos(&relatPosition);

	playerRelatPosition = *(thePlayer->getRelatPosition());
	playerPosition = *(thePlayer->getPosition());

	Position.x = playerPosition.x + (relatPosition.x - playerRelatPosition.x);
	Position.y = playerPosition.y + (relatPosition.y - playerRelatPosition.y);

	direction[0] = Position.x - thePlayer->Position.x;
	direction[1] = Position.y - thePlayer->Position.y;

	pathLength = sqrt(pow(direction[0], 2) + pow(direction[1], 2));

	direction[0] /= pathLength;
	direction[1] /= pathLength;
}
