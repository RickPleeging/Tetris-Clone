#pragma once
#include <iostream>
#include "SFMLWRAPPER.h"
class Sounds
{
public:
	Sounds();

	void playSound(std::string sound);

private:
	void initSounds();
	sf::SoundBuffer dropbuffer;
	sf::SoundBuffer movebuffer;
	sf::SoundBuffer rotatebuffer;

	sf::Sound drop;
	sf::Sound move;
	sf::Sound rotate;
};

