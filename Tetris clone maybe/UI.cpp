#include "UI.h"


UI::UI()
{
	initVariables();
}

void UI::initVariables()
{
	//globals
	columns = g_columns;
	rows = g_rows;
	cellsize = g_cellSize;
	//Preview Window
	initPreview();
}

void UI::initPreview()
{
	//previewwindow
	previewsize = cellsize*4;

	PreviewWindow.setSize(sf::Vector2f(previewsize, previewsize));
	//middle of gameboard and edge?
	prev_x = g_gamewidth + (g_windowwidth - g_gamewidth)/2 -previewsize/2;
	prev_y = 70;
	PreviewWindow.setPosition(sf::Vector2f(prev_x, prev_y));
	PreviewWindow.setFillColor(sf::Color::Transparent);
	PreviewWindow.setOutlineColor(sf::Color::Cyan);
	PreviewWindow.setOutlineThickness(2);
}



void UI::renderui(sf::RenderWindow& window)
{

	drawscore(window);
	drawpreview(window);

}

void UI::updateui()
{
}

void UI::drawscore(sf::RenderWindow& window)
{
}

void UI::drawpreview(sf::RenderWindow& window)
{
	window.draw(PreviewWindow);
	float offset;
	switch (previewblock.getblocksize()) {
	case 2:
		offset = cellsize;
		break;
	case 3:
		offset = cellsize/2;
		break;
	case 4:
		offset = 0;
		break;
	}
	previewblock.drawblockOffGrid(window,prev_x+offset,prev_y+offset);
}

void UI::updatepreview(int blocktype)
{
	previewblock.createblock(blocktype);


}

