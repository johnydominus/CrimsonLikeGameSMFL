#include "pch.h"
#include "Map.h"


Map::Map()
{
	mTexture.loadFromFile("img/background.jpg");
	mSprite.setTexture(mTexture);
	Position.x = 0;
	Position.y = 0;
}

Map::~Map()
{
}

aPOINT* Map::getPosition()
{
	return &Position;
}

aPOINT* Map::getRelatPosition()
{
	return &relatPosition;
}

std::vector<float>* Map::getSize()
{
	return &size;
}

sf::Sprite* Map::getSprite()
{
	return &mSprite;
}

void Map::setPosition(float x, float y)
{
	Position.x = x;
	Position.y = y;
}

void Map::setRelativePosition(float x, float y)
{
	relatPosition.x = x;
	relatPosition.y = y;
}

void Map::setSize(float x, float y)
{
	size[0] = x;
	size[1] = y;
}

void Map::setPlayer(Player * aPlayer)
{
	thePlayer = aPlayer;
}

void Map::update()
{
	relatMovement = *(thePlayer->getRelatMovement());
	relatPosition.x -= (float)relatMovement[0];
	relatPosition.y -= (float)relatMovement[1];
}
