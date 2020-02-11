#include "GameObject.h"

/* Component Includes */
#include "I_Input.h"
#include "I_Graphics.h"

GameObject::GameObject(I_Graphics* graphics, I_Input* input) : graphics_(graphics), input_(input) {
	// Linking Interfaces
	components.push_back(graphics);
	components.push_back(input);
}

void GameObject::update(UPDATE_TYPE update) {
	if(input_ != nullptr && (update == UPDATE_TYPE::ALL || update == UPDATE_TYPE::INPUT)) { input_->update(*this); }
	if(graphics_ != nullptr && (update == UPDATE_TYPE::ALL || update == UPDATE_TYPE::GRAPHICS)) { graphics_->update(*this); }

	if(x >= 3) { std::cout << "right" << std::endl; x = 0; }
	if(x <= -3) { std::cout << "left" << std::endl; x = 0; }
	if(y >= 3) { std::cout << "up" << std::endl; y = 0; }
	if(y <= -3) { std::cout << "down" << std::endl; y = 0; }
	if(z >= 3) { std::cout << "forward" << std::endl; z = 0; }
	if(z <= -3) { std::cout << "backward" << std::endl; z = 0; }

}

void GameObject::send(int msg) {
	for(unsigned i = 0; i < components.size(); i++) {
		components[i]->receive(msg);
	}
}