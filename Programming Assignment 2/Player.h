#pragma once
#include <SFML/Graphics.hpp>
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

	float moveSpeed;

	direction moveDirection;

public:
	Player();
	~Player();

	void update();

	inline void move(direction t_dir) { moveDirection = t_dir; };
	inline void draw(sf::RenderWindow & t_window) { t_window.draw(body); }

	inline sf::FloatRect getBounds() { return body.getGlobalBounds(); }
};