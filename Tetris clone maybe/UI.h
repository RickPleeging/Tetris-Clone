#pragma once
#include <SFML/graphics.hpp>
//Class For the UI of the game
class UI
{
public:
	UI();
	void renderui(sf::RenderWindow& window);
	void updateui();
private:
	void renderscore();
	void initVariables();

};

