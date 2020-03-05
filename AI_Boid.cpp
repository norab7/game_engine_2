#include "AI_Boid.h"

AI_Boid::AI_Boid(const std::vector<GameObject*>* boids) : BOIDS_(boids) {
	glm::vec3 way(WAYPOINTS_[0]);
}
AI_Boid::AI_Boid(const std::vector<GameObject*>* boids, std::vector<glm::vec3> waypoints) : BOIDS_(boids), WAYPOINTS_(waypoints) {
	glm::vec3 way(WAYPOINTS_[0]);
}


void AI_Boid::update(GameObject& g) {
	way_timer += g.delta_time * 60;
	//std::cout << "boid_delta: " << way_timer << std::endl;

	float delta_speed = g.delta_time * 10.0f;

	glm::vec3 s_vel {0};
	glm::vec3 c_vel {0};
	glm::vec3 a_vel {0};
	glm::vec3 t_vel {0};

	float inf = 0;

	for(GameObject* boid : *BOIDS_) {
		if(&g == boid && g.get_position() == boid->get_position()) { continue; }

		/* Seperation */
		float sep = glm::length(boid->get_position() - g.get_position());
		glm::vec3 s_dir = g.get_position() - boid->get_position();
		float repulse = 1 / sep;
		s_vel += glm::normalize(s_dir) * powf(repulse, SEPERATION_) * g.delta_time;

		// Move to Centre
		c_vel += boid->get_position();

		// Alignment

	}

	float avg = BOIDS_->size() - 1.0f;

	/* Target */
	if(way_timer > 3.0f || glm::length((c_vel / avg) - POINT_) < 0.5) {
		way_timer = 0.0f;
		WAY_ = ++WAY_ % WAYPOINTS_.size();
		POINT_ = WAYPOINTS_[WAY_];
		//std::cout << "New Target: (" << POINT_.x << "," << POINT_.y << "," << POINT_.z << ")" << std::endl;
	}

	/* Target */
	glm::vec3 y_offset(0, 5, 0);
	glm::vec3 t_dir = glm::normalize((POINT_ + y_offset) - g.get_position());
	t_vel = t_dir * g.delta_time * 3.0f;


	/* Centre */
	c_vel = glm::normalize((c_vel / avg) - g.get_position());
	c_vel = c_vel * g.delta_time * 8.0f;


	/* Alignment */



	/* Position and Velocity Change */
	float mod = 2.0f;
	g.velocity += s_vel + (c_vel * mod) + a_vel + (t_vel * mod);
	g.velocity *= 0.999f;

	glm::vec3 new_pos(g.get_position() + g.velocity);

	if(new_pos.y < 0) {
		new_pos = glm::vec3(new_pos.x, 0, new_pos.z);
	}

	g.set_position(new_pos);
}

void AI_Boid::receive(std::string component, std::string action) {

}
void AI_Boid::activate() {

}
void AI_Boid::deactivate() {

}