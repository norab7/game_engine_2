#include "PE_Explosion.h"
#include <glfw3.h>

PE_Explosion::PE_Explosion(glm::vec3 position, I_Graphics* graphics, I_Physics* physics, glm::vec3 velocity, float life, unsigned count, float v_offset)
	: created_time(glfwGetTime()), graphics_(graphics), physics_(physics), velocity(velocity), life_span(life), active_max(count), velocity_offset(v_offset) {

	srand(glfwGetTime());
	for(unsigned i = 0; i < count; i++) {
		GameObject* particle = new GameObject(position, graphics, nullptr, nullptr, physics);

		glm::vec3 temp_velocity {0};
		temp_velocity.x = velocity.x + (((-v_offset - v_offset) * ((float) rand() / RAND_MAX)) + v_offset);
		temp_velocity.y = velocity.y + (((-v_offset - v_offset) * ((float) rand() / RAND_MAX)) + v_offset);
		temp_velocity.z = velocity.z + (((-v_offset - v_offset) * ((float) rand() / RAND_MAX)) + v_offset);
		particle->velocity = temp_velocity;

		particles.push_back(particle);
	}
}

void PE_Explosion::update(GameObject& g) {
	for(GameObject* particle : particles) {
		particle->update();
	}

	if(glfwGetTime() - created_time >= life_span) {
		g.alive = false;
	}
}

void PE_Explosion::receive(int msg) {

}
void PE_Explosion::activate() {

}
void PE_Explosion::deactivate() {

}