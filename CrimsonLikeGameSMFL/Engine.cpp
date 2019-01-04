#include "pch.h"
#include "Engine.h"


Engine::Engine(int widthWindow, int heightWindow, int mapWidth, int mapHeight, int ammoN, int enemiesN)
{
	//setting game values
	setWindowSize(widthWindow, heightWindow);
	setMapSize(mapWidth, mapHeight);
	setAmmoNumber(ammoN);
	setEnemiesNumber(enemiesN);

	//setting map sprites
	a = ((mapY+windowY) / theMap.getSprite()->getTexture()->getSize().y) + 1;
	b = ((mapX+windowX) / theMap.getSprite()->getTexture()->getSize().x) + 1;
	mapSprites = new sf::Sprite*[a];
	for (i = 0; i < a; i++) {
		mapSprites[i] = new sf::Sprite[b];
		for (j = 0; j < b; j++) {
			mapSprites[i][j].setTexture(*theMap.getSprite()->getTexture());
		}
	}

	//setting fence sprites
	theFenceTexture.loadFromFile("img/fence.png");

	c = (((mapX / theFenceTexture.getSize().x)+1)*2);
	d = (((mapY / theFenceTexture.getSize().x)+1)*2);

	fenceSpritesX = new sf::Sprite[c];
	fenceSpritesY = new sf::Sprite[d];

	for (i = 0; i < c; i++)
		fenceSpritesX[i].setTexture(theFenceTexture);

	for (i = 0; i < d; i++) {
		fenceSpritesY[i].setTexture(theFenceTexture);
		fenceSpritesY[i].setRotation(90);
	}

	//setting HUD text
	theFont.loadFromFile("img/MajorMonoDisplayRegular.ttf");
	hud.setFont(theFont);
	hud.setCharacterSize(12);
	hud.setFillColor(sf::Color::Black);

	//setting window
	mWindow.create(sf::VideoMode(windowX, windowY), "CrimsonLikeGame", sf::Style::Default);

	//record start game values, we'll use this parameters for restarting the game, when player dies
	if (mapWidth&&mapHeight) {
		mapXstart = mapWidth;
		mapYstart = mapHeight;
	}

	if (ammoN)
		ammoNumberStart = ammoN;

	if (enemiesN)
		enemiesNumberStart = enemiesN;

	//creating data storage needed for monsters collision handling
	enemiesNextSteps = new aPOINT[enemiesNumber];
	monstersCollide = new bool[enemiesNumber];

	//setting game objects
	//player
	thePlayer.setPosition(mapX / 2, mapY / 2);
	thePlayer.setRelativePosition(windowX / 2, windowY / 2);
	thePlayer.setMapSize(mapX, mapY);

	//map
	int mapRelX, mapRelY;
	mapRelX = thePlayer.getRelatPosition()->x - (windowX / 2);
	mapRelY = thePlayer.getRelatPosition()->y - (windowY / 2);

	theMap.setRelativePosition(mapRelX, mapRelY);
	theMap.setSize(mapX, mapY);
	theMap.setPlayer(&thePlayer);

	//reticle
	theReticle.setPlayer(&thePlayer);

	//monsters
	allMonsters = new Monster[enemiesNumber];
	enemiesAlive = enemiesNumber;

	setMonsterRandomPosition();
	for (i = 0; i < enemiesNumber; i++) {
		allMonsters[i].setPlayer(&thePlayer);
		allMonsters[i].setMap(&theMap);
	}
	setEnemiesRandomSpeed();

	//bullets
	bullets = new Bullet[ammoNumber];

	for (i = 0; i < ammoNumber; i++) {
		bullets[i].setPlayer(&thePlayer);
		bullets[i].setReticle(&theReticle);
		bullets[i].setMap(&theMap);
		bullets[i].setMapSize(*theMap.getSize());
		bullets[i].setPosition(thePlayer.getPosition()->x,thePlayer.getPosition()->y);
	}
}	

Engine::~Engine()
{
	delete mapSprites;
	//delete bullets;
	//delete allMonsters;
	delete enemiesNextSteps;
	delete monstersCollide;
}

