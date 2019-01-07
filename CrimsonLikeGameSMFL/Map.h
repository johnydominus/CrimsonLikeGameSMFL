#pragma once
#include "Player.h"

struct Node {
	bool occupied;
	aPOINT centerPosition;
};

class Map:
	public Object
{
private:
	sf::Sprite mSprite;
	sf::Texture mTexture;

	aPOINT Position;
	aPOINT relatPosition;

	std::vector<float> relatMovement{0,0};
	std::vector<float> size{0,0};

	Player* thePlayer;

	int i, j;

public:
	Map();
	~Map();

	Node** mGrid;
	Node** nextGrid;

	void fillTheGrid(int mapWidth, int mapHeigth);
	int gridX, gridY;
	
	sf::Sprite* getSprite();
	aPOINT* getPosition();
	aPOINT* getRelatPosition();
	std::vector<float>* getSize();

	void setPosition(float x, float y);
	void setRelativePosition(float x, float y);
	void setSize(float x, float y);
	void setPlayer(Player* aPlayer);

	void update();
};

