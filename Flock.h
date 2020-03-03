#pragma once
#include <vector>
#include "I_Emitter.h"

class Flock : public I_Emitter {

	glm::vec3 FLOCK_CENTRE_ {0};
	unsigned MAX_SIZE_ = 10;

public:
	std::vector<GameObject*>* BOIDS_ {};

	Flock(std::vector<GameObject*>& flock, glm::vec3 pos = glm::vec3(0), unsigned max_size = 10);
	~Flock() = default;

	void update(GameObject& g) override;
	void receive(int message) override;
	void activate() override;
	void deactivate() override;

	void update_graphics(float& delta);
	void update_physics(float& delta);
	void update_move(float& delta);
};