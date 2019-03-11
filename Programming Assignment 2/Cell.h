#pragma once
#include "GLOBALS.h"

enum class cellType
{
	wall,
	pellet,
	door, // for ghosts
	null
};

class Cell
{
	cellType m_currentCell;
	sf::RectangleShape m_wall;
	sf::RectangleShape m_door;
	sf::CircleShape m_pellet;

	sf::Vector2i m_position;

public:

	inline cellType getType() { return m_currentCell; }
	inline void setType(cellType t_cell) { m_currentCell = t_cell; }

	inline sf::Vector2i getPosition() { return m_position; }
	inline void setPosition(sf::Vector2i t_pos) { m_position = t_pos; }

	sf::FloatRect getBounds();

	Cell();
	~Cell();

	void draw(sf::RenderWindow & t_window);
};