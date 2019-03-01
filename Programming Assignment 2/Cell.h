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
	inline void setType(cellType t_cell) { currentCell = t_cell; }

	Cell();
	~Cell();
};