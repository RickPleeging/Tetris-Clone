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
	columns = g_columns;
	rows = g_rows;
	cellsize = g_cellSize;
	//init window
	ev = sf::Event();
	window.create(sf::VideoMode(cellsize*columns+200, cellsize * rows +150), "Teris");
	window.setFramerateLimit(144);

	//variables
	speed = 0.5;
	isfalling = false;
	isrunning = true;

	//randomizer

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
	return isrunning;
}



void Game::update()
{
	//Add Gamelogic here
	static int type = 1;

	if (!isfalling) {




		if (!block.createblock(generateRandomNumber(1,7), grid.matrix)) {
			//Add Gameover here
			std::cout << "Game over\n";
			isrunning = false;
		}

		isfalling = true;
	}
	if (falltimer.getElapsedTime().asSeconds() > speed) {
		falltimer.restart();
		if (!block.updateblock(grid.matrix)) {
			isfalling = false;
		}

	}
		grid.update();
	return;
}

void Game::updateEvents()
{
	while (window.pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed) {
			window.close();
		}
		if (ev.type == sf::Event::KeyPressed) {
			if (ev.key.code == sf::Keyboard::X)
			{
				window.close();
			}
			if (ev.key.code == sf::Keyboard::Left) {
				block.moveleft(grid.matrix);

			}
			if (ev.key.code == sf::Keyboard::Right) {
				block.moveright(grid.matrix);

			}
			if (ev.key.code == sf::Keyboard::R) {
				block.rotateblock();
			}
			if (ev.key.code == sf::Keyboard::Down) {
				if (droptimer.getElapsedTime().asSeconds() > 0.2) {
					block.drop(grid.matrix);
					droptimer.restart();
				}
			}

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Hyphen)) {
			speed+=0.05;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) {
			speed-=0.05;
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

int Game::generateRandomNumber(int min, int max)
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);

}


