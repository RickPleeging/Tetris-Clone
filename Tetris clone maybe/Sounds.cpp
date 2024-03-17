#include "Sounds.h"

Sounds::Sounds()
{
	initSounds();
}



void Sounds::playSound(std::string sound)
{
	if (sound == "drop") {
		drop.play();
	}
	if (sound == "move") {
		move.play();
	}
	if (sound == "rotate") {
		rotate.play();
	}

}



void Sounds::initSounds()
{

	if (!dropbuffer.loadFromFile("..\\Assets\\Audio\\drop.wav")) {
		std::cout << "Error Loading soundfile\n";
	}

	if (!movebuffer.loadFromFile("..\\Assets\\Audio\\move.wav")) {
		std::cout << "Error Loading soundfile\n";
	}
	if (!rotatebuffer.loadFromFile("..\\Assets\\Audio\\rotate.wav")) {
		std::cout << "Error Loading soundfile\n";
	}
	rotate.setBuffer(rotatebuffer);
	rotate.setVolume(70);
	drop.setBuffer(dropbuffer);
	move.setBuffer(movebuffer);
	drop.setVolume(70);

}
