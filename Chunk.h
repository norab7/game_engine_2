/*
Spawing chunks can be based on the distance away from the player character
Loading / Saving chunks can be based on the coordinate system

Store a file with coordinates of chunks that has been altered
If there exists a chunk at the coordinates load it, otherwise spawn fresh

To make things easier, assume all cells are 1 meter wide.
Not calculations will be required to adjust for increasing chunk sizes as it
will be handled by the world generation and not the individual chunks

Could eventually have a sub-cell break up to have extra fidelity of the cell
itself allowing more dynamic curves and build up of the world.

*/


#pragma once
#include <map>

#include "Point.h"
#include "Cell.h"

class Chunk {
	const Point anchorPoint;

	/* Cell Values */
	std::map<Point, Cell> cells;
	const unsigned horCellCount;
	const unsigned vertCellCount;

public:
	Chunk(const Point& p, const unsigned& horCells, const unsigned& vertCells);
	~Chunk() = default;

	bool drawChunk();
	bool resetChunk();
	void printChunk();
};

/* Chunk.cpp file when built */
//#include "Chunk.h"
Chunk::Chunk(const Point& p, const unsigned& horCells, const unsigned& vertCells)
	: anchorPoint(p), horCellCount(horCells), vertCellCount(vertCells) {

	for(int zIndex = 0; zIndex < horCellCount; zIndex++) {
		for(int xIndex = 0; xIndex < horCellCount; xIndex++) {
			Point cellPos = Point(anchorPoint) + Point::rect(xIndex, 0, zIndex);
			cells.insert(std::pair<Point, Cell>(cellPos, *new Cell(cellPos)));
		}
	}

}

void Chunk::printChunk() {
	Point temp = Point::rect(0, 0, 0);

	for(int zIndex = 0; zIndex < horCellCount; zIndex++) {
		for(int xIndex = 0; xIndex < horCellCount; xIndex++) {
			temp.set(xIndex + anchorPoint.xi(), 0, zIndex + anchorPoint.zi());
			cells.at(temp).printCell();
		}
	}
}