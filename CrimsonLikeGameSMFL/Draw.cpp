#include "pch.h"
#include "Engine.h"

void Engine::draw() {
	mWindow.clear(sf::Color::White);
	
	//preparing map draw
	spriteSizeY = 0;
	for (i = 0; i < a; i ++) {
		spriteSizeX = 0;
		for (j = 0; j < b; j ++) {
			mapSprites[i][j].setPosition(theMap.relatPosition.x /*- (windowX / 2)*/ + spriteSizeX, theMap.relatPosition.y /*- (windowY / 2)*/ + spriteSizeY);
			mWindow.draw(mapSprites[i][j]);
			//theMap.mSprite.setPosition(theMap.relatPosition.x, theMap.relatPosition.y);
			//mWindow.draw(theMap.getSprite());
			spriteSizeX += theMap.mSprite.getTexture()->getSize().x;
		}
		spriteSizeY+=theMap.mSprite.getTexture()->getSize().y;
	}
	
	
	//preparing fence draw
	spriteSizeX = 0;
	for (i = 0; i < c / 2; i++) {
		fenceSpritesX[i].setPosition(theMap.relatPosition.x + (windowX / 2) + spriteSizeX - theFenceTexture.getSize().y, theMap.relatPosition.y + (windowY / 2) - theFenceTexture.getSize().y);
		mWindow.draw(fenceSpritesX[i]);
		spriteSizeX += theFenceTexture.getSize().x;
	}
	spriteSizeX = 0;
	for (i = c / 2; i < c; i++) {
		fenceSpritesX[i].setPosition(theMap.relatPosition.x + (windowY / 2) + spriteSizeX, theMap.relatPosition.y + mapY + (windowX / 2));
		mWindow.draw(fenceSpritesX[i]);
		spriteSizeX += theFenceTexture.getSize().x;
	}

	spriteSizeY = 0;
	for (i = 0; i < d / 2; i++) {
		fenceSpritesY[i].setPosition(theMap.relatPosition.x + (windowX / 2), theMap.relatPosition.y + (windowY / 2) + spriteSizeY);
		mWindow.draw(fenceSpritesY[i]);
		spriteSizeY += theFenceTexture.getSize().x;
	}
	spriteSizeY = 0;
	for (i = d / 2; i < d; i++) {
		fenceSpritesY[i].setPosition(theMap.relatPosition.x + (windowX / 2) + mapX, theMap.relatPosition.y + (windowY / 2) + spriteSizeY);
		mWindow.draw(fenceSpritesY[i]);
		spriteSizeY += theFenceTexture.getSize().x;
	}


	//preparing player draw
	angle = -(atan2(theReticle.relatPosition.x - thePlayer.relatPosition.x, theReticle.relatPosition.y - thePlayer.relatPosition.y) * 180 / 3.141592);
	thePlayer.mSprite.setPosition (thePlayer.relatPosition.x, thePlayer.relatPosition.y);
	thePlayer.mSprite.setRotation(angle);
	mWindow.draw(thePlayer.getSprite());

	//preparing reticle draw
	theReticle.mSprite.setPosition(theReticle.relatPosition.x, theReticle.relatPosition.y);
	mWindow.draw(theReticle.getSprite());
	
	for (i = 0; i < enemiesNumber; i++) {
		angle = -(atan2(thePlayer.relatPosition.x - allMonsters[i].relatPosition.x, thePlayer.relatPosition.y - allMonsters[i].relatPosition.y) * 180 / 3.141592);
		allMonsters[i].mSprite.setPosition(allMonsters[i].relatPosition.x, allMonsters[i].relatPosition.y);
		allMonsters[i].mSprite.setRotation(angle);
		mWindow.draw(allMonsters[i].getSprite());
	}

	for (i = 0; i < ammoNumber; i++) {
		if (bullets[i].isShot()) {
			bullets[i].mSprite.setPosition(bullets[i].relatPosition.x, bullets[i].relatPosition.y);
			mWindow.draw(bullets[i].getSprite());
		}
	}

	mWindow.draw(hud);

	mWindow.display();
}