#include "Collisions.h"

Collisions::Collisions(const std::vector<GameObject*>* objects) : OBJECTS_(objects) {

}

void Collisions::update(GameObject& g) {
	// TODO: Update to using AABB tree eventually

	glm::vec3 pos(g.get_position());
	glm::vec3 tpos(pos.x + g.velocity.x, pos.y + g.velocity.y, pos.z + g.velocity.z);
	if(abs(pos.x - tpos.x) == 0 && abs(pos.y - tpos.y) == 0 && abs(pos.z - tpos.z) == 0) { return; }

	for(GameObject* o : *OBJECTS_) {
		if(g.bounds == nullptr || o->bounds == nullptr) { continue; } // Means that it hasn't updated enough to collide yet
		if(!o->has_collision || g.get_position() == o->get_position()) { continue; }

		//glm::vec3 a_min(g.bounds->minx, g.bounds->miny, g.bounds->minz);
		//glm::vec3 a_max(g.bounds->maxx, g.bounds->maxy, g.bounds->maxz);

		//glm::vec3 b_min(o->bounds->minx, o->bounds->miny, o->bounds->minz);
		//glm::vec3 b_max(o->bounds->maxx, o->bounds->maxy, o->bounds->maxz);

		//// find less than zero and smallest overlap
		//// if overlap is positive it doesn't intersect
		//float intersects[6] = {
		//	b_min.x - a_max.x,
		//	a_min.x - b_max.x,
		//	b_min.y - a_max.y,
		//	a_min.y - b_max.y,
		//	b_min.z - a_max.z,
		//	a_min.z - b_max.z
		//};

		//float min = 9;
		//int index = -1;
		//for(unsigned i = 0; i < 6; i++) {
		//	if(intersects[i] > 0) { continue; } // if it's greater there is no interect

		//	if(min < intersects[i]) {
		//		min = intersects[i];
		//		index = i;
		//	}
		//}


		//glm::vec3 dir(glm::normalize(g.get_position() - o->get_position()));
		if(g.bounds->overlaps(*o->bounds)) {
			//if(o->is_static) { g.velocity = (-g.velocity); continue; }

			// add all velocities, together through the loop
			// use the masses of the objects if they are not static to calcualte force return
			// if it's static just have it bounce at the invert of the velocity
			// should not update the position untill all objects are accounted for

			glm::vec3 relative(o->velocity - g.velocity);
			glm::vec3 force = relative * o->mass;
			glm::vec3 acc = force / g.mass;
			glm::vec3 new_vel = (-g.velocity) + (acc * g.delta_time);
			//time += g.delta_time;
			//glm::vec3 acc(glm::vec3(gravity.x / g.mass, gravity.y / g.mass, gravity.z / g.mass));
			//g.set_position(g.get_position() + g.delta_time * (g.velocity + g.delta_time * (acc * 0.5f)));
			//g.velocity += g.delta_time * acc;

			float variance = ((float) (rand() % 100)) / 1000.0f;

			glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), new_vel));
			new_vel += (right * variance);
			g.velocity = new_vel;

			// g.velocity = (g.velocity * (g.mass / (g.mass + o->mass)));

		}
	}
}

void Collisions::receive(int msg) {
	// TODO: incorporate some form of message system
}

void Collisions::activate() {

}

void Collisions::deactivate() {

}