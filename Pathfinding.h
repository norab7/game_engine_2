#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <list>

#include "World.h"


class Pathfinding {
	class Node {
	public:
		Node* parent = nullptr;
		Node* child = nullptr;

		// glm::vec3 pos {0};
		unsigned x = 0, y = 0, z = 0;
		float g = 0, h = 0, f = 0;

		Node(Node* n);
		Node(glm::vec3 pos, float g = 0.0f, float h = 0.0f, float f = 0.0f);
		~Node() = default;

		float calculate_g(Node& cur);
		float calculate_h(Node& end);
		float calculate_f(Node& end);
	};
	// Node End


	//std::list<Node> path {};
	Node* cur_node;

	Node* start_node;
	Node* end_node;

	std::vector<Node> open_nodes;
	std::vector<Node> closed_nodes;

	const float GRIDSPACE_ = 6;

public:
	bool no_path = false;

	Pathfinding() = default;
	~Pathfinding() = default;

	void search(const World& world, const glm::vec3& start, const glm::vec3& end);

	glm::vec3& get_current_pos();
	glm::vec3& get_next_pos();
	std::vector<Node> get_neighbours(const World& world, const Pathfinding::Node& cur);

	bool has_next();

};