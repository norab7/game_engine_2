#include "Particle_Emitter.h"
#include <glfw3.h>

Particle_Emitter::Particle_Emitter(I_Graphics* graphics, I_Physics* physics, glm::vec3 velocity, unsigned life, unsigned count, bool burst, float rate, float v_offset) : life_span(life), active_max(count), explosion(burst), spawn_rate(rate) {
	this->graphics_ = graphics;
	this->physics_ = physics;
	this->velocity = velocity;
	this->active_max = count;
	this->explosion = burst;
	this->spawn_rate = rate;
	this->velocity_offset = v_offset;
	
	if(burst) {
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
	} else {
		// currently do nothing to test !!EXPLOSION!!
	}
}

void Particle_Emitter::update(GameObject& g) {
	if(explosion && first_run) {
		first_run = false;
		for(GameObject* particle : particles) {
			particle->set_position(g.get_position());
		}
	}

	for(GameObject* particle : particles) {
		particle->update();
	}
}

void Particle_Emitter::receive(int msg) {

}
void Particle_Emitter::activate() {

}
void Particle_Emitter::deactivate() {

}