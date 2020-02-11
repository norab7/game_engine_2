#pragma once
#include <vector>
#include <iostream>
#include <glm/glm.hpp>

#include "I_Component.h"
#include "Transform.h"

/* Class forward Declarations - Much like includes */
class I_Input;
class I_Physics;
class I_Graphics;
class I_Mesh;

class GameObject {
	std::vector<I_Component*> components;

protected:
	Transform transform; // used for transforming the object

	/* Components */
	I_Input* input_;
	//Mesh* mesh;
	//Animation* animation;
	//Rigid_body* rigid_body;
public:

	/* TEMP VARIABLES FOR TESTING */
	float x = 0.0f, y = 0.0f, z = 0.0f;

	// Set all defaults to nullptr to allow for unused sections of gameobjects
	GameObject(I_Input* input = nullptr);
	~GameObject() = default;

	void update(); // Give class everything required for an update
	void send(int msg);
};