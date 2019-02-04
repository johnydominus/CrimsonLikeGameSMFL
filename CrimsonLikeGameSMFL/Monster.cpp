#include "pch.h"
#include "Monster.h"


Monster::Monster()
{
	mTexture.loadFromFile("img/player-monster.png");
	mSprite.setTexture(mTexture);
	alive = true;

	for (auto i = 0; i < 8; i++) {
		rectTextures.push_back(sf::IntRect());
		rectTextures[i].width = 46;
		rectTextures[i].height = 46;
	}

	sprtIter = rectTextures.begin();

	rectTextures[0].left = 0;
	rectTextures[0].top = 146;
	
	rectTextures[1].left = 49;
	rectTextures[1].top = 146;

	rectTextures[2].left = 97;
	rectTextures[2].top = 146;

	rectTextures[3].left = 145;
	rectTextures[3].top = 146;

	rectTextures[4].left = 0;
	rectTextures[4].top = 194;

	rectTextures[5].left = 48;
	rectTextures[5].top = 194;
	
	rectTextures[6].left = 97;
	rectTextures[6].top = 194;

	rectTextures[7].left = 144;
	rectTextures[7].top = 194;

	mSprite.setTextureRect(*sprtIter);
	mSprite.setOrigin(mSprite.getTextureRect().width*0.5, mSprite.getTextureRect().height*0.5);
}


Monster::~Monster()
{
}

aPOINT* Monster::getPosition()
{
	return &Position;
}

aPOINT* Monster::getRelatPosition()
{
	return &relatPosition;
}

aPOINT* Monster::getPlayerPosition()
{
	return &playerPosition;
}

std::vector<float>* Monster::getDirection() {
	return &direction;
}

sf::Sprite* Monster::getSprite()
{
	return &mSprite;
}

float* Monster::getAngle() 
{
	return &angle;
}

float * Monster::getSpeed()
{
	return &speed;
}

bool* Monster::isAlive()
{
	return &alive;
}

aPOINT Monster::setMovement() 
{
	playerPosition = *thePlayer->getPosition();

	direction[0] = playerPosition.x - Position.x;
	direction[1] = playerPosition.y - Position.y;

	pathLength = sqrt(pow(direction[0], 2) + pow(direction[1], 2));

	direction[0] /= pathLength;
	direction[1] /= pathLength;

	vSpeed[0] = (direction[0] * speed) / 10.0;
	vSpeed[1] = (direction[1] * speed) / 10.0;
	
	angle = -(atan2(thePlayer->getRelatPosition()->x - relatPosition.x, thePlayer->getRelatPosition()->y - relatPosition.y) * 180.0 / 3.141592);
	
	aPOINT nextPosition;
	nextPosition.x = Position.x + vSpeed[0];
	nextPosition.y = Position.y + vSpeed[1];
	return  nextPosition;
}

void Monster::setMovement(Node goal) 
{
	direction[0] = goal.centerPosition.x - Position.x;
	direction[1] = goal.centerPosition.y - Position.y;

	pathLength = sqrt(pow(direction[0], 2) + pow(direction[1], 2));

	direction[0] /= pathLength;
	direction[1] /= pathLength;

	vSpeed[0] = (direction[0] * speed) / 10.0;
	vSpeed[1] = (direction[1] * speed) / 10.0;

	angle = -(atan2((thePlayer->getRelatPosition()->x + (goal.centerPosition.x - thePlayer->getPosition()->x)) - relatPosition.x, (thePlayer->getRelatPosition()->y + (goal.centerPosition.y - thePlayer->getPosition()->y)) - relatPosition.y) * 180.0 / 3.141592);
}

void Monster::setPosition(float x, float y)
{
	Position.x = x;
	Position.y = y;
}

void Monster::setRelativePosition(float x, float y)
{
	relatPosition.x = x;
	relatPosition.y = x;
}

void Monster::setPlayerPosition()
{
	playerPosition = *thePlayer->getPosition();
}

void Monster::setDirection(float x, float y)
{
	direction[0] = x;
	direction[1] = y;
}

void Monster::setSpeed(float x)
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

void Monster::killPlayer()
{
	thePlayer->setAlive(false);
}

void Monster::updateRelativePosition()
{
	relatPosition.x = thePlayer->getRelatPosition()->x + (Position.x - thePlayer->getPosition()->x);
	relatPosition.y = thePlayer->getRelatPosition()->y + (Position.y - thePlayer->getPosition()->y);

	if (sqrt(pow(thePlayer->getPosition()->x - Position.x, 2) + pow(thePlayer->getPosition()->y - Position.y, 2)) < thePlayer->getSprite()->getTextureRect().width)
		killPlayer();
}

void Monster::update()
{
	Position.x += vSpeed[0];
	Position.y += vSpeed[1];

	relatPosition.x = thePlayer->getRelatPosition()->x + (Position.x - thePlayer->getPosition()->x);
	relatPosition.y = thePlayer->getRelatPosition()->y + (Position.y - thePlayer->getPosition()->y);

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

	if (sqrt(pow(thePlayer->getPosition()->x - Position.x, 2) + pow(thePlayer->getPosition()->y - Position.y, 2)) < thePlayer->getSprite()->getTextureRect().width)
		killPlayer();
}
