#include "Ghost.h"

/// <summary>
/// Sets up ghost sprite and texture
/// </summary>
void Ghost::setupSprite()
{
}

/// <summary>
/// Default constructor
/// </summary>
Ghost::Ghost()
{
	m_body.setRadius(16.0f);
	m_body.setOrigin({ 16.0f,16.0f });
	m_body.setFillColor(sf::Color::White);

	m_moveSpeed = 1.0f;
	m_vulnerable = false;

	m_huntClock.restart();
	m_huntDelay = sf::seconds(3.0f);
	m_huntTimer = sf::seconds(1.0f);

	m_moveDirection = direction::left;
	m_currentState = ghostState::initial;

	m_active = false;
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
	m_active = true;
	m_currentState = ghostState::hunting;
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

	if (m_currentState == ghostState::hunting)
	{
		hunt(t_playerPos, t_cellArray);
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
/// Moves the ghost in its move direction, and rotates its sprite accordingly
/// </summary>
void Ghost::move()
{
	switch (m_moveDirection)
	{
	case direction::up:
		m_sprite.setRotation(270.0f);
		m_body.move(0, -m_moveSpeed);
		break;
	case direction::down:
		m_sprite.setRotation(90.0f);
		m_body.move(0, m_moveSpeed);
		break;
	case direction::left:
		m_sprite.setRotation(180.0f);
		m_body.move(-m_moveSpeed, 0);
		break;
	case direction::right:
		m_sprite.setRotation(0.0f);
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