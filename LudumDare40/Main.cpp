#include "Engine\GameManager.h"

GameManager *game;

int main()
{
	game = new GameManager();

	game->run();

	return 0;
}