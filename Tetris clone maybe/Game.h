#pragma once

#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <queue>

#include "SFMLWRAPPER.h"

#include "gameconfig.h"
#include "Grid.h"
#include "Blocks.h"
#include "Menu.h"
#include "UI.h"
#include "random.h"
#include "Sounds.h"


class Game
{

public:

	//Con-Destructors
	Game();
	virtual ~Game();

	bool isRunning();

	void run();

	void updateGame();
	void handleEvents(const sf::Event& event);
	void renderGame();

	enum class GameState {
		Menu,
		Playing,
		GameOver
	};
	static GameState gameState;


	void gamereset();

	void loaddata();
	void savedata();

	

private:
	bool isrunning;

	int columns;
	int rows;
	float cellsize;

	int randomizer;


	sf::RenderWindow window;
	sf::Event ev;
	sf::Font globalFont;

	sf::Clock clock;
	sf::Clock falltimer;
	sf::Clock droptimer;
	float speed;

	void initVariables();


	Grid grid;
	Blocks block;
	UI UserInterface;
	Sounds sounds;
	Menu menu;

	std::queue<int> nextblock;

	bool isfalling;

};

