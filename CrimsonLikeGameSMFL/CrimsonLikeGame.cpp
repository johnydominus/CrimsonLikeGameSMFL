#include "pch.h"
#include "Engine.h"
#include <iostream>

int i, j, widthWindow = 0, heightWindow = 0, mapWidth = 0, mapHeight = 0, ammoN = 0, enemiesN = 0;

void provideInputedParameters(int argc, char* argv[]) {
	if (argc > 1) {
		for (i = 1; i < argc + 1; i++) {
			std::string argument(argv[i]);
			if (argument == "-window") {
				std::string argument(argv[i + 1]);
				std::size_t n = argument.find('x');
				if (n != std::string::npos) {
					std::string::size_type st;
					widthWindow = std::stoi(argument, &st);
					heightWindow = std::stoi(argument.substr(st + 1));
				}
			}
			else if (argument == "-map") {
				std::string argument(argv[i + 1]);
				std::size_t n = argument.find('x');
				if (n != std::string::npos) {
					std::string::size_type st;
					mapWidth = std::stoi(argument, &st);
					mapHeight = std::stoi(argument.substr(st + 1));
				}
			}
			else if (argument == "- num_enemies") {
				std::string argument(argv[i + 1]);
				std::string::size_type st;
				enemiesN = std::stoi(argument, &st);
			}
			else if (argument == "-num_ammo") {
				std::string argument(argv[i + 1]);
				std::string::size_type st;
				ammoN = std::stoi(argument, &st);
			}
			else
				continue;
		}
	}
}

int main(int argc, char* argv[])
{
	//provideInputedParameters(argc, argv);

	Engine theEngine(widthWindow, heightWindow, mapWidth, mapHeight, ammoN, enemiesN);

	theEngine.start();

	return 0;
}