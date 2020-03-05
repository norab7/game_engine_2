#include "Collisions.h"

Collisions::Collisions(const std::vector<GameObject*>* objects) : OBJECTS_(objects) {

}

void Collisions::update(GameObject& g) {
	// TODO: Update to using AABB tree eventually

	glm::vec3 pos(g.get_position());
	glm::vec3 tpos(pos.x + g.velocity.x, pos.y + g.velocity.y, pos.z + g.velocity.z);
	if(abs(pos.x - tpos.x) == 0 && abs(pos.y - tpos.y) == 0 && abs(pos.z - tpos.z) == 0) { return; }

	for(GameObject* o : *OBJECTS_) {
		if(g.bounds == nullptr || o->bounds == nullptr || g.is_static) { continue; } // Means that it hasn't updated enough to collide yet
		if(!o->has_collision || g.get_position() == o->get_position()) { continue; }
		if(g.bounds->overlaps(*o->bounds)) {
			// add all velocities, together through the loop
			// use the masses of the objects if they are not static to calcualte force return
			// if it's static just have it bounce at the invert of the velocity
			// should not update the position untill all objects are accounted for

			glm::vec3 v_dir(glm::normalize(o->get_position() - g.get_position()));

			if(o->is_static) {
				g.velocity = -v_dir * (glm::length(g.velocity) * 0.8f);
			} else {



				float g_mom = glm::length(g.velocity) * g.mass;
				float o_mom = glm::length(o->velocity) * o->mass;
				float t_mom = g_mom + o_mom;
				float t_mass = g.mass + o->mass;

				float d_vel = t_mom / t_mass;
				glm::vec3 d_dir = (g_mom > o_mom) ? v_dir : -v_dir;
				g.velocity += (d_dir * (d_vel / g.mass));
				if(g.get_position().y <= 0) { g.velocity.y = 0; }

				//if(!o->is_static) { o->velocity += d_dir * (d_vel / o->mass); }
			}

			float variance = ((float) (rand() % 10)) / 100000.0f;
			if(g.velocity.x > g.velocity.z) {
				g.velocity.z += variance;
			} else {
				g.velocity.x += variance;
			}


			g.wire = !g.wire;

		}
	}
}

void Collisions::receive(std::string component, std::string action) {
	// TODO: incorporate some form of message system
}

void Collisions::activate() {

}

void Collisions::deactivate() {

}