/// <summary>
/// Author: Ben Millar – C00236772
/// Date: 01/03/2019
/// Estimated time to complete: 12 hours
/// Session 1 Start: 18:45 End: 19:45
/// </summary>

#pragma once
#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MyVector3.h"
#include "Cell.h"
#include "Player.h"

enum class gameState
{
	menu,
	gameplay,
	gameover
};

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

	bool m_exitGame = false; // control exiting game

	static const int NUM_ROWS = 20;
	static const int NUM_COLS = 20;

	int gameMap[NUM_ROWS][NUM_COLS] = 
  { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,1,
	1,2,1,1,2,1,1,1,2,1,1,2,1,1,1,2,1,1,2,1,
	1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
	1,2,1,1,2,1,2,1,1,1,1,1,1,2,1,2,1,1,2,1,
	1,2,1,1,2,1,2,2,2,1,1,2,2,2,1,2,1,1,2,1,
	1,2,2,2,2,1,1,1,2,1,1,2,1,1,1,2,2,2,2,1,
	1,2,1,1,1,1,2,2,2,2,2,2,2,2,1,1,1,1,2,1,
	1,2,2,2,2,2,2,1,1,1,1,1,1,2,2,2,2,2,2,1,
	1,1,1,2,1,1,2,1,0,0,0,0,1,2,1,1,2,1,1,1,
	1,2,2,2,2,1,2,1,1,1,1,1,1,2,1,2,2,2,2,1,
	1,2,1,1,2,1,2,2,2,2,2,2,2,2,1,2,1,1,2,1,
	1,2,2,1,2,1,2,1,1,1,1,1,1,2,1,2,1,2,2,1,
	1,1,2,1,2,2,2,2,2,1,1,2,2,2,2,2,1,2,1,1,
	1,1,2,1,2,1,1,1,2,1,1,2,1,1,1,2,1,2,1,1,
	1,1,2,1,2,2,2,2,2,2,2,2,2,2,2,2,1,2,1,1,
	1,2,2,1,2,1,2,1,1,1,1,1,1,2,1,2,1,2,2,1,
	1,2,1,1,2,1,2,2,2,1,1,2,2,2,1,2,1,1,2,1,
	1,2,2,2,2,2,2,1,2,2,2,2,1,2,2,2,2,2,2,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };

	// +++++++++++++++++++++++++++++

	// ++++++++++ Objects ++++++++++
	sf::RenderWindow m_window; // main SFML window

	gameState currentState;

	sf::Font m_ArialBlackfont;
	Player m_player;

	sf::RectangleShape wall;
	sf::CircleShape pellet;

	Cell maze[NUM_ROWS][NUM_COLS];

	// +++++++++++++++++++++++++++++
};

#endif // !GAME