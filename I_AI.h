#pragma once
#include "GameObject.h"

class I_AI : public I_Component {
protected:
public:
	virtual ~I_AI() = default;
	virtual void update(GameObject& Object) = 0;
};