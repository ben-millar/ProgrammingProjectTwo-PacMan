/// <summary>
/// Author: Ben Millar – C00236772
/// Date:
/// Estimated time to complete:
/// Session 1 Start: End:
/// </summary>

#include "game.h"
#include <iostream>


/// <summary>
/// default construcor
/// pass parameters for sfml window, setup m_exitGame
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800, 800, 32 }, "SFML Game" },
	m_exitGame{ false } //when true game will exit
{
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

			if (sf::Keyboard::Up == event.key.code)
			{
				m_player.move(direction::up);
			}
			if (sf::Keyboard::Down == event.key.code)
			{
				m_player.move(direction::down);
			}
			if (sf::Keyboard::Left == event.key.code)
			{
				m_player.move(direction::left);
			}
			if (sf::Keyboard::Right == event.key.code)
			{
				m_player.move(direction::right);
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
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Game::setupSounds()
{
	
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Game::setupSprites()
{

}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

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

	wall.setSize({ 40.0f,40.0f });
	wall.setFillColor(sf::Color::Blue);

	pellet.setRadius(4.0f);
	pellet.setOrigin({ -18.0f,-18.0f });
	pellet.setFillColor(sf::Color::White);
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

	m_player.update();
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);

	for (int i = 0; i < NUM_ROWS; i++)
	{
		for (int j = 0; j < NUM_COLS; j++)
		{
			if (maze[i][j].getType() == cellType::wall)
			{
				wall.setPosition({ j*40.0f, i*40.0f });
				m_window.draw(wall);
			}
			else if (maze[i][j].getType() == cellType::pellet)
			{	
				pellet.setPosition({ j*40.0f,i*40.0f });
				m_window.draw(pellet);
			}
		}
	}

	m_player.draw(m_window);

	m_window.display();
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++