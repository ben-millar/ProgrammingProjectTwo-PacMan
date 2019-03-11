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
	body.setRadius(16.0f);
	body.setOrigin({ 16.0f,16.0f });
	body.setFillColor(sf::Color::White);

	moveSpeed = 1.3f;
	vulnerable = false;

	moveDirection = direction::up;
}

/// <summary>
/// Default destructor
/// </summary>
Ghost::~Ghost()
{
}

/// <summary>
/// Main update method for ghost class
/// </summary>
void Ghost::update()
{
	// ( position / cell size ) returns the position in terms of cells
	currentCell = { int(body.getPosition().x / CELL_SIZE.x), int(body.getPosition().y / CELL_SIZE.y) };

	move();
}

/// <summary>
/// Moves the ghost in its move direction, and rotates its sprite accordingly
/// </summary>
void Ghost::move()
{
	switch (moveDirection)
	{
	case direction::up:
		m_sprite.setRotation(270.0f);
		body.move(0, -moveSpeed);
		break;
	case direction::down:
		m_sprite.setRotation(90.0f);
		body.move(0, moveSpeed);
		break;
	case direction::left:
		m_sprite.setRotation(180.0f);
		body.move(-moveSpeed, 0);
		break;
	case direction::right:
		m_sprite.setRotation(0.0f);
		body.move(moveSpeed, 0);
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
	// set body position to center of its current cell
	body.setPosition({ (currentCell.x * CELL_SIZE.x) + body.getRadius() , (currentCell.y * CELL_SIZE.y) + body.getRadius() });

	int newDir = rand() % 2; // random number for choosing direction

	// If the ghost is moving up or down, it can only switch to left or right
	if (moveDirection == direction::up || moveDirection == direction::down)
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
	else if (moveDirection == direction::left || moveDirection == direction::right)
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
		if (t_cellArray[currentCell.y - 1][currentCell.x].getType() != cellType::wall) // if not a wall
		{
			moveDirection = t_dir; // move up
		}
		else
		{
			result = false; // otherwise, return false
		}
		break;
	case direction::down:
		if (t_cellArray[currentCell.y + 1][currentCell.x].getType() != cellType::wall) // if not a wall
		{
			moveDirection = t_dir; // move down
		}
		else
		{
			result = false; // otherwise, return false
		}
		break;
	case direction::left:
		if (t_cellArray[currentCell.y][currentCell.x - 1].getType() != cellType::wall) // if not a wall
		{
			moveDirection = t_dir; // move left
		}
		else
		{
			result = false; // otherwise, return false
		}
		break;
	case direction::right:
		if (t_cellArray[currentCell.y][currentCell.x + 1].getType() != cellType::wall) // if not a wall 
		{
			moveDirection = t_dir; // move right
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