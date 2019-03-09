#pragma once
#include <SFML/Graphics.hpp>
#include "Cell.h"
#include "GLOBALS.h"

class Player
{
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	void setupSprite();
	sf::CircleShape body; // players body

	sf::Vector2i currentCell; // tracks the players current cell
	float moveSpeed; // speed at which the player moves
	direction moveDirection; // instance of the 'direction' enum class

public:
	// default constructor/destructor
	Player();
	~Player();

	void update(); // main update loop for player class

	void changeDirection(direction t_dir, Cell t_cellArray[][20]); // change move direction
	void hitWall(); // called when the player hits a wall

	inline void draw(sf::RenderWindow & t_window) { m_sprite.setPosition(body.getPosition());  t_window.draw(m_sprite); } // render method for player class
	 
	// +++++ inline get/set functions +++++
	inline sf::FloatRect getBounds() { return body.getGlobalBounds(); }
	inline sf::Vector2f getPosition() { return body.getPosition(); }
	inline sf::Vector2i getCell() { return currentCell; }
	inline void setPosition(sf::Vector2f t_pos) { body.setPosition(t_pos); }
};