#include "pch.h"
#include "Engine.h"

void Engine::update(float timeInSeconds) {
	
	std::stringstream theStringStream;
	theStringStream << "Monsters:" << enemiesAlive << "     Ammo:" << ammoNumber << "     MapSize:" << mapX << "x" << mapY <<"    WindowSize:"<<windowX<<"x"<<windowY<<"\nPPos:" << thePlayer.getPosition()->x << "x" << thePlayer.getPosition()->y << "    MSpeed:" << *(allMonsters[0].getSpeed()) << "     PSpeed:" << *(thePlayer.getSpeed())<<"    MapRelPos:"<<theMap.relatPosition.x<<"x"<<theMap.relatPosition.y<<"    PRPos"<<thePlayer.relatPosition.x<<"x"<<thePlayer.relatPosition.y;
	hud.setString(theStringStream.str());

	if (thePlayer.isAlive()&&enemiesAlive) {

		thePlayer.update(timeInSeconds);
		theMap.update();
		theReticle.update();
		ScreenToClient (mWindow.getSystemHandle() , &theReticle.relatPosition);

		//Writing down, where each monster is going to go by it's next step
		for (i = 0; i < enemiesNumber; i++) {
			if (allMonsters[i].isAlive()) {
				enemiesNextSteps[i] = allMonsters[i].checkUpdate(timeInSeconds);
			}
		}

		//cheking - does anybody is going to collide
		/*for (i = 0; i < enemiesNumber; i++) {
			if (allMonsters[i].isAlive()) {
				int j;
				for (j = 0; j < enemiesNumber; j++) {
					if (j == i)
						continue;
					else {
						if ((((allMonsters[i].shape.left <= allMonsters[j].shape.right) && (allMonsters[i].shape.left >= allMonsters[j].shape.left)) || ((allMonsters[i].shape.right <= allMonsters[j].shape.right) && (allMonsters[i].shape.right >= allMonsters[j].shape.left))) && (((allMonsters[i].shape.bottom >= allMonsters[j].shape.top) && (allMonsters[i].shape.bottom <= allMonsters[j].shape.bottom)) || ((allMonsters[i].shape.top >= allMonsters[j].shape.top) && (allMonsters[i].shape.top <= allMonsters[j].shape.bottom)))) {
							monstersCollide[i] = true;
						}
					}
				}
			}
		}
		*/
		//updating each alive monster position without collisions
		for (i = 0; i < enemiesNumber; i++) {
			if (allMonsters[i].isAlive()/*&&!monstersCollide[i]*/) 
				allMonsters[i].update(timeInSeconds, enemiesNextSteps[i]);
		}

		/********************************
		BULLETS HANDLING
		********************************/

		//if button is not released - shoot
		if (mouseButtonPressed == true) {
			shoot(&bullets[ammoNumber-1]);
		}

		//updating each shot bullet position
		for (i = 0; i < ammoNumber; i++) {
			bullets[i].update(timeInSeconds);
			for (j = 0; j < enemiesNumber; j++) {
				if (bullets[i].isShot()) {
					killMonster(&(allMonsters[j]), &(bullets[i]));
				}
			}
		}

		//respawn one bullet if they ended
		if (ammoNumber == 0) {
			int was = 1, become = 1;
			for (i = 0; i < ammoNumber; i++) {
				if (bullets[i].isShot())
					become++;
			}
			if (was == become)
				ammoNumber++;
		}
	}
	else {										//if player is dead - restart the game
		thePlayer.setAlive(true);
		setAmmoNumber(ammoNumberStart);
		setEnemiesRandomSpeed();
		enemiesAlive = enemiesNumber;
		for (i = 0; i < enemiesNumber; i++) {
			allMonsters[i].setAlive(true);
		}
		setMonsterRandomPosition();

		for (i = 0; i < ammoNumber; i++)
			bullets[i].setShot(false);
	}
}