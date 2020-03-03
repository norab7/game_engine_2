#pragma once
#include <vector>

#include "I_AI.h"

class AI_Boid : public I_AI {
	float way_timer = 0;

	const std::vector<GameObject*>* BOIDS_ {};

	glm::vec3 POINT_ {};
	std::vector<glm::vec3> WAYPOINTS_ {
		glm::vec3(0,10,0),
		glm::vec3(0,10,-30),
		glm::vec3(-30,10,-30),
		glm::vec3(-30, 10, 0)
	};

	float SEPERATION_ = 1.0f;
public:
	unsigned WAY_ = 0;

	AI_Boid(const std::vector<GameObject*>* boids);
	AI_Boid(const std::vector<GameObject*>* boids, std::vector<glm::vec3> waypoints);
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