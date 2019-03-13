#pragma once
#include <SFML/Graphics.hpp>
#include "GLOBALS.h"
#include "Cell.h"

enum class ghostState
{
	initial,
	random,
	hunting
};

class Ghost
{
	sf::Texture m_texture;
	sf::Sprite m_sprite;

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

	void start();
	void update(sf::Vector2i t_playerPos, Cell t_cellArray[][20]);
	void hunt(sf::Vector2i t_playerPos, Cell t_cellArray[][20]);
	void hitWall(Cell t_cellArray[][20]);

	inline void draw(sf::RenderWindow & t_window) { t_window.draw(m_body); }

	// +++++ inline get/set functions +++++
	inline bool isActive() { return m_active; }
	inline sf::FloatRect getBounds() { return m_body.getGlobalBounds(); }
	inline void setColor(sf::Color t_color) { m_body.setFillColor(t_color); }
	inline void setPosition(sf::Vector2f t_pos) { m_body.setPosition(t_pos); }
	inline sf::Vector2i getCell() { return m_currentCell; }
};