#pragma once
#include <SFML/graphics.hpp>
#include <sstream>
#include "gameconfig.h"
#include "Blocks.h"


//Class For the UI of the game
class UI
{
public:
	UI();
	void renderui(sf::RenderWindow& window);
	void updateui();
	void updatepreview(int blocktype);
	void updatescore(int score);
	void updateHighScore(int highscore);

private:
	void initVariables();
	void initPreview();
	void drawscore(sf::RenderWindow& window);
	void drawHighScore(sf::RenderWindow& window); //fortnite
	void drawpreview(sf::RenderWindow& window);
	void initfont();
	int columns;
	int rows;
	float cellsize;

	int prev_x;
	int prev_y;
	Blocks previewblock;
	sf::RectangleShape PreviewWindow;
	float previewsize;
	
	sf::Font font;
	sf::Text t_score;
	sf::Text t_highscore;
	int m_highscore;
};

