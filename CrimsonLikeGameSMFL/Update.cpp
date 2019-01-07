#include "pch.h"
#include "Engine.h"

void Engine::update(float timeInSeconds) {
	
	std::stringstream theStringStream;
	theStringStream <<"SCORE:\nPlayer:"<<score.player<<"     Monsters:"<<score.monsters<<"\n\nMonsters:" << enemiesAlive << "     Ammo:" << ammoNumber << "     MapSize:" << mapX << "x" << mapY <<"    WindowSize:"<<windowX<<"x"<<windowY<< "    MonstSpeed:" << *(allMonsters[0].getSpeed()) <<"\nBullPos:"<<(int)bullets[0].getPosition()->x<<"x"<< (int)bullets[0].getPosition()->y<<"    BullRelPos:"<< (int)bullets[0].getRelatPosition()->x<<"x"<<(int)bullets[0].getRelatPosition()->y<<"\nPlayerPos:" << (int)thePlayer.getPosition()->x << "x" << (int)thePlayer.getPosition()->y << "    PlayRPos" << (int)thePlayer.getRelatPosition()->x << "x" << (int)thePlayer.getRelatPosition()->y << "     PlayerSpeed:" << *(thePlayer.getSpeed())<<"\nMapRelPos:"<< (int)theMap.getRelatPosition()->x<<"x"<< (int)theMap.getRelatPosition()->y<<"\nRetRelPos:" << theReticle.getScreenPosition()->x << "x" << theReticle.getScreenPosition()->y <<"    RetPos:"<<(int)theReticle.getPosition()->x<<"x"<<(int)theReticle.getPosition()->y;
	hud.setString(theStringStream.str());

	if (*thePlayer.isAlive()&&enemiesAlive) {

		thePlayer.update(timeInSeconds);
		theMap.update();
		theReticle.update();
		ScreenToClient (mWindow.getSystemHandle() , theReticle.getScreenPosition());

		//Writing down, where each monster is going to go by it's next step
		for (i = 0; i < enemiesNumber; i++) {
			if (allMonsters[i].isAlive()) {
				enemiesNextSteps[i] = allMonsters[i].checkUpdate(timeInSeconds);
			}
		}
		
		for (i = 0; i < enemiesNumber; i++) {
			if (*allMonsters[i].isAlive()) {
				for (j = 0; j < enemiesNumber; j++) {
					if (j != i) {
						if (sqrt(pow(enemiesNextSteps[i].x - enemiesNextSteps[j].x, 2) + pow(enemiesNextSteps[i].y - enemiesNextSteps[j].y, 2)) <= 30.0) {
							//monstersCollide[i] = true;
						}
					}
				}
				allMonsters[i].update(timeInSeconds, enemiesNextSteps[i]);
				killPlayer(&allMonsters[i]);
			}
		}
		//if (monstersCollide[i]==true) {
			//time(allMonsters->getSinceCollide());
			//allMonsters[i].setCollide(true);
			//enemiesNextSteps[i] = *allMonsters[i].getPosition();
		//}
		
		//cheking - does anybody is going to collide
		//for (i = 0; i < enemiesNumber; i++) {
		//	if (allMonsters[i].isAlive()) {
		//		int j;
		//		for (j = 0; j < enemiesNumber; j++) {
		//			if (j != i)
		//				if (sqrt(pow(allMonsters[i].getPosition()->x - allMonsters[j].getPosition()->x,2)+pow(allMonsters[i].getPosition()->y - allMonsters[j].getPosition()->y, 2))<=30.0) {
		//					monstersCollide[i] = true;
		//				}
		//				else {
		//					monstersCollide[i] = false;
		//				}
					
		//		}
		//	}
		//}

		//updating each alive monster position without collisions
		//for (i = 0; i < enemiesNumber; i++) {
		//	if (*allMonsters[i].isAlive()/*&&!monstersCollide[i]*/) {
		//		allMonsters[i].update(timeInSeconds, enemiesNextSteps[i]);
		//		killPlayer(&allMonsters[i]);
		//	}
			//else if (allMonsters[i].isAlive() && monstersCollide[i]) {
				//enemiesNextSteps[i].x = allMonsters[i].getPosition()->x;
				//enemiesNextSteps[i].y = allMonsters[i].getPosition()->y;
			//}
		//}

		/********************************
		BULLETS HANDLING
		********************************/

		//if button is not released - shoot
		if (mouseButtonPressed) {
			if(!*bullets[ammoNumber-1].isShot()){
				shoot(&(bullets[ammoNumber-1]));
			}
		}

		//updating each shot bullet position
		for (i = 0; i < ammoNumber; i++) {
			if (*bullets[i].isShot()) {
				bullets[i].update(timeInSeconds);
			}
			
			for (j = 0; j < enemiesNumber; j++) {
				if (*bullets[i].isShot()&&*allMonsters[j].isAlive()) {
					killMonster(&(allMonsters[j]), &(bullets[i]));
				}
			}
		}

		//respawn one bullet if they ended
		if (ammoNumber == 0) {
			int was = 1, become = 1;
			for (i = 0; i < ammoNumber; i++) {
				if (*bullets[i].isShot())
					become++;
			}
			if (was == become)
				ammoNumber++;
		}
	}
	else {										//if player is dead - restart the game
		if (!*thePlayer.isAlive())
			score.monsters++;
		else
			score.player++;
		
		thePlayer.setAlive(true);
		setAmmoNumber(ammoNumberStart);
		setEnemiesRandomSpeed();
		enemiesAlive = enemiesNumber;
		for (i = 0; i < enemiesNumber; i++) {
			allMonsters[i].setAlive(true);
		}
		thePlayer.setPosition(mapX / 2, mapY / 2);
		setMonsterRandomPosition();

		for (i = 0; i < ammoNumber; i++)
			bullets[i].setShot(false);
	}
}