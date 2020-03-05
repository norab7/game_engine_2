#include "Rigid_Body_Physics.h"

Rigid_Body_Physics::Rigid_Body_Physics() {

}

void Rigid_Body_Physics::update(GameObject& g, int world_placeholder) {
	time += g.delta_time;
	glm::vec3 acc(glm::vec3(gravity.x / g.mass, gravity.y / g.mass, gravity.z / g.mass));
	g.set_position(g.get_position() + g.delta_time * (g.velocity + g.delta_time * (acc * 0.5f)));
	g.velocity += g.delta_time * acc;
}

void Rigid_Body_Physics::receive(std::string component, std::string action) {

}
void Rigid_Body_Physics::activate() {

}
void Rigid_Body_Physics::deactivate() {

}