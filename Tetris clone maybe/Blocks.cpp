#include "Blocks.h"

Blocks::Blocks()
{
	//globals
	columns = g_columns;
	rows = g_rows;
	cellsize = g_cellSize;

	//Rectangle
	rect.setSize(sf::Vector2f(cellsize, cellsize));
	rect.setFillColor(sf::Color::Red);
	rect.setOutlineColor(sf::Color::Cyan);
	rect.setOutlineThickness(1);
	//outline
	outline.setFillColor(sf::Color::Transparent);
	outline.setOutlineColor(sf::Color::Magenta);
	outline.setOutlineThickness(2);
	block.clear();
	block.resize(4, std::vector<int>(4));
	//variables 
	blocktype = 0;
	rotation = 1;

	//position x,y // rows,collumns
	position.clear();
	position.resize(2);
	//debug

}

//return true if updated, return false if block placed
bool Blocks::updateblock(Matrix matrix)
{
	
	//move, if no free space bellow -> place in grid
	if (!movedown(matrix))
	{
		placeblock(matrix, position);
		return false;
	}
	else
		return true;


}

bool Blocks::movedown(Matrix matrix)
{
	
	//for each square in a block check if bellow it is free, if not return false
	if (position[1] + 1 == rows)
		return false;
	for (int i = 0; i < block.size(); i++) {
		for (int j = 0; j < block[i].size(); j++) {
			if (block[i][j] == 0)
				continue;
			if (matrix[(i + position[1])+1][(j + position[0])] != 0 || i+position[1]+1 == rows)
				return false;
		}
	}
	position[1]++;
	return true;
}

void Blocks::drop(Matrix matrix)
{
	// FUCKING FIXED IT YEET

	int empty=0;
	bool stopit = false;
	//Find Ammount of empty rows starting from the bottom
	for (int i = block.size()-1; i >= 0; i--) {
		if (stopit) {
			break;
		}
		for (int j = 0; j < block[i].size(); j++) {
			if (block[i][j] == 1) {
				stopit = true;
				break;
			}
			else if (j == block[i].size()-1) {
				empty++;
			}
			
		}
	}
	int temp;
	//Remaining to the bottom
	int remaining = rows - position[1]; //20
	//Remaining to the bottom + lowest position of the block
	int droppos = remaining - block[1].size()+empty; //19

	//For Every square in the block find its lowest possible position
 	for (int i = 0; i < block.size(); i++) {
		for (int j = 0; j < block[i].size(); j++) {
			if (block[i][j] == 0)
				continue;
			
			temp = 0;
			for (int r = 0; r < remaining; r++) {
				//check if bellow is free space
				if (i + position[1] + r < rows && matrix[i + position[1]+r+1][j + position[0]] == 0)
				{
					temp++;
					continue;
				}
				//drop position should be the highest out of all squares lowest positions
				if (temp < droppos) {
					droppos = temp;
					break;
				}
			}
		}
	}
	position[1] += droppos;
	//placeblock(matrix, position);
}



bool Blocks::moveleft(Matrix matrix)
{
	//for each square in a block, check if right is left, return true if moved
	for (int i = 0; i < block.size(); i++) {
		for (int j = 0; j < block[i].size(); j++) {
			if (block[i][j] == 0)
				continue;
			if (position[0] + j - 1 < 0)
				return false;
			if (matrix[(i + position[1])][(j + position[0]-1)] != 0)
				return false;
		}
	}
	position[0]--;
	return true;
}

bool Blocks::moveright(Matrix matrix)
{
	//for each square in a block, check if right is free, return true if moved
	for (int i = 0; i < block.size(); i++) {
		for (int j = 0; j < block[i].size(); j++) {
			if (block[i][j] == 0)
				continue;
			if (position[0] + j + 1 == columns)
				return false;
			if (matrix[(i + position[1])][(j + position[0]) + 1] != 0)
				return false;
		}
	}
	position[0]++;
	return true;
}


void Blocks::placeblock(Matrix matrix, std::vector<int> position)
{
	for (int i = 0; i < block.size(); i++) {
		for (int j = 0; j < block[i].size(); j++) {
			if (block[i][j] == 0)
				continue;
			matrix[(i + position[1])][(j + position[0])] = blocktype;
		}
	}

}

