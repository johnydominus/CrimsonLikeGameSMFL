#pragma once
#include "Player.h"

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

public:
	Map();
	~Map();

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

