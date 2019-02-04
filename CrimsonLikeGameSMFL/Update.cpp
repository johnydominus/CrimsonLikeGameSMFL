#include "pch.h"
#include "Engine.h"

void Engine::update(float timeInSeconds) {
	
	std::stringstream theStringStream;
	if (devMode) {
		theStringStream 
			<< "SCORE:\nPlayer:" << score.player
			<< "    Monsters:" << score.monsters << std::endl << std::endl
			<< "MonstersNum:" << theMap.enemiesAlive
			<< "    Ammo:" << thePlayer.ammoNumber
			<< "    MapSize:" << mapX << "x" << mapY
			<< "    WindowSize:" << windowX << "x" << windowY
			<< "    MonstSpeed:" << *(theMap.getMonster(0)->getSpeed()) << std::endl
			<< "BullPos:" << (int)thePlayer.getBullet(0)->getPosition()->x << "x" << (int)thePlayer.getBullet(0)->getPosition()->y
			<< "    BullRelPos:" << (int)thePlayer.getBullet(0)->getRelatPosition()->x << "x" << (int)thePlayer.getBullet(0)->getRelatPosition()->y << std::endl
			<< "PlayerPos:" << (int)thePlayer.getPosition()->x << "x" << (int)thePlayer.getPosition()->y
			<< "    PlayRelPos" << (int)thePlayer.getRelatPosition()->x << "x" << (int)thePlayer.getRelatPosition()->y
			<< "    PlayerSpeed:" << *(thePlayer.getSpeed()) << std::endl
			<< "MapRelPos:" << (int)theMap.getRelatPosition()->x << "x" << (int)theMap.getRelatPosition()->y << std::endl
			<< "RetRelPos:" << theReticle.getScreenPosition()->x << "x" << theReticle.getScreenPosition()->y
			<< "    RetPos:" << (int)theReticle.getPosition()->x << "x" << (int)theReticle.getPosition()->y;
	}
	else
	{
		theStringStream
			<< "SCORE:\nPlayer:" << score.player
			<< "    Monsters:" << score.monsters << std::endl << std::endl
			<< "MonstersNum:" << theMap.enemiesAlive
			<< "    Ammo:" << thePlayer.ammoNumber << std::endl
			<< "MonstSpeed:" << *(theMap.getMonster(0)->getSpeed()) << std::endl;
	}
	hud.setString(theStringStream.str());

	if (*thePlayer.isAlive()&&theMap.enemiesAlive) {
		thePlayer.update(timeInSeconds);
		theReticle.update(thePlayer.getPosition(), thePlayer.getRelatPosition());
		ScreenToClient (mWindow.getSystemHandle(), theReticle.getScreenPosition());

		theMap.update();
	}
	else {										//if player is dead - restart the game
		if (!*thePlayer.isAlive())
			score.monsters++;
		else
			score.player++;
		
		thePlayer.setAlive(true);
		thePlayer.bulletNumber = 0;
		setAmmoNumber(ammoNumberStart);
		theMap.deocuppyMap();
		theMap.setEnemiesRandomSpeed();
		theMap.enemiesAlive = theMap.enemiesNumber;

		for (auto i = 0; i < theMap.enemiesNumber; i++) {
			theMap.getMonster(i)->setAlive(true);
		}
		thePlayer.setPosition(mapX / 2, mapY / 2);
		theMap.setMonsterRandomPosition();

		for (auto i = 0; i < ammoNumberStart; i++)
			thePlayer.getBullet(i)->setShot(false);
	}
}