#include "pch.h"
#include "Engine.h"
#include <iostream>
#include <string>

int i, j, widthWindow = 0, heightWindow = 0, mapWidth = 0, mapHeight = 0, ammoN = 0, enemiesN = 0;

void provideInputParameters(int argc, char* argv[]) {
	char * pEnd;
	if (argc > 1) {
		for (i = 1; i < argc; i++) {
			if (!strcmp(argv[i], "-window")) {
				for (j = 0; j < strlen(argv[i + 1]); j++) {
					if (argv[i + 1][j] == 'x')
						argv[i + 1][j] = ' ';
				}
				widthWindow = strtol(argv[i + 1], &pEnd, 10);
				heightWindow = strtol(pEnd, NULL, 10);
			}
			else if (!strcmp(argv[i], "-map")) {
				for (j = 0; j < strlen(argv[i + 1]); j++) {
					if (argv[i + 1][j] == 'x')
						argv[i + 1][j] = ' ';
				}
				mapWidth = strtol(argv[i + 1], &pEnd, 10);
				mapHeight = strtol(pEnd, NULL, 10);
			}
			else if (!strcmp(argv[i], "-num_enemies")) {
				enemiesN = strtol(argv[i + 1], NULL, 10);
			}
			else if (!strcmp(argv[i], "-num_ammo")) {
				ammoN = strtol(argv[i + 1], NULL, 10);
			}
		}
	}
}

int main(int argc, char* argv[])
{
	provideInputParameters(argc, argv);

	Engine theEngine(widthWindow, heightWindow, mapWidth, mapHeight, ammoN, enemiesN);

	theEngine.start();

	return 0;
}