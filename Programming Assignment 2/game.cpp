/// <summary>
/// Author: Ben Millar – C00236772
/// Date: 01/03/2019
/// Estimated time to complete: 12 hours
/// Session 1 Start: 18:45 End: 19:45
/// Session 2 Start: 18:00 End: 19:30
/// Session 3 Start: 09:30 End: 11:00
/// Session 4 Start: 14:30 End: 15:30 
/// Session 5 Start: 16:45 End: 17:10
/// Session 6 Start: 18:00 End: 18:45 TOTAL TIME: 6:10
/// </summary>

#include "game.h"
#include "GLOBALS.h"
#include <iostream>

/// <summary>
/// default construcor
/// pass parameters for sfml window, setup m_exitGame
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ SCREEN_SIZE.x, SCREEN_SIZE.y, 32 }, "SFML Game" },
	m_exitGame{ false } //when true game will exit
{
#ifdef _DEBUG
	m_currentState = gameState::gameplay;
	m_playerNameString = "Debug";
#else
	m_currentState = gameState::menu;
#endif
	setupFontAndText(); // load font 
	setupObjects(); // set sfml object parameters
	setupSprites(); // load and setup textures
	setupSounds(); // load and setup sound buffers
}

/// <summary>
/// default destructor for game, nothing to release
/// </summary>
Game::~Game()
{
}

