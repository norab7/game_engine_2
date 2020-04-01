/*
Cells position is based on a calculation between the chunksize of the cellcount
size of the cell will not be calculated inside the cell itself

Each cell will hold informtion about it's current state and what it contains

Collision detection will be a chunk-based calculation, resolution will be cell

Each cell will contain only 1 gameobject currently
*/

#pragma once

class Cell {

	/* Cell Properties */

public:
	Cell();
	~Cell() = default;

	bool drawCell();
	bool resetCell();

};

/* Cell.cpp file when built */
//#include "Cell.h"
Cell::Cell() {

}