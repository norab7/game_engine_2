#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <list>

#include "World.h"

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

	bool equals(const Node& n) { return (x == n.x && y == n.y && z == n.z); }
	bool less_than(const Node& n) { return (h + g < n.h + n.g); }

};

class Pathfinding {
	// Node End


	//std::list<Node> path {};
	World* WORLD_;
	Node* cur_node;

	Node* start_node;
	Node* end_node;

	std::vector<Node> open_nodes;
	std::vector<Node> closed_nodes;

public:
	bool no_path = false;

	Pathfinding() = default;
	~Pathfinding() = default;

	void search(World* world, const glm::vec3& start, const glm::vec3& end);

	bool has_path();
	glm::vec3& get_current_pos();
	glm::vec3& get_next_pos();
	glm::vec3& get_prev_pos();
	std::vector<Node> get_neighbours(const Node& cur);

	bool has_next();
	bool has_prev();
};