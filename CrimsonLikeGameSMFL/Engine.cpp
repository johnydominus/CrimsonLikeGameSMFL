#include "pch.h"
#include "Engine.h"


Engine::Engine(int widthWindow, int heightWindow, int mapWidth, int mapHeight, int ammoN, int enemiesN)
{
	srand(time(NULL));
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
	theFont.loadFromFile("img/RobotoBlack.ttf");
	hud.setFont(theFont);
	hud.setCharacterSize(12);
	hud.setFillColor(sf::Color::Black);

	//setting window
	mWindow.create(sf::VideoMode(windowX, windowY), "CrimsonLikeGame", sf::Style::Default);

	//record start game values, we'll use this parameters for restarting the game, when player dies
	mapXstart = mapX;
	mapYstart = mapY;
	ammoNumberStart = thePlayer.ammoNumber;
	enemiesNumberStart = enemiesNumber;

	//creating data storage needed for monsters collision handling
	enemiesNextSteps = new aPOINT[enemiesNumber];
	monstersCollide = new bool[enemiesNumber];

	//setting game objects
	//player
	thePlayer.setPosition(mapX / 2, mapY / 2);
	thePlayer.setRelativePosition(windowX / 2, windowY / 2);
	thePlayer.setMapSize(mapX, mapY);
	thePlayer.bulletMax = ammoNumberStart;

	//map
	int mapRelX, mapRelY;
	mapRelX = thePlayer.getRelatPosition()->x - (windowX / 2);
	mapRelY = thePlayer.getRelatPosition()->y - (windowY / 2);

	theMap.setRelativePosition(mapRelX, mapRelY);
	theMap.setSize(mapX, mapY);
	theMap.setPlayer(&thePlayer);
	theMap.fillTheGrid(mapX, mapY);

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
	thePlayer.bullets = new Bullet[thePlayer.ammoNumber];

	for (i = 0; i < thePlayer.ammoNumber; i++) {
		thePlayer.bullets[i].setReticle(&theReticle);
		thePlayer.bullets[i].setMapSize(*theMap.getSize());
		thePlayer.bullets[i].setPosition(thePlayer.getPosition()->x,thePlayer.getPosition()->y);
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
	if (sqrt(pow(aBullet->getPosition()->x - aMonster->getPosition()->x, 2) + pow(aBullet->getPosition()->y - aMonster->getPosition()->y,2 ))< 15.0) {
		aMonster->setAlive(false);
		aBullet->setShot(false);
		enemiesAlive--;
	}
}

void Engine::killPlayer(Monster *aMonster)
{
	if (sqrt(pow(thePlayer.getPosition()->x - aMonster->getPosition()->x, 2) + pow(thePlayer.getPosition()->y - aMonster->getPosition()->y, 2)) < 27.5) {
		thePlayer.setAlive(false);
	}
}

void Engine::setWindowSize(int widthWindow, int heightWindow){
	
	if (widthWindow&&heightWindow) {
		windowX = widthWindow;
		windowY = heightWindow;
	}
	else
	{
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
		thePlayer.ammoNumber = ammoN;
	}
	else {
		thePlayer.ammoNumber = (rand() % 30) + 1;
	}
}

void Engine::setEnemiesNumber(int enemiesN)
{
	if (enemiesN) {
		enemiesNumber = enemiesN;
	}
	else {
		enemiesNumber = (rand() % 30) + 1;
	}
}

void Engine::setEnemiesRandomSpeed() {
	int randomEnemiesSpeed = (rand() % 7) + 1;
	for (i = 0; i < enemiesNumber; i++)
		allMonsters[i].setSpeed((float)randomEnemiesSpeed);
}

void Engine::setMonsterRandomPosition() {
	
	std::vector<float> mapSize = *(theMap.getSize());
	bool spawnCollide;
	
	for (i = 0; i < enemiesNumber; i++) {
		spawnCollide = false;
		std::vector<float> monsterSize;
		monsterSize = *(allMonsters[i].getSize());

		allMonsters[i].getPosition()->x = rand() % (int)(mapSize[0]-secureZone);
		allMonsters[i].getPosition()->y = rand() % (int)(mapSize[1] - secureZone);

		if ((allMonsters[i].getPosition()->x > ((mapSize[0] / 2) - (secureZone / 2)) && (allMonsters[i].getPosition()->x < ((mapSize[0] / 2) + (secureZone / 2)))) && (allMonsters[i].getPosition()->y > ((mapSize[1] / 2) - (secureZone / 2)) && (allMonsters[i].getPosition()->y < ((mapSize[1] / 2) + (secureZone / 2))))) {
			if(rand()%2+1)
				allMonsters[i].getPosition()->x +=secureZone;
			else
				allMonsters[i].getPosition()->y += secureZone;
		}

		//allMonsters[i].getShape()->left = allMonsters[i].getPosition()->x - monsterSize[0] * 0.5;
		//allMonsters[i].getShape()->right = allMonsters[i].getPosition()->x + monsterSize[0] * 0.5;
		//allMonsters[i].getShape()->top = allMonsters[i].getPosition()->y - monsterSize[1] * 0.5;
		//allMonsters[i].getShape()->bottom = allMonsters[i].getPosition()->y + monsterSize[1] * 0.5;

		//allMonsters[i].occupyNode();



		for (j = i; j >= 0; j--) {
			do {
				if (j != i) {
					if((((allMonsters[i].getShape()->left <= allMonsters[j].getShape()->right) && (allMonsters[i].getShape()->left >= allMonsters[j].getShape()->left)) || ((allMonsters[i].getShape()->right <= allMonsters[j].getShape()->right) && (allMonsters[i].getShape()->right >= allMonsters[j].getShape()->left))) && (((allMonsters[i].getShape()->bottom <= allMonsters[j].getShape()->top) && (allMonsters[i].getShape()->bottom >= allMonsters[j].getShape()->top)) || ((allMonsters[i].getShape()->bottom <= allMonsters[j].getShape()->top) && (allMonsters[i].getShape()->bottom >= allMonsters[j].getShape()->bottom))))
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
		}
		allMonsters[i].getShape()->left = allMonsters[i].getPosition()->x - 15;
		allMonsters[i].getShape()->right = allMonsters[i].getPosition()->x + 15;
		allMonsters[i].getShape()->top = allMonsters[i].getPosition()->y - 15;
		allMonsters[i].getShape()->bottom = allMonsters[i].getPosition()->y + 15;

		//allMonsters[i].occupyNode();
	}
}