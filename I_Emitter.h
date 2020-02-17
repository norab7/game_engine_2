#pragma once

#include "GameObject.h"

class I_Emitter : public I_Component {

public:
	virtual ~I_Emitter() = default;
	virtual void update(GameObject& g) = 0;
};