#include "pch.h"
#include "Engine.h"

void Engine::update(float timeInSeconds) {
	
	std::stringstream theStringStream;
	theStringStream <<"SCORE:\nPlayer:"<<score.player<<"     Monsters:"<<score.monsters<<"\n\nMonsters:" << enemiesAlive << "     Ammo:" << thePlayer.ammoNumber << "     MapSize:" << mapX << "x" << mapY <<"    WindowSize:"<<windowX<<"x"<<windowY<< "    MonstSpeed:" << *(allMonsters[0].getSpeed()) <<"\nBullPos:"<<(int)thePlayer.bullets[0].getPosition()->x<<"x"<< (int)thePlayer.bullets[0].getPosition()->y<<"    BullRelPos:"<< (int)thePlayer.bullets[0].getRelatPosition()->x<<"x"<<(int)thePlayer.bullets[0].getRelatPosition()->y<<"\nPlayerPos:" << (int)thePlayer.getPosition()->x << "x" << (int)thePlayer.getPosition()->y << "    PlayRPos" << (int)thePlayer.getRelatPosition()->x << "x" << (int)thePlayer.getRelatPosition()->y << "     PlayerSpeed:" << *(thePlayer.getSpeed())<<"\nMapRelPos:"<< (int)theMap.getRelatPosition()->x<<"x"<< (int)theMap.getRelatPosition()->y<<"\nRetRelPos:" << theReticle.getScreenPosition()->x << "x" << theReticle.getScreenPosition()->y <<"    RetPos:"<<(int)theReticle.getPosition()->x<<"x"<<(int)theReticle.getPosition()->y;
	hud.setString(theStringStream.str());

	if (*thePlayer.isAlive()&&enemiesAlive) {

		thePlayer.update(timeInSeconds);
		theReticle.update(thePlayer.getPosition(), thePlayer.getRelatPosition());
		ScreenToClient (mWindow.getSystemHandle() , theReticle.getScreenPosition());

		for (i = 0; i < enemiesNumber; i++) {
			if (*allMonsters[i].isAlive()) {
				allMonsters[i].update();
				killPlayer(&allMonsters[i]);
			}
		}

		for (i = 0; i < ammoNumberStart; i++) {
			for (j = 0; j < enemiesNumber; j++) {
				if (*(thePlayer.bullets[i].isShot()) && *allMonsters[j].isAlive()) {
					killMonster(&(allMonsters[j]), &(thePlayer.bullets[i]));
				}
			}
		}

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
		setEnemiesRandomSpeed();
		enemiesAlive = enemiesNumber;

		for (i = 0; i < enemiesNumber; i++) {
			allMonsters[i].setAlive(true);
		}
		thePlayer.setPosition(mapX / 2, mapY / 2);
		setMonsterRandomPosition();

		for (i = 0; i < ammoNumberStart; i++)
			thePlayer.bullets[i].setShot(false);
	}
}