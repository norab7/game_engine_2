#include "AI_Pathfinder.h"

AI_Pathfinder::AI_Pathfinder(World* world, glm::vec3 target, float speed) : world_(world), target_(target), speed_(speed) {

}

void AI_Pathfinder::update(GameObject& g) {
	if(path_complete) { return; }
	if(!path_found) { generate_path(g); }

	if(glm::length(g.pos - cur_goal) <= stoppage) {
		if(path->has_next()) {
			cur_goal = path->get_next_pos();
		} else {
			path_complete = true;
			return;
		}
	}

	glm::vec3 direction = glm::normalize(cur_goal - g.get_position());
	g.velocity += (direction * speed);

}

void AI_Pathfinder::generate_path(GameObject& g) {
	path->search(*world_, g.get_position(), target_);
	cur_goal = path->get_current_pos();
}

void AI_Pathfinder::receive(int msg) {

}
void AI_Pathfinder::activate() {

}
void AI_Pathfinder::deactivate() {

}