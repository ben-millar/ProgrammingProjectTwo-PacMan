#pragma once
#include <SFML/Graphics.hpp>
#include "GLOBALS.h"
#include "Cell.h"

enum class ghostState
{
	initial, // moving left to right
	starting, // moving out of ghost house
	random, // random movement
	hunting // following player
};

enum class ghostColor
{
	red, 
	blue,
	orange,
	pink,
	scared,
	null
};

class Ghost
{
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::IntRect m_textureRect{ 0,0,30,32 };

	void setupSprite();
	sf::CircleShape m_body; // players body

	sf::Vector2i m_currentCell; // tracks the ghosts current cell
	float m_moveSpeed; // speed at which the ghosts moves
	direction m_moveDirection; // instance of the 'direction' enum class

	bool m_active;
	bool m_vulnerable;

	void move();
	bool changeDirection(direction t_dir, Cell t_cellArray[][20]);

	// used for timing phases/states
	sf::Clock m_huntClock; 
	sf::Time m_huntDelay;
	sf::Time m_huntTimer;

	ghostState m_currentState;

public:
	Ghost();
	~Ghost();

	void start(); // start the ghost moving out of the ghost house
	void stop(); // reset the ghost to its initial state

	void update(sf::Vector2i t_playerPos, Cell t_cellArray[][20]); // main update method
	void hunt(sf::Vector2i t_playerPos, Cell t_cellArray[][20]); // move to the players position
	void hitWall(Cell t_cellArray[][20]); // hit wall, try to change direction

	void setColor(ghostColor t_color);
	inline void draw(sf::RenderWindow & t_window) { m_sprite.setPosition(m_body.getPosition()); t_window.draw(m_sprite); }

	// +++++ inline get/set functions +++++
	inline bool isActive() { return m_active; }
	inline sf::FloatRect getBounds() { return m_body.getGlobalBounds(); }
	inline void setPosition(sf::Vector2f t_pos) { m_body.setPosition(t_pos); }
	inline sf::Vector2i getCell() { return m_currentCell; }
};