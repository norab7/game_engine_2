#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <iostream>


class World {
	bool in_range(const unsigned& val, const unsigned& range);
public:
	const unsigned WIDTH_ = 10;
	const unsigned LENGTH_ = 10;
	const unsigned HEIGHT_ = 4;
	bool*** GRID_;

	World(const unsigned& width, const unsigned& height, const unsigned& length);

	bool walkable(const glm::vec3& coords);
	bool walkable(const unsigned& width, const unsigned& height, const unsigned& length);

	std::vector<glm::vec3> get_neighbours(const glm::vec3& coords);
	std::vector<glm::vec3> get_neighbours(const unsigned& width, const unsigned& height, const unsigned& length);

	std::vector<glm::vec3> get_walkable_neighbours(const glm::vec3& coords);
	std::vector<glm::vec3> get_walkable_neighbours(const unsigned& width, const unsigned& height, const unsigned& length);

};