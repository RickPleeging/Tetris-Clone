#include "Game.h"


//Constructors and Destructors
Game::Game() :UserInterface(globalFont), menu(window,globalFont)
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
	window.create(sf::VideoMode(g_windowwidth, g_windowheight), "Teris");
	window.setFramerateLimit(144);

	//variables
	speed = 0.5;
	isfalling = false;
	isrunning = true;

	//initiate 1 block + 3 previews 
	nextblock.push(generateRandomNumber(1, 7));
	nextblock.push(generateRandomNumber(1, 7));
	nextblock.push(generateRandomNumber(1, 7));


	//Font
	if (!globalFont.loadFromFile("..\\Assets\\arial.ttf"))
	{
		std::cout << "error loading font!";
	}


}
//init const Gamestate
Game::GameState Game::gameState = Game::GameState::Menu;


//Functions
void Game::run()
{
	sf::Time dt = clock.restart();
	float dts = dt.asMicroseconds();


	while (window.pollEvent(ev)) {
		handleEvents(ev);
	}

	switch (gameState)
	{
	case Game::GameState::Menu:
		menu.updateMenu();
		menu.renderMenu();
		break;
	case Game::GameState::Playing:
		updateGame();
		renderGame();
		break;
	case Game::GameState::GameOver:
		break;
	default:
		break;
	}


	//std::cout << dts << "\n";
}

void Game::handleEvents(const sf::Event& event)
{


	switch (ev.type) {
	case sf::Event::Closed:
		window.close();
		break;
	case sf::Event::KeyPressed:
		if (ev.key.code == sf::Keyboard::X) 
			window.close();
		break;
	default:
		break;
	}



	switch (gameState)
	{
	case Game::GameState::Menu:
		break;
	case Game::GameState::Playing:
		if (ev.type == sf::Event::KeyPressed) 
		{

			if (ev.key.code == sf::Keyboard::Left) {
				block.moveleft(grid.matrix);

				sounds.playSound("move");

			}
			if (ev.key.code == sf::Keyboard::Right) {
				block.moveright(grid.matrix);
				sounds.playSound("move");

			}
			if (ev.key.code == sf::Keyboard::Up) {
				block.rotateblock(grid.matrix, 0);
				sounds.playSound("rotate");

			}
			if (ev.key.code == sf::Keyboard::R) {
				grid.gridclear();
			}
			if (ev.key.code == sf::Keyboard::Down) {
				if (droptimer.getElapsedTime().asSeconds() > 0.2)
				{
					block.drop(grid.matrix);
					sounds.playSound("drop");
					droptimer.restart();
					falltimer.restart();
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Hyphen)) {
				speed += 0.05;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) {
				speed -= 0.05;
			}
		}

		break;
	case Game::GameState::GameOver:
		break;
	default:
		break;
	}



}

bool Game::isRunning()
{
	if (!window.isOpen()) {
		return false;
	}
	return isrunning;
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
	int key = grid.highscore * 2 / (sin(grid.highscore + 5));

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
	if (!file.good()) {
		std::cout << "no savefile found.";
		return;
	}
	else if (file.is_open()) {
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

