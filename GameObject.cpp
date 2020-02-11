#include "GameObject.h"

/* Component Includes */
#include "I_Input.h"

GameObject::GameObject(I_Input* input) : input_(input) {
	// Linking Interfaces
	components.push_back(input);
}

void GameObject::update() {
	if(input_ != nullptr) { input_->update(*this); }

	if(x >= 5) { std::cout << "right" << std::endl; x = 0; }
	if(x <= -5) { std::cout << "left" << std::endl; x = 0; }
	if(y >= 5) { std::cout << "up" << std::endl; y = 0; }
	if(y <= -5) { std::cout << "down" << std::endl; y = 0; }
	if(z >= 5) { std::cout << "forward" << std::endl; z = 0; }
	if(z <= -5) { std::cout << "backward" << std::endl; z = 0; }

}

void GameObject::send(int msg) {
	for(unsigned i = 0; i < components.size(); i++) {
		components[i]->receive(msg);
	}
}