#pragma once
#include "SFMLWRAPPER.h"
#include "Button.h"


class Menu
{
public:
	Menu(sf::RenderWindow& windowref,sf::Font& globalFont);

	void updateMenu();
	void renderMenu();


private:
	Button start;
	Button settings;

	sf::RenderWindow& window;


	sf::Font& font;
};

