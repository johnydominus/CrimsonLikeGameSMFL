#include "pch.h"
#include "Engine.h"

void Engine::draw() {
	mWindow.clear(sf::Color::White);
	
	//preparing map draw
	spriteSizeY = 0;
	for (auto i = 0; i < mapSpritesYnumber; i ++) {
		spriteSizeX = 0;
		for (auto j = 0; j < mapSpritesXnumber; j ++) {
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
	for (auto i = 0; i < fenceSpritesXnumber / 2; i++) {
		fenceSpritesX[i].setPosition(theMap.getRelatPosition()->x + ((float)windowX / 2.0) + spriteSizeX - theFenceTexture.getSize().y, theMap.getRelatPosition()->y + ((float)windowY / 2.0) - theFenceTexture.getSize().y);
		mWindow.draw(fenceSpritesX[i]);
		spriteSizeX += theFenceTexture.getSize().x;
	}
	spriteSizeX = 0;
	for (auto i = fenceSpritesXnumber / 2; i < fenceSpritesXnumber; i++) {
		fenceSpritesX[i].setPosition(theMap.getRelatPosition()->x + (windowX / 2) + spriteSizeX, theMap.getRelatPosition()->y + (windowY / 2) + mapY);
		mWindow.draw(fenceSpritesX[i]);
		spriteSizeX += theFenceTexture.getSize().x;
	}

	spriteSizeY = 0;
	for (auto i = 0; i < fenceSpritesYnumber / 2; i++) {
		fenceSpritesY[i].setPosition(theMap.getRelatPosition()->x + ((float)windowX / 2.0), theMap.getRelatPosition()->y + ((float)windowY / 2.0) + spriteSizeY);
		mWindow.draw(fenceSpritesY[i]);
		spriteSizeY += theFenceTexture.getSize().x;
	}
	spriteSizeY = 0;
	for (auto i = fenceSpritesYnumber / 2; i < fenceSpritesYnumber; i++) {
		fenceSpritesY[i].setPosition(theMap.getRelatPosition()->x + ((float)windowX / 2.0) + (float)mapX +theFenceTexture.getSize().y, theMap.getRelatPosition()->y + ((float)windowY / 2.0) + spriteSizeY);
		mWindow.draw(fenceSpritesY[i]);
		spriteSizeY += theFenceTexture.getSize().x;
	}

	//testing node ocuppation draw
	//for (auto i = 0; i < theMap.gridY; i++) {
	//	for (auto j = 0; j < theMap.gridX; j++) {
	//		if (theMap.mGrid[i][j].occupied)
	//			theMap.squareSprite.setTexture(theMap.squareTextureRed);
	//		else
	//			theMap.squareSprite.setTexture(theMap.squareTextureGreen);
	//		theMap.squareSprite.setPosition(theMap.getRelatPosition()->x + (windowX/2) + theMap.mGrid[i][j].j * theMap.getMonster(0)->getSprite()->getTextureRect().width, theMap.getRelatPosition()->y + (windowY / 2) + theMap.mGrid[i][j].i * theMap.getMonster(0)->getSprite()->getTextureRect().height);
	//		mWindow.draw(theMap.squareSprite);
	//	}
	//}

	//preparing player draw
	auto angle = -(atan2(theReticle.getScreenPosition()->x - thePlayer.getRelatPosition()->x, theReticle.getScreenPosition()->y - thePlayer.getRelatPosition()->y) * 180.0 / 3.141592);
	thePlayer.getSprite()->setPosition (thePlayer.getRelatPosition()->x, thePlayer.getRelatPosition()->y);
	thePlayer.getSprite()->setRotation(angle);
	mWindow.draw(*thePlayer.getSprite());

	//preparing reticle draw
	theReticle.getSprite()->setPosition(theReticle.getScreenPosition()->x, theReticle.getScreenPosition()->y);
	mWindow.draw(*theReticle.getSprite());
	
	//preparing monsters draw
	for (auto i = 0; i < theMap.enemiesNumber; i++) {
		if (*theMap.getMonster(i)->isAlive()) {
			theMap.getMonster(i)->getSprite()->setPosition(theMap.getMonster(i)->getRelatPosition()->x, theMap.getMonster(i)->getRelatPosition()->y);
			theMap.getMonster(i)->getSprite()->setRotation(*theMap.getMonster(i)->getAngle());
			mWindow.draw(*theMap.getMonster(i)->getSprite());
		}
	}

	//preparing bullets draw
	for (auto i = 0; i < ammoNumberStart; i++) {
		if (*thePlayer.getBullet(i)->isShot()) {
			thePlayer.getBullet(i)->getSprite()->setPosition(thePlayer.getBullet(i)->getRelatPosition()->x, thePlayer.getBullet(i)->getRelatPosition()->y);
			mWindow.draw(*thePlayer.getBullet(i)->getSprite());
		}
	}

	//preparing hud draw
	mWindow.draw(hud);

	//drawing all the stuff
	mWindow.display();
}