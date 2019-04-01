#include "Ghost.h"
#include <iostream>

/// <summary>
/// Sets up ghost sprite and texture
/// </summary>
void Ghost::setupSprite()
{
	if (!m_texture.loadFromFile("ASSETS//IMAGES//ghostTextures.png"))
	{
		std::cout << "Unable to load m_texture for Ghost class, located at 'ASSETS//IMAGES//ghostTexture.png'" << std::endl;
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin({ 15.0f,16.0f });
	m_sprite.setTextureRect(m_textureRect);
}

/// <summary>
/// Default constructor
/// </summary>
Ghost::Ghost()
{
	// set up our sprite
	setupSprite();

	// set up SF circle body
	m_body.setRadius(16.0f);
	m_body.setOrigin({ 16.0f,16.0f });
	m_body.setFillColor(sf::Color::White);

	// set moveSpeed to 1
	m_moveSpeed = 1.0f;

	// restart our state clock (used to switch movement states)
	m_huntClock.restart();
	m_huntDelay = sf::seconds(3.0f);
	m_huntTimer = sf::seconds(1.0f);

	// initialise movement direction and AI state
	m_moveDirection = direction::left;
	m_currentState = ghostState::initial;

	// start inactive (in ghost house) and not vulnerable
	m_active = false;
	m_vulnerable = false;
}

/// <summary>
/// Default destructor
/// </summary>
Ghost::~Ghost()
{
}

/// <summary>
/// Starts the ghost
/// </summary>
void Ghost::start()
{
	m_currentState = ghostState::starting;
}

/// <summary>
/// resets the ghost
/// </summary>
void Ghost::stop()
{
	m_huntClock.restart();
	m_currentState = ghostState::initial;
	m_active = false;
}

/// <summary>
/// Main update method for ghost class
/// </summary>
void Ghost::update(sf::Vector2i t_playerPos, Cell t_cellArray[][20])
{
	// ( position / cell size ) returns the position in terms of cells
	m_currentCell = { int(m_body.getPosition().x / CELL_SIZE.x), int(m_body.getPosition().y / CELL_SIZE.y) };

	int randomNum = rand() % 10;

	// Every 3 seconds, ghosts will hunt player for 1 second
	if (m_currentState != ghostState::initial)
	{
		if (m_huntClock.getElapsedTime() > m_huntDelay)
		{
			m_currentState = ghostState::hunting;
			if (m_huntClock.getElapsedTime() > m_huntDelay + m_huntTimer)
			{
				m_huntClock.restart();
				m_currentState = ghostState::random;
			}
		}
	}
	else
	{
		if (m_moveDirection != direction::right)
		{
			changeDirection(direction::left, t_cellArray);
		}
	}
	
	if (m_currentState == ghostState::hunting)
	{
		hunt(t_playerPos, t_cellArray);
	}
	
	if (m_currentState == ghostState::starting)
	{
		if (m_currentCell.x < 9)
		{
			changeDirection(direction::right, t_cellArray);
		}
		else if (m_currentCell.x > 11)
		{
			changeDirection(direction::right, t_cellArray);
		}
		else
		{
			changeDirection(direction::up, t_cellArray);
			m_active = true;
		}
	}

	move();
}

/// <summary>
/// Tracks the player position and moves the ghost toward that
/// </summary>
/// <param name="t_playerPos">Current player cell</param>
/// <param name="t_cellArray">Information on where walls are</param>
void Ghost::hunt(sf::Vector2i t_playerPos, Cell t_cellArray[][20])
{
	if (t_playerPos.x > m_currentCell.x)
	{
		if (m_moveDirection != direction::left)
		{
			changeDirection(direction::right, t_cellArray);
		}
	}
	else if (t_playerPos.x < m_currentCell.x)
	{
		if (m_moveDirection != direction::right)
		{
			changeDirection(direction::left, t_cellArray);
		}
	}
	if (t_playerPos.y > m_currentCell.y)
	{
		if (m_moveDirection != direction::up)
		{
			changeDirection(direction::down, t_cellArray);
		}
	}
	else if (t_playerPos.y < m_currentCell.y)
	{
		if (m_moveDirection != direction::down)
		{
			changeDirection(direction::up, t_cellArray);
		}
	}
}

/// <summary>
/// Moves the ghost in its move direction, by its move speed
/// </summary>
void Ghost::move()
{
	switch (m_moveDirection)
	{
	case direction::up:
		m_body.move(0, -m_moveSpeed);
		break;
	case direction::down:
		m_body.move(0, m_moveSpeed);
		break;
	case direction::left:
		m_body.move(-m_moveSpeed, 0);
		break;
	case direction::right:
		m_body.move(m_moveSpeed, 0);
		break;
	default:
		break;
	}
}

/// <summary>
/// Called when the ghost hits a wall; stops and changes direction at random
/// </summary>
/// <param name="t_cellArray">Information on the maze layout</param>
void Ghost::hitWall(Cell t_cellArray[][20])
{
	if (m_currentState == ghostState::initial)
	{
		if (m_moveDirection == direction::left)
		{
			changeDirection(direction::right, t_cellArray);
		}
		else if (m_moveDirection == direction::right)
		{
			changeDirection(direction::left, t_cellArray);
		}
	}
	else
	{
		// set body position to center of its current cell
		m_body.setPosition({ (m_currentCell.x * CELL_SIZE.x) + m_body.getRadius() , (m_currentCell.y * CELL_SIZE.y) + m_body.getRadius() });

		int newDir = rand() % 2; // random number for choosing direction

		// If the ghost is moving up or down, it can only switch to left or right
		if (m_moveDirection == direction::up || m_moveDirection == direction::down)
		{
			// pick left/right at random
			switch (newDir)
			{
			case 0:
				if (!changeDirection(direction::left, t_cellArray)) // try to turn left
				{
					changeDirection(direction::right, t_cellArray); // if not possible, turn right
				}
				break;
			case 1:
				if (!changeDirection(direction::right, t_cellArray)) // try to turn right
				{
					changeDirection(direction::left, t_cellArray); // if not possible, turn left 
				}
				break;
			default:
				break;
			}
		}
		// If the ghost is moving left or right, it can only switch to up or down
		else if (m_moveDirection == direction::left || m_moveDirection == direction::right)
		{
			// pick up/down at random
			switch (newDir)
			{
			case 0:
				if (!changeDirection(direction::up, t_cellArray)) // try to turn up
				{
					changeDirection(direction::down, t_cellArray); // if not possible, turn down
				}
				break;
			case 1:
				if (!changeDirection(direction::down, t_cellArray)) // try to turn down
				{
					changeDirection(direction::up, t_cellArray); // if not possible, turn up
				}
				break;
			default:
				break;
			}
		}
	}
}

void Ghost::setColor(ghostColor t_color)
{
	switch(t_color)
	{
	case ghostColor::red:
		m_body.setFillColor(sf::Color::Red);
		m_textureRect = { 0,0,30,32 };
		break;
	case ghostColor::blue:
		m_body.setFillColor(sf::Color::Blue);
		m_textureRect = { 30,0,30,32 };
		break;
	case ghostColor::orange:
		m_body.setFillColor(sf::Color(255,255,128,255));
		m_textureRect = { 0,32,30,32 };
		break;
	case ghostColor::pink:
		m_body.setFillColor(sf::Color(255,192,192,255));
		m_textureRect = { 30,32,30,32 };
		break;	
	case ghostColor::scared:
		m_body.setFillColor(sf::Color::Blue);
		m_textureRect = { 0,64,30,32 };
		break;
	default:
		std::cout << "Error setting ghost color in Ghost::setColor" << std::endl;
		break;
	}

	m_sprite.setTextureRect(m_textureRect);
}

/// <summary>
/// Called to change ghost direction. Changes direction and returns true if possible, 
/// doesn't change direction and returns false if not possible.
/// </summary>
/// <param name="t_dir">Direction the ghost wants to change to</param>
/// <param name="t_cellArray">Information on the maze</param>
/// <returns>Bool stating whether direction change completed</returns>
bool Ghost::changeDirection(direction t_dir, Cell t_cellArray[][20])
{
	bool result = true; // default set to true

	switch (t_dir)
	{
	case direction::up:
		if (t_cellArray[m_currentCell.y - 1][m_currentCell.x].getType() != cellType::wall) // if not a wall
		{
			m_moveDirection = t_dir; // move up
		}
		else
		{
			result = false; // otherwise, return false
		}
		break;
	case direction::down:
		if (t_cellArray[m_currentCell.y + 1][m_currentCell.x].getType() != cellType::wall &&
			t_cellArray[m_currentCell.y + 1][m_currentCell.x].getType() != cellType::door) // if not a wall OR a door
		{
			m_moveDirection = t_dir; // move down
		}
		else
		{
			result = false; // otherwise, return false
		}
		break;
	case direction::left:
		if (t_cellArray[m_currentCell.y][m_currentCell.x - 1].getType() != cellType::wall) // if not a wall
		{
			m_moveDirection = t_dir; // move left
		}
		else
		{
			result = false; // otherwise, return false
		}
		break;
	case direction::right:
		if (t_cellArray[m_currentCell.y][m_currentCell.x + 1].getType() != cellType::wall) // if not a wall 
		{
			m_moveDirection = t_dir; // move right
		}
		else
		{
			result = false; // otherwise, return false
		}
		break;
	default:
		break;
	}

	return result;
}