#pragma once
#include <SFML/Graphics.hpp>
#include "GLOBALS.h"
#include "Cell.h"

enum class ghostState
{

};

class Ghost
{
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	void setupSprite();
	sf::CircleShape body; // players body

	sf::Vector2i currentCell; // tracks the ghosts current cell
	float moveSpeed; // speed at which the ghosts moves
	direction moveDirection; // instance of the 'direction' enum class

	bool vulnerable;

	void move();
	bool changeDirection(direction t_dir, Cell t_cellArray[][20]);

public:
	Ghost();
	~Ghost();

	void start();
	void update();
	void hitWall(Cell t_cellArray[][20]);

	inline void draw(sf::RenderWindow & t_window) { t_window.draw(body); }

	// +++++ inline get/set functions +++++
	inline sf::FloatRect getBounds() { return body.getGlobalBounds(); }
	inline void setColor(sf::Color t_color) { body.setFillColor(t_color); }
	inline void setPosition(sf::Vector2f t_pos) { body.setPosition(t_pos); }
	inline sf::Vector2i getCell() { return currentCell; }
};