#include "Rigid_Body_Physics.h"

Rigid_Body_Physics::Rigid_Body_Physics() {

}

void Rigid_Body_Physics::update(GameObject& g, int world_placeholder) {
	if(g.at_rest) { return; }

	glm::vec3 d_pos(g.velocity);

	float delta = 0.0025f;
	force = glm::vec3(0, mass * gravity, 0);

	glm::vec3 acceleration = glm::vec3(force.x / mass, force.y / mass, force.z / mass);
	g.velocity.x += acceleration.x * delta;
	g.velocity.y += acceleration.y * delta;
	g.velocity.z += acceleration.z * delta;

	g.velocity *= drag;

}

void Rigid_Body_Physics::receive(int msg) {

}
void Rigid_Body_Physics::activate() {

}
void Rigid_Body_Physics::deactivate() {

}