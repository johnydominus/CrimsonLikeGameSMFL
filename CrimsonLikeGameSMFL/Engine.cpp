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
	a = ((mapY+windowY) / theMap.mSprite.getTexture()->getSize().y) + 1;
	b = ((mapX+windowX) / theMap.mSprite.getTexture()->getSize().x) + 1;
	mapSprites = new sf::Sprite*[a];
	for (i = 0; i < a; i++) {
		mapSprites[i] = new sf::Sprite[b];
		for (j = 0; j < b; j++) {
			mapSprites[i][j].setTexture(*theMap.mSprite.getTexture());
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
	enemiesNextSteps = new POINT[enemiesNumber];
	monstersCollide = new bool[enemiesNumber];

	//setting game objects
	//player
	thePlayer.setPosition(mapX / 2, mapY / 2);
	thePlayer.setRelativePosition(windowX / 2, windowY / 2);
	thePlayer.setMapSize(mapX, mapY);

	//map
	int mapRelX, mapRelY;
	mapRelX = thePlayer.relatPosition.x - (windowX / 2);
	mapRelY = thePlayer.relatPosition.y - (windowY / 2);

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
		bullets[i].mapSize = *(theMap.getSize());
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
	if (((aBullet->Position.x >= aMonster->shape.left) && (aBullet->Position.x <= aMonster->shape.right)) && ((aBullet->Position.y >= aMonster->shape.bottom) && (aBullet->Position.y <= aMonster->shape.top))) {
		aMonster->setAlive(false);
		aBullet->setShot(false);
		enemiesAlive--;
	}
}

void Engine::killPlayer(Monster *aMonster)
{
	if ((((thePlayer.shape.left <= aMonster->shape.right) && (thePlayer.shape.left >= aMonster->shape.left)) || ((thePlayer.shape.right <= aMonster->shape.right) && (thePlayer.shape.right >= aMonster->shape.left))) && (((thePlayer.shape.bottom <= aMonster->shape.top) && (thePlayer.shape.bottom >= aMonster->shape.bottom)) || ((thePlayer.shape.top <= aMonster->shape.top) && (thePlayer.shape.top >= aMonster->shape.bottom)))) {
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
	int randomEnemiesSpeed = (rand() % 10) + 1;
	for (i = 0; i < enemiesNumber; i++)
		allMonsters[i].setSpeed(randomEnemiesSpeed);
}

void Engine::setMonsterRandomPosition() {
	
	srand(time(NULL));
	
	std::vector<float> mapSize = *(theMap.getSize());
	bool spawnCollide;
	
	for (i = 0; i < enemiesNumber; i++) {
		spawnCollide = false;
		std::vector<float> monsterSize;
		monsterSize = *(allMonsters[i].getSize());
		allMonsters[i].Position.x = rand() % (int)(mapSize[0]-secureZone);
		allMonsters[i].Position.y = rand() % (int)(mapSize[1]-secureZone);

		allMonsters[i].shape.left = allMonsters[i].Position.x - (monsterSize[0] / 2);
		allMonsters[i].shape.right = allMonsters[i].Position.x + (monsterSize[0] / 2);
		allMonsters[i].shape.top = allMonsters[i].Position.y - (monsterSize[1] / 2);
		allMonsters[i].shape.bottom = allMonsters[i].Position.y + (monsterSize[1] / 2);

		for (j = i; j >= 0; j--) {
			do {
				if (j != i) {
					if((((allMonsters[i].shape.left <= allMonsters[j].shape.right) && (allMonsters[i].shape.left >= allMonsters[j].shape.left)) || ((allMonsters[i].shape.right <= allMonsters[j].shape.right) && (allMonsters[i].shape.right >= allMonsters[j].shape.left))) && (((allMonsters[i].shape.bottom <= allMonsters[j].shape.top) && (allMonsters[i].shape.bottom >= allMonsters[j].shape.top)) || ((allMonsters[i].shape.bottom <= allMonsters[j].shape.top) && (allMonsters[i].shape.bottom >= allMonsters[j].shape.bottom))))
					spawnCollide = true;			
				}
				if (spawnCollide == true) {
					allMonsters[i].Position.x = rand() % (int)(mapSize[0] - secureZone);
					allMonsters[i].Position.y = rand() % (int)(mapSize[1] - secureZone);

					allMonsters[i].shape.left = allMonsters[i].Position.x - (monsterSize[0] / 2);
					allMonsters[i].shape.right = allMonsters[i].Position.x + (monsterSize[0] / 2);
					allMonsters[i].shape.top = allMonsters[i].Position.y - (monsterSize[1] / 2);
					allMonsters[i].shape.bottom = allMonsters[i].Position.y + (monsterSize[1] / 2);

					spawnCollide = false;
				}
			} while (spawnCollide == true);
		}
	}
}