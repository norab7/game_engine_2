#include "Collisions.h"

Collisions::Collisions(const std::vector<GameObject*>* objects) : OBJECTS_(objects) {

}

void Collisions::update(GameObject& g) {
	// TODO: Update to using AABB tree eventually
	glm::vec3 pos(g.get_position());
	glm::vec3 tpos(pos.x + g.velocity.x, pos.y + g.velocity.y, pos.z + g.velocity.z);
	if(glm::length(glm::vec3(pos.x - tpos.x, pos.y - tpos.y, pos.z - tpos.z)) > 0) { return; }

	for(GameObject* o : *OBJECTS_) {
		if(!o->has_collision || g.get_position() == o->get_position()) { continue; }

		glm::vec3 a_min(g.bounds->minx, g.bounds->miny, g.bounds->minz);
		glm::vec3 a_max(g.bounds->maxx, g.bounds->maxy, g.bounds->maxz);

		glm::vec3 b_min(o->bounds->minx, o->bounds->miny, o->bounds->minz);
		glm::vec3 b_max(o->bounds->maxx, o->bounds->maxy, o->bounds->maxz);

		// find less than zero and smallest overlap
		// if overlap is positive it doesn't intersect
		float intersects[6] = {
			b_min.x - a_max.x,
			a_min.x - b_max.x,
			b_min.y - a_max.y,
			a_min.y - b_max.y,
			b_min.z - a_max.z,
			a_min.z - b_max.z
		};

		float min = 9;
		int index = -1;
		for(unsigned i = 0; i < 6; i++) {
			if(intersects[i] > 0) { continue; } // if it's greater there is no interect

			if(min < intersects[i]) {
				min = intersects[i];
				index = i;
			}
		}


		glm::vec3 dir(glm::normalize(g.get_position() - o->get_position()));


		if(g.bounds->overlaps(*o->bounds)) {
			std::cout << "Collisions Detected" << std::endl;
			glm::vec3 relative(g.velocity - o->velocity);




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