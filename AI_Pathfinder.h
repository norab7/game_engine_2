#pragma once
#include "I_AI.h"
#include "PathmapWorld.h"
#include "Pathfinding.h"

class AI_Pathfinder : public I_AI {
	bool path_found = false;
	bool goal_complete = false;
	bool path_complete = false;

	float stoppage = 0.5f;
	float speed = 0.1f;

	glm::vec3 cur_goal {};

public:
	Pathfinding* PATH_ = new Pathfinding();
	PathmapWorld* WORLD_ = nullptr;
	glm::vec3 START_ {0};
	glm::vec3 TARGET_ {0};

	bool first_run = true;
	bool has_path = false;
	bool forward = false;

	AI_Pathfinder(PathmapWorld* world, glm::vec3 start, glm::vec3 target);
	~AI_Pathfinder() = default;

	void update(GameObject& g) override;

	void receive(std::string component, std::string action) override;
	void activate() override;
	void deactivate() override;
};