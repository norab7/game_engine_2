#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <iostream>


class World {
	const bool in_range(const unsigned& val, const unsigned& range) const;
public:
	std::vector<glm::vec3> open {};
	glm::vec3 ORIGIN_ {0};

	const unsigned WIDTH_ = 10;
	const unsigned LENGTH_ = 10;
	const unsigned HEIGHT_ = 4;
	const float GRIDSPACE_ = 6;
	bool*** GRID_;

	World(const unsigned& width, const unsigned& height, const unsigned& length, const glm::vec3& origin = glm::vec3(0));
	World(const glm::vec3& grid, const glm::vec3& origin = glm::vec3(0));

	const glm::vec3 get_min_limits() const;
	const glm::vec3 get_max_limits() const;
	const glm::vec3 translate(const glm::vec3& coords) const;

	const bool walkable(const glm::vec3& coords) const;
	const bool walkable(const unsigned& width, const unsigned& height, const unsigned& length) const;

	const std::vector<glm::vec3> get_neighbours(const glm::vec3& coords) const;
	const std::vector<glm::vec3> get_neighbours(const unsigned& width, const unsigned& height, const unsigned& length) const;

	const std::vector<glm::vec3> get_walkable_neighbours(const glm::vec3& coords) const;
	const std::vector<glm::vec3> get_walkable_neighbours(const unsigned& width, const unsigned& height, const unsigned& length) const;

};