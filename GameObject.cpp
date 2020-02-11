#include "GameObject.h"

#include "I_Input.h"

GameObject::GameObject(I_Input* input) : input_(input) {
	// Linking Interfaces
}

void GameObject::update() {
	// if(input_ != nullptr) { input_->update(*this); }

	input_->update(*this);

	std::cout << "Position(" << x << ", " << y << ", " << z << ")" << std::endl;
}