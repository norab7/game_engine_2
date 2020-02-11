#pragma once
#include <iostream>

#include "Transform.h"


class I_Input;

class GameObject {
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
	GameObject(I_Input* input);
	~GameObject() = default;

	void update(); // Give class everything required for an update
};