/// <summary>
/// game loop running at 60fps
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	srand(static_cast<unsigned>(time(nullptr)));
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type) // window message
		{
			m_window.close();
		}
		if (sf::Event::KeyPressed == event.type) //user key press
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_exitGame = true;
			}
		}

		// ++++++++ Checks gamestate and takes keyboard events as required ++++++++
		switch (m_currentState)
		{
		// ++++++++ MENU ++++++++
		case gameState::menu: 

			// proceed to gameplay when they press enter
			if (sf::Event::KeyPressed == event.type)
			{
				if (sf::Keyboard::Enter == event.key.code)
				{
					m_currentState = gameState::gameplay;
				}
			}

			// take player input
			if (sf::Event::TextEntered == event.type)
			{
				inputText(event, m_playerNameString, 16);
			}
			
			break;
		// ++++++++ GAMEPLAY ++++++++
		case gameState::gameplay: 

			if (sf::Event::KeyPressed == event.type)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					m_player.changeDirection(direction::up, maze);
					break;
				case sf::Keyboard::Down:
					m_player.changeDirection(direction::down, maze);
					break;
				case sf::Keyboard::Left:
					m_player.changeDirection(direction::left, maze);
					break;
				case sf::Keyboard::Right:
					m_player.changeDirection(direction::right, maze);
					break;
				default:
					break; // break out of KeyPress event
				}
			break; // break out of gameplay
		// ++++++++ GAME OVER ++++++++
		case gameState::gameover: 
			break;

		default:
			break;
			}
		}
	}
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	m_HUDText.setFont(m_ArialBlackfont);
	m_HUDText.setFillColor(sf::Color::White);
	m_HUDText.setString("");
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Game::setupSounds()
{
	
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Game::setupSprites()
{

}


///<summary>
/// sets up attributes for all SFML objects
///</summary>
void Game::setupObjects()
{
	// Set up maze array using game map
	for (int i = 0; i < NUM_ROWS; i++)
	{
		for (int j = 0; j < NUM_COLS; j++)
		{
			if (gameMap[i][j] == 1)
			{
				maze[i][j].setType(cellType::wall);
			}
			else if (gameMap[i][j] == 2)
			{
				maze[i][j].setType(cellType::pellet);
			}
			else if (gameMap[i][j] == 3)
			{
				maze[i][j].setType(cellType::door);
			}
			else
			{
				maze[i][j].setType(cellType::null);
			}

			maze[i][j].setPosition({ j, i });
		}
	}

	// Initialise wall
	m_wall.setSize(CELL_SIZE);
	m_wall.setFillColor(sf::Color::Blue);

	// Initialise door
	m_door.setSize({ CELL_SIZE.x, CELL_SIZE.y / 2.0f });
	m_door.setFillColor(sf::Color(192, 192, 192, 255));

	// Initialise pellet
	m_pellet.setRadius(4.0f);
	m_pellet.setOrigin({ -(CELL_SIZE.x / 2.0f - 4.0f),-(CELL_SIZE.y / 2.0f - 4.0f) });
	m_pellet.setFillColor(sf::Color::White);

	// Initialise player
	m_player.setPosition({ CELL_SIZE.x * 1.5f, CELL_SIZE.y * 1.5f });
	m_playerScore = 0;

	// Initialise ghosts
	for (int i = 0; i < NUM_GHOSTS; i++)
	{
		m_ghost[i].setPosition(GHOST_STARTING_POSITION[i]);
	}

	m_ghost[0].setColor(sf::Color::Red);
	m_ghost[1].setColor(sf::Color(255,128,0,255));
	m_ghost[2].setColor(sf::Color::Cyan);
	m_ghost[3].setColor(sf::Color(255, 192, 192, 255));
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/// <summary>
/// This functions accepts a user keyPress event and a string, 
/// and will concatonate onto the string any text the user enters
/// </summary>
/// <param name="t_event">User keyPress event</param>
/// <param name="t_string">String to be appended</param>
/// <param name="t_maxChars">Character limit for string</param>
void Game::inputText(sf::Event t_event, std::string & t_string, unsigned t_maxChars)
{
	// if user types backspace
	if (t_event.text.unicode == 8) 
	{
		// and string is longer than 0 characters
		if (t_string.length() > 0) 
		{
			// erase the last element in the string
			t_string.erase(t_string.length()-1); 
		}
	}
	// otherwise, if not backspace, and string not full
	else if (t_string.length() < t_maxChars)
	{
		// append unicode char typed to string
		t_string += t_event.text.unicode; 
	}
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	switch(m_currentState)
	{
	// +++++++ MENU +++++++
	case gameState::menu:
		break;
	// +++++ GAMEPLAY +++++
	case gameState::gameplay:
		m_player.update();

		for (int i = 0; i < NUM_GHOSTS; i++)
		{
			m_ghost[i].update();
		}

		checkCollisions();

		break;
	// ++++ GAME OVER ++++
	case gameState::gameover:
		break;
	default:
		break;
	}
}

/// <summary>
/// Checks for collisions between game entities and the maze
/// </summary>
void Game::checkCollisions()
{
	for (int i = 0; i < NUM_ROWS; i++) // for all rows
	{
		for (int j = 0; j < NUM_COLS; j++) // for all columns
		{
			// check player collisions
			if (m_player.getBounds().intersects(maze[i][j].getBounds()))
			{
				if (maze[i][j].getType() == cellType::wall || maze[i][j].getType() == cellType::door)
				{
					m_player.hitWall();
				}
				else if (maze[i][j].getType() == cellType::pellet)
				{
					m_playerScore += m_pelletScore; // increment score
					maze[i][j].setType(cellType::null); // remove pellet
					if (countPellets() == 0)
					{
						m_currentState = gameState::gameover;
					}
				}
			}

			// check ghost collisions
			for (int k = 0; k < NUM_GHOSTS; k++)
			{
				if (m_ghost[k].getBounds().intersects(maze[i][j].getBounds()))
				{
					if (maze[i][j].getType() == cellType::wall)
					{
						m_ghost[k].hitWall(maze);
					}
				}
			}
		} // end inner for
	} // end outer for
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/// <summary>
/// Counts the number of pellets remaining in the maze
/// </summary>
/// <returns>Number of pellets remaining</returns>
int Game::countPellets()
{
	int count = 0; 

	for (int i = 0; i < NUM_ROWS; i++)
	{
		for (int j = 0; j < NUM_COLS; j++)
		{
			if (maze[i][j].getType() == cellType::pellet)
			{
				count++;
			}
		}
	}

	std::cout << count << std::endl;

	return count;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);

	switch(m_currentState)
	{
		// ++++++ MENU ++++++
		case gameState::menu:
			// display instructions
			m_HUDText.setPosition({ 100.0f,200.0f });
			m_HUDText.setCharacterSize(26U);
			m_HUDText.setString("Please enter your name below:");
			m_window.draw(m_HUDText);

			// display player name
			m_HUDText.setPosition({ 200.0f, 400.0f });
			m_HUDText.setCharacterSize(36U);
			m_HUDText.setString(m_playerNameString);
			m_window.draw(m_HUDText);
			break;

		// ++++ GAMEPLAY ++++
		case gameState::gameplay:
			for (int i = 0; i < NUM_ROWS; i++) // for all rows
			{
				for (int j = 0; j < NUM_COLS; j++) // for all columns
				{
					maze[i][j].draw(m_window);
				}
			}

			// draw player score
			m_HUDText.setPosition({ 30.0f, 670.0f });
			m_HUDText.setCharacterSize(36U);
			m_HUDText.setString(m_playerNameString + "'s score: " + std::to_string(m_playerScore));
			m_window.draw(m_HUDText);

			for (int i = 0; i < NUM_GHOSTS; i++)
			{
				m_ghost[i].draw(m_window); // draw ghost
			}

			m_player.draw(m_window); // draw player
			break;

		// ++++ GAMEOVER ++++
		case gameState::gameover:
			break;

		default:
			break;
	} // end switch


	m_window.display();
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++