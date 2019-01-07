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

void Map::fillTheGrid(int mapWidth, int mapHeigth)
{
	gridX = (mapWidth / 30) + 1;
	if (mapWidth % 30 >= 15) {
		gridX++;
	}
	gridY = (mapHeigth / 30) + 1;
	if (mapHeigth % 30 >= 15) {
		gridX++;
	}

	mGrid = new Node*[gridY];
	for (i = 0; i < gridX; i++) {
		mGrid[i] = new Node[gridX];
	}

	nextGrid = new Node*[gridY];
	for (i = 0; i < gridX; i++) {
		nextGrid[i] = new Node[gridX];
	}
	for (i = 0; i < gridY; i++) {
		for (j = 0; j < gridX; j++) {
			mGrid[i][j].centerPosition.x = (j * 30) + 15;
			mGrid[i][j].centerPosition.y = (i * 30) + 15;

			nextGrid[i][j].centerPosition.x = (j * 30) + 15;
			nextGrid[i][j].centerPosition.y = (i * 30) + 15;
		}
	}
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
