#include "World.h"

World::World(const unsigned& width, const unsigned& height, const unsigned& length) :WIDTH_(width), HEIGHT_(height), LENGTH_(length) {
	GRID_ = new bool** [WIDTH_];
	for(unsigned w = 0; w < WIDTH_; w++) {
		GRID_[w] = new bool* [HEIGHT_];
		for(unsigned h = 0; h < HEIGHT_; h++) {
			GRID_[w][h] = new bool[LENGTH_] {false};
			for(unsigned l = 0; l < LENGTH_; l++) {
				if(h > 0) { break; }
				if(w % 2 == 0 || l % 2 == 0) {
					GRID_[w][h][l] = true;
				}
			}
		}
	}
}

const bool World::in_range(const unsigned& val, const unsigned& range) const {
	return (val < range && val >= 0);
}

const bool World::walkable(const glm::vec3& coords)  const {
	const unsigned x = coords.x;
	const unsigned y = coords.y;
	const unsigned z = coords.z;

	if(!(in_range(x, WIDTH_)) || !(in_range(y, HEIGHT_)) || !(in_range(z, LENGTH_))) {
		return false;
	}

	return (GRID_[x][y][z]);
}
const bool World::walkable(const unsigned& width, const unsigned& height, const unsigned& length)  const {
	return walkable(glm::vec3(width, height, length));
}

const std::vector<glm::vec3> World::get_neighbours(const glm::vec3& coords) const {
	const unsigned x = coords.x;
	const unsigned y = coords.y;
	const unsigned z = coords.z;

	std::vector<glm::vec3> res {};

	if(in_range(x + 1, WIDTH_)) { res.push_back(glm::vec3(x + 1, y, z)); }
	if(in_range(x - 1, WIDTH_)) { res.push_back(glm::vec3(x - 1, y, z)); }
	if(in_range(y + 1, HEIGHT_)) { res.push_back(glm::vec3(x, y + 1, z)); }
	if(in_range(y - 1, HEIGHT_)) { res.push_back(glm::vec3(x, y - 1, z)); }
	if(in_range(z + 1, LENGTH_)) { res.push_back(glm::vec3(x, y, z + 1)); }
	if(in_range(z - 1, LENGTH_)) { res.push_back(glm::vec3(x, y, z - 1)); }

	return res;
}
const std::vector<glm::vec3> World::get_neighbours(const unsigned& width, const unsigned& height, const unsigned& length) const {
	return get_neighbours(glm::vec3(width, height, length));
}

const std::vector<glm::vec3> World::get_walkable_neighbours(const glm::vec3& coords) const {
	const unsigned x = coords.x;
	const unsigned y = coords.y;
	const unsigned z = coords.z;

	std::vector<glm::vec3> res;

	if(walkable(x + 1, y, z)) { res.push_back(glm::vec3(x + 1, y, z)); }
	std::cout << "walkable size: " << res.size() << std::endl;
	if(walkable(x - 1, y, z)) { res.push_back(glm::vec3(x - 1, y, z)); }
	std::cout << "walkable size: " << res.size() << std::endl;
	if(walkable(x, y + 1, z)) { res.push_back(glm::vec3(x, y + 1, z)); }
	std::cout << "walkable size: " << res.size() << std::endl;
	if(walkable(x, y - 1, z)) { res.push_back(glm::vec3(x, y - 1, z)); }
	std::cout << "walkable size: " << res.size() << std::endl;
	if(walkable(x, y, z + 1)) { res.push_back(glm::vec3(x, y, z + 1)); }
	std::cout << "walkable size: " << res.size() << std::endl;
	if(walkable(x, y, z - 1)) { res.push_back(glm::vec3(x, y, z - 1)); }
	std::cout << "walkable size: " << res.size() << std::endl;

	return res;
}
const std::vector<glm::vec3> World::get_walkable_neighbours(const unsigned& width, const unsigned& height, const unsigned& length) const {
	return get_walkable_neighbours(glm::vec3(width, height, length));
}