#pragma once

#include "GameObject.h"

class I_Camera : public I_Component {

public:
	virtual ~I_Camera() = default;
	virtual void update(GameObject& g) = 0;
};