#include "pch.h"
#include "Player.h"


Player::Player()
{
	mTexture.loadFromFile("img/player-monster.png");
	mSprite.setTexture(mTexture);
	alive = true;
	previous_shot = Clock::now();
	bulletNumber=0;

	for (auto i = 0; i < 8; i++) {
		rectTextures.push_back(sf::IntRect());
		rectTextures[i].width = 45;
		rectTextures[i].height = 46;
	}

	sprtIter = rectTextures.begin();

	rectTextures[0].left = 1;
	rectTextures[0].top = 1;

	rectTextures[1].left = 48;
	rectTextures[1].top = 1;

	rectTextures[2].left = 96;
	rectTextures[2].top = 1;

	rectTextures[3].left = 144;
	rectTextures[3].top = 1;

	rectTextures[4].left = 1;
	rectTextures[4].top = 49;

	rectTextures[5].left = 49;
	rectTextures[5].top = 49;

	rectTextures[6].left = 97;
	rectTextures[6].top = 49;

	rectTextures[7].left = 145;
	rectTextures[7].top = 49;

	mSprite.setTextureRect(*sprtIter);
	mSprite.setOrigin(mSprite.getTextureRect().width*0.5, mSprite.getTextureRect().height*0.5);
}

Player::~Player()
{
	delete[] bullets;
}

aPOINT* Player::getPosition()
{
	return &Position;
}

aPOINT* Player::getRelatPosition()
{
	return &relatPosition;
}

aPOINT * Player::getPrevPosition()
{
	return &prevPosition;
}

sf::Sprite* Player::getSprite()
{
	return &mSprite;
}

sf::Texture * Player::getTexture()
{
	return &mTexture;
}

float * Player::getSpeed()
{
	return &speed;
}

bool * Player::isAlive()
{
	return &alive;
}

Bullet * Player::getBullet(int i)
{
	return &bullets[i];
}

void Player::fillAmmo()
{
	bullets = new Bullet[ammoNumber];
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

void Player::shoot()
{
	if (ammoNumber>0) {
		current_shot = Clock::now();
		ms = std::chrono::duration_cast<milliseconds>(current_shot - previous_shot);
		if (ms.count() > 200) {
			bullets[bulletNumber].setShot(true);
			bullets[bulletNumber].setMovement();
			previous_shot = current_shot;
			bulletNumber++;
			ammoNumber--;
		}
	}
}

void Player::fire() 
{
	mouseButtonPressed = true;
}

void Player::stopFire() 
{
	mouseButtonPressed = false;
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
	if (rightPressed && ((Position.x + speed * elapsedTime < mapSize[0])))
		Position.x += speed * elapsedTime;
	else if (rightPressed && ((Position.x + speed * elapsedTime >= mapSize[0]))) 
		Position.x = mapSize[0];

	if (leftPressed && (Position.x - speed * elapsedTime > 0))
		Position.x -= speed * elapsedTime;
	else if (leftPressed && ((Position.x - speed * elapsedTime <= 0)))
		Position.x = 0;

	if (upPressed && (Position.y + speed * elapsedTime > 0)) 
		Position.y -= speed * elapsedTime;
	else if (upPressed && ((Position.y + speed * elapsedTime >= mapSize[1])))
		Position.y = 0;

	if (downPressed && ((Position.y + speed * elapsedTime < mapSize[1]))) 
		Position.y += speed * elapsedTime;
	else if(downPressed && ((Position.y + speed * elapsedTime >= mapSize[1])))
		Position.y = mapSize[1];

	if (downPressed || leftPressed || rightPressed || upPressed) {
		if (cntr == 20) {
			cntr = 0;
			if (sprtIter == rectTextures.end()) {
				sprtIter = rectTextures.begin();
				mSprite.setTextureRect(*sprtIter);
			}
			else
			{
				mSprite.setTextureRect(*sprtIter);
				++sprtIter;
			}
		}
		cntr++;
	}

	relatMovement[0] = (float)Position.x - (float)prevPosition.x;
	relatMovement[1] = (float)Position.y - (float)prevPosition.y;

	prevPosition = Position;

	/********************************
	BULLETS HANDLING
	********************************/

	//updating each shot bullet position
	if (mouseButtonPressed) {
		shoot();
	}

	for (auto i = 0; i < bulletMax; i++) {
		bullets[i].update(Position, relatPosition, elapsedTime);
	}

	//respawn one bullet if they ended
	if (ammoNumber == 0) {
		if (!*bullets[bulletNumber-1].isShot()) {
			ammoNumber++;
			bulletNumber--;
			bullets[bulletNumber].setMovement();
			bullets[bulletNumber].update(Position,relatPosition,elapsedTime);
		}
	}
}