#include "Player_Inputs.h"


Player_Inputs::Player_Inputs(std::shared_ptr<bool[1024]> keys) : KEYS(keys) {

}

void Player_Inputs::update(GameObject& g) {
	process_keyboard(g);
}

void Player_Inputs::receive(int msg) {
	// TODO: incorporate some form of message system
}

void Player_Inputs::process_keyboard(GameObject& g) {
	float deltaSpeed = speed; //  *delta;
	if(KEYS[GLFW_KEY_LEFT_SHIFT]) { deltaSpeed *= 2; }
	if(KEYS[GLFW_KEY_LEFT_ALT]) { deltaSpeed /= 2; }
	if(KEYS[GLFW_KEY_W]) {}	//set_position(get_position() + front * deltaSpeed); }
	if(KEYS[GLFW_KEY_S]) {} //set_position(get_position() - front * deltaSpeed); }
	if(KEYS[GLFW_KEY_A]) {}//set_position(get_position() - right * deltaSpeed); }
	if(KEYS[GLFW_KEY_D]) {} //set_position(get_position() + right * deltaSpeed); }
	if(KEYS[GLFW_KEY_SPACE]) {} //set_position(get_position() + up * deltaSpeed); }
	if(KEYS[GLFW_KEY_LEFT_CONTROL]) {} //set_position(get_position() - up * deltaSpeed); }
}
void Player_Inputs::process_mouse_movement(GameObject& g,double xpos, double ypos) {

}
void Player_Inputs::process_mouse_scroll(GameObject& g) {

}