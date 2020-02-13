#include "Player_Inputs.h"
#include <glfw3.h>

bool reset = false;

Player_Inputs::Player_Inputs(const bool(&KEY_MAP)[1024], const std::pair<float, float>& mouse) : key_map(KEY_MAP), mouse_offset(&mouse) {

}

void Player_Inputs::update(GameObject& g) {
	process_keyboard(g);
	process_mouse_movement(g);
	if(reset) { g.x = 0, g.y = 0, g.z = 0; }
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
	float deltaSpeed = speed; //  *delta;
	if(key_map[GLFW_KEY_LEFT_SHIFT]) { deltaSpeed *= 2; }
	if(key_map[GLFW_KEY_LEFT_ALT]) { deltaSpeed /= 2; }
	if(key_map[GLFW_KEY_W]) { g.transform.set_position(g.transform.get_position() + g.transform.front * deltaSpeed); }	//set_position(get_position() + front * deltaSpeed); }
	if(key_map[GLFW_KEY_S]) { g.transform.set_position(g.transform.get_position() - g.transform.front * deltaSpeed); } //set_position(get_position() - front * deltaSpeed); }
	if(key_map[GLFW_KEY_A]) { g.transform.set_position(g.transform.get_position() - g.transform.right * deltaSpeed); }//set_position(get_position() - right * deltaSpeed); }
	if(key_map[GLFW_KEY_D]) { g.transform.set_position(g.transform.get_position() + g.transform.right * deltaSpeed); } //set_position(get_position() + right * deltaSpeed); }
	if(key_map[GLFW_KEY_SPACE]) { g.transform.set_position(g.transform.get_position() + g.transform.up * deltaSpeed); } //set_position(get_position() + up * deltaSpeed); }
	if(key_map[GLFW_KEY_LEFT_CONTROL]) { g.transform.set_position(g.transform.get_position() - g.transform.up * deltaSpeed); } //set_position(get_position() - up * deltaSpeed); }

	g.send(g.x + g.y + g.z);
	if(reset) { g.x = 0, g.y = 0, g.z = 0; }
}
void Player_Inputs::process_mouse_movement(GameObject& g) {
	float yaw = mouse_offset->first * 0.05;
	float pitch = mouse_offset->second * 0.05;

	if(pitch > 89.0f) { pitch = 89.0f; }
	if(pitch < -89.0f) { pitch = -89.0f; }

	g.send(-1); // TODO: Change to sending message to camera interfaces for updating viewport

	// std::cout << "Mouse: ("<< yaw << "," << pitch << ")" << std::endl;
}

void Player_Inputs::process_mouse_scroll(GameObject& g) {

}