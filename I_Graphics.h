#pragma once

#include "GameObject.h"
#include "Model.h"

class I_Graphics : public I_Component {
public:
	virtual ~I_Graphics() = default;
	virtual void update(GameObject& Object) = 0;
};