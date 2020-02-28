#include "Pathfinding.h"

/* Node */
Pathfinding::Node::Node(Node* n) {
	this->parent = n->parent;
	this->child = n->child;

	this->g = n->g;
	this->f = n->f;
	this->h = n->h;

	this->x = n->x;
	this->y = n->y;
	this->z = n->z;
}
Pathfinding::Node::Node(glm::vec3 pos, float g, float h, float f) :x(pos.x), y(pos.y), z(pos.z) {

}

float Pathfinding::Node::calculate_g(Node& cur) {
	return cur.g + 1;
}
float Pathfinding::Node::calculate_h(Node& end) {
	return glm::length(glm::vec3(end.x, end.y, end.z) - glm::vec3(x, y, z));
}
float Pathfinding::Node::calculate_f(Node& end) {
	return g + h;
}

/* Pathfinding */
void Pathfinding::search(const World& world, const glm::vec3& start, const glm::vec3& end) {

	// Initialize start node
	start_node = new Pathfinding::Node(start);
	end_node = new Pathfinding::Node(end);

	open_nodes.push_back(*start_node);

	unsigned count = 0;


	// Start searching
	while(!open_nodes.empty()) {
		Pathfinding::Node cur = open_nodes[0];
		unsigned cur_index = 0;
		for(unsigned i = 0; i < open_nodes.size(); i++) {
			if(open_nodes[i].f < cur.f) { cur = open_nodes[i]; cur_index = i; }
		}

		closed_nodes.push_back(cur);
		open_nodes.erase(open_nodes.begin() + cur_index);

		if((cur.x == end_node->x) && (cur.y == end_node->y) && (cur.z == end_node->z)) {
			*end_node = cur;
			no_path = true;
			break;
		}

		for(Pathfinding::Node n : get_neighbours(world, cur)) {
			bool skip = false;
			for(Pathfinding::Node m : closed_nodes) {
				if((n.x == m.x) && (n.y == m.y) && (n.z == m.z)) { skip = true; }
			}
			if(skip) {
				count++;
				continue;
			}

			n.parent = new Node(&cur);
			n.calculate_g(*n.parent);
			n.calculate_h(*end_node);
			n.calculate_f(*end_node);

			skip = false;
			for(Pathfinding::Node l : open_nodes) {
				if((l.x == n.x) && (l.y == n.y) && (l.z == n.z) && l.g < n.g) {
					skip = true;
				}
			}
			if(skip) { continue; }

			open_nodes.push_back(n);

			//for(unsigned i = 0; i < open_nodes.size(); i++) {
			//	if((open_nodes[i].x == n.x) && (open_nodes[i].y == n.y) && (open_nodes[i].z == n.z)) {
			//		if(open_nodes[i].g > n.g) {
			//			open_nodes.erase(open_nodes.begin() + i);
			//			open_nodes.push_back(n);
			//			break;
			//		}
			//	}
			//}
		}
	}

	std::cout << "SKIPPED CLOSED NODES: " << count << std::endl;

	Node cur = *end_node;
	while(cur.parent != nullptr) {
		if(cur.parent != nullptr) { cur.parent->child = new Node(&cur); }
		cur = *cur.parent;
		cur_node = new Node(&cur);
	}
	std::cout << ""; // Debugging without a set end point

}

glm::vec3& Pathfinding::get_current_pos() {
	glm::vec3 res(glm::vec3(cur_node->x * GRIDSPACE_, cur_node->y * GRIDSPACE_, cur_node->z * GRIDSPACE_));
	return res;
}
glm::vec3& Pathfinding::get_next_pos() {
	cur_node = cur_node->child;
	glm::vec3 res(glm::vec3(cur_node->x * GRIDSPACE_, cur_node->y * GRIDSPACE_, cur_node->z * GRIDSPACE_));
	return res;
}

bool Pathfinding::has_next() {
	return (cur_node->child != nullptr);
}

std::vector<Pathfinding::Node> Pathfinding::get_neighbours(const World& world, const Node& cur) {
	std::vector<Pathfinding::Node> nodes {};

	glm::vec3 res(glm::vec3(cur.x, cur.y, cur.z));
	std::vector<glm::vec3> neighbours(world.get_walkable_neighbours(res));

	for(glm::vec3 pos : neighbours) {
		nodes.push_back(Node(pos));
	}

	return nodes;
}