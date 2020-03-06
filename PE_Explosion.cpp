#include "PE_Explosion.h"
#include <glfw3.h>

PE_Explosion::PE_Explosion(glm::vec3 vel, unsigned max, I_Graphics* g, I_Physics* p, I_Collider* c, std::vector<GameObject*>* self, std::vector<GameObject*>* objects) : P_VEL_(vel), SIZE_(max), graphics(g), physics(p), collisions(c), PARTICLES_(self), OBJECTS_(objects) {
	ACC_ = 5.0f;
}

void PE_Explosion::update(GameObject& g) {
	ACC_ += g.delta_time * 60.0f;
	if(ACC_ > 10.0f) {
		for(unsigned i = 0; i < SIZE_; i++) {
			GameObject* object = new GameObject(g.get_position(), graphics, nullptr, nullptr, physics, nullptr, nullptr, collisions);
			object->life = 20.0f;
			object->mass = 1.0f;

			float rand_val = 1.0f;
			float x_ran = (float) (rand() % (int) rand_val) - rand_val / 2.0f;
			//float y_ran = (float) (rand() % (int) rand_val) - rand_val / 2.0f;
			float z_ran = (float) (rand() % (int) rand_val) - rand_val / 2.0f;

			object->velocity += glm::vec3(x_ran, 0, z_ran) + P_VEL_;
			object->scale(glm::vec3(5));
			OBJECTS_->push_back(object);
		}
		ACC_ = 0;
	}
}

void PE_Explosion::receive(std::string component, std::string action) {

}
void PE_Explosion::activate() {

}
void PE_Explosion::deactivate() {

}