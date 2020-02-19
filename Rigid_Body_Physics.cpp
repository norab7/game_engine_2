#include "Rigid_Body_Physics.h"

Rigid_Body_Physics::Rigid_Body_Physics() {

}

void Rigid_Body_Physics::update(GameObject& g, int world_placeholder) {
	if(at_rest) { return; }

	glm::vec3 pos(g.get_position());
	glm::vec3 d_pos(g.velocity);

	float delta = 0.0025f;
	force = glm::vec3(0, mass * gravity, 0);

	glm::vec3 acceleration = glm::vec3(force.x / mass, force.y / mass, force.z / mass);
	g.velocity.x += acceleration.x * delta;
	g.velocity.y += acceleration.y * delta;
	g.velocity.z += acceleration.z * delta;

	g.velocity *= drag;

	pos.x += g.velocity.x * delta;
	pos.y += g.velocity.y * delta;
	pos.z += g.velocity.z * delta;

	float stoppage = 0.0005f;
	if(!falling) {
		glm::vec3 diff(std::abs(pos.x - g.get_position().x), std::abs(pos.y - g.get_position().y), std::abs(pos.z - g.get_position().z));

		pos.x = (diff.x <= stoppage) ? g.get_position().x : pos.x;
		pos.y = (diff.y <= stoppage) ? g.get_position().y : pos.y;
		pos.z = (diff.z <= stoppage) ? g.get_position().z : pos.z;

		at_rest = (diff.x <= stoppage && diff.y <= stoppage && diff.z <= stoppage);
	}

	if(pos.y <= 0) {
		pos.y = 0;
		falling = false;
	} else {
		falling = true;
	}

	g.set_position(pos);
}

void Rigid_Body_Physics::receive(int msg) {

}
void Rigid_Body_Physics::activate() {

}
void Rigid_Body_Physics::deactivate() {

}