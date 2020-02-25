#include "Rigid_Body_Physics.h"

Rigid_Body_Physics::Rigid_Body_Physics() {

}

void Rigid_Body_Physics::update(GameObject& g, int world_placeholder) {
	//if(g.at_rest) { return; }
	//float drag = 0.8f;

	//force = glm::vec3(0, mass * gravity, 0);
	//glm::vec3 acceleration = glm::vec3(force.x / mass, force.y / mass, force.z / mass);
	//g.velocity.x += (acceleration.x * g.delta_time) * drag;
	//g.velocity.y += (acceleration.y * g.delta_time) * drag;
	//g.velocity.z += (acceleration.z * g.delta_time) * drag;

	g.velocity.x += gravity.x * g.delta_time;
	g.velocity.y += (gravity.y * g.delta_time) * 0.2f;
	g.velocity.z += gravity.z * g.delta_time;
	g.velocity *= 0.9f;
}

void Rigid_Body_Physics::receive(int msg) {

}
void Rigid_Body_Physics::activate() {

}
void Rigid_Body_Physics::deactivate() {

}