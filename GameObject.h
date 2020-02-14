#pragma once
#include <vector>
#include <iostream>
#include <glm/glm.hpp>

#include "I_Component.h"
#include "Transform.h"

/* Class forward Declarations - Much like includes */
class I_Graphics;
class I_Input;
class I_Physics;
class I_Mesh;

class GameObject {
	std::vector<I_Component*> components;

protected:
	I_Graphics* graphics_ = nullptr;
	I_Input* input_ = nullptr;
public:
	glm::mat4 matrix {1};
	glm::vec3 target {0, 0, 0};
	glm::vec3 direction {0,0,1};
	glm::vec3 up {0,1,0};
	glm::vec3 right {1,0,0};
	glm::vec3 front {0,0,-1};

	enum class UPDATE_TYPE { NONE, ALL, GRAPHICS, INPUT };

	// Set all defaults to nullptr to allow for unused sections of gameobjects
	GameObject(I_Graphics* graphics = nullptr, I_Input* input = nullptr);
	~GameObject() = default;

	void update(UPDATE_TYPE type = UPDATE_TYPE::ALL); // Give class everything required for an update
	void send(int msg);

	glm::mat4 get_matrix();
	const glm::vec3 get_position() const;
	void set_position(glm::vec3 pos);
	void transform(glm::mat4 trans);
	void translate(glm::vec3 trans);
	void rotate(float degrees, glm::vec3 axis, bool radians = false);
	void scale(float scale);
	void scale(glm::vec3 scale);
};