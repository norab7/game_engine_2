#pragma once
#include "I_AI.h"

class AI_Waypoint : public I_AI {
public:
	std::vector<glm::vec3> WAYPOINTS_;
	unsigned INDEX_ = 0;
	float TOLERANCE_ = 0.5;

	AI_Waypoint(std::vector<glm::vec3>& waypoints);
	~AI_Waypoint() = default;

	void update(GameObject& g) override;

	void receive(std::string component, std::string action) override;
	void activate() override;
	void deactivate() override;

};