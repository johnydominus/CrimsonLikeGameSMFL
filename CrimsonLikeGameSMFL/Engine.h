#pragma once
#include "Object.h"
#include "Player.h"
#include "Map.h"
#include "Reticle.h"
#include "Monster.h"
#include "Bullet.h"
#include <ctime>
#include <chrono>
#include <sstream>
#include "SFML/Graphics.hpp"

class Engine
{
private:
	sf::RenderWindow mWindow;

	Player thePlayer;
	Map theMap;
	Reticle theReticle;

	sf::Sprite** mapSprites;
	sf::Sprite* fenceSpritesX;
	sf::Sprite* fenceSpritesY;
	sf::Texture theFenceTexture;
	sf::Text hud;
	sf::Font theFont;

	SCORE score{0,0};

	float spriteSizeX, spriteSizeY;

	int mapSpritesYnumber, mapSpritesXnumber, fenceSpritesXnumber, fenceSpritesYnumber, windowX, windowY, mapX, mapY;
	int mapXstart=0, mapYstart=0, ammoNumberStart=0, enemiesNumberStart=0;

	void input();
	void update(float timeInSeconds);
	void draw();

	void setWindowSize(int mapX, int mapY);
	void setMapSize(float mapWidth, float mapHeight);
	void setAmmoNumber(int ammoN);
	void setEnemiesNumber(int enemiesN);

public:
	Engine(int widthWindow = 0, int heightWindow = 0, int mapWidth = 0, int mapHeight = 0, int ammoN = 0, int enemiesN = 0);
	~Engine();

	void start();
};

