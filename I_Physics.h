#pragma once
#include "GameObject.h"

class I_Physics : public I_Component {
public:
	virtual ~I_Physics() = default;
	virtual void update(GameObject& Object, int world_placeholder) = 0;
};