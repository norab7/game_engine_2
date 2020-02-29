#pragma once
#include "GameObject.h"

class I_Collider : public I_Component {
protected:
public:
	virtual ~I_Collider() = default;
	virtual void update(GameObject& Object) = 0;
};