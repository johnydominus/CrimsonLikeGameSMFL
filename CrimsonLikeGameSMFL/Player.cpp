#include "pch.h"
#include "Player.h"


Player::Player()
{
	mTexture.loadFromFile("img/player.png");
	mSprite.setTexture(mTexture);
	mSprite.setOrigin (mSprite.getTexture()->getSize().x*0.5, mSprite.getTexture()->getSize().y*0.5);
	alive = true;
}

Player::~Player()
{
}

POINT* Player::getPosition()
{
	return &Position;
}

POINT* Player::getRelatPosition()
{
	return &relatPosition;
}

std::vector<float>* Player::getSize()
{
	return &size;
}

sf::Sprite Player::getSprite()
{
	return mSprite;
}

float * Player::getSpeed()
{
	return &speed;
}

bool * Player::isAlive()
{
	return &alive;
}

void Player::setPosition(float x, float y)
{
	Position.x = x;
	Position.y = y;
}

void Player::setRelativePosition(float x, float y)
{
	relatPosition.x = x;
	relatPosition.y = y;
}

void Player::setSize(float x, float y)
{
	size[0] = x;
	size[1] = y;
}

void Player::setSpeed(float x)
{
	speed = x;
}

void Player::setAlive(bool x)
{
	alive = x;
}

void Player::setMapSize(float x, float y)
{
	mapSize[0] = x;
	mapSize[1] = y;
}

std::vector<float>* Player::getRelatMovement()
{
	return &relatMovement;
}

void Player::moveLeft()
{
	leftPressed = true;
}

void Player::moveRight()
{
	rightPressed = true;
}

void Player::moveUp()
{
	upPressed = true;
}

void Player::moveDown()
{
	downPressed = true;
}

void Player::stopLeft()
{
	leftPressed = false;
}

void Player::stopRight()
{
	rightPressed = false;
}

void Player::stopUp()
{
	upPressed = false;
}

void Player::stopDown()
{
	downPressed = false;
}

void Player::update(float elapsedTime)
{
	if (rightPressed /*&& ((Position.x + speed * elapsedTime < mapSize[0]))*/) 
		Position.x += speed * elapsedTime;
	//else if (rightPressed && ((Position.x + speed * elapsedTime >= mapSize[0]))) 
	//	Position.x = mapSize[0];

	if (leftPressed /*&& ((Position.x - speed * elapsedTime > 0))*/)
		Position.x -= speed * elapsedTime;
	//else if (leftPressed && ((Position.x - speed * elapsedTime <= 0)))
	//	Position.x = 0;

	if (upPressed /*&& ((Position.y + speed * elapsedTime < mapSize[1]))*/) 
		Position.y -= speed * elapsedTime;
	//else if (upPressed && ((Position.y + speed * elapsedTime >= mapSize[1])))
	//	Position.y = mapSize[1];

	if (downPressed /*&& ((Position.y + speed * elapsedTime > 0))*/) 
		Position.y += speed * elapsedTime;
	//else if(downPressed && ((Position.y + speed * elapsedTime > 0)))
	//	Position.y = 0;

	relatMovement[0] = (float)Position.x - (float)prevPosition.x;
	relatMovement[1] = (float)Position.y - (float)prevPosition.y;

	prevPosition = Position;

	//shape.left = Position.x - (size[0] / 2.0);
	//shape.right = Position.x + (size[0] / 2.0);
	//shape.top = Position.y - (size[1] / 2.0);
	//shape.bottom = Position.y + (size[1] / 2.0);
}

