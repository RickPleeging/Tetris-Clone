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
	std::vector<std::vector<int>> ghostblock;

	std::vector<int> position;
	std::vector<int> ghostposition;
	sf::RectangleShape rect;
	sf::RectangleShape ghostrect;

	sf::RectangleShape outline;

	using Matrix = std::vector<std::vector<int>>&;


public:
	Blocks();
	
	void createblock(int blocktype);
	bool checkspace(Matrix matrix);
	void rotateblock(Matrix matrix, int offset);
	bool kickback(Matrix matrix);
	bool updateblock(Matrix matrix);
	
	bool movedown(Matrix matrix);
	bool moveleft(Matrix matrix);
	bool moveright(Matrix matrix);
	void drop(Matrix matrix);

	void setposition(int x, int y);

	void placeblock(Matrix matrix, std::vector<int> position);

	int getblocksize();
	void setghostblock(Matrix matrix);
	void drawghostblock(sf::RenderWindow& window);

	void drawblock(sf::RenderWindow& window);
	void drawblockOffGrid(sf::RenderWindow& window,int x, int y);
	float centercoordinates;


};
 
