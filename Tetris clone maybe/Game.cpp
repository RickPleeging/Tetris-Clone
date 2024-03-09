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
	//init window
	ev = sf::Event();
	window.create(sf::VideoMode(cellsize*rows, cellsize * columns), "SFML Game");
	window.setFramerateLimit(144);
	//init Grid
	matrix.resize(rows+1, std::vector<int>(columns+1));
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			matrix[i][j] = 0;
		}
	}
	//init Gridblock
	gridblock.setSize(sf::Vector2f(cellsize, cellsize));
	gridblock.setFillColor(sf::Color::Black);
	gridblock.setOutlineColor(sf::Color::Cyan);
	gridblock.setOutlineThickness(1);
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
		block.createblock();
		isfalling = true;
	}
	if (falltimer.getElapsedTime().asSeconds() > 0.02) {
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
		if (window.hasFocus())
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				sf::Vector2i mousepos = sf::Mouse::getPosition(window);
				if (mousepos.x / cellsize > rows || mousepos.x / cellsize < 0)
					break;
				if (mousepos.y/cellsize > columns || mousepos.y/cellsize < 0)
					break;
				std::cout << mousepos.x / cellsize << " y:" << mousepos.y / cellsize << "\n";
				matrix[mousepos.x/cellsize][mousepos.y/cellsize] = 1;
			}
		}
		

	}
}

void Game::render()
{
	window.clear(sf::Color::Black);

	//Draw Objects
	drawgrid();

	block.drawblock(window);

	window.display();
}

void Game::drawgrid()
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			gridblock.setPosition(sf::Vector2f(i*cellsize, j*cellsize));
			if (matrix[i][j] == 1) {
				gridblock.setFillColor(sf::Color::Red);
			}
			else
			{
				gridblock.setFillColor(sf::Color::Black);
			}
			window.draw(gridblock);
		}
	}
			
}
