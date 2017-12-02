#include "Engine\GameManager.h"

GameManager *game;

int main()
{
	game = new GameManager();

	game->run();

	delete game;

	return 0;
}