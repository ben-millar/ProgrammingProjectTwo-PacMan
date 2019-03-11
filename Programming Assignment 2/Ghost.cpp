#include "Ghost.h"


void Ghost::setupSprite()
{
}

Ghost::Ghost()
{
	body.setRadius(16.0f);
	body.setOrigin({ 16.0f,16.0f });
	body.setFillColor(sf::Color::White);

	moveSpeed = 1.3f;
	vulnerable = false;

	moveDirection = direction::up;
}

Ghost::~Ghost()
{
}

void Ghost::update()
{
	// ( position / cell size ) returns the position in terms of cells
	currentCell = { int(body.getPosition().x / CELL_SIZE.x), int(body.getPosition().y / CELL_SIZE.y) };

	move();
}

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

void Ghost::hitWall(Cell t_cellArray[][20])
{
	// set body position to center of its current cell
	body.setPosition({ (currentCell.x * CELL_SIZE.x) + body.getRadius() , (currentCell.y * CELL_SIZE.y) + body.getRadius() });

	int newDir = rand() % 2;

	if (moveDirection == direction::up || moveDirection == direction::down)
	{
		switch (newDir)
		{
		case 0:
			if (!changeDirection(direction::left, t_cellArray))
			{
				changeDirection(direction::right, t_cellArray);
			}
			break;
		case 1:
			if (!changeDirection(direction::right, t_cellArray))
			{
				changeDirection(direction::left, t_cellArray);
			}
			break;
		default:
			break;
		}
	}
	else if (moveDirection == direction::left || moveDirection == direction::right)
	{
		switch (newDir)
		{
		case 0:
			if (!changeDirection(direction::up, t_cellArray))
			{
				changeDirection(direction::down, t_cellArray);
			}
			break;
		case 1:
			if (!changeDirection(direction::down, t_cellArray))
			{
				changeDirection(direction::up, t_cellArray);
			}
			break;
		default:
			break;
		}
	}
}

bool Ghost::changeDirection(direction t_dir, Cell t_cellArray[][20])
{
	switch (t_dir)
	{
	case direction::up:
		if (t_cellArray[currentCell.y - 1][currentCell.x].getType() != cellType::wall) // if not a wall
			moveDirection = t_dir;
		break;
	case direction::down:
		if (t_cellArray[currentCell.y + 1][currentCell.x].getType() != cellType::wall &&
			t_cellArray[currentCell.y + 1][currentCell.x].getType() != cellType::door) // if not a wall OR a door
			moveDirection = t_dir;
		break;
	case direction::left:
		if (t_cellArray[currentCell.y][currentCell.x - 1].getType() != cellType::wall) // if not a wall
			moveDirection = t_dir;
		break;
	case direction::right:
		if (t_cellArray[currentCell.y][currentCell.x + 1].getType() != cellType::wall) // if not a wall 
			moveDirection = t_dir;
		break;
	default:
		break;
	}

	return false;
}