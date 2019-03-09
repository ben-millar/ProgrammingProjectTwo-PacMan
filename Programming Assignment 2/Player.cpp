#include "Player.h"
#include <iostream>


void Player::setupSprite()
{
	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\pacmanSprite.png"))
	{
		// error message
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin({ 16.0f,16.0f });
}

Player::Player()
{
	setupSprite();

	body.setRadius(CELL_SIZE.x/2.0f);
	body.setFillColor(sf::Color::Yellow);
	body.setOrigin(CELL_SIZE.x / 2.0f, CELL_SIZE.x / 2.0f);

	moveSpeed = 1.5f;
	moveDirection = direction::null;
}


Player::~Player()
{
}

void Player::update()
{
	currentCell = { int(body.getPosition().x / CELL_SIZE.x), int(body.getPosition().y / CELL_SIZE.y) };

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

void Player::changeDirection(direction t_dir, Cell t_cellArray[][20])
{
	switch (t_dir)
	{
	case direction::up:
		if (t_cellArray[currentCell.y-1][currentCell.x].getType() != cellType::wall) // if not a wall
			moveDirection = t_dir;
		break;
	case direction::down:
		if (t_cellArray[currentCell.y+1][currentCell.x].getType() != cellType::wall &&
			t_cellArray[currentCell.y + 1][currentCell.x].getType() != cellType::door) // if not a wall OR a door
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
	body.setPosition({ (currentCell.x * CELL_SIZE.x) + body.getRadius() , (currentCell.y * CELL_SIZE.y) + body.getRadius() });
}
