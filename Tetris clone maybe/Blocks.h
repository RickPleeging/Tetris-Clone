#pragma once
#include <SFML/Graphics.hpp>

class Blocks
{
private:

	int rows = 10;
	int columns = 20;
	float cellsize = 40;

	int blocktype;
		
	std::vector<std::vector<int>> block;
	std::vector<int> position;
	sf::RectangleShape rect;

public:
	Blocks();
	

	void movedown();
	void createblock();

	void getblocktype();
	void drawblock(sf::RenderWindow& window);

};

