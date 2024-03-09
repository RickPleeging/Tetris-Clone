#pragma once
#include <SFML/Graphics.hpp>
#include "gameconfig.h"

class Grid
{
public:
	Grid();
	void drawgrid(sf::RenderWindow& window);

	void update();
	bool checklines();


	std::vector<std::vector<int>> matrix;
private:

	int columns;
	int rows;
	float cellsize;

	sf::RectangleShape gridblock;

	void initgrid();
};

