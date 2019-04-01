#include "Cell.h"

Cell::Cell()
{
	m_wall.setSize(CELL_SIZE);
	m_wall.setFillColor(sf::Color::Blue); 

	m_door.setSize({ CELL_SIZE.x, CELL_SIZE.y / 3.0f });
	m_door.setFillColor(sf::Color(128, 128, 128, 255));

	m_pellet.setRadius(4.0f);
	m_pellet.setOrigin({ -(CELL_SIZE.x / 2.0f - 4.0f),-(CELL_SIZE.y / 2.0f - 4.0f) });
	m_pellet.setFillColor(sf::Color::White);
}


Cell::~Cell()
{
}

sf::FloatRect Cell::getBounds()
{
	sf::FloatRect result = { 0.0f,0.0f,0.0f,0.0f };

	switch (m_currentCell)
	{
	case cellType::wall:
		result = m_wall.getGlobalBounds();
		break;
	case cellType::pellet:
		result = m_pellet.getGlobalBounds();
		break;
	case cellType::door:
		result = m_door.getGlobalBounds();
		break;
	default:
		break;
	}

	return result;
}

void Cell::draw(sf::RenderWindow & t_window)
{
	switch (m_currentCell)
	{
	case cellType::wall:
		m_wall.setPosition({ m_position.x*CELL_SIZE.x, m_position.y*CELL_SIZE.y });
		break;
	case cellType::pellet:
		m_pellet.setPosition({ m_position.x*CELL_SIZE.x, m_position.y*CELL_SIZE.y });
		t_window.draw(m_pellet); // only draw pellets over the background
		break;
	case cellType::door:
		m_door.setPosition({ m_position.x*CELL_SIZE.x, m_position.y*CELL_SIZE.y });
		break;
	default:
		break;
	}
}