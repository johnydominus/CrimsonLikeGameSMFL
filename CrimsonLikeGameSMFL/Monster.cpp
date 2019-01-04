#include "pch.h"
#include "Monster.h"


Monster::Monster()
{
	mTexture.loadFromFile("img/monster.png");
	mSprite.setTexture(mTexture);
	mSprite.setOrigin(mSprite.getTexture()->getSize().x*0.5, mSprite.getTexture()->getSize().y*0.5); 
	alive = true;
}


Monster::~Monster()
{
}

POINT* Monster::getPosition()
{
	return &Position;
}

POINT* Monster::getRelatPosition()
{
	return &relatPosition;
}

std::vector<float>* Monster::getSize()
{
	return &size;
}

sf::Sprite Monster::getSprite()
{
	return mSprite;
}

int * Monster::getSpeed()
{
	return &speed;
}

bool * Monster::isAlive()
{
	return &alive;
}

void Monster::setPosition(POINT newPosition)
{
	Position = newPosition;
}

void Monster::setRelativePosition(float x, float y)
{
	relatPosition.x = x;
	relatPosition.y = x;
}

void Monster::setSize(float x, float y)
{
	size[0] = x;
	size[1] = y;
}

void Monster::setSpeed(int x)
{
	speed = x;
}

void Monster::setAlive(bool x)
{
	alive = x;
}

void Monster::setPlayer(Player * aPlayer)
{
	thePlayer = aPlayer;
}

void Monster::setMap(Map * aMap)
{
	theMap = aMap;
}

POINT Monster::checkUpdate(float elapsedTime)
{
	nextStep = Position;
	playerPosition = *(thePlayer->getPosition());
	
	direction[0] = playerPosition.x - Position.x;
	direction[1] = playerPosition.y - Position.y;

	pathLength = sqrt(pow(direction[0], 2) + pow(direction[1], 2));

	direction[0] /= pathLength;
	direction[1] /= pathLength;

	vSpeed[0] = ((float)direction[0] * (float)speed)/10.0;
	vSpeed[1] = ((float)direction[1] * (float)speed)/10.0;

	nextStep.x += vSpeed[0];
	nextStep.y += vSpeed[1];

	return nextStep;
}

void Monster::update(float elapsedTime, POINT aNextStep)
{
	Position = aNextStep;
	playerPosition = *(thePlayer->getPosition());
	playerRelatPosition = *(thePlayer->getRelatPosition());

	relatPosition.x = playerRelatPosition.x + (Position.x - playerPosition.x);
	relatPosition.y = playerRelatPosition.y + (Position.y - playerPosition.y);

	shape.left = Position.x - (size[0] / 2);
	shape.right = Position.x + (size[0] / 2);
	shape.top = Position.y - (size[1] / 2);
	shape.bottom = Position.y + (size[1] / 2);
}
