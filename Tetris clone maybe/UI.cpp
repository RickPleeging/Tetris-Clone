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
	int x = g_windowwidth - g_gamewidth;
	int y = 50;
	PreviewWindow.setPosition(sf::Vector2f(x, y));
	PreviewWindow.setFillColor(sf::Color::Yellow);
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
	window.draw(PreviewWindow);
}

void UI::drawpreview(sf::RenderWindow& window)
{
}

