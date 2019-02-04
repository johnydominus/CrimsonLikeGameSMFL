#include "pch.h"
#include "Map.h"

Map::Map()
{
	mTexture.loadFromFile("img/background.jpg");
	mSprite.setTexture(mTexture);
	Position.x = 0;
	Position.y = 0;

	squareTextureRed.loadFromFile("img/redsqr.png");
	squareTextureGreen.loadFromFile("img/greensqr.png");
}

Map::~Map()
{
	delete[] allMonsters;
	for (auto i = 0; i < gridY; i++)
		delete[] mGrid[i];
	delete[] mGrid;
}

void Map::createEnemies() 
{
	allMonsters = new Monster[enemiesNumber];
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

Monster* Map::getMonster(int i)
{
	return &allMonsters[i];
}

void Map::killMonster(int ID, Bullet* aBullet)
{
	allMonsters[ID].setAlive(false);
	aBullet->setShot(false);
	enemiesAlive--;
}

void Map::defineNodeSize() 
{
	nodeSize.x = allMonsters[0].getSprite()->getTextureRect().width;
	nodeSize.y = allMonsters[0].getSprite()->getTextureRect().height;
}

void Map::fillTheGrid(int mapWidth, int mapHeigth)
{
	gridX = (mapWidth / nodeSize.x) + 1;
	if (mapWidth % (int)nodeSize.x >= (nodeSize.x/2)) {
		gridX++;
	}
	gridY = (mapHeigth / nodeSize.y) + 1;
	if (mapHeigth % (int)nodeSize.y >= (nodeSize.y/2)) {
		gridY++;
	}

	mGrid = new Node*[gridY];
	for (auto i = 0; i < gridY; i++) {
		mGrid[i] = new Node[gridX];
	}

	for (auto i = 0; i < gridY; i++) {
		for (auto j = 0; j < gridX; j++) {
			mGrid[i][j].occupied = false;
			mGrid[i][j].i = i;
			mGrid[i][j].j = j;
			mGrid[i][j].centerPosition.x = (j * nodeSize.x) + nodeSize.x/2;
			mGrid[i][j].centerPosition.y = (i * nodeSize.y) + nodeSize.y/2;
		}
	}
}

void Map::setEnemiesRandomSpeed() {
	int randomEnemiesSpeed = (rand() % 7) + 1;
	for (auto i = 0; i < enemiesNumber; i++)
		allMonsters[i].setSpeed((float)randomEnemiesSpeed);
}

void Map::setMonsterRandomPosition() {

	std::vector<float> mapSize = size;

	for (auto i = 0; i < enemiesNumber; i++) {

		allMonsters[i].getPosition()->x = rand() % (int)(mapSize[0] - secureZone);
		allMonsters[i].getPosition()->y = rand() % (int)(mapSize[1] - secureZone);

		if ((allMonsters[i].getPosition()->x > ((size[0] / 2) - (secureZone / 2)) && 
			(allMonsters[i].getPosition()->x < ((size[0] / 2) + (secureZone / 2)))) &&
			(allMonsters[i].getPosition()->y > ((size[1] / 2) - (secureZone / 2)) && 
			(allMonsters[i].getPosition()->y < ((size[1] / 2) + (secureZone / 2))))) {
			if (rand() % 2 + 1)
				allMonsters[i].getPosition()->x += secureZone;
			else
				allMonsters[i].getPosition()->y += secureZone;
		}

		/*for (auto j = i; j >= 0; j--) {
			do {
				if (j != i) {
					if ((mGrid[(int)(allMonsters[i].getPosition()->y / nodeSize.y)][(int)(allMonsters[i].getPosition()->x / nodeSize.x)].occupied ||
						(mGrid[(int)(allMonsters[i].getPosition()->y / nodeSize.y)][(int)(allMonsters[i].getPosition()->x / nodeSize.x)].monsterID != i)))
						spawnCollide = true;
				}
				if (spawnCollide == true) {
					allMonsters[i].getPosition()->x = rand() % (int)(mapSize[0] - secureZone);
					allMonsters[i].getPosition()->y = rand() % (int)(mapSize[1] - secureZone);

					if ((allMonsters[i].getPosition()->x > ((mapSize[0] / 2) - (secureZone / 2)) && (allMonsters[i].getPosition()->x < ((mapSize[0] / 2) + (secureZone / 2)))) && (allMonsters[i].getPosition()->y > ((mapSize[1] / 2) - (secureZone / 2)) && (allMonsters[i].getPosition()->y < ((mapSize[1] / 2) + (secureZone / 2))))) {
						if (rand() % 2 + 1)
							allMonsters[i].getPosition()->x += secureZone;
						else
							allMonsters[i].getPosition()->y += secureZone;
					}
					spawnCollide = false;
				}
			} while (spawnCollide == true);
		}*/
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

bool Map::isValid(int nodeX, int nodeY)
{
	return (nodeX >= 0) && (nodeX < gridX) &&
		   (nodeY>= 0) && (nodeY < gridY);
}

Node Map::findBestNode(int ID)
{
	Node** nearNodes = new Node*[8];
	//defining nodes surrounding the actual position
	nearNodes[0] = &mGrid[(int)(abs(allMonsters[ID].getPosition()->y/nodeSize.y - 1))]	[(int)(abs(allMonsters[ID].getPosition()->x / nodeSize.x))];
	nearNodes[1] = &mGrid[(int)(abs(allMonsters[ID].getPosition()->y / nodeSize.y + 1))][(int)(abs(allMonsters[ID].getPosition()->x / nodeSize.x))];
	nearNodes[2] = &mGrid[(int)(abs(allMonsters[ID].getPosition()->y / nodeSize.y))]	[(int)(abs(allMonsters[ID].getPosition()->x / nodeSize.x + 1))];
	nearNodes[3] = &mGrid[(int)(abs(allMonsters[ID].getPosition()->y / nodeSize.y))]	[(int)(abs(allMonsters[ID].getPosition()->x / nodeSize.x - 1))];
	nearNodes[4] = &mGrid[(int)(abs(allMonsters[ID].getPosition()->y / nodeSize.y - 1))][(int)(abs(allMonsters[ID].getPosition()->x / nodeSize.x + 1))];
	nearNodes[5] = &mGrid[(int)(abs(allMonsters[ID].getPosition()->y / nodeSize.y - 1))][(int)(abs(allMonsters[ID].getPosition()->x / nodeSize.x - 1))];
	nearNodes[6] = &mGrid[(int)(abs(allMonsters[ID].getPosition()->y / nodeSize.y + 1))][(int)(abs(allMonsters[ID].getPosition()->x / nodeSize.x + 1))];
	nearNodes[7] = &mGrid[(int)(abs(allMonsters[ID].getPosition()->y / nodeSize.y + 1))][(int)(abs(allMonsters[ID].getPosition()->x / nodeSize.x - 1))];

	int* length = new int[8];
	std::unique_ptr<aPOINT> sourcePath(new aPOINT);
	std::unique_ptr<aPOINT> goalPath(new aPOINT);
	std::deque<Node*> bestNodes;

	auto theLength = 9999.0;
	for (auto i = 0; i < 8; i++) {
		if (nodesFree(i)) {
			sourcePath->x	= allMonsters[ID].getPosition()->x			- nearNodes[i]->centerPosition.x;
			sourcePath->y	= allMonsters[ID].getPosition()->y			- nearNodes[i]->centerPosition.y;
			goalPath->x		= allMonsters[ID].getPlayerPosition()->x	- nearNodes[i]->centerPosition.x;
			goalPath->y		= allMonsters[ID].getPlayerPosition()->y	- nearNodes[i]->centerPosition.y;

			length[i] = abs(sqrt(pow(sourcePath->x, 2) + pow(sourcePath->y, 2))) + abs(sqrt(pow(goalPath->x, 2) + pow(goalPath->y, 2)));
			if (length[i] < theLength)
			{
				bestNodes.push_front(nearNodes[i]);
				theLength = length[i];
			}
		}
	}
	Node bestNode;
	if (!bestNodes.empty()) {
		bestNode = *bestNodes[0];
	}
	else {
		auto nodei = (int)(abs(allMonsters[ID].getPosition()->y / nodeSize.y));
		auto nodej = (int)(abs(allMonsters[ID].getPosition()->x / nodeSize.x));

		while (nodei < 0)
			nodei++;
		while (nodei >= gridY)
			nodei--;
		while (nodej < 0)
			nodej++;
		while (nodej >= gridX)
			nodej--;

		bestNode = mGrid[nodei][nodej];
	}
	bestNodes.clear();
		
	return bestNode;

	delete[] nearNodes;
	delete[] length;
}

void Map::setNodesShape(int ID)
{
	monsterNodes.top	= abs(allMonsters[ID].getPosition()->y - (allMonsters[ID].getSprite()->getTextureRect().height / 2)) / nodeSize.y;
	monsterNodes.bottom = abs(allMonsters[ID].getPosition()->y + (allMonsters[ID].getSprite()->getTextureRect().height / 2)) / nodeSize.y;
	monsterNodes.left	= abs(allMonsters[ID].getPosition()->x - (allMonsters[ID].getSprite()->getTextureRect().width / 2)) / nodeSize.x;
	monsterNodes.right	= abs(allMonsters[ID].getPosition()->x + (allMonsters[ID].getSprite()->getTextureRect().width / 2)) / nodeSize.x;
}

void Map::deocuppyMap() {
	for (auto i = 0; i < gridY; i++) {
		for (auto j = 0; j < gridX; j++) {
			mGrid[i][j].occupied = false;
			mGrid[i][j].monsterID = -1;
		}
	}
}
void Map::freeNode(int ID) 
{
	//for (auto i = (int)monsterNodes.top; i < (int)monsterNodes.bottom; i++) {
	//	if (i < gridY && i >= 0) {
	//		for (auto j = (int)monsterNodes.left; j < (int)monsterNodes.right; j++) {
	//			if (j < gridX && j >= 0) {
	//				mGrid[i][j].occupied = false;
	//				mGrid[i][j].monsterID = -1;
	//			}
	//		}
	//	}
	//}
	mGrid[(int)abs(allMonsters[ID].getPosition()->y / nodeSize.y)][(int)abs(allMonsters[ID].getPosition()->x / nodeSize.x)].occupied = false;
	mGrid[(int)abs(allMonsters[ID].getPosition()->y / nodeSize.y)][(int)abs(allMonsters[ID].getPosition()->x / nodeSize.x)].monsterID = -1;

}

void Map::occupyNode(int ID)
{
	//for (auto i = (int)monsterNodes.top; i < (int)monsterNodes.bottom; i++) {
	//	if (i < gridY && i>=0) {
	//		for (auto j = (int)monsterNodes.left; j < (int)monsterNodes.right; j++) {
	//			if (j < gridX && j>=0) {
	//				mGrid[i][j].occupied = true;
	//				mGrid[i][j].monsterID = ID;
	//			}
	//		}
	//	}
	//}
	mGrid[(int)abs(allMonsters[ID].getPosition()->y / nodeSize.y)][(int)abs(allMonsters[ID].getPosition()->x / nodeSize.x)].occupied = true;
	mGrid[(int)abs(allMonsters[ID].getPosition()->y / nodeSize.y)][(int)abs(allMonsters[ID].getPosition()->x / nodeSize.x)].monsterID = ID;
}

bool Map::nodesFree(int ID) 
{
	auto free = true;

	for (auto i = (int)monsterNodes.top; i < (int)monsterNodes.bottom; i++) {
		if (i < gridY && i >= 0) {
			for (auto j = (int)monsterNodes.left; j < (int)monsterNodes.right; j++) {
				if (j < gridX && j >= 0) {
					if (mGrid[i][j].occupied && mGrid[i][j].monsterID != ID)
						free = false;
				}
			}
		}
	}
	return free;
}

void Map::update()
{
	relatMovement = *(thePlayer->getRelatMovement());
	relatPosition.x -= (float)relatMovement[0];
	relatPosition.y -= (float)relatMovement[1];

	//for (auto i = 0; i < gridY; i++) {
	//	for (auto j = 0; j < gridX; j++) {
	//		mGrid[i][j].occupied = false;
	//		mGrid[i][j].monsterID = -1;
	//	}
	//}

	for (auto i = 0; i < enemiesNumber; i++) {
		if (*allMonsters[i].isAlive()) {
			freeNode(i);
			auto nextPosition = allMonsters[i].setMovement();
			if (!mGrid[(int)abs(nextPosition.y / nodeSize.y)][(int)abs(nextPosition.x / nodeSize.x)].occupied
			  || mGrid[(int)abs(nextPosition.y / nodeSize.y)][(int)abs(nextPosition.x / nodeSize.x)].monsterID == i)
				allMonsters[i].update();
			else
				allMonsters[i].updateRelativePosition();
			occupyNode(i);
			//setNodesShape(i);
			//if (nodesFree(i)) {
			//	allMonsters[i].setMovement(findBestNode(i));
			//	freeNode(i);
			//	allMonsters[i].update();
			//	setNodesShape(i);
			//	occupyNode(i);
			//}
		}
	}

	for (auto i = 0; i < thePlayer->bulletNumber; i++) {
		for (auto j = 0; j < enemiesNumber; j++) {
			if ((sqrt(pow(thePlayer->getBullet(i)->getPosition()->x - allMonsters[j].getPosition()->x, 2) + pow(thePlayer->getBullet(i)->getPosition()->y - allMonsters[j].getPosition()->y, 2)) < 15.0)
				&& ((*thePlayer->getBullet(i)->isShot()) && (*allMonsters[j].isAlive()))) {
				killMonster(j, thePlayer->getBullet(i));
				freeNode(j);
			}
		}
	}
}
