#include "Grid.h"

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
	matrix.resize(columns + 1, std::vector<int>(rows + 1));
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
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
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			gridblock.setPosition(sf::Vector2f(i * cellsize, j * cellsize));
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

}

bool Grid::checklines()
{
	int clearammount = 0;

	for (int i = 0; i <= columns; i++) {
		for (int j = 0; j <= rows; j++) {
			if (matrix[i][j] == 0)
			{
				break;
			}
			if (j == columns) {

				clearammount++;
				for (int n = 0; n < rows; n++) {
					matrix[i][n] = 0;
				}
			}
		}
	}
	if (clearammount != 0) {

		return true;
	}
	return false;
}

