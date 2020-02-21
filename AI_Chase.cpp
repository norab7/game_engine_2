#include "AI_Chase.h"

AI_Chase::AI_Chase(glm::vec3 target, float speed) : speed(speed) {

}

void AI_Chase::update(GameObject& g) {
	if(glm::length(target - g.get_position()) <= stoppage) { return; }

	glm::vec3 direction = glm::normalize(target - g.get_position());

	g.velocity += (direction * speed);

}

void AI_Chase::receive(int msg) {

}
void AI_Chase::activate() {

}
void AI_Chase::deactivate() {

}