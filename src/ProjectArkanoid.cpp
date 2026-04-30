
#define _CRTDBG_MAP_ALLOC
#include "Game.h"
#include <iostream>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Game game;
	game.run();
    return 0;
}