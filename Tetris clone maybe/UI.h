#pragma once
#include <SFML/graphics.hpp>
#include "gameconfig.h"

//Class For the UI of the game
class UI
{
public:
	UI();
	void renderui(sf::RenderWindow& window);
	void updateui();
private:
	void initVariables();
	void initPreview();
	void drawscore(sf::RenderWindow& window);
	void drawpreview(sf::RenderWindow& window);
	
	int columns;
	int rows;
	float cellsize;

	sf::RectangleShape PreviewWindow;
	float previewsize;
	
	
};

