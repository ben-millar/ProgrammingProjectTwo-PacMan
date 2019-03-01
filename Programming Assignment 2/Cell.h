#pragma once

enum class cellType
{
	wall,
	pellet,
	null
};

class Cell
{
	cellType currentCell;

public:

	inline cellType getType() { return currentCell; }
	Cell();
	~Cell();
};