#include "Menu.h"
#include "Game.h"

class Game;

Menu::Menu(sf::RenderWindow& windowref, sf::Font& globalFont)
	: window(windowref), font(globalFont), start(windowref,globalFont, "start"), settings(windowref, globalFont, "settings")
{
	start.setPosition((g_windowwidth / 2) - 25, g_windowheight / 2);




	settings.setPosition((g_windowwidth / 2) - 25, (g_windowheight / 2) + 150);
}

void Menu::updateMenu() {

	auto mousePos = sf::Mouse::getPosition(window);

	start.updateButton();
	settings.updateButton();

	if (start.isPressed(mousePos)) {
		std::cout << "pressed";
		Game::gameState = Game::GameState::Playing;
	}

}
void Menu::renderMenu() {

	window.clear(sf::Color::Black);

	settings.drawButton();
	start.drawButton();

	window.display();
}
