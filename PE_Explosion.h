#pragma once
#include "I_Emitter.h"

class PE_Explosion : public I_Emitter {
	I_Graphics* graphics = nullptr;
	I_Physics* physics = nullptr;
	I_Collider* collisions = nullptr;

public:
	std::vector<GameObject*>* OBJECTS_ {};
	std::vector<GameObject*>* PARTICLES_ {};

	glm::vec3 P_POS_ {0,0,0};
	glm::vec3 P_VEL_ {0, 10, 0};

	unsigned SIZE_ = 1;
	float LIFE_ = 0.0f;
	float VARIANCE_ = 0.2f;
	float DELAT_ = 5.0f;
	float ACC_ = 0.0f;

	PE_Explosion(glm::vec3 vel, unsigned mass, I_Graphics* g, I_Physics* p, I_Collider* c, std::vector<GameObject*>* self, std::vector<GameObject*>* objects);
	~PE_Explosion() = default;

	void update(GameObject& g) override;
	void receive(std::string component, std::string action) override;
	void activate() override;
	void deactivate() override;
};