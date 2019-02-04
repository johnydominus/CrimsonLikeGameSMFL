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

void Bullet::setDirection(float x, float y)
{
	direction[0] = x;
	direction[1] = y;
}

void Bullet::setSpeed(float x)
{
	speed = x;
}

void Bullet::setShot(bool x)
{
	shot = x;
}

void Bullet::setReticle(Reticle * aReticle)
{
	theReticle = aReticle;
}

void Bullet::setMovement()
{
	direction[0] = theReticle->getScreenPosition()->x - relatPosition.x;
	direction[1] = theReticle->getScreenPosition()->y - relatPosition.y;

	auto pathLength = sqrt(pow(direction[0], 2) + pow(direction[1], 2));
	auto theAngle = -(atan2(theReticle->getScreenPosition()->x - relatPosition.x, theReticle->getScreenPosition()->y - relatPosition.y) * 180.0 / 3.141592);
	mSprite.setRotation(theAngle);

	direction[0] /= pathLength;
	direction[1] /= pathLength;

	vSpeed[0] = direction[0] * speed;
	vSpeed[1] = direction[1] * speed;

}

void Bullet::setMapSize(std::vector<float> aMapSize)
{
	mapSize = aMapSize;
}

void Bullet::update(aPOINT playerPosition, aPOINT playerRelPosition, float elapsedTime)
{
	if (shot) {
		relatPosition.x = playerRelPosition.x + (Position.x - playerPosition.x);
		relatPosition.y = playerRelPosition.y + (Position.y - playerPosition.y);

		Position.x += vSpeed[0] * elapsedTime;
		Position.y += vSpeed[1] * elapsedTime;

		if (Position.x <= 0 || Position.x >= mapSize[0] || Position.y <= 0 || Position.y >= mapSize[1]) {
			shot = false;
		}
	}
	else {
		Position = playerPosition;
		relatPosition = playerRelPosition;
	}
}