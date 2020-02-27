#include "AI_Pathfinder.h"

AI_Pathfinder::AI_Pathfinder(World* world, glm::vec3 target, float speed) : world_(world), target_(target), speed_(speed) {

}

void AI_Pathfinder::update(GameObject& g) {
	if(path_complete) { return; }
	if(!path_found) {
		generate_path(g);
		std::cout << "Goal: (" << cur_goal.x << "," << cur_goal.y << "," << cur_goal.z << ")" << std::endl;
	}

	if(glm::length(g.get_position() - cur_goal) <= stoppage) {
		if(path->has_next()) {
			cur_goal = path->get_next_pos();
			std::cout << "Goal Complete - Next Goal: (" << cur_goal.x << "," << cur_goal.y << "," << cur_goal.z << ")" << std::endl;
		} else {
			static bool done = true;
			if(done) { done = false; std::cout << "Done!" << std::endl; }
			g.velocity = glm::vec3(0);
		}
	} else {
		glm::vec3 pos(g.get_position());
		glm::vec3 direction = glm::normalize(cur_goal - g.get_position());
		g.velocity += (direction * speed) * (glm::length(cur_goal - g.get_position()) * 10);
		g.velocity *= 0.5f;
	}

}

void AI_Pathfinder::generate_path(GameObject& g) {
	path->search(*world_, g.get_position(), target_);
	cur_goal = path->get_current_pos();
	path_found = true;
	//std::cout << "cur: " << cur_goal.x << "," << cur_goal.y << "," << cur_goal.z << ")" << std::endl;

}

void AI_Pathfinder::receive(int msg) {

}
void AI_Pathfinder::activate() {

}
void AI_Pathfinder::deactivate() {

}