#include "World.h"
#include <glfw3.h>

World::World(const unsigned& width, const unsigned& height, const unsigned& length, const glm::vec3& origin) :WIDTH_(width), HEIGHT_(height), LENGTH_(length), ORIGIN_(origin) {
	unsigned percentage = 15.0f;

	GRID_ = new bool** [WIDTH_];
	for(unsigned w = 0; w < WIDTH_; w++) {
		GRID_[w] = new bool* [HEIGHT_];
		for(unsigned h = 0; h < HEIGHT_; h++) {
			GRID_[w][h] = new bool[LENGTH_] {false};
			for(unsigned l = 0; l < LENGTH_; l++) {
				if(rand() % 100 >= percentage || ((w == 0 || w == WIDTH_ - 1) && (h == 0 || h == HEIGHT_ - 1) && (l == 0 || l == LENGTH_ - 1))) {
					GRID_[w][h][l] = true;
					open.push_back(translate(glm::vec3(w, h, l)));
				} else {
					closed.push_back(translate(glm::vec3(w, h, l)));
				}
			}
		}
	}
}

World::World(const glm::vec3& grid, const glm::vec3& origin) : World::World(grid.x, grid.y, grid.z, origin) {

}

const glm::vec3 World::translate(const glm::vec3& coords) const {
	return (coords * GRIDSPACE_) + ORIGIN_;
}

const bool World::in_range(const unsigned& val, const unsigned& range) const {
	return (val < range && val >= 0);
}


const glm::vec3 World::get_min_limits() const {
	return ORIGIN_;
}
const glm::vec3 World::get_max_limits() const {
	return ORIGIN_ + glm::vec3(WIDTH_, HEIGHT_, LENGTH_);
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
	if(walkable(x - 1, y, z)) { res.push_back(glm::vec3(x - 1, y, z)); }
	if(walkable(x, y + 1, z)) { res.push_back(glm::vec3(x, y + 1, z)); }
	if(walkable(x, y - 1, z)) { res.push_back(glm::vec3(x, y - 1, z)); }
	if(walkable(x, y, z + 1)) { res.push_back(glm::vec3(x, y, z + 1)); }
	if(walkable(x, y, z - 1)) { res.push_back(glm::vec3(x, y, z - 1)); }

	return res;
}
const std::vector<glm::vec3> World::get_walkable_neighbours(const unsigned& width, const unsigned& height, const unsigned& length) const {
	return get_walkable_neighbours(glm::vec3(width, height, length));
}