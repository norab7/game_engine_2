#include "PE_Emitter.h"


PE_Emitter::PE_Emitter(glm::vec3 vel, float mass, I_Graphics* g, I_Physics* p, I_Collider* c, std::vector<GameObject*>* objects) : P_VEL_(vel), MASS_(mass), graphics(g), physics(p), collisions(c), OBJECTS_(objects) {

}

void PE_Emitter::update(GameObject& g) {
	ACC_ += g.delta_time * 60.0f;
	if(ACC_ > 1.0f) {
		GameObject* object = new GameObject(g.get_position(), graphics, nullptr, nullptr, physics, nullptr, nullptr, collisions);
		object->life = 5.0f;
		object->velocity = P_VEL_;
		object->mass = MASS_;
		OBJECTS_->push_back(object);

		ACC_ = 0;
	}
}

void PE_Emitter::receive(std::string component, std::string action) {

}
void PE_Emitter::activate() {

}
void PE_Emitter::deactivate() {

}