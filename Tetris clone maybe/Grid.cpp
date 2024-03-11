#include "Grid.h"
#include <iostream>
Grid::Grid() {
	initgrid();
}

void Grid::initgrid()
{
	//globals
	columns = g_columns;
	rows = g_rows;
	cellsize = g_cellSize;
	//grid = 0
	temp.clear();
	temp.resize(20, std::vector<int>(20));

	std::cout << "temp size[0]: " << temp.size() << "temp size[1]: " << temp[1].size();
	matrix.resize(rows + 1, std::vector<int>(columns + 1));
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			matrix[i][j] = 0;
		}
	}
	//init Gridblock
	gridblock.setSize(sf::Vector2f(cellsize, cellsize));
	gridblock.setFillColor(sf::Color::Black);
	gridblock.setOutlineColor(sf::Color::Cyan);
	gridblock.setOutlineThickness(1);
}

void Grid::drawgrid(sf::RenderWindow& window)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			gridblock.setPosition(sf::Vector2f(j * cellsize, i * cellsize));
			switch (matrix[i][j])
			{
			case 1:
				gridblock.setFillColor(sf::Color(223, 227, 11, 155));
				break;
			case 2:
				gridblock.setFillColor(sf::Color(165, 9, 171, 155));
				break;
			case 3:
				gridblock.setFillColor(sf::Color(60, 65, 230, 155));
				break;
			case 4:
				gridblock.setFillColor(sf::Color(230, 135, 41, 155));
				break;
			case 5:
				gridblock.setFillColor(sf::Color(7, 222, 28, 155));
				break;
			case 6:
				gridblock.setFillColor(sf::Color(148, 14, 7, 155));
				break;
			case 7:
				gridblock.setFillColor(sf::Color(51, 184, 189, 155));
				break;
			default:
				gridblock.setFillColor(sf::Color::Black);
				break;
			}
			window.draw(gridblock);
		}
	}

}

void Grid::update()
{
	if(checklines() == true)
	{
		clearlines();
		for (auto i : toClear) {
			movelines();
		}
	}
	return;
}

bool Grid::checklines()
{
	//TODO fix
	toclear.clear();

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (matrix[i][j] == 0) {
				break;
			}
			if (j == columns-1) {
				//std::cout << "Line detected at row: " << i;
				toClear.push_back(i);
			}
		}
	}
	if (!toClear.empty()) {
		return true;
	}
	return false;
}

void Grid::clearlines()
{
	for (int i : toClear) {
		for (int j = 0; j < columns; j++) {
			matrix[i][j] = 0;
		}
	}
	//toclear.clear();
}



void Grid::movelines()
  {

	for (int i = toClear[0]; i > 0; i--) {
		for (int j = 0; j < columns; j++) {
			temp[i][j] = matrix[i][j];
			matrix[i][j] = matrix[i - 1][j];
			matrix[i - 1][j] = temp[i][j];
		}
	}
	toClear.pop_front();

}

void Grid::checknomoremoves()
{

}

