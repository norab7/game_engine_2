#pragma once
#include "Transform.h"

class GameObject {
protected:
	Transform transform; // used for transforming the object

	/* Components */
	//Mesh* mesh;
	//Animation* animation;
	//Rigid_body* rigid_body;
public:
	GameObject() {
		// Sets all components to nullptr;
	}
	~GameObject() {
		// delete all components created
	}
};