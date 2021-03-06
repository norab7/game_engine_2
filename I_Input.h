#pragma once

#include "GameObject.h"

class I_Input : public I_Component {

public:
	virtual ~I_Input() = default;
	virtual void update(GameObject& g) = 0;
};