#include "Player.h"
#include <iostream>


Player::Player()
{
	body.setRadius(20.0f);
	body.setFillColor(sf::Color::Yellow);
	body.setOrigin(20.0f, 20.0f);

	moveSpeed = 1.5f;
	moveDirection = direction::null;
}


Player::~Player()
{
}

void Player::update()
{
	currentCell = { int(body.getPosition().x / 40), int(body.getPosition().y / 40) };
	std::cout << "X: " << currentCell.x << "Y: " << currentCell.y << std::endl;
	switch (moveDirection)
	{
	case direction::up:
		body.move(0, -moveSpeed);
		break;
	case direction::down:
		body.move(0, moveSpeed);
		break;
	case direction::left:
		body.move(-moveSpeed, 0);
		break;
	case direction::right:
		body.move(moveSpeed, 0);
		break;
	default:
		break;
	}
}

void Player::changeDirection(direction t_dir, Cell t_cellArray[][20])
{
	switch (t_dir)
	{
	case direction::up:
		if (t_cellArray[currentCell.y-1][currentCell.x].getType() != cellType::wall) // if not a wall
			moveDirection = t_dir;
		break;
	case direction::down:
		if (t_cellArray[currentCell.y+1][currentCell.x].getType() != cellType::wall) // if not a wall
			moveDirection = t_dir;
		break;
	case direction::left:
		if (t_cellArray[currentCell.y][currentCell.x-1].getType() != cellType::wall) // if not a wall
			moveDirection = t_dir;
		break;
	case direction::right:
		if (t_cellArray[currentCell.y][currentCell.x+1].getType() != cellType::wall) // if not a wall 
			moveDirection = t_dir;
		break;
	default:
		break;
	}
}

void Player::hitWall()
{
	// set player position to center of their current cell
	body.setPosition({ (currentCell.x * 40.0f) + 20.0f, (currentCell.y * 40.0f) + 20.0f });
}
