#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <list>

#include "World.h"

class Pathfinding {
	class Node {
	public:
		Node* parent = nullptr;

		glm::vec3 pos {0};
		float g = 0, h = 0, f = 0;

		Node(glm::vec3 pos, float g = 0.0f, float h = 0.0f, float f = 0.0f);
		~Node() = default;

		float calculate_g(Node& cur);
		float calculate_h(Node& end);
		float calculate_f(Node& end);
	};
	// Node End

	std::vector<Node*> open_nodes;
	std::vector<Node*> closed_nodes;
	std::list<glm::vec3> path;
public:
	Pathfinding() = default;
	~Pathfinding() = default;

	void search(const World& world, const glm::vec3& start, const glm::vec3& end);
	std::vector<Node*> get_neighbours(const World& world, const Node* cur);
};