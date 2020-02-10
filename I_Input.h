#pragma once
#include "GameObject.h"

class I_Input {
protected:
	virtual void process_keyboard() = 0;
	virtual void process_mouse_movement(double xpos, double ypos) = 0;
	virtual void process_mouse_scroll() = 0;
public:
	virtual void update(GameObject& g) = 0;
};