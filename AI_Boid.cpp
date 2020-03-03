#include "AI_Boid.h"

AI_Boid::AI_Boid(const std::vector<GameObject*>* boids) : BOIDS_(boids) {
}

void AI_Boid::update(GameObject& g) {
	float delta_speed = g.delta_time * 10.0f;

	glm::vec3 target {-30, 10,-30};

	glm::vec3 s_vel {0};
	glm::vec3 c_vel {0};
	glm::vec3 a_vel {0};
	glm::vec3 t_vel {0};

	for(GameObject* boid : *BOIDS_) {
		if(&g == boid && g.get_position() == boid->get_position()) { continue; }

		/* Seperation */
		//float sep = glm::length(boid->get_position() - g.get_position());
		//if(sep < SEPERATION_) {
		//	float mult = (sep < SEPERATION_ / 2.0f) ? 1.0f / sep : 1.0f;
		//	s_vel = s_vel - ((boid->get_position() - g.get_position()) * (-mult * (sep - SEPERATION_)));
		//	s_vel *= g.delta_time * 2.0f;
		//}
		float sep = glm::length(boid->get_position() - g.get_position());
		glm::vec3 s_dir = g.get_position() - boid->get_position();
		float repulse = 1 / sep;
		s_vel += glm::normalize(s_dir) * powf(repulse, SEPERATION_) * g.delta_time;

		// Move to Centre
		c_vel += boid->get_position() * g.delta_time;

		// Alignment
		// a_vel += boid->velocity;

	}

	/* Seperation */
	// s_vel *= g.delta_time;

	float avg = BOIDS_->size() - 1.0f;

	/* Target */
	glm::vec3 t_dir = glm::normalize(target - g.get_position());
	t_vel = t_dir * g.delta_time;
	// t_vel = (target - g.get_position()) * (0.5f * (g.get_position() - target));
	//t_vel *= g.delta_time * 10.0f;


	/* Centre */
	c_vel = glm::normalize((c_vel / avg) - g.get_position());
	c_vel = c_vel * g.delta_time * 10.0f;


	/* Alignment */
	//a_vel = a_vel / avg;
	//a_vel = a_vel - g.velocity;


	/* Position and Velocity Change */
	g.velocity += s_vel + c_vel + a_vel + t_vel;
	//g.velocity *= delta_speed;
	g.set_position(g.get_position() + g.velocity);
}

void AI_Boid::receive(int msg) {

}
void AI_Boid::activate() {

}
void AI_Boid::deactivate() {

}