
#include "DebugMemory.h"
#include "Game.h"
#include <iostream>

int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	{
		Game game;
		game.run();
	}

	return 0;
}