#include "pch.h"
#include "Engine.h"

void Engine::draw() {
	mWindow.clear(sf::Color::White);
	
	//preparing map draw
	spriteSizeY = 0;
	for (i = 0; i < a; i ++) {
		spriteSizeX = 0;
		for (j = 0; j < b; j ++) {
			mapSprites[i][j].setPosition(theMap.getRelatPosition()->x /*- (windowX / 2)*/ + spriteSizeX, theMap.getRelatPosition()->y /*- (windowY / 2)*/ + spriteSizeY);
			mWindow.draw(mapSprites[i][j]);
			//theMap.mSprite.setPosition(theMap.relatPosition.x, theMap.relatPosition.y);
			//mWindow.draw(theMap.getSprite());
			spriteSizeX += theMap.getSprite()->getTexture()->getSize().x;
		}
		spriteSizeY+=theMap.getSprite()->getTexture()->getSize().y;
	}
	
	//preparing fence draw
	spriteSizeX = 0;
	for (i = 0; i < c / 2; i++) {
		fenceSpritesX[i].setPosition(theMap.getRelatPosition()->x + ((float)windowX / 2.0) + spriteSizeX - theFenceTexture.getSize().y, theMap.getRelatPosition()->y + ((float)windowY / 2.0) - theFenceTexture.getSize().y);
		mWindow.draw(fenceSpritesX[i]);
		spriteSizeX += theFenceTexture.getSize().x;
	}
	spriteSizeX = 0;
	for (i = c / 2; i < c; i++) {
		fenceSpritesX[i].setPosition(theMap.getRelatPosition()->x + (windowX / 2) + spriteSizeX, theMap.getRelatPosition()->y + (windowY / 2) + mapY);
		mWindow.draw(fenceSpritesX[i]);
		spriteSizeX += theFenceTexture.getSize().x;
	}

	spriteSizeY = 0;
	for (i = 0; i < d / 2; i++) {
		fenceSpritesY[i].setPosition(theMap.getRelatPosition()->x + ((float)windowX / 2.0), theMap.getRelatPosition()->y + ((float)windowY / 2.0) + spriteSizeY);
		mWindow.draw(fenceSpritesY[i]);
		spriteSizeY += theFenceTexture.getSize().x;
	}
	spriteSizeY = 0;
	for (i = d / 2; i < d; i++) {
		fenceSpritesY[i].setPosition(theMap.getRelatPosition()->x + ((float)windowX / 2.0) + (float)mapX +theFenceTexture.getSize().y, theMap.getRelatPosition()->y + ((float)windowY / 2.0) + spriteSizeY);
		mWindow.draw(fenceSpritesY[i]);
		spriteSizeY += theFenceTexture.getSize().x;
	}

	//preparing player draw
	angle = -(atan2(theReticle.getScreenPosition()->x - thePlayer.getRelatPosition()->x, theReticle.getScreenPosition()->y - thePlayer.getRelatPosition()->y) * 180.0 / 3.141592);
	thePlayer.getSprite()->setPosition (thePlayer.getRelatPosition()->x, thePlayer.getRelatPosition()->y);
	thePlayer.getSprite()->setRotation(angle);
	mWindow.draw(*thePlayer.getSprite());

	//preparing reticle draw
	theReticle.getSprite()->setPosition(theReticle.getScreenPosition()->x, theReticle.getScreenPosition()->y);
	mWindow.draw(*theReticle.getSprite());
	
	//preparing monsters draw
	for (i = 0; i < enemiesNumber; i++) {
		if (*allMonsters[i].isAlive()) {
			angle = -(atan2(thePlayer.getRelatPosition()->x - allMonsters[i].getRelatPosition()->x, thePlayer.getRelatPosition()->y - allMonsters[i].getRelatPosition()->y) * 180.0 / 3.141592);
			allMonsters[i].getSprite()->setPosition(allMonsters[i].getRelatPosition()->x, allMonsters[i].getRelatPosition()->y);
			allMonsters[i].getSprite()->setRotation(angle);
			mWindow.draw(*allMonsters[i].getSprite());
		}
	}

	//preparing bullets draw
	for (i = 0; i < ammoNumberStart; i++) {
		if (*thePlayer.bullets[i].isShot()) {
			thePlayer.bullets[i].getSprite()->setPosition(thePlayer.bullets[i].getRelatPosition()->x, thePlayer.bullets[i].getRelatPosition()->y);
			mWindow.draw(*thePlayer.bullets[i].getSprite());
		}
	}

	//preparing hud draw
	mWindow.draw(hud);

	//drawing all the stuff
	mWindow.display();
}