#include <iostream>
#include "Game.h"

int main(int argc, char** argv)
{
	string cfgFileName;

	switch (argc) {
		case 1: {
			cfgFileName = "C:\\Users\\mamkad\\source\\repos\\PingPong\\x64\\Release\\init.txt";
			break;
		}
		case 2: {
			cfgFileName = argv[1];
			break;
		}
		default:
			return -1;
	}

	Game pingPong(cfgFileName);
	return pingPong.Run();
}