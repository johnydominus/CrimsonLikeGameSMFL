#pragma once

#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <vector>
#include "SFML/Graphics.hpp"
#include <Windows.h> 

class Object
{
private:
	sf::Texture mTexture;

public:
	Object();
	~Object();

	POINT Position;
	POINT relatPosition;
	sf::Sprite mSprite;

	virtual POINT* getPosition() = 0;
	virtual POINT* getRelatPosition() = 0;
	virtual sf::Sprite getSprite() = 0;

	virtual void setRelativePosition(float x, float y) = 0;
};

#endif // !OBJECT_H