#include "Player_Inputs.h"
#include <glfw3.h>

bool reset = false;

Player_Inputs::Player_Inputs(bool (&KEY_MAP)[1024]) : key_map(KEY_MAP) {

}

void Player_Inputs::update(GameObject& g) {
	process_keyboard(g);
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
	if(key_map[GLFW_KEY_LEFT_ALT]) { deltaSpeed /= 2;  }
	if(key_map[GLFW_KEY_W]) { g.z += deltaSpeed; }	//set_position(get_position() + front * deltaSpeed); }
	if(key_map[GLFW_KEY_S]) { g.z -= deltaSpeed; } //set_position(get_position() - front * deltaSpeed); }
	if(key_map[GLFW_KEY_A]) { g.x -= deltaSpeed; }//set_position(get_position() - right * deltaSpeed); }
	if(key_map[GLFW_KEY_D]) { g.x += deltaSpeed; } //set_position(get_position() + right * deltaSpeed); }
	if(key_map[GLFW_KEY_SPACE]) { g.y += deltaSpeed; } //set_position(get_position() + up * deltaSpeed); }
	if(key_map[GLFW_KEY_LEFT_CONTROL]) { g.y -= deltaSpeed; } //set_position(get_position() - up * deltaSpeed); }

	g.send(g.x + g.y + g.z);

}
void Player_Inputs::process_mouse_movement(GameObject& g, double xpos, double ypos) {

}
void Player_Inputs::process_mouse_scroll(GameObject& g) {

}