#include "Flock.h"

Flock::Flock(std::vector<GameObject*>& flock, glm::vec3 pos, unsigned max_size) : BOIDS_(&flock), FLOCK_CENTRE_(pos), MAX_SIZE_(max_size) {
	//unsigned i = 0;
	//for(i = 0; i < MAX_SIZE_; i++) {
	//	BOIDS_.push_back(new GameObject(FLOCK_CENTRE_, graphic, nullptr, nullptr, nullptr, nullptr, ai_boid));
	//}
	//std::cout << "created " << i << " boids" << std::endl;
}

void Flock::update(GameObject& g) {

}

void Flock::update_graphics(float& delta) {
	for(GameObject* g : *BOIDS_) {
		g->update_graphics(delta);
	}
	//std::cout << "Graphics Updated" << std::endl;

}

void Flock::update_physics(float& delta) {
	for(GameObject* g : *BOIDS_) {
		g->update_physics(delta);
	}
	//std::cout << "Physics Updated" << std::endl;

}

void Flock::update_move(float& delta) {
	for(GameObject* g : *BOIDS_) {
		g->update_move(delta);
	}
	//std::cout << "Movement Updated" << std::endl;
}

void Flock::receive(std::string component, std::string action) {

}
void Flock::activate() {

}
void Flock::deactivate() {

}