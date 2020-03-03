#pragma once
#include <vector>

#include "I_AI.h"

class AI_Boid : public I_AI {
	const std::vector<GameObject*>* BOIDS_ {};
	float SEPERATION_ = 1.0f;
public:
	AI_Boid(const std::vector<GameObject*>* boids);
	~AI_Boid() = default;

	void update(GameObject& g) override;
	void receive(int message) override;
	void activate() override;
	void deactivate() override;
};

/*

veloctiy change for seperation
	(1/(actual / required))/2
	variable velocity change depending on distance
	 ** might not work **

*/