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
	currentState = gameState::menu;
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

		switch (currentState)
		{
		case gameState::menu:

			// proceed to gameplay when they press enter
			if (sf::Event::KeyPressed == event.type)
			{
				if (sf::Keyboard::Enter == event.key.code)
				{
					currentState = gameState::gameplay;
				}
			}

			// take player input
			if (sf::Event::TextEntered == event.type)
			{
				inputText(event, m_playerNameString, 16);
			}
			
			break;

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

	m_instructionsText.setFont(m_ArialBlackfont);
	m_instructionsText.setPosition({ 175.0f,200.0f });
	m_instructionsText.setFillColor(sf::Color::White);
	m_instructionsText.setCharacterSize(26U);
	m_instructionsText.setString("Please enter your name below:");

	m_playerNameText.setFont(m_ArialBlackfont);
	m_playerNameText.setPosition({ 250.0f, 400.0f });
	m_playerNameText.setFillColor(sf::Color::White);
	m_playerNameText.setCharacterSize(36U);
	m_playerNameText.setString("");
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
	// Set up maze array
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
			else
			{
				maze[i][j].setType(cellType::null);
			}
		}
	}

	wall.setSize(CELL_SIZE);
	wall.setFillColor(sf::Color::Blue);

	pellet.setRadius(4.0f);
	pellet.setOrigin({ -(CELL_SIZE.x / 2.0f - 4.0f),-(CELL_SIZE.y / 2.0f - 4.0f) });
	pellet.setFillColor(sf::Color::White);

	m_player.setPosition({ CELL_SIZE.x * 1.5f, CELL_SIZE.y * 1.5f });
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

	switch(currentState)
	{
	case gameState::menu:
		break;
	case gameState::gameplay:
		m_player.update();
		break;
	case gameState::gameover:
		break;
	default:
		break;
	}
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);

	switch(currentState)
	{
		case gameState::menu:
			m_window.draw(m_instructionsText);
			m_playerNameText.setString(m_playerNameString);
			m_window.draw(m_playerNameText);
			break;

		case gameState::gameplay:
			for (int i = 0; i < NUM_ROWS; i++) // for all rows
			{
				for (int j = 0; j < NUM_COLS; j++) // for all columns
				{
					// if cell type is wall
					if (maze[i][j].getType() == cellType::wall)
					{
						// set wall position
						wall.setPosition({ j*CELL_SIZE.x, i*CELL_SIZE.y });
						// check if player colliding
						if (m_player.getBounds().intersects(wall.getGlobalBounds()))
						{
							m_player.hitWall(); // tell player hit wall
						}
						m_window.draw(wall); // draw to screen
					}
					// if cell type is pellet
					else if (maze[i][j].getType() == cellType::pellet)
					{
						// set pellet position
						pellet.setPosition({ j*CELL_SIZE.x,i*CELL_SIZE.y });
						// check if player colliding
						if (m_player.getBounds().intersects(pellet.getGlobalBounds()))
						{
							maze[i][j].setType(cellType::null); // remove pellet
						}
						m_window.draw(pellet); // draw to screen
					}
				} // end inner for
			} // end outer for

			m_player.draw(m_window); // draw player
			break;

		case gameState::gameover:
			break;

		default:
			break;
	} // end switch

	

	m_window.display();
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++