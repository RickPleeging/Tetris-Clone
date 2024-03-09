#pragma once
#include <SFML/Graphics.hpp>
#include "gameconfig.h"
#include "Grid.h"

class Blocks
{
private:

	int rows;
	int columns;
	float cellsize;

	int blocktype;
		
	std::vector<std::vector<int>> block;
	std::vector<int> position;
	sf::RectangleShape rect;

public:
	Blocks();
	

	bool movedown();
	void createblock(int blocktype);

	void getblocktype();
	void drawblock(sf::RenderWindow& window);

};