bool Blocks::checkspace(Matrix matrix)
{
	for (int i = 0; i < block.size(); i++) {
		for (int j = 0; j < block[i].size(); j++) {
			if (i+position[0] < 0 || i+position[0] > rows || j+ position[1] < 0 || j+ position[1] > columns)
			{
				return false;
			}
			if (block[i][j] == 0)
				continue;
			if (matrix[i+position[1]][j+position[0]] != 0)
				return false;
		}
	}

	return true;
}

void Blocks::setposition(int x, int y)
{
	position[0] = x;
	position[1] = y;
}

void Blocks::createblock(int type)
{
	rotation = 1;
	switch (type)
	{
	case 1: //square
		block.clear();
		block.resize(2, std::vector<int>(2));
		outline.setSize(sf::Vector2f(2*cellsize, 2*cellsize));
		block = { {1,1},{1,1}};

		blocktype = 1;
		rect.setFillColor(sf::Color(223, 227, 11, 255));

		position = { 4,0 };
		break;
	case 2: //T BLOCK

		block.clear();
		block.resize(3, std::vector<int>(3));
		outline.setSize(sf::Vector2f(3 * cellsize, 3 * cellsize));

		block = { {0,0,0},{0,1,0}, {1,1,1} };

		blocktype = 2;
		rect.setFillColor(sf::Color(165, 9, 171, 255));
		position = { 4,0 };
		break;
	case 3: // L Block
		block.clear();
		block.resize(3, std::vector<int>(3));
		outline.setSize(sf::Vector2f(3 * cellsize, 3 * cellsize));

		block = { {0,0,1},{1,1,1}, {0,0,0} };


		position = { 4,0 };
		blocktype = 3;
		rect.setFillColor(sf::Color(60, 65, 230, 255));
		break;
	case 4: // J Block
		block.clear();
		block.resize(3, std::vector<int>(3));
		outline.setSize(sf::Vector2f(3 * cellsize, 3 * cellsize));

		block = { {1,0,0},{1,1,1}, {0,0,0} };
		position = { 4,0 };
		blocktype = 4;
		rect.setFillColor(sf::Color(230, 135, 41, 255));

		break;
	case 5: // S Block
		block.clear();
		block.resize(3, std::vector<int>(3));
		outline.setSize(sf::Vector2f(3 * cellsize, 3 * cellsize));

		block = { {0,1,1},{1,1,0}, {0,0,0} };
		position = { 4,0 };
		blocktype = 5;
		rect.setFillColor(sf::Color(7, 222, 28, 255));
		break;
	case 6: // Z Block
		block.clear();
		block.resize(3, std::vector<int>(3));
		block.resize(3, std::vector<int>(3));
		outline.setSize(sf::Vector2f(3 * cellsize, 3 * cellsize));

		block = { {1,1,0},{0,1,1}, {0,0,0} };
		position = { 4,0 };
		blocktype = 6;
		rect.setFillColor(sf::Color(148, 14, 7, 255));
		break;

	case 7: 
		block.clear();
		block.resize(4, std::vector<int>(4));
		outline.setSize(sf::Vector2f(4 * cellsize, 4 * cellsize));

		block = { {0,0,0,0},{1,1,1,1}, {0,0,0,0}, {0,0,0,0} };
		position = { 3,0 };
		blocktype = 7;
		rect.setFillColor(sf::Color(51, 184, 189, 255));
		break;
	default:
		break;
	}

	centercoordinates = (cellsize * block.size()) / 2;

}


