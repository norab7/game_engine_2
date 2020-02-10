#pragma once
#include <iostream>

#include "Transform.h"
// #include "I_Input.h"

class GameObject {
protected:
	Transform transform; // used for transforming the object

	/* Components */
	// I_Input* input_;
	//Mesh* mesh;
	//Animation* animation;
	//Rigid_body* rigid_body;
public:

	/* TEMP VARIABLES FOR TESTING */
	float x, y, z;

	// Set all defaults to nullptr to allow for unused sections of gameobjects
	GameObject();
	~GameObject() = default;

	void update(); // Give class everything required for an update
};