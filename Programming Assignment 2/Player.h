#pragma once
#include <SFML/Graphics.hpp>
#include "Cell.h"
enum class direction
{
	up,
	down,
	left,
	right,
	null
};

class Player
{
	sf::CircleShape body;

	sf::Vector2i currentCell;
	float moveSpeed;
	direction moveDirection;

public:
	Player();
	~Player();

	void update();

	void changeDirection(direction t_dir, Cell t_cellArray[][20]);
	void hitWall();

	inline void draw(sf::RenderWindow & t_window) { t_window.draw(body); }

	inline sf::FloatRect getBounds() { return body.getGlobalBounds(); }

	inline sf::Vector2f getPosition() { return body.getPosition(); }
	inline sf::Vector2i getCell() { return currentCell; }
	inline void setPosition(sf::Vector2f t_pos) { body.setPosition(t_pos); }
};