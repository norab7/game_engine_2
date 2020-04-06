/* Class Object that contains the generic world environment data and information

Indexed chunks with a set distance away from the player in index values
if the player traverses to a new chunk check/load additional at world edge

Only care about horizontal values for loading chunks for simplicity
leave room for adding in vertical chunks for future

Start at coords (0,0,0) and spread in a positive direction for starters
Make it so the world can be offset as a whole

Anchor coords are the (0,0) of each chunk, with an increasing value for both (x,z) values
the Y coordinate will not be used for now to keep the coords easy and simple

*/

#pragma once
#include <map>

#include "Point.h"
#include "Chunk.h"

class World {
	Point anchorPoint = Point::rect(0.0f, 0.0f, 0.0f);

	/* Chunk Values */
	std::map<Point, Chunk> chunks {};
	const int chunkRadius = 1; // Number of chunks around the player character
	const int chunkLength = 10;
	const int chunkHeight = 10; // Split height even over zero

public:
	World();
	World(unsigned radius);
	World(unsigned length, unsigned height);
	World(unsigned radius, unsigned length, unsigned height);
	World(Point& anchor);
	World(Point& anchor, unsigned radius);
	World(Point& anchor, unsigned length, unsigned height);
	World(Point& anchor, unsigned radius, unsigned length, unsigned height);
	~World() = default;

	void printWorld();

	bool drawWorld();
	bool resetWorld();

	std::map<Point, Chunk> all_chunks();
	Chunk* chunk(const unsigned& x, const unsigned& z);
	bool chunkTransitioned();
	bool hasChunkLoaded(const unsigned& x, const unsigned& z);
	bool loadChunk(const unsigned& x, const unsigned& z);
	bool resetChunk(const unsigned& x, const unsigned& z);


};

/* World.cpp file when built */
//#include "World.h"
World::World()
	: World(anchorPoint, chunkRadius, chunkLength, chunkHeight) {
}
World::World(unsigned radius)
	: World(anchorPoint, radius, chunkLength, chunkHeight) {
}
World::World(unsigned length, unsigned height)
	: World(anchorPoint, chunkRadius, length, height) {
}
World::World(unsigned radius, unsigned length, unsigned height)
	: World(anchorPoint, radius, length, height) {
}
World::World(Point& anchor)
	: World(anchor, chunkRadius, chunkLength, chunkHeight) {
}
World::World(Point& anchor, unsigned radius)
	: World(anchor, radius, chunkLength, chunkHeight) {
}
World::World(Point& anchor, unsigned length, unsigned height)
	: World(anchor, chunkRadius, length, height) {
}
World::World(Point& anchor, unsigned radius, unsigned length, unsigned height)
	: anchorPoint(anchor), chunkRadius(radius), chunkLength(length), chunkHeight(height) {

	std::cout << "Setting up World Chunks" << std::endl;

	anchorPoint.anchor(chunkLength).floor(); // Normalise anchor point to middle chunk anchor coords

	int offset = chunkLength * chunkRadius;
	int xEnd = anchorPoint.xi() + offset;
	int zEnd = anchorPoint.zi() + offset;

	// Generate Chunks based on the anchor point offsetting them by the radius and length
	for(int zIndex = anchorPoint.zi() - (chunkLength * chunkRadius); zIndex <= zEnd; zIndex += chunkLength) {
		for(int xIndex = anchorPoint.xi() - (chunkLength * chunkRadius); xIndex <= xEnd; xIndex += chunkLength) {
			Point chunkPoint = Point::rect(xIndex, 0.0f, zIndex);
			chunks.insert(std::pair<Point, Chunk>(chunkPoint, *new Chunk(chunkPoint, chunkLength, chunkHeight)));

		}
	}
}

void World::printWorld() {
	Point temp = Point::rect(0, 0, 0);
	for(int zIndex = 0; zIndex < (chunkRadius * 2) + 1; zIndex++) {
		for(int xIndex = 0; xIndex < (chunkRadius * 2) + 1; xIndex++) {
			temp.set((xIndex - chunkRadius) * chunkLength, 0, (zIndex - chunkRadius) * chunkLength);
			chunks.at(temp).printChunk();
		}
	}
}





// Initial location of the world will be (0,0).
// Only consider (X,Z) chunk locations leaving Y=0.
// Chunk Radius is how many layers of chunks surround the central point (5 on numpad has radius=1).
