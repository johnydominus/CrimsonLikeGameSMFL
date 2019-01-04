#pragma once
#include "Player.h"

class Map:
	public Object
{
private:
	std::vector<float> relatMovement{0,0};
	std::vector<float> size{0,0};
	sf::Texture mTexture;
	Player* thePlayer;

public:
	Map();
	~Map();

	POINT Position;
	POINT relatPosition;
	sf::Sprite mSprite;

	POINT* getPosition();
	POINT* getRelatPosition();
	std::vector<float>* getSize();
	sf::Sprite getSprite();

	void setPosition(float x, float y);
	void setRelativePosition(float x, float y);
	void setRelativePosition(int x, int y);
	void setSize(float x, float y);
	void setSize(int x, int y);
	void setPlayer(Player* aPlayer);

	void update();
};