void Blocks::rotateblock(Matrix matrix, int offset)
{
	
	// TODO Fix Collision
	rotation++;
	rotation -= offset;
	
	if (rotation > 4) {
		rotation = 1;
	}

	//std::cout << "\nRotated: " << rotation;
	switch (blocktype) {
	case 1:
		break;
	case 2: // T block
		if (rotation == 1) { newblock = { {0,0,0},{0,1,0}, {1,1,1} }; }
		if (rotation == 2) { newblock = { {1,0,0},{1,1,0}, {1,0,0} }; }
		if (rotation == 3) { newblock = { {1,1,1},{0,1,0}, {0,0,0} }; }
		if (rotation == 4) { newblock = { {0,0,1},{0,1,1}, {0,0,1} }; }
	break;
	case 3: // L BLOCK		 
		if (rotation == 1) { newblock = { {0,0,1},{1,1,1}, {0,0,0} }; }
		if (rotation == 2) { newblock = { {0,1,0},{0,1,0}, {0,1,1} }; }
		if (rotation == 3) { newblock = { {0,0,0},{1,1,1}, {1,0,0} }; }
		if (rotation == 4) { newblock = { {1,1,0},{0,1,0}, {0,1,0} }; }
		break;				 
	case 4: // J BLOCK		 
		if (rotation == 1) { newblock = { {1,0,0},{1,1,1}, {0,0,0} }; }
		if (rotation == 2) { newblock = { {0,1,1},{0,1,0}, {0,1,0} }; }
		if (rotation == 3) { newblock = { {0,0,0},{1,1,1}, {0,0,1} }; }
		if (rotation == 4) { newblock = { {0,1,0},{0,1,0}, {1,1,0} }; }
		break;				 
	case 5: // S BLOCK		 
		if (rotation == 1) { newblock = { {0,1,1},{1,1,0}, {0,0,0} }; }
		if (rotation == 2) { newblock = { {0,1,0},{0,1,1}, {0,0,1} }; }
		if (rotation == 3) { newblock = { {0,0,0},{0,1,1}, {1,1,0} }; }
		if (rotation == 4) { newblock = { {1,0,0},{1,1,0}, {0,1,0} }; }
		break;				 
	case 6: // Z BLOCK		 
		if (rotation == 1) { newblock = { {1,1,0},{0,1,1}, {0,0,0} }; }
		if (rotation == 2) { newblock = { {0,0,1},{0,1,1}, {0,1,0} }; }
		if (rotation == 3) { newblock = { {0,0,0},{1,1,0}, {0,1,1} }; }
		if (rotation == 4) { newblock = { {0,1,0},{1,1,0}, {1,0,0} }; }
		break;

	case 7: // I (LINE) BLOCK
		if (rotation == 1) { newblock = { {0,0,0,0},{1,1,1,1}, {0,0,0,0}, {0,0,0,0} }; }
		if (rotation == 2) { newblock = { {0,0,1,0},{0,0,1,0}, {0,0,1,0}, {0,0,1,0} }; }
		if (rotation == 3) { newblock = { {0,0,0,0},{0,0,0,0}, {1,1,1,1}, {0,0,0,0} }; }
		if (rotation == 4) { newblock = { {0,1,0,0},{0,1,0,0}, {0,1,0,0}, {0,1,0,0} }; }
		break;
	default:
		break;
	}
	if(blocktype != 1 && kickback(matrix))
	{
		for (int i = 0; i < newblock.size(); i++) {
			for (int j = 0; j < newblock[i].size(); j++) {
				block[i][j] = newblock[i][j];
			}
		}
	}
	else 
	{
		rotation--;
	}
}

bool Blocks::kickback(Matrix matrix)
{
	for (int i = 0; i < newblock.size(); i++) {
		for (int j = 0; j < newblock[i].size(); j++) {
			if (newblock[i][j] == 0) {
				continue;
			}
			if (i + position[1] < 0 || i + position[1] > rows - 1) {
				return false;
			}
			if (j + position[0] < 0 || j + position[0] > columns - 1) {
				return false;
			}
			if (matrix[i + position[1]][j + position[0]] != 0)
			{
				return false;
			}
		}
	}
	return true;
}



int Blocks::getblocksize()
{
	return block.size();
}



void Blocks::drawblock(sf::RenderWindow& window)
{
	for (int i = 0; i < block.size(); i++) {
		for (int j = 0; j < block[i].size(); j++) {
			if (block[i][j] != 0) {
				rect.setPosition(sf::Vector2f((j + position[0]) * cellsize, (i + position[1]) * cellsize));
				window.draw(rect);
			}
		}
	}
	//outline.setPosition(sf::Vector2f(position[0] * cellsize, position[1] * cellsize));
	//window.draw(outline);
}

void Blocks::drawblockOffGrid(sf::RenderWindow& window,int x, int y) {
	for (int i = 0; i < block.size(); i++) {
		for (int j = 0; j < block[i].size(); j++) {
			if (block[i][j] == 0)
				continue;

			rect.setPosition(sf::Vector2f(j * cellsize + x, i * cellsize + y));
			window.draw(rect);
		}
	}
	//outline.setPosition(sf::Vector2f(x,y));
	//window.draw(outline);
}