#include "Button.h"


Button::Button(sf::RenderWindow& windowref,sf::Font& globalFont, std::string text) : window(windowref), font(globalFont)
{

	buttontext.setFont(font);
	buttontext.setString(text);
	initButton();

}

void Button::initButton()
{
	button.setPosition(sf::Vector2f(0, 0));
	button.setSize(sf::Vector2f(50, 50));
	button.setFillColor(sf::Color(0, 255, 0, 255));

	state = Buttonstate::normal;

	buttontext.setPosition(sf::Vector2f(0, 0));
	buttontext.setCharacterSize(50);
	buttontext.setFillColor(sf::Color::White);

}



void Button::updateButton()
{

	auto mousePos = sf::Mouse::getPosition(window);
	if (mousePos.x < 0 || mousePos.x > g_windowwidth || mousePos.y < 0 || mousePos.y > g_windowheight) {
		state = Buttonstate::normal;
		return;
	}
	
	if (isMouseOver(mousePos)) {
		state = Buttonstate::hovered;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			state = Buttonstate::clicked;
		}
	}
	else {
		state = Buttonstate::normal;
	}


	switch (state)
	{
	case Button::normal:
		button.setFillColor(sf::Color(0, 255, 0, 255));
		break;
	case Button::hovered:
		button.setFillColor(sf::Color(0, 255, 0, 155));
		break;
	case Button::clicked:
		button.setFillColor(sf::Color(255, 0, 0, 255));
		break;
	default:
		break;
	}
}


bool Button::isMouseOver(const sf::Vector2i& mousePos) const
{
	sf::FloatRect buttonBounds = button.getGlobalBounds();
	if (buttonBounds.contains(static_cast<sf::Vector2f>(mousePos))) {
		return true;
	}

	return false;
}

bool Button::isPressed(const sf::Vector2i& mousePos) const
{
	if (isMouseOver(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		return true;
	}

	return false;
}

void Button::setPosition(float x, float y)
{
	button.setPosition(sf::Vector2f(x, y));
	buttontext.setPosition(sf::Vector2f(x, y));
}

void Button::setSize(float height,float width)
{
	button.setSize(sf::Vector2f(height, width));
	buttontext.setCharacterSize(static_cast<unsigned int>(height / 2));
}

void Button::drawButton()
{
	window.draw(button);
	window.draw(buttontext);
}