#pragma once
#include <SFML/Graphics.hpp>
#include "GLOBALS.h"


class Ghost
{
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	void setupSprite();
	sf::CircleShape body; // players body

	sf::Vector2i currentCell; // tracks the players current cell
	float moveSpeed; // speed at which the player moves
	direction moveDirection; // instance of the 'direction' enum class
public:
	Ghost();
	~Ghost();

	void update();
	void hitWall();

	inline void draw(sf::RenderWindow & t_window) { t_window.draw(body); }

	// +++++ inline get/set functions +++++
	inline sf::FloatRect getBounds() { return body.getGlobalBounds(); }
	inline void setColor(sf::Color t_color) { body.setFillColor(t_color); }
	inline void setPosition(sf::Vector2f t_pos) { body.setPosition(t_pos); }
};