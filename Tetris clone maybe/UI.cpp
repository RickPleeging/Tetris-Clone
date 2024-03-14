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
	initfont();
	//score
	t_score.setString("0");
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
void UI::initfont()
{

	if (!font.loadFromFile("..\\Assets\\arial.ttf")) {
		std::cout << "error loading font!";
	}

	t_score.setFont(font);
	t_score.setFillColor(sf::Color::White);
	t_score.setCharacterSize(40);
	t_score.setPosition(40, g_gameheight+50);

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
	window.draw(t_score);
}

void UI::updatescore(int score)
{
	std::ostringstream scorestring;
	scorestring << "SCORE: " << score;
	t_score.setString(scorestring.str());
	
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

