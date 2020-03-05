#pragma once
#include "I_Collider.h"

class Collisions : public I_Collider {
protected:

	const glm::vec3 normals[6] = {
		glm::vec3(-1, 0, 0),
		glm::vec3(1, 0, 0),
		glm::vec3(0, -1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 0, -1),
		glm::vec3(0, 0, 1)
	};

	const std::vector<GameObject*>* OBJECTS_;
	std::vector<GameObject*> collisions;
public:
	Collisions(const std::vector<GameObject*>* objects);

	void update(GameObject& g) override;
	void receive(std::string component, std::string action) override; // TODO: Need to advance this to accept specific messages etc
	void activate() override;
	void deactivate() override;
};