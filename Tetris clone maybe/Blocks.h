#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "gameconfig.h"
#include "Grid.h"

class Blocks
{
private:


	int columns;
	int rows;
	float cellsize;

	int blocktype;
	int rotation;
	std::vector<std::vector<int>> block;
	std::vector<std::vector<int>> newblock;

	std::vector<int> position;
	sf::RectangleShape rect;
	sf::RectangleShape outline;

	using Matrix = std::vector<std::vector<int>>&;


public:
	Blocks();
	
	bool createblock(int blocktype,Matrix matrix);
	void rotateblock(Matrix matrix, int offset);
	bool kickback(Matrix matrix);
	bool updateblock(Matrix matrix);
	
	bool movedown(Matrix matrix);
	bool moveleft(Matrix matrix);
	bool moveright(Matrix matrix);
	void drop(Matrix matrix);

	bool checkspace(Matrix matrix);

	void placeblock(Matrix matrix, std::vector<int> position);

	void getblocktype();

	void drawblock(sf::RenderWindow& window);
};

