#pragma once
#include <SFML/Graphics.hpp>
#include "gameconfig.h"

class Grid
{
public:
	Grid();
	void drawgrid(sf::RenderWindow& window);
	void setgridatpos(int set, int x, int y);
	int getgridatpos(int x, int y);
private:

	int rows;
	int columns;
	float cellsize;

	std::vector<std::vector<int>> matrix;
	sf::RectangleShape gridblock;

	void initgrid();
};

