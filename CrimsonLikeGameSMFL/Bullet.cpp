#include "pch.h"
#include "Bullet.h"


Bullet::Bullet()
{
	mTexture.loadFromFile("img/bullet.png");
	mSprite.setTexture(mTexture);
	mSprite.setOrigin(mSprite.getTexture()->getSize().x*0.5, mSprite.getTexture()->getSize().y*0.5); 
	shot = false;
}


Bullet::~Bullet()
{
}

aPOINT* Bullet::getPosition()
{
	return &Position;
}

aPOINT* Bullet::getRelatPosition()
{
	return &relatPosition;
}

sf::Sprite* Bullet::getSprite()
{
	return &mSprite;
}

float* Bullet::getSpeed()
{
	return &speed;
}

bool * Bullet::isShot()
{
	return &shot;
}

void Bullet::setPosition(float x, float y)
{
	Position.x = x;
	Position.y = y;
}

void Bullet::setRelativePosition(float x, float y)
{
	relatPosition.x = x;
	relatPosition.y = y;
}

void Bullet::setSpeed(float x)
{
	speed = x;
}

void Bullet::setShot(bool x)
{
	shot = x;
}

void Bullet::setPlayer(Player * aPlayer)
{
	thePlayer = aPlayer;
}

void Bullet::setMap(Map * aMap)
{
	theMap = aMap;
}

void Bullet::setReticle(Reticle * aReticle)
{
	theReticle = aReticle;
}

void Bullet::shoot()
{
	/*
	reticlePosition = *(theReticle->getPosition());
	Position = *(thePlayer->getPosition());

	direction[0] = reticlePosition.x - Position.x;
	direction[1] = reticlePosition.y - Position.y;

	pathLength = sqrt(pow(direction[0], 2) + pow(direction[1], 2));
	direction[0] /= pathLength;
	direction[1] /= pathLength;
	*/
	
	direction = *(theReticle->getDirection());

	vSpeed[0] = direction[0] * speed;
	vSpeed[1] = direction[1] * speed;

	theAngle = atan2(theReticle->getScreenPosition()->x - relatPosition.x, theReticle->getScreenPosition()->y - relatPosition.y) * 180.0 / 3.141592;
	mSprite.setRotation(theAngle);

	setShot(true);
}

void Bullet::setMapSize(std::vector<float> aMapSize)
{
	mapSize = aMapSize;
}

void Bullet::update(float elapsedTime)
{
	if (shot) {
		Position.x += vSpeed[0] * elapsedTime;
		Position.y += vSpeed[1] * elapsedTime;

		playerPosition = *(thePlayer->getPosition());
		playerRelatPosition = *(thePlayer->getRelatPosition());

		relatPosition.x = playerRelatPosition.x + (Position.x - playerPosition.x);
		relatPosition.y = playerRelatPosition.y + (Position.y - playerPosition.y);

		if (Position.x < 0 || Position.x > mapSize[0] || Position.y < 0 || Position.y > mapSize[1]) {
			shot = false;
		}
	}
	if (!shot) {
		Position = *thePlayer->getPosition();
		relatPosition = *thePlayer->getRelatPosition();
	}
}
