#pragma once
#include <SFML/graphics.hpp>
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
private:
	void initVariables();
	void initPreview();
	void drawscore(sf::RenderWindow& window);
	void drawpreview(sf::RenderWindow& window);
	
	int columns;
	int rows;
	float cellsize;

	int prev_x;
	int prev_y;
	Blocks previewblock;
	sf::RectangleShape PreviewWindow;
	float previewsize;
	
	
};

