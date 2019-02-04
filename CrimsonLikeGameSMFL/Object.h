#pragma once

#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <vector>
#include "SFML/Graphics.hpp"
#include <Windows.h> 
#include <memory>

struct aPOINT
{
	float x;
	float y;
};

struct aRECT 
{
	float left;
	float right;
	float top;
	float bottom;
};

struct SCORE
{
	int player;
	int monsters;
};

struct Node {
	bool occupied;
	aPOINT centerPosition;

	int i;
	int j;
	int monsterID;
};

class Object
{
private:
	sf::Sprite mSprite;
	sf::Texture mTexture;
	aPOINT Position;
	aPOINT relatPosition;

public:
	Object();
	~Object();

	virtual aPOINT* getPosition() = 0;
	virtual aPOINT* getRelatPosition() = 0;
	virtual sf::Sprite* getSprite() = 0;

	virtual void setPosition(float x, float y) = 0;
	virtual void setRelativePosition(float x, float y) = 0;
};

#endif // !OBJECT_H