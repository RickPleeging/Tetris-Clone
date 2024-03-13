#include "Game.h"
int g_columns = 10;
int g_rows = 20;
float g_cellSize = 40.0f;
int g_gameheight = g_cellSize * g_rows;
int g_gamewidth = g_cellSize * g_columns;
int g_windowheight = g_gameheight + 150;
int g_windowwidth = g_gamewidth + 300;

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