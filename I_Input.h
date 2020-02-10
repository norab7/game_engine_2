#pragma once

#include "GameObject.h"

class I_Input {
protected:

public:
	virtual void update(GameObject& g) = 0;

	//virtual void process_keyboard(GameObject& g) = 0;
	//virtual void process_mouse_movement(GameObject& g, double xpos, double ypos) = 0;
	//virtual void process_mouse_scroll(GameObject& g) = 0;
};