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
	bool cellActive;
	bool cellFilled;
	// CellType type = Type.DIRT; // TODO: some form of different cells

public:
	Cell(const Point& pos, const bool& active, const bool& filled);
	~Cell() = default;

	void buildCell(std::vector<float> vert, std::vector<float> ind);

	bool resetCell();
	bool isActive();
	bool isFilled();

	void printCell();

};

/* Cell.cpp file when built */
//#include "Cell.h"
Cell::Cell(const Point& pos, const bool& active, const bool& filled)
	: cellPosition(pos), cellActive(active), cellFilled(filled) {

}

void Cell::printCell() {
	if(cellActive) {
		std::cout << "Pos: ";
		cellPosition.print();
		std::cout << " Active: " << cellActive << " Filled: " << cellFilled << std::endl;
	}
}