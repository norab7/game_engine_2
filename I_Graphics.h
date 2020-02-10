#pragma once

#include "GameObject.h"

class I_Graphics {
public:
	virtual ~I_Graphics() = default;
	virtual void update(GameObject& Object, int graphics_placeholder) = 0;
};