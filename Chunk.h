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

#include "World.h"
#include "Point.h"
#include "Cell.h"

#include "Shader.h" // Find a way to get rid of this (decouple)
#include "Mesh.h"

class World;

class Chunk {
	const Point anchorPoint;

	/* Cell Values */
	std::map<Point, Cell> cells;
	std::vector<Point> activeCells; // Only need to render active cells, indexed cells map means just store it's index
	std::vector<Point> mesh; // May need a mesh class to store this data

	const unsigned horCellCount;
	const unsigned vertCellCount;

public:
	std::vector<Mesh> meshes;
	Chunk(const Point& p, const unsigned& horCells, const unsigned& vertCells);
	~Chunk() = default;

	void build(const World& w);

	bool drawChunk(Shader* shader);
	bool resetChunk();
	void printChunk();
};

/* Chunk.cpp file when built */
//#include "Chunk.h"
Chunk::Chunk(const Point& p, const unsigned& horCells, const unsigned& vertCells)
	: anchorPoint(p), horCellCount(horCells), vertCellCount(vertCells) {

	for(int yIndex = 0; yIndex < vertCellCount; yIndex++) {
		for(int zIndex = 0; zIndex < horCellCount; zIndex++) {
			for(int xIndex = 0; xIndex < horCellCount; xIndex++) {
				// TODO: Can generate basic surface of terrain with heightmap checks here
				Point cellPos = Point(anchorPoint) + Point::rect(xIndex, yIndex, zIndex);
				bool cellActive = (yIndex == vertCellCount - 1);
				bool cellFilled = (yIndex < vertCellCount - 1);

				if(cellFilled) { cells.insert(std::pair<Point, Cell>(cellPos, *new Cell(cellPos, cellActive, cellFilled))); }
				if(cellActive) { activeCells.push_back(cellPos); }

			}
		}
	}
}

void Chunk::build(const World& w) {
	Point offset = Point::rect(0.5f, 0.5f, 0.5f);
	float half = 0.5f;

	for(Point p : activeCells) {
		Point centre = p + offset;

		/* TODO: Adjust vertices and indices to match surrounding cells */
		std::vector<float> vertices {
			centre.X_, centre.Y_ + half, centre.Z_, // 0 - top 
			centre.X_ + half, centre.Y_, centre.Z_, // 1 - right
			centre.X_, centre.Y_, centre.Z_ + half, // 2 - front
			centre.X_ - half, centre.Y_, centre.Z_, // 3 - left
			centre.X_, centre.Y_, centre.Z_ - half, // 4 - back
			centre.X_, centre.Y_ - half, centre.Z_  // 5 - bottom
		};

		std::vector<unsigned> indices {
			1, 0, 2, // top right front
			3, 0, 2, // top left front
			3, 0, 4, // top left back
			1, 0, 4, // top right back
			1, 5, 2, // bottom right front
			3, 5, 2, // bottom left front
			3, 5, 4, // bottom left back
			1, 5, 4  // bottom right back
		};

		meshes.push_back(*new Mesh(centre.toFloat(), vertices, indices));

	}

}

bool Chunk::drawChunk(Shader* shader) {
	glm::mat4 mat(1);

	shader->use();
	shader->setMat4("model", mat);


	for(Mesh m : meshes) {
		m.Draw(*shader);
	}

	return true;
}

void Chunk::printChunk() {
	Point temp = Point::rect(0, 0, 0);

	for(int yIndex = 0; yIndex < vertCellCount; yIndex++) {
		for(int zIndex = 0; zIndex < horCellCount; zIndex++) {
			for(int xIndex = 0; xIndex < horCellCount; xIndex++) {
				temp.set(xIndex + anchorPoint.xi(), yIndex + anchorPoint.yi(), zIndex + anchorPoint.zi());
				cells.at(temp).printCell();
			}
		}
	}
}