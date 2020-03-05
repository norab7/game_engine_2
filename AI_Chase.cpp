#include "AI_Chase.h"

AI_Chase::AI_Chase(glm::vec3& target, float speed) : speed(speed) {
	this->target = &target;
}

void AI_Chase::update(GameObject& g) {
	if(glm::length(*target - g.get_position()) <= stoppage) { return; }

	glm::vec3 direction = glm::normalize(*target - g.get_position());
	g.velocity += (direction * speed);

	if(glm::length(g.get_position() - *target) <= 0.1 && g.goal_achieved == false) {
		g.goal_achieved = true;
		g.alive = false;
	}

}

void AI_Chase::receive(std::string component, std::string action) {

}
void AI_Chase::activate() {

}
void AI_Chase::deactivate() {

}