#pragma once
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm\ext\matrix_transform.hpp>

#include "I_Component.h"
#include "AABB.h"

/* Class forward Declarations - Much like includes */
class I_Graphics;
class I_Input;
class I_Camera;
class I_Physics;
class I_Emitter;
class I_AI;
class I_Collider;

class GameObject {
	std::vector<I_Component*> components;

protected:
public:
	std::string name = "";


	// TODO: once everything is settled, change to messaging system instead of public
	I_Graphics* graphics_ = nullptr;
	I_Input* input_ = nullptr;
	I_Camera* camera_ = nullptr;
	I_Physics* physics_ = nullptr;
	I_Emitter* emitter_ = nullptr;
	I_AI* ai_ = nullptr;
	I_Collider* collider_ = nullptr;

	// TODO: make public variables private
	glm::mat4 matrix {1};
	glm::mat4 view {0};
	glm::vec3 up {0,1,0};
	glm::vec3 right {-1,0,0};
	glm::vec3 front {0,0,-1};
	glm::vec3 flat_front {0,0,-1};
	glm::vec3 world_up {0,1,0};

	glm::vec3 velocity {0};

	bool at_rest = true;
	bool falling = true;
	bool alive = true;
	bool goal_achieved = false;

	// Collisions and Boundaries and now physics
	float life = -1.0f;
	float mass = 1.0f;
	bool is_static = false;
	bool has_collision = false;
	glm::vec3 last_position {0};
	AABB* bounds = nullptr;
	glm::vec3 centre {0}; // fix for actual centre of mass

	// Temporary Child Storage
	std::vector<GameObject*> children {};
	bool wire = false;

	float delta_time;

	// Set all defaults to nullptr to allow for unused sections of gameobjects
	GameObject(glm::vec3 position, I_Graphics* graphics = nullptr, I_Input* input = nullptr, I_Camera* camera = nullptr, I_Physics* physics = nullptr, I_Emitter* emitter = nullptr, I_AI* ai = nullptr, I_Collider* collider = nullptr);
	~GameObject() = default;

	void update_input(float& delta);
	void update_physics(float& delta);
	void update_graphics(float& delta);
	void update_move(float& delta);
	void send(std::string component, std::string action);

	// Setting Functions
	void set_velocity(glm::vec3 v);
	void set_velocity(float x, float y, float z);
	void add_velocity(glm::vec3 v);
	void add_velocity(float x, float y, float z);

	// TODO: Move transform code back to seperate object
	glm::mat4 get_matrix();
	const glm::vec3 get_position() const;
	void set_position(glm::vec3 pos);
	void transform(glm::mat4 trans);
	void translate(glm::vec3 trans);
	void rotate(float degrees, glm::vec3 axis, bool radians = false);
	void scale(float scale);
	void scale(glm::vec3 scale);
};