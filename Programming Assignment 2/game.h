/// <summary>
/// Author: Ben Millar – C00236772
/// Date: 01/03/2019
/// 
/// Description: A pacman clone where the player must navigate a 2D maze
/// collecting pellets, whilst FOUR ghost enemies try to catch the player.
/// The player wins the game if they collect all the pellets, and the player
/// loses if they are caught by the ghosts
/// 
/// Estimated time to complete: 12 hours
/// Session 1 Start: 18:45 End: 19:45
/// Session 2 Start: 18:00 End: 19:30
/// Session 3 Start: 09:30 End: 11:00
/// Session 4 Start: 14:30 End: 15:30 
/// Session 5 Start: 16:45 End: 17:10
/// Session 6 Start: 18:00 End: 18:45
/// Session 7 Start: 15:15 End: 16:30 
/// Session 8 Start: 13:30 End: 14:05 TOTAL TIME: 8:00
/// </summary>

// TO DO: Cells should have their own texture which they draw as appropriate; draw call should be sent to cells in render function.
// No drawing (of maze) should be done in the game.cpp -- DONE --

// Collision detection should be refactored to be based entirely off of cell information rather than getGlobalBounds. -- Not done, but improved --

#pragma once
#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MyVector3.h"
#include "Cell.h"
#include "Player.h"
#include "Ghost.h"

enum class gameState
{
	menu,
	gameplay,
	gameover
};

struct scoreEntry
{
	std::string name;
	int score;
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
	void setupMaze(); // set up our maze array from our int array
	void setupSprites(); // set up all images
	void inputText(sf::Event t_event, std::string & t_string, unsigned t_maxChars); // takes input from keyboard and assigns to string
	void update(sf::Time t_deltaTime); // main update method
	void checkCollisions(); // check collisions between game entities
	int countPellets(); // counts the number of pellets remaining in the game
	void render(); // renders framebuffer

	void saveScore(); // saves player score to a file

	void softReset(); // resets player and ghost positions after a player loses a life
	void hardReset(); // resets game to its initial state after a game over

	// +++++++++++++++++++++++++++++

	// +++++++++ Variables +++++++++

	bool m_exitGame = false; // control exiting game

	static const int NUM_ROWS = 20;
	static const int NUM_COLS = 20;
	static const int NUM_GHOSTS = 4;
	const sf::Vector2f M_GHOST_STARTING_POSITION[NUM_GHOSTS]
	{ 
		{ CELL_SIZE.x * 8.5f, CELL_SIZE.y * 9.5f }, 
		{ CELL_SIZE.x * 9.5f,CELL_SIZE.y * 9.5f },
		{ CELL_SIZE.x * 10.5f,CELL_SIZE.y * 9.5f },
		{ CELL_SIZE.x * 11.5f,CELL_SIZE.y * 9.5f } 
	};

	const sf::Vector2f M_PLAYER_STARTING_POSITION{ CELL_SIZE.x * 10.5f, CELL_SIZE.y * 11.5f };

	// Stores information on the game cells
	int gameMap[NUM_ROWS][NUM_COLS] = 
  { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,1,
	1,2,1,1,2,1,1,1,2,1,1,2,1,1,1,2,1,1,2,1,
	1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
	1,2,1,1,2,1,2,1,1,1,1,1,1,2,1,2,1,1,2,1,
	1,2,1,1,2,1,2,2,2,1,1,2,2,2,1,2,1,1,2,1,
	1,2,2,2,2,1,1,1,2,1,1,2,1,1,1,2,2,2,2,1,
	1,2,1,1,1,1,2,2,2,2,2,2,2,2,1,1,1,1,2,1,
	1,2,2,2,2,2,2,1,1,3,3,1,1,2,2,2,2,2,2,1,
	1,1,1,2,1,1,2,1,0,0,0,0,1,2,1,1,2,1,1,1,
	1,2,2,2,2,1,2,1,1,1,1,1,1,2,1,2,2,2,2,1,
	1,2,1,1,2,1,2,2,2,0,0,2,2,2,1,2,1,1,2,1,
	1,2,2,1,2,1,2,1,1,1,1,1,1,2,1,2,1,2,2,1,
	1,1,2,1,2,2,2,2,2,1,1,2,2,2,2,2,1,2,1,1,
	1,1,2,1,2,1,1,1,2,1,1,2,1,1,1,2,1,2,1,1,
	1,1,2,1,2,2,2,2,2,2,2,2,2,2,2,2,1,2,1,1,
	1,2,2,1,2,1,2,1,1,1,1,1,1,2,1,2,1,2,2,1,
	1,2,1,1,2,1,2,2,2,1,1,2,2,2,1,2,1,1,2,1,
	1,2,2,2,2,2,2,1,2,2,2,2,1,2,2,2,2,2,2,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };

	std::string m_playerNameString; // used to store the players name

	int m_playerScore; // stores the players current score
	const int m_pelletScore = 10;

	// +++++++++++++++++++++++++++++

	// ++++++++++ Objects ++++++++++

	sf::RenderWindow m_window; // main SFML window

	gameState m_currentState; // current game state (menu/gameplay/gameover)

	sf::Texture m_livesTexture;
	sf::Sprite m_livesSprite;

	sf::Font m_ArialBlackfont;
	sf::Text m_HUDText; // displays information to the user (name/score/instructions)

	// entities
	Player m_player; // instance of object of type player
	Ghost m_ghost[NUM_GHOSTS]; // array of objects of type ghost

	sf::Clock m_ghostClock;
	sf::Time m_ghostTimer[NUM_GHOSTS] =
	{
		sf::seconds(2.0f),
		sf::seconds(5.0f),
		sf::seconds(10.0f),
		sf::seconds(15.0f)
	};

	sf::RectangleShape m_wall;
	sf::RectangleShape m_door;
	sf::CircleShape m_pellet;

	// Array of cells
	Cell maze[NUM_ROWS][NUM_COLS];

	// +++++++++++++++++++++++++++++
};

#endif // !GAME