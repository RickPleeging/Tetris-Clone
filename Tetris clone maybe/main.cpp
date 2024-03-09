#include "Game.h"
int g_columns = 10;
int g_rows = 20;
float g_cellSize = 40.0f;

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