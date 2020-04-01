#include "Pathfinding.h"

/* Node */
Node::Node(Node* n) {
	this->parent = n->parent;
	this->child = n->child;

	this->g = n->g;
	this->f = n->f;
	this->h = n->h;

	this->x = n->x;
	this->y = n->y;
	this->z = n->z;
}
Node::Node(glm::vec3 pos, float g, float h, float f) :x(pos.x), y(pos.y), z(pos.z) {

}

float Node::calculate_g(Node& cur) {
	return cur.g + 1;
}
float Node::calculate_h(Node& end) {
	return glm::length(glm::vec3(end.x, end.y, end.z) - glm::vec3(x, y, z));
}
float Node::calculate_f(Node& end) {
	return g + h;
}

/* Pathfinding */
void Pathfinding::search(PathmapWorld* world, const glm::vec3& start, const glm::vec3& end) {

	// Initialize start node
	WORLD_ = world;
	start_node = new Node(start);
	end_node = new Node(end);

	open_nodes.push_back(*start_node);

	// Start searching
	while(!open_nodes.empty()) {
		Node cur = open_nodes.front();
		for(Node n : open_nodes) {
			if(n.less_than(cur)) { cur = n; }
		}

		if(cur.equals(end_node)) {
			*end_node = new Node(cur);
			break;
		}

		for(unsigned i = 0; i < open_nodes.size(); i++) {
			if(open_nodes[i].equals(cur)) {
				open_nodes.erase(open_nodes.begin() + i);
			}
		}
		closed_nodes.push_back(cur);

		for(Node n : get_neighbours(cur)) {
			bool skip = false;
			for(Node m : closed_nodes) {
				if(n.equals(m)) { skip = true; }
			}
			if(skip) {
				continue; // Do not calculate the node or add it to open nodes etc
			}

			n.parent = new Node(&cur);
			n.calculate_g(*n.parent);
			n.calculate_h(*end_node);
			n.calculate_f(*end_node);

			skip = false;
			for(Node l : open_nodes) {
				if(l.equals(n) && l.less_than(n)) {
					skip = true;
					break;
				}
			}
			if(skip) { continue; }

			open_nodes.push_back(n);

		}
	}

	Node cur = *end_node;
	while(cur.parent != nullptr) {
		if(cur.parent != nullptr) { cur.parent->child = new Node(&cur); }
		cur = *cur.parent;
		cur_node = new Node(&cur);
	}
	std::cout << ""; // Debugging without a set end point

}

bool Pathfinding::has_path() {
	if(cur_node == nullptr) { return false; }
	return true;
}

glm::vec3& Pathfinding::get_current_pos() {
	glm::vec3 res = (cur_node != nullptr) ? WORLD_->translate(glm::vec3(cur_node->x, cur_node->y, cur_node->z)) : glm::vec3(0);
	return res;
}
glm::vec3& Pathfinding::get_next_pos() {
	cur_node = cur_node->child;
	glm::vec3 res(glm::vec3(cur_node->x * WORLD_->GRIDSPACE_, cur_node->y * WORLD_->GRIDSPACE_, cur_node->z * WORLD_->GRIDSPACE_));
	return res;
}
glm::vec3& Pathfinding::get_prev_pos() {
	cur_node = cur_node->parent;
	glm::vec3 res(glm::vec3(cur_node->x * WORLD_->GRIDSPACE_, cur_node->y * WORLD_->GRIDSPACE_, cur_node->z * WORLD_->GRIDSPACE_));
	return res;
}

bool Pathfinding::has_next() {
	return (cur_node->child != nullptr);
}
bool Pathfinding::has_prev() {
	return (cur_node->parent != nullptr);
}

std::vector<Node> Pathfinding::get_neighbours(const Node& cur) {
	std::vector<Node> nodes {};

	glm::vec3 res(glm::vec3(cur.x, cur.y, cur.z));
	std::vector<glm::vec3> neighbours(WORLD_->get_walkable_neighbours(res));

	for(glm::vec3 pos : neighbours) {
		nodes.push_back(Node(pos));
	}

	return nodes;
}

std::vector<glm::vec3> Pathfinding::get_path(PathmapWorld* world, const glm::vec3& start, const glm::vec3& end) {
	search(world, start, end);
	std::vector<glm::vec3> res {};

	if(cur_node != nullptr) {
		Node cur = *cur_node;
		while(cur.child != nullptr) {
			cur = *cur.child;
			res.push_back(world->translate(glm::vec3(cur.x, cur.y, cur.z)));
		}
	} else {
		return get_path(world, start, world->open.at(rand() % world->open.size()));
	}

	return res;
}