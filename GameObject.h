#pragma once
#include "Transform.h"
#include "I_Input.h"

class GameObject {
protected:
	Transform transform; // used for transforming the object

	/* Components */
	I_Input* input_;
	//Mesh* mesh;
	//Animation* animation;
	//Rigid_body* rigid_body;
public:
	// Set all defaults to nullptr to allow for unused sections of gameobjects
	GameObject(I_Input* input = nullptr);
	~GameObject();
};