void Engine::start()
{
	time(&previous_shot);
	sf::Clock clock;

	//game loop
	while (mWindow.isOpen()) {
		sf::Time dt = clock.restart();
		float dtAsSeconds = dt.asSeconds();

		input();
		update(dtAsSeconds);
		draw();
	}
}

void Engine::killMonster(Monster* aMonster, Bullet* aBullet)
{
	//if (((aBullet->getPosition()->x >= aMonster->getShape()->left) && (aBullet->getPosition()->x <= aMonster->getShape()->right)) && ((aBullet->getPosition()->y >= aMonster->getShape()->bottom) && (aBullet->getPosition()->y <= aMonster->getShape()->top))) {
	//	aMonster->setAlive(false);
	//	aBullet->setShot(false);
	//	enemiesAlive--;
	//}
}

void Engine::killPlayer(Monster *aMonster)
{
	if (sqrt(pow(thePlayer.getPosition()->x - aMonster->getPosition()->x, 2) + pow(thePlayer.getPosition()->y - aMonster->getPosition()->y, 2)) < 27.5) {
		thePlayer.setAlive(false);
	}
}

void Engine::shoot(Bullet* aBullet)
{
	time(&current_shot);
	if (difftime(current_shot, previous_shot) > 0.1) {
		aBullet->shoot();
		previous_shot = current_shot;
		ammoNumber--;
	}
}

Bullet * Engine::getBullet(int i)
{
	return &bullets[i];
}

void Engine::setWindowSize(int widthWindow, int heightWindow){
	
	if (windowX&&windowY) {
		windowX = widthWindow;
		windowY = heightWindow;
	}
	else
	{
		srand(time(NULL));
		i = rand() % 11;

		switch (i)
		{
		case 0: {
			windowX = 480;
			windowY = 360;
			break;
		}
		case 1: {
			windowX = 640;
			windowY = 360;
			break;
		}
		case 2: {
			windowX = 640;
			windowY = 480;
			break;
		}
		case 3: {
			windowX = 854;
			windowY = 480;
			break;
		}
		case 4: {
			windowX = 800;
			windowY = 600;
			break;
		}
		case 5: {
			windowX = 1024;
			windowY = 600;
			break;
		}
		case 6: {
			windowX = 1136;
			windowY = 640;
			break;
		}
		case 7: {
			windowX = 1280;
			windowY = 720;
			break;
		}
		case 8: {
			windowX = 1280;
			windowY = 720;
			break;
		}
		case 9: {
			windowX = 1600;
			windowY = 900;
			break;
		}
		case 10: {
			windowX = 1280;
			windowY = 1024;
			break;
		}
		default:
			break;
		}
	}
}

void Engine::setMapSize(float mapWidth, float mapHeight)
{
	if (mapWidth&&mapHeight) {
		mapX = mapWidth;
		mapY = mapHeight;
	}
	else
	{
		srand(time(NULL));
		i = rand() % 22;

		switch (i)
		{
		case 0: {
			mapX = 400;
			mapY = 400;
			break;
		}
		case 1: {
			mapX = 400;
			mapY = 600;
			break;
		}
		case 2: {
			mapX = 400;
			mapY = 800;
			break;
		}
		case 3: {
			mapX = 400;
			mapY = 1000;
			break;
		}
		case 4: {
			mapX = 600;
			mapY = 600;
			break;
		}
		case 5: {
			mapX = 600;
			mapY = 800;
			break;
		}
		case 6: {
			mapX = 600;
			mapY = 1000;
			break;
		}
		case 7: {
			mapX = 600;
			mapY = 1200;
			break;
		}
		case 8: {
			mapX = 800;
			mapY = 800;
			break;
		}
		case 9: {
			mapX = 800;
			mapY = 1000;
			break;
		}
		case 10: {
			mapX = 800;
			mapY = 1200;
			break;
		}
		case 11: {
			mapX = 800;
			mapY = 1400;
			break;
		}
		case 12: {
			mapX = 1000;
			mapY = 1000;
			break;
		}
		case 13: {
			mapX = 1000;
			mapY = 1200;
			break;
		}
		case 14: {
			mapX = 1000;
			mapY = 1400;
			break;
		}
		case 15: {
			mapX = 1000;
			mapY = 1600;
			break;
		}
		case 16: {
			mapX = 1200;
			mapY = 1200;
			break;
		}
		case 17: {
			mapX = 1200;
			mapY = 1400;
			break;
		}
		case 18: {
			mapX = 1400;
			mapY = 1400;
			break;
		}
		case 19: {
			mapX = 1400;
			mapY = 1600;
			break;
		}
		case 20: {
			mapX = 1400;
			mapY = 1800;
			break;
		}
		case 21: {
			mapX = 1400;
			mapY = 2000;
			break;
		}
		default:
			break;
		}
	}
}

