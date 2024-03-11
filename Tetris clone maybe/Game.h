#pragma once

#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "Blocks.h"
#include "Grid.h"
#include "gameconfig.h"

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

	int generateRandomNumber(int min, int max);


};

