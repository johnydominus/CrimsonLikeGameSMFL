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
	mapSpritesYnumber = ((mapY+windowY) / theMap.getSprite()->getTexture()->getSize().y) + 1;
	mapSpritesXnumber = ((mapX+windowX) / theMap.getSprite()->getTexture()->getSize().x) + 1;
	mapSprites = new sf::Sprite*[mapSpritesYnumber];
	for (auto i = 0; i < mapSpritesYnumber; i++) {
		mapSprites[i] = new sf::Sprite[mapSpritesXnumber];
		for (auto j = 0; j < mapSpritesXnumber; j++) {
			mapSprites[i][j].setTexture(*theMap.getSprite()->getTexture());
		}
	}

	//setting fence sprites
	theFenceTexture.loadFromFile("img/fence.png");

	fenceSpritesXnumber = (((mapX / theFenceTexture.getSize().x)+1)*2);
	fenceSpritesYnumber = (((mapY / theFenceTexture.getSize().x)+1)*2);

	fenceSpritesX = new sf::Sprite[fenceSpritesXnumber];
	fenceSpritesY = new sf::Sprite[fenceSpritesYnumber];

	for (auto i = 0; i < fenceSpritesXnumber; i++)
		fenceSpritesX[i].setTexture(theFenceTexture);

	for (auto i = 0; i < fenceSpritesYnumber; i++) {
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
	enemiesNumberStart = theMap.enemiesNumber;

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
	theMap.createEnemies();
	theMap.defineNodeSize();
	theMap.fillTheGrid(mapX, mapY);

	//monsters
	theMap.enemiesAlive = theMap.enemiesNumber;
	theMap.setMonsterRandomPosition();
	theMap.setEnemiesRandomSpeed();

	//bullets
	thePlayer.fillAmmo();

	for (auto i = 0; i < theMap.enemiesNumber; i++)
		theMap.getMonster(i)->setPlayer(&thePlayer);

	for (auto i = 0; i < thePlayer.ammoNumber; i++) {
		thePlayer.getBullet(i)->setReticle(&theReticle);
		thePlayer.getBullet(i)->setMapSize(*theMap.getSize());
		thePlayer.getBullet(i)->setPosition(thePlayer.getPosition()->x,thePlayer.getPosition()->y);
	}
}	

Engine::~Engine()
{
	delete[] fenceSpritesX;
	delete[] fenceSpritesY;
	for (auto i = 0; i < mapSpritesYnumber; i++)
		delete[] mapSprites[i];
	delete[] mapSprites;
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

void Engine::setWindowSize(int widthWindow, int heightWindow){
	
	if (widthWindow&&heightWindow) {
		windowX = widthWindow;
		windowY = heightWindow;
	}
	else
	{
		auto i = rand() % 11;

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
		auto i = rand() % 22;

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
		theMap.enemiesNumber = enemiesN;
	}
	else {
		theMap.enemiesNumber = (rand() % 30) + 1;
	}
}