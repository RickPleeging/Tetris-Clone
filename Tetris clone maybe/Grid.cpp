#include "Grid.h"

Grid::Grid() {
	initgrid();
}

void Grid::initgrid()
{
	//globals
	rows = g_rows;
	columns = g_columns;
	cellsize = g_cellSize;
	//grid = 0
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
			gridblock.setPosition(sf::Vector2f(i * cellsize, j * cellsize));
			if (matrix[i][j] == 1) {
				gridblock.setFillColor(sf::Color::Red);
			}
			else
			{
				gridblock.setFillColor(sf::Color::Black);
			}
			window.draw(gridblock);
		}
	}

}

void Grid::setgridatpos(int set, int x, int y)
{
	matrix[y][x] = set;
}

int Grid::getgridatpos(int x, int y)
{
	return matrix[y][x];
}


