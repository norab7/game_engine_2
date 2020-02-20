#include "PE_Explosion.h"
#include <glfw3.h>

PE_Explosion::PE_Explosion(I_Graphics* graphics, I_Physics* physics, glm::vec3 velocity, float life, unsigned count, float v_offset) : life_span(life), active_max(count) {
	this->created_time = glfwGetTime();
	this->graphics_ = graphics;
	this->physics_ = physics;
	this->velocity = velocity;
	this->active_max = count;
	this->velocity_offset = v_offset;

	srand(glfwGetTime());
	for(unsigned i = 0; i < count; i++) {
		GameObject* particle = new GameObject(graphics, nullptr, nullptr, physics);

		glm::vec3 temp_velocity {0};
		temp_velocity.x = velocity.x + (((-v_offset - v_offset) * ((float) rand() / RAND_MAX)) + v_offset);
		temp_velocity.y = velocity.y + (((-v_offset - v_offset) * ((float) rand() / RAND_MAX)) + v_offset);
		temp_velocity.z = velocity.z + (((-v_offset - v_offset) * ((float) rand() / RAND_MAX)) + v_offset);
		particle->velocity = temp_velocity;

		particles.push_back(particle);
	}
}

void PE_Explosion::update(GameObject& g) {
	if(explosion && first_run) {
		first_run = false;
		for(GameObject* particle : particles) {
			particle->set_position(g.get_position());
		}
	}

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