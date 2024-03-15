#pragma once

#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "gameconfig.h"
#include "Grid.h"
#include "Blocks.h"
#include "UI.h"
#include <queue>

class Game
{
private:
	bool isrunning;

	int columns;
	int rows;
	float cellsize;

	int randomizer;


	sf::RenderWindow window;
	sf::Event ev;

	sf::Clock clock;
	sf::Clock falltimer;
	sf::Clock droptimer;
	float speed;

	void initVariables();

	Grid grid;
	Blocks block;


	UI UserInterface;

	std::queue<int> nextblock;

	bool isfalling;
public:
	
	//Con-Destructors
	Game();
	virtual ~Game();

	bool isRunning();

	void run();
	void update();
	void updateEvents();
	void render();
	void gamereset();

	int generateRandomNumber(int min, int max);


};

