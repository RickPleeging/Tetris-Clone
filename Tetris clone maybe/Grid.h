#pragma once
#include <SFML/Graphics.hpp>
#include "gameconfig.h"
#include <deque>
class Grid
{
public:
	Grid();
	void drawgrid(sf::RenderWindow& window);

	void update();
	bool checklines();
	void clearlines();
	void movelines();
	void checknomoremoves();

	void gridclear();

	std::vector<std::vector<int>> matrix;
	std::vector<std::vector<int>> temp;

	int score;
	int highscore;


private:

	int columns;
	int rows;
	float cellsize;
	std::vector<int> toclear;
	std::deque<int> toClear;
	sf::RectangleShape gridblock;

	void initgrid();
};

