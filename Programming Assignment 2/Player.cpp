#include "Player.h"



Player::Player()
{
	body.setRadius(20.0f);
	body.setFillColor(sf::Color::Yellow);

	moveSpeed = 1.5f;
	moveDirection = direction::null;
}


Player::~Player()
{
}

void Player::update()
{
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