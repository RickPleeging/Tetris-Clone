#include "Game.h"

//Constructors and Destructors
Game::Game()
{
	initVariables();
}

Game::~Game()
{

}
//Private Functions
void Game::initVariables()
{
	//globals
	rows = g_rows;
	columns = g_columns;
	cellsize = g_cellSize;
	//init window
	ev = sf::Event();
	window.create(sf::VideoMode(cellsize*rows, cellsize * columns), "SFML Game");
	window.setFramerateLimit(144);

	//variables
	speed = 1;
	isfalling = false;
	

}



//Functions
void Game::run()
{
	sf::Time dt = clock.restart();
	float dts = dt.asMicroseconds();

	updateEvents();
	update();
	render();

	//std::cout << dts << "\n";
}

bool Game::isRunning()
{
	return window.isOpen();
}


void Game::update()
{
	//Add Gamelogic here


	if (!isfalling) {
		block.createblock(1);
		isfalling = true;
	}
	if (falltimer.getElapsedTime().asSeconds() > speed) {
		falltimer.restart();
		block.movedown();
	}

	return;
}

void Game::updateEvents()
{
	while (window.pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed) {
			window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
			window.close();
		}
	}
}

void Game::render()
{
	window.clear(sf::Color::Black);

	//Draw Objects
	grid.drawgrid(window);

	block.drawblock(window);

	window.display();
}


