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
	//position x,y // rows,collumns
	position.clear();
	position.resize(2);

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
	int empty=0;
	//Find Ammount of empty rows starting from the bottom
	for (int i = block.size()-1; i >= 0; i--) {
		for (int j = 0; j < block[i].size(); j++) {
			if (block[i][j] == 1)
				break;
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
	placeblock(matrix, position);
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
			if (block[i][j] == 0)
				continue;
			if (matrix[i+position[1]][j+position[0]] != 0)
				return false;
		}
	}

	return true;
}

bool Blocks::createblock(int type, Matrix matrix)
{
	switch (type)
	{
	case 1: //square
		block.clear();
		block.resize(2, std::vector<int>(2));
		outline.setSize(sf::Vector2f(2*cellsize, 2*cellsize));

		block[0][0] = 1;
		block[0][1] = 1;
		block[1][0] = 1;
		block[1][1] = 1;
		blocktype = 1;
		rect.setFillColor(sf::Color(223, 227, 11, 255));

		position = { 4,0 };
		break;
	case 2: //T BLOCK

		block.clear();
		block.resize(3, std::vector<int>(3));
		outline.setSize(sf::Vector2f(3 * cellsize, 3 * cellsize));

		block[0][0] = 1;
		block[0][1] = 1;
		block[0][2] = 1;

		block[1][0] = 0;
		block[1][1] = 1;
		block[1][2] = 0;
		blocktype = 2;
		rect.setFillColor(sf::Color(165, 9, 171, 255));
		position = { 4,0 };
		break;
	case 3: // L Block
		block.clear();
		block.resize(3, std::vector<int>(3));
		outline.setSize(sf::Vector2f(3 * cellsize, 3 * cellsize));

		block[0][0] = 1;
		block[0][1] = 0;
		block[0][2] = 0;

		block[1][0] = 1;
		block[1][1] = 0;
		block[1][2] = 0;

		block[2][0] = 1;
		block[2][1] = 1;
		block[2][2] = 0;


		position = { 4,0 };
		blocktype = 3;
		rect.setFillColor(sf::Color(60, 65, 230, 255));
		break;
	case 4: // J Block
		block.clear();
		block.resize(3, std::vector<int>(3));
		outline.setSize(sf::Vector2f(3 * cellsize, 3 * cellsize));

		block[0][0] = 0;
		block[0][1] = 0;
		block[0][2] = 1;

		block[1][0] = 0;
		block[1][1] = 0;
		block[1][2] = 1;

		block[2][0] = 0;
		block[2][1] = 1;
		block[2][2] = 1;
		position = { 4,0 };
		blocktype = 4;
		rect.setFillColor(sf::Color(230, 135, 41, 255));

		break;
	case 5: // S Block
		block.clear();
		block.resize(3, std::vector<int>(3));
		outline.setSize(sf::Vector2f(3 * cellsize, 3 * cellsize));

		block[0][0] = 0;
		block[0][1] = 1;
		block[0][2] = 1;

		block[1][0] = 1;
		block[1][1] = 1;
		block[1][2] = 0;

		block[2][0] = 0;
		block[2][1] = 0;
		block[2][2] = 0;
		position = { 4,0 };
		blocktype = 5;
		rect.setFillColor(sf::Color(7, 222, 28, 255));
		break;
	case 6: // Z Block
		block.clear();
		block.resize(3, std::vector<int>(3));
		block.resize(3, std::vector<int>(3));
		outline.setSize(sf::Vector2f(3 * cellsize, 3 * cellsize));

		block[0][0] = 1;
		block[0][1] = 1;
		block[0][2] = 0;

		block[1][0] = 0;
		block[1][1] = 1;
		block[1][2] = 1;

		block[2][0] = 0;
		block[2][1] = 0;
		block[2][2] = 0;
		position = { 4,0 };
		blocktype = 6;
		rect.setFillColor(sf::Color(148, 14, 7, 255));
		break;

	case 7: 
		block.clear();
		block.resize(4, std::vector<int>(4));
		outline.setSize(sf::Vector2f(4 * cellsize, 4 * cellsize));

		block[0][0] = 0;
		block[0][1] = 0;
		block[0][2] = 1;
		block[0][3] = 0;

		block[1][0] = 0;
		block[1][1] = 0;
		block[1][2] = 1;
		block[1][3] = 0;

		block[2][0] = 0;
		block[2][1] = 0;
		block[2][2] = 1;
		block[2][3] = 0;

		block[3][0] = 0;
		block[3][1] = 0;
		block[3][2] = 1;
		block[3][3] = 0;
		position = { 3,0 };
		blocktype = 7;
		rect.setFillColor(sf::Color(51, 184, 189, 255));
		break;
	default:
		break;
	}

	if (checkspace(matrix)) {
		return true;
	}
	else
	{
		return false;
	}

}


void Blocks::rotateblock()
{
	std::vector<std::vector<int>> rotatedBlock;
	int blockSize = block.size();

	// Transpose the block matrix to rotate it clockwise
	for (int i = 0; i < blockSize; ++i) {
		rotatedBlock.push_back(std::vector<int>());
		for (int j = 0; j < blockSize; ++j) {
			rotatedBlock[i].push_back(block[blockSize - 1 - j][i]);
		}
	}

	// Update the block with the rotated block
	block = rotatedBlock;

	// Update the outline size accordingly
	outline.setSize(sf::Vector2f(blockSize * cellsize, blockSize * cellsize));

	//// Check if the rotated block can fit in the current position
	//if (!checkspace(matrix)) {
	//	// Revert the block to its original state if it cannot fit
	//	block = rotatedBlock;
	//}
}



void Blocks::getblocktype()
{

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
	outline.setPosition(sf::Vector2f(position[0]*cellsize, position[1]*cellsize));
	window.draw(outline);
}
