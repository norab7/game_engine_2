#include "Rigid_Body_Physics.h"

Rigid_Body_Physics::Rigid_Body_Physics() {

}

void Rigid_Body_Physics::update(GameObject& g, int world_placeholder) {
	static unsigned count = 0;
	bool show = (count++ % 1000 == -1);

	glm::vec3 pos(g.get_position());
	if(show) { std::cout << "physics_before: (" << pos.x << "," << pos.y << "," << pos.z << ")" << std::endl; }

	float delta = 0.001f;
	force = glm::vec3(0, mass * gravity, 0);

	if(show) { std::cout << "physics_force: (" << force.x << "," << force.y << "," << force.z << ")" << std::endl; }

	glm::vec3 acceleration = glm::vec3(force.x / mass, force.y / mass, force.z / mass);
	if(show) { std::cout << "physics_acceleration: (" << acceleration.x << "," << acceleration.y << "," << acceleration.z << ")" << std::endl; }

	if(show) { std::cout << "physics_velocity_before: (" << g.velocity.x << "," << g.velocity.y << "," << g.velocity.z << ")" << std::endl; }
	g.velocity.x += acceleration.x * delta;
	g.velocity.y += acceleration.y * delta;
	g.velocity.z += acceleration.z * delta;
	if(show) { std::cout << "physics_velocity_after: (" << g.velocity.x << "," << g.velocity.y << "," << g.velocity.z << ")" << std::endl; }

	glm::vec3 position(g.get_position());
	g.set_position(glm::vec3(
		position.x + g.velocity.x * delta,
		position.y + g.velocity.y * delta,
		position.z + g.velocity.z * delta
	));

	if(show) { std::cout << "physics_after: (" << pos.x << "," << pos.y << "," << pos.z << ")" << std::endl; }

	// delta++;
}

void Rigid_Body_Physics::receive(int msg) {

}
void Rigid_Body_Physics::activate() {

}
void Rigid_Body_Physics::deactivate() {

}