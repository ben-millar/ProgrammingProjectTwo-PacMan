/// <summary>
/// Author: Ben Millar – C00236772
/// Date: 01/03/2019
/// Estimated time to complete: 12 hours
/// Session 1 Start: 18:45 End: 19:45
/// Session 2 Start: 18:00 End: 19:30
/// Session 3 Start: 09:30 End: 11:00
/// Session 4 Start: 14:30 End: 15:30 
/// Session 5 Start: 16:45 End: 17:10 TOTAL TIME: 5:25
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
	void inputText(sf::Event t_event, std::string & t_string, unsigned t_maxChars); // takes input from keyboard and assigns to string
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

	std::string m_playerNameString;

	// +++++++++++++++++++++++++++++

	// ++++++++++ Objects ++++++++++
	sf::RenderWindow m_window; // main SFML window

	gameState currentState;

	sf::Font m_ArialBlackfont;
	sf::Text m_instructionsText;
	sf::Text m_playerNameText;

	Player m_player;

	sf::RectangleShape wall;
	sf::CircleShape pellet;

	Cell maze[NUM_ROWS][NUM_COLS];

	// +++++++++++++++++++++++++++++
};

#endif // !GAME