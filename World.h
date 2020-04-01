/* Class Object that contains the generic world environment data and information

Indexed chunks with a set distance away from the player in index values
if the player traverses to a new chunk check/load additional at world edge

Only care about horizontal values for loading chunks for simplicity
leave room for adding in vertical chunks for future

Start at coords (0,0,0) and spread in a positive direction for starters
Make it so the world can be offset as a whole

*/

#pragma once
#include <map>

#include "Point.h"
#include "Chunk.h"

class World {

	/* Chunk Values */
	std::map<Point, Chunk> chunks;
	const unsigned chunkRadius = 1; // Number of chunks around the player character
	const unsigned chunkXLength = 10;
	const unsigned chunkYLength = 10; // Split height even over zero
	const unsigned chunkZLength = 10;

public:
	World() = default;
	~World() = default;

	bool drawWorld();
	bool resetWorld();

	std::map<Point, Chunk> all_chunks();
	Chunk* chunk(const unsigned& x, const unsigned& z);
	bool chunkTransitioned();
	bool hasChunkLoaded(const unsigned& x, const unsigned& z);
	bool loadChunk(const unsigned& x, const unsigned& z);
	bool resetChunk(const unsigned& x, const unsigned& z);


};