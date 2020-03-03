#include "AI_Boid.h"

AI_Boid::AI_Boid(const std::vector<GameObject*>* boids) : BOIDS_(boids) {
}

void AI_Boid::update(GameObject& g) {

	glm::vec3 s_vel {0};
	glm::vec3 c_vel {0};
	glm::vec3 v_vel {0};
	glm::vec3 t_vel {0};

	for(GameObject* boid : *BOIDS_) {

		if(g.get_position() == boid->get_position()) { continue; }

		// Seperation
		glm::vec3 sep(boid->get_position() - g.get_position());
		if(glm::length(sep) < SEPERATION_) { s_vel -= sep; }

		// Move to Centre
		c_vel += boid->get_position();

		// Alignment via Velocity
		//v_vel += boid->velocity;


	}

	// Tend Towards Location
	t_vel = (glm::vec3(0) - g.get_position()) / 100.0f;
	c_vel /= (BOIDS_->size() - 1) / 100.0f; // Slight movement to centre
	// v_vel /= (BOIDS_->size() - 1) / 8.0f; // Slow direction change

	g.velocity += s_vel + c_vel + v_vel + t_vel * g.delta_time;
	//g.set_position(g.get_position() + g.velocity);
	//std::cout << "(s,c,v): (" << glm::length(s_vel) << "," << glm::length(c_vel) << "," << glm::length(v_vel) << ")" << std::endl;
	//std::cout << "Boid Position: (" << g.get_position().x << "," << g.get_position().y << "," << g.get_position().z << ")" << std::endl;
}

void AI_Boid::receive(int msg) {

}
void AI_Boid::activate() {

}
void AI_Boid::deactivate() {

}