void Engine::setAmmoNumber(int ammoN)
{
	if (ammoN) {
		ammoNumber = ammoN;
	}
	else {
		srand(time(NULL));
		ammoNumber = (rand() % 30) + 1;
	}
}

void Engine::setEnemiesNumber(int enemiesN)
{
	if (enemiesN) {
		enemiesNumber = enemiesN;
	}
	else {
		srand(time(NULL));
		enemiesNumber = (rand() % 30) + 1;
	}
}

void Engine::setEnemiesRandomSpeed() {
	srand(time(NULL));
	int randomEnemiesSpeed = (rand() % 7) + 1;
	for (i = 0; i < enemiesNumber; i++)
		allMonsters[i].setSpeed((float)randomEnemiesSpeed);
}

void Engine::setMonsterRandomPosition() {
	
	srand(time(NULL));
	
	std::vector<float> mapSize = *(theMap.getSize());
	bool spawnCollide;
	
	for (i = 0; i < enemiesNumber; i++) {
		spawnCollide = false;
		std::vector<float> monsterSize;
		monsterSize = *(allMonsters[i].getSize());
		allMonsters[i].getPosition()->x = rand() % (int)(mapSize[0]-secureZone);
		allMonsters[i].getPosition()->y = rand() % (int)(mapSize[1]-secureZone);

		allMonsters[i].getShape()->left = allMonsters[i].getPosition()->x - (monsterSize[0] / 2);
		allMonsters[i].getShape()->right = allMonsters[i].getPosition()->x + (monsterSize[0] / 2);
		allMonsters[i].getShape()->top = allMonsters[i].getPosition()->y - (monsterSize[1] / 2);
		allMonsters[i].getShape()->bottom = allMonsters[i].getPosition()->y + (monsterSize[1] / 2);

		for (j = i; j >= 0; j--) {
			do {
				if (j != i) {
					if((((allMonsters[i].getShape()->left <= allMonsters[j].getShape()->right) && (allMonsters[i].getShape()->left >= allMonsters[j].getShape()->left)) || ((allMonsters[i].getShape()->right <= allMonsters[j].getShape()->right) && (allMonsters[i].getShape()->right >= allMonsters[j].getShape()->left))) && (((allMonsters[i].getShape()->bottom <= allMonsters[j].getShape()->top) && (allMonsters[i].getShape()->bottom >= allMonsters[j].getShape()->top)) || ((allMonsters[i].getShape()->bottom <= allMonsters[j].getShape()->top) && (allMonsters[i].getShape()->bottom >= allMonsters[j].getShape()->bottom))))
					spawnCollide = true;			
				}
				if (spawnCollide == true) {
					allMonsters[i].getPosition()->x = rand() % (int)(mapSize[0] - secureZone);
					allMonsters[i].getPosition()->y = rand() % (int)(mapSize[1] - secureZone);

					allMonsters[i].getShape()->left = allMonsters[i].getPosition()->x - (monsterSize[0] / 2);
					allMonsters[i].getShape()->right = allMonsters[i].getPosition()->x + (monsterSize[0] / 2);
					allMonsters[i].getShape()->top = allMonsters[i].getPosition()->y - (monsterSize[1] / 2);
					allMonsters[i].getShape()->bottom = allMonsters[i].getPosition()->y + (monsterSize[1] / 2);

					spawnCollide = false;
				}
			} while (spawnCollide == true);
		}
	}
}