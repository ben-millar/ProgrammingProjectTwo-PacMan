#pragma once
#include <SFML/Graphics.hpp>
#include "Cell.h"
#include "GLOBALS.h"

class Player
{
	// Player textures/sprite
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	void setupSprite();
	sf::CircleShape m_body; // players body

	int m_lives;

	sf::Vector2i m_currentCell; // tracks the players current cell
	float m_moveSpeed; // speed at which the player moves
	direction m_moveDirection; // instance of the 'direction' enum class

public:
	// default constructor/destructor
	Player();
	~Player();

	void update(); // main update loop for player class

	void changeDirection(direction t_dir, Cell t_cellArray[][20]); // change move direction
	void hitWall(); // called when the player hits a wall

	inline void kill() { m_lives--; } // Player has been killed by an enemy; deduct a life

	inline void draw(sf::RenderWindow & t_window) { m_sprite.setPosition(m_body.getPosition());  t_window.draw(m_sprite); } // render method for player class
	 
	// +++++ inline get/set functions +++++
	inline sf::FloatRect getBounds() { return m_body.getGlobalBounds(); } // get players bounding rectangle
	inline sf::Vector2f getPosition() { return m_body.getPosition(); } // get position of player (in pixels)
	inline sf::Vector2i getCell() { return m_currentCell; } // get players current cell (in terms of game cells)
	inline int getLives() { return m_lives; } // returns the players current lives
	inline void setLives(int t_lives) { m_lives = t_lives; } // set the players current lives
	inline void setPosition(sf::Vector2f t_pos) { m_body.setPosition(t_pos); } // set the players position (in pixels)
	inline bool isMoving() { return (m_moveDirection != direction::null) ? true : false; } // return true if moving, false if not
};