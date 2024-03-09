#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "Blocks.h"

class Game
{
private:
	int rows = 10;
	int columns = 20;
	float cellsize = 40;

	sf::RenderWindow window;
	sf::Event ev;

	sf::Clock clock;
	sf::Clock falltimer;
	float speed;

	void initVariables();


	std::vector<std::vector<int>> matrix;
	sf::RectangleShape gridblock;
	Blocks block;
	bool isfalling;
public:
	

	//Con-Destructors
	Game();
	virtual ~Game();

	bool isRunning();
	void drawgrid();

	void run();
	void update();
	void updateEvents();
	void render();



};

