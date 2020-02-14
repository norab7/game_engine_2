#include "Player_Inputs.h"
#include <glfw3.h>

bool reset = false;

Player_Inputs::Player_Inputs(const bool(&KEY_MAP)[1024], const std::pair<float, float>& mouse) : key_map(KEY_MAP), mouse_offset(&mouse) {

}

void Player_Inputs::update(GameObject& g) {
	float deltaSpeed = speed; //  *delta;
	if(key_map[GLFW_KEY_LEFT_SHIFT]) { deltaSpeed *= 2; }
	if(key_map[GLFW_KEY_LEFT_ALT]) { deltaSpeed /= 2; }
	if(key_map[GLFW_KEY_W]) { g.set_position(g.get_position() + g.front * deltaSpeed); }
	if(key_map[GLFW_KEY_S]) { g.set_position(g.get_position() - g.front * deltaSpeed); }
	if(key_map[GLFW_KEY_A]) { g.set_position(g.get_position() - g.right * deltaSpeed); }
	if(key_map[GLFW_KEY_D]) { g.set_position(g.get_position() + g.right * deltaSpeed); }
	if(key_map[GLFW_KEY_SPACE]) { g.set_position(g.get_position() + g.up * deltaSpeed); }
	if(key_map[GLFW_KEY_LEFT_CONTROL]) { g.set_position(g.get_position() - g.up * deltaSpeed); }
}

void Player_Inputs::receive(int msg) {
	// TODO: incorporate some form of message system
	if(msg >= 5) {
		std::cout << "Input Recieved Message: " << msg << " | Resetting position" << std::endl;
		reset = true;
	} else {
		reset = false;
	}
}

void Player_Inputs::process_keyboard(GameObject& g) {

}
void Player_Inputs::process_mouse_movement(GameObject& g) {
	float sensitivity = 0.025f;
	float yaw = mouse_offset->first * sensitivity;
	float pitch = mouse_offset->second * sensitivity;
	if(pitch > 89.0f) { pitch = 89.0f; }
	if(pitch < -89.0f) { pitch = -89.0f; }
	
}

void Player_Inputs::process_mouse_scroll(GameObject& g) {

}