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
	window.create(sf::VideoMode(g_windowwidth,g_windowheight ), "Teris");
	window.setFramerateLimit(144);

	//variables
	speed = 0.5;
	isfalling = false;
	isrunning = true;

	//initiate 1 block + 3 previews 
	nextblock.push(generateRandomNumber(1, 7));
	nextblock.push(generateRandomNumber(1, 7));
	nextblock.push(generateRandomNumber(1, 7));

	
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
	if (!window.isOpen()) {
		return false;
	}
	return isrunning;
}



void Game::update()
{
	//Revamp this thing please for the love of god its bad 
	

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
		grid.update();
		UserInterface.updatescore(grid.score);
		UserInterface.updateHighScore(grid.highscore);

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
			if (ev.key.code == sf::Keyboard::Up) {
				block.rotateblock(grid.matrix,0);
			}
			if (ev.key.code == sf::Keyboard::R) {
				grid.gridclear();
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

	UserInterface.renderui(window);

	window.display();
}

void Game::gamereset()
{
	grid.score = 0;
	grid.gridclear();
}

void Game::savedata()
{

	std::ifstream check("tetrissavedata.txt");
	if (!check.good()) {
		std::ofstream outputFile("tetrissavedata.txt");
		std::cout << "Creating tetrissavedata.txt";
	}

	//Encrypt score
	int key = grid.highscore *2 / (sin(grid.highscore+5));

	std::string encryptedscore = std::to_string(grid.highscore) + ":" + std::to_string(key);
	std::cout << "\nencryptedscore = " << encryptedscore;

	std::ofstream file("tetrissavedata.txt");
	if (file.is_open()) {
		file << encryptedscore;
		file.close();
	}
}
void Game::loaddata()
{
	std::string encryptedscore;


	std::ifstream file("tetrissavedata.txt");
	if (file.is_open()) {
		file >> encryptedscore;
	}
	//decrypt check
	size_t colon_pos = encryptedscore.find(':');
	std::string score_str = encryptedscore.substr(0, colon_pos);
	std::string key_str = encryptedscore.substr(colon_pos + 1);
	int score;
	int key;
	std::istringstream(score_str) >> score;
	std::istringstream(key_str) >> key;
	int result = score * 2 / (sin(score + 5));
	if (key == result) {
		std::cout << "key correct!";
		grid.highscore = score;
	}
	else {
		std::cout << "key false!";
	}

}



int Game::generateRandomNumber(int min, int max)
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);

}


