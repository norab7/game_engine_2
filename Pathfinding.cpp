#include "Pathfinding.h"

/* Node */
Pathfinding::Node::Node(glm::vec3 pos, float g, float h, float f) {
	this->pos = pos;
}

float Pathfinding::Node::calculate_g(Node& cur) {
	return cur.g + 1;
}
float Pathfinding::Node::calculate_h(Node& end) {
	return glm::length(end.pos - pos);
}
float Pathfinding::Node::calculate_f(Node& end) {
	return g + h;
}

/* Pathfinding */
void Pathfinding::search(const World& world, const glm::vec3& start, const glm::vec3& end) {

	// Initialize start node
	Node* start_node = new Node(start);
	Node* end_node = new Node(end);
	open_nodes.push_back(start_node);

	// Start searching
	while(!open_nodes.empty()) {
		Node* cur = open_nodes[0];
		unsigned cur_index = 0;
		for(cur_index = 0; cur_index < open_nodes.size(); cur_index++) {
			if(open_nodes[cur_index]->f < cur->f) { cur = open_nodes[cur_index]; }
		}

		closed_nodes.push_back(cur);
		open_nodes.erase(open_nodes.begin() + cur_index);

		if(cur->pos == end_node->pos) { end_node = cur; break; }

		for(Node* n : get_neighbours(world, cur)) {
			bool skip = false;
			for(Node* m : closed_nodes) {
				if(n->pos == m->pos) { skip = true; }
			}
			if(skip) { continue; }

			n->parent = cur;
			n->calculate_g(*cur);
			n->calculate_h(*end_node);
			n->calculate_f(*end_node);

			skip = false;
			for(Node* l : open_nodes) {
				if(l->pos == n->pos && l->g < n->g) { skip = true; }
			}
			if(skip) { continue; }

			open_nodes.push_back(n);

		}
	}

	path = *new std::list<glm::vec3> {};
	Node* cur = end_node;
	while(cur->parent != nullptr) {
		path.push_back(cur->pos);
		cur = cur->parent;
	}
	path.push_back(start_node->pos);
	path.reverse();

}

std::vector<Pathfinding::Node*> Pathfinding::get_neighbours(const World& world, const Node* cur) {
	std::vector<Pathfinding::Node*> nodes {};
	std::vector<glm::vec3> neighbours(world.get_walkable_neighbours(cur->pos));

	for(glm::vec3 pos : neighbours) {
		nodes.push_back(new Node(pos));
	}

	return nodes;
}