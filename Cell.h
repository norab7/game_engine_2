/*
Cells position is based on a calculation between the chunksize of the cellcount
size of the cell will not be calculated inside the cell itself

Each cell will hold informtion about it's current state and what it contains

Collision detection will be a chunk-based calculation, resolution will be cell

Each cell will contain only 1 gameobject currently
*/

#pragma once

class Cell {
	const Point cellPosition;

	/* Cell Properties */
	bool active = false;
	// VertexType type;

public:
	Cell(const Point& pos);
	~Cell() = default;

	bool drawCell();
	bool resetCell();
	bool isActive();

	void printCell();

};

/* Cell.cpp file when built */
//#include "Cell.h"
Cell::Cell(const Point& pos) : cellPosition(pos) {

}

void Cell::printCell() {
	cellPosition.print(true);
}