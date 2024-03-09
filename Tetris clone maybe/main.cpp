#include "Game.h"
int main() {

	//Create Game Object
	Game game;

	//Game Loop
	while (game.isRunning())
	{
		game.run();
	}




	return 0;
}