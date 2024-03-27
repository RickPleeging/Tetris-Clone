#include "Game.h"

void Game::updateGame()
{


	if (!isfalling) // if the block is placed into the grid
	{

		//create block from queue
		block.createblock(nextblock.front());
		nextblock.pop();
		nextblock.push(generateRandomNumber(1, 7));
		UserInterface.updatepreview(nextblock.front());
		//check if blockcreation possible
		if (!block.checkspace(grid.matrix)) {
			//if cant create block, gameover
			std::cout << "Game over\n";
			sf::Clock looseclock;
			looseclock.restart();
			while (looseclock.getElapsedTime().asSeconds() < 2) {

			}
			gamereset();
		}

		isfalling = true;
	}
	if (falltimer.getElapsedTime().asSeconds() > speed) {
		falltimer.restart();
		if (!block.updateblock(grid.matrix)) {
			isfalling = false;
		}
	}

	block.setghostblock(grid.matrix);

	grid.update();
	UserInterface.updatescore(grid.score);
	UserInterface.updateHighScore(grid.highscore);

	return;
}

void Game::renderGame()
{
	window.clear(sf::Color::Black);

	//Draw Objects
	grid.drawgrid(window);

	block.drawblock(window);
	block.drawghostblock(window);


	UserInterface.renderui(window);

	window.display();
}

