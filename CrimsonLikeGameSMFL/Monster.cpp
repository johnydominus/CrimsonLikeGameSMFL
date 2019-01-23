#include "pch.h"
#include "Monster.h"


Monster::Monster()
{
	mTexture.loadFromFile("img/player-monster.png");
	mSprite.setTexture(mTexture);
	alive = true;

	for (i = 0; i < 8; i++) {
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

void Monster::setPosition(float x, float y)
{
	Position.x = x;
	Position.y = y;
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

void Monster::occupyNode() {

	theMap->mGrid[(int)Position.y / 30][(int)Position.x / 30].occupied = true;

	theMap->mGrid[abs((int)(shape.top / 30))][abs((int)(shape.left / 30))].occupied = true;

	if (abs((int)(shape.right / 30)) <= theMap->gridX) {
		theMap->mGrid[abs((int)(shape.top / 30))][abs((int)(shape.right / 30))].occupied = true;
	}
	if ((abs((int)shape.bottom / 30)) <= theMap->gridY) {
		theMap->mGrid[abs((int)shape.bottom / 30)][abs((int)(shape.left / 30))].occupied = true;
		if ((abs((int)shape.right / 30)) <= theMap->gridX) {
			theMap->mGrid[abs((int)shape.bottom / 30)][abs((int)(shape.right / 30))].occupied = true;
		}
	}
	mNode.y = Position.y / 30;
	mNode.x = Position.x / 30;
}

void Monster::update()
{
	if (alive) {
		nextStep = Position;
		playerPosition = *(thePlayer->getPosition());

		direction[0] = playerPosition.x - Position.x;
		direction[1] = playerPosition.y - Position.y;

		pathLength = sqrt(pow(direction[0], 2) + pow(direction[1], 2));

		direction[0] /= pathLength;
		direction[1] /= pathLength;

		vSpeed[0] = (direction[0] * speed) / 10.0;
		vSpeed[1] = (direction[1] * speed) / 10.0;

		nextStep.x += vSpeed[0];
		nextStep.y += vSpeed[1];

		mNextNode.y = nextStep.y / 30;
		mNextNode.x = nextStep.x / 30;

		if (theMap->mGrid[abs((int)mNextNode.y)][abs((int)mNextNode.x)].occupied == true) {
			int i, a, b;
			for (i = 0; i < 8; i++) {
				for (a = -1; a < 2; a++) {
					for (b = -1; b < 2; b++) {
						if ((a == 0 && b == 0) && (((mNode.y + a) == mNextNode.y) && ((mNode.x + b) == mNextNode.x))) {
							continue;
						}
						else {
							if ((((mNode.y + a >= 0) && (mNode.y + a <= theMap->gridY)) && ((mNode.x + b >= 0) && (mNode.x + b <= theMap->gridX)))
							 && ((((int)mNextNode.y + a >= 0) && ((int)mNextNode.y + a <= theMap->gridY)) && (((int)mNextNode.x + b >= 0) && ((int)mNextNode.x + b <= theMap->gridX)))) {
								if ((theMap->mGrid[(int)(mNode.y + a)][(int)(mNode.x + b)].occupied == false) 
								 && (theMap->nextGrid[(int)mNode.y + a][(int)mNode.x + b].occupied == false)) {
									playerPosition = *(thePlayer->getPosition());

									direction[0] = theMap->mGrid[(int)(mNode.y + a)][(int)(mNode.x + b)].centerPosition.x - Position.x;
									direction[1] = theMap->mGrid[(int)(mNode.y + a)][(int)(mNode.x + b)].centerPosition.y - Position.y;
									theMap->mGrid[(int)mNode.y + a][(int)mNextNode.x + b].occupied = true;

									pathLength = sqrt(pow(direction[0], 2) + pow(direction[1], 2));

									direction[0] /= pathLength;
									direction[1] /= pathLength;

									vSpeed[0] = (direction[0] * speed) / 10.0;
									vSpeed[1] = (direction[1] * speed) / 10.0;
								}
							}
						}
					}
				}
			}
		}
		else {
			Position = nextStep;
		}
	}

	Position.x += vSpeed[0];
	Position.y += vSpeed[1];

	shape.left = Position.x - (size[0] / 2);
	shape.right = Position.x + (size[0] / 2);
	shape.top = Position.y - (size[1] / 2);
	shape.bottom = Position.y + (size[1] / 2);

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

	occupyNode();	
}
