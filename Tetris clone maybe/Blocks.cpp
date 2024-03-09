#include "Blocks.h"

Blocks::Blocks()
{
	//globals
	rows = g_rows;
	columns = g_columns;
	cellsize = g_cellSize;
	//Rectangle
	rect.setSize(sf::Vector2f(cellsize, cellsize));
	rect.setFillColor(sf::Color::Red);
	rect.setOutlineColor(sf::Color::Cyan);
	rect.setOutlineThickness(1);
	//Shape
	blocktype = 1;
	//position x,y
	position.resize(2);
}

bool Blocks::movedown()
{
	for (int i = 0; i < block.size(); i++) {
		for (int j = 0; j < block[i].size(); j++) {
			if (block[i][j] != 0)
			{
				//TODO check grid on position
			}
		}
	}

	if(position[1] >= columns-2)
	{
		return;
	}
	position[1]++;
}

void Blocks::createblock(int blocktype)
{
	switch (blocktype)
	{
	case 1: //square
		block.resize(2, std::vector<int>(2));
		block[0][0] = 1;
		block[0][1] = 1;
		block[1][0] = 1;
		block[1][1] = 1;
		position = { 4,0 };
		break;
	default:
		break;
	}
}



void Blocks::getblocktype()
{

}


void Blocks::drawblock(sf::RenderWindow& window)
{
	for (int i = 0; i < block.size(); i++) {
		for (int j = 0; j < block[i].size(); j++) {
			if (block[i][j] != 0) {
				rect.setPosition(sf::Vector2f((i+position[0]) * cellsize, (j+position[1]) * cellsize));
				window.draw(rect);
			}
		}
	}
}
