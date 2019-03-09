#include "Ghost.h"


void Ghost::setupSprite()
{
}

Ghost::Ghost()
{
	body.setRadius(16.0f);
	body.setOrigin({ 16.0f,16.0f });
	body.setFillColor(sf::Color::White);
}


Ghost::~Ghost()
{
}

void Ghost::update()
{
}

void Ghost::hitWall()
{
	// set body position to center of its current cell
	//body.setPosition({ (currentCell.x * CELL_SIZE.x) + body.getRadius() , (currentCell.y * CELL_SIZE.y) + body.getRadius() });
}
