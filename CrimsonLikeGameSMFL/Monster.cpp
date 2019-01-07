#include "pch.h"
#include "Monster.h"


Monster::Monster()
{
	mTexture.loadFromFile("img/monster.png");
	mSprite.setTexture(mTexture);
	mSprite.setOrigin(mSprite.getTexture()->getSize().x*0.5, mSprite.getTexture()->getSize().y*0.5); 
	alive = true;
	collide = false;
	time(&since_collide);
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

aRECT * Monster::getShape()
{
	return &shape;
}

std::vector<float>* Monster::getSize()
{
	return &size;
}

std::vector<float>* Monster::getDirection() {
	return &direction;
}

sf::Sprite* Monster::getSprite()
{
	return &mSprite;
}

float * Monster::getSpeed()
{
	return &speed;
}

time_t* Monster::getSinceCollide() {
	return &since_collide;
}

bool * Monster::isAlive()
{
	return &alive;
}

void Monster::setCollide(bool collision) {
	collide = collision;
}

void Monster::setPosition(aPOINT newPosition)
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

void Monster::setMap(Map * aMap)
{
	theMap = aMap;
}
/*
void Monster::occupyNode() {
	theMap->mGrid[(int)(shape.top / 30)][(int)(shape.left / 30)].occupied = true;

	if ((shape.right / 30) <= theMap->gridX) {
		theMap->mGrid[(int)shape.top / 30][(int)(shape.right / 30)].occupied = true;
	}
	if ((shape.bottom / 30) <= theMap->gridY) {
		theMap->mGrid[(int)shape.bottom / 30][(int)(shape.left / 30)].occupied = true;
		if ((shape.right / 30) <= theMap->gridX) {
			theMap->mGrid[(int)shape.bottom / 30][(int)(shape.right / 30)].occupied = true;
		}
	}
}

void Monster::occupyNextNode() {
	theMap->mGrid[(int)(nextShape.top / 30)][(int)(nextShape.left / 30)].occupied = true;

	if ((shape.right / 30) <= theMap->gridX) {
		theMap->mGrid[(int)nextShape.top / 30][(int)(nextShape.right / 30)].occupied = true;
	}
	if ((shape.bottom / 30) <= theMap->gridY) {
		theMap->mGrid[(int)nextShape.bottom / 30][(int)(nextShape.left / 30)].occupied = true;
		if ((shape.right / 30) <= theMap->gridX) {
			theMap->mGrid[(int)nextShape.bottom / 30][(int)(nextShape.right / 30)].occupied = true;
		}
	}
}
*/
aPOINT Monster::checkUpdate(float elapsedTime)
{
	nextStep = Position;
	playerPosition = *(thePlayer->getPosition());
	
	direction[0] = playerPosition.x - Position.x;
	direction[1] = playerPosition.y - Position.y;

	pathLength = sqrt(pow(direction[0], 2) + pow(direction[1], 2));

	direction[0] /= pathLength;
	direction[1] /= pathLength;

	vSpeed[0] = (direction[0] * speed)/10.0;
	vSpeed[1] = (direction[1] * speed)/10.0;

	nextStep.x += vSpeed[0];
	nextStep.y += vSpeed[1];

	nextShape.left = nextStep.x - (size[0] / 2);
	nextShape.right = nextStep.x + (size[0] / 2);
	nextShape.top = nextStep.y - (size[1] / 2);
	nextShape.bottom = nextStep.y + (size[1] / 2);

	//occupyNextNode();

	return nextStep;
}

void Monster::update(float elapsedTime, aPOINT aNextStep)
{
	if (alive) {
	//	if (collide==false) {
			Position = aNextStep;

			relatPosition.x = thePlayer->getRelatPosition()->x + (Position.x - thePlayer->getPosition()->x);
			relatPosition.y = thePlayer->getRelatPosition()->y + (Position.y - thePlayer->getPosition()->y);

			shape.left = Position.x - (size[0] / 2);
			shape.right = Position.x + (size[0] / 2);
			shape.top = Position.y - (size[1] / 2);
			shape.bottom = Position.y + (size[1] / 2);

			//occupyNode();
	}
}
