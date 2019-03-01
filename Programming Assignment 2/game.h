/// <summary>
/// Author: Ben Millar – C00236772
/// Date: 01/03/2019
/// Estimated time to complete: 12 hours
/// Session 1 Start: End:
/// </summary>

#pragma once
#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MyVector3.h"

class Game
{
public:

	Game();
	~Game();
	void run();

private:

	// ++++++++++ Methods ++++++++++

	void processEvents(); // checks for all input
	void setupFontAndText(); // set up all text
	void setupSounds(); // set up all sounds
	void setupObjects(); // set up all sfml objects
	void setupSprites(); // set up all images
	void update(sf::Time t_deltaTime); // main update method
	void render(); // renders framebuffer

	// +++++++++++++++++++++++++++++

	// +++++++++ Variables +++++++++
	sf::Vector2f m_mouseClick = { 0,0 }; // {x,y} of mouse click 

	bool m_exitGame = false; // control exiting game

	// +++++++++++++++++++++++++++++

	// ++++++++++ Objects ++++++++++
	sf::RenderWindow m_window; // main SFML window

	sf::Font m_ArialBlackfont;

	// +++++++++++++++++++++++++++++
};

#endif // !GAME