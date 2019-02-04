#pragma once
#include "Player.h"
#include "Monster.h"
#include <deque>

class Map:
	public Object
{
private:
	sf::Sprite mSprite;
	sf::Texture mTexture;

	aPOINT Position;
	aPOINT relatPosition;
	aPOINT nodeSize;
	aRECT monsterNodes;

	std::vector<float> relatMovement{0,0};
	std::vector<float> size{0,0};

	Monster* allMonsters;
	Player* thePlayer;

	int secureZone = 399;

public:
	Map();
	~Map();

	int gridX, gridY, enemiesNumber, enemiesAlive;
	Node** mGrid;

	sf::Sprite squareSprite;
	sf::Texture squareTextureRed;
	sf::Texture squareTextureGreen;

	void setPosition(float x, float y) override;
	void setRelativePosition(float x, float y) override;

	void setSize(float x, float y);
	void setPlayer(Player* aPlayer);
	void fillTheGrid(int mapWidth, int mapHeigth);
	void setEnemiesRandomSpeed();
	void setMonsterRandomPosition();
	void createEnemies();

	void killMonster(int ID, Bullet * aBullet);
	void defineNodeSize();
	void occupyNode(int ID);
	void deocuppyMap();
	void freeNode(int ID);
	bool isValid(int nodeX, int nodeY);
	Node findBestNode(int ID);

	void setNodesShape(int ID);
	
	sf::Sprite* getSprite() override;
	bool nodesFree(int ID);
	aPOINT* getPosition() override;
	aPOINT* getRelatPosition() override;
	std::vector<float>* getSize();
	Monster* getMonster(int i);

	void update();
};