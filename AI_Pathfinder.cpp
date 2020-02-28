#include "AI_Pathfinder.h"

AI_Pathfinder::AI_Pathfinder(World* world, glm::vec3 start, glm::vec3 target) : WORLD_(world), START_(start), TARGET_(target) {
	PATH_->search(*WORLD_, START_, TARGET_);
	cur_goal = PATH_->get_current_pos();
}

void AI_Pathfinder::update(GameObject& g) {
	if(path_complete) { return; }

	if(glm::length(g.get_position() - cur_goal) <= stoppage) {
		if(PATH_->has_next()) {
			cur_goal = PATH_->get_next_pos();
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

void AI_Pathfinder::receive(int msg) {

}
void AI_Pathfinder::activate() {

}
void AI_Pathfinder::deactivate() {

}