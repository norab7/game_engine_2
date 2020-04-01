/*
Spawing chunks can be based on the distance away from the player character
Loading / Saving chunks can be based on the coordinate system

Store a file with coordinates of chunks that has been altered
If there exists a chunk at the coordinates load it, otherwise spawn fresh

*/


#pragma once
#include <map>

#include "Point.h"
#include "Cell.h"

class Chunk {
	const Point& anchorPoint;

	/* Cell Values */
	std::map<Point, Cell> cells;
	const unsigned xCellCount = 10;
	const unsigned yCellCount = 10; // Remember 'Y' is up in opengl
	const unsigned zCellCount = 10;

public:
	Chunk(const Point& p);
	~Chunk() = default;

	bool drawChunk();
	bool resetChunk();

};

/* Chunk.cpp file when built */
//#include "Chunk.h"
Chunk::Chunk(const Point& p) : anchorPoint(p) {

}