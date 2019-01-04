#include "pch.h"
#include "Engine.h"

void Engine::input() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		mWindow.close();
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		thePlayer.moveLeft();
	}
	else {
		thePlayer.stopLeft();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		thePlayer.moveRight();
	}
	else {
		thePlayer.stopRight();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		thePlayer.moveUp();
	}
	else {
		thePlayer.stopUp();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		thePlayer.moveDown();
	}
	else {
		thePlayer.stopDown();
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		mouseButtonPressed = true;
	}
	else {
		mouseButtonPressed = false;
	}
}