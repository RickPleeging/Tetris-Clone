#pragma once
#include "SFMLWRAPPER.h"
#include <iostream>
#include "gameconfig.h"

class Button
{
public:
	Button(sf::RenderWindow& windowref,sf::Font& globalFont, std::string text);

	void initButton();

	void updateButton();
	void drawButton();

	void setPosition(float x, float y);
	void setSize(float height, float length);

	bool isMouseOver(const sf::Vector2i& mousePos) const;
	bool isPressed(const sf::Vector2i& mousePos) const;
private:
	

	sf::RenderWindow& window;

	sf::RectangleShape button;
	sf::Font& font;
	sf::Text buttontext;

	enum Buttonstate 
	{
		normal=0,
		hovered=1,
		clicked=2
	};
	Buttonstate state;

};

