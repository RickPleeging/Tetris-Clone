#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "Blocks.h"
#include "Grid.h"
#include "gameconfig.h"

class Game
{
private:

	int columns;
	int rows;
	float cellsize;

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



};
