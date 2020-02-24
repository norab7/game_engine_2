#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <list>

class world;

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
	std::list<Node*> path;
	const world* grid;

public:
	Pathfinding(const world& grid);
	~Pathfinding() = default;

	void search(glm::vec3 start, glm::vec3 end);
	std::vector<Node*> get_neighbours(Node* cur);
};