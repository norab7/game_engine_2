#pragma once
#include "I_AI.h"
#include "World.h"
#include "Pathfinding.h"

class AI_Pathfinder : public I_AI {
	bool path_found = false;
	bool goal_complete = false;
	bool path_complete = false;

	float stoppage = 0.1f;
	float speed = 0.01f;

	glm::vec3 cur_goal {};

public:
	Pathfinding* PATH_ = new Pathfinding();
	World* WORLD_ = nullptr;
	glm::vec3 START_ {0};
	glm::vec3 TARGET_ {0};

	AI_Pathfinder(World* world, glm::vec3 start, glm::vec3 target);
	~AI_Pathfinder() = default;

	void update(GameObject& g) override;

	void receive(int message) override;
	void activate() override;
	void deactivate() override;
};