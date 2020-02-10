#include "GameObject.h"

GameObject::GameObject() {
	// Linking Interfaces
}

void GameObject::update() {
	// if(input_ != nullptr) { input_->update(*this); }

	std::cout << "Position(" << x << ", " << y << ", " << z << ")" << std::endl;
}