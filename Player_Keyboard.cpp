#include "Player_Keyboard.h"
#include <glfw3.h>

Player_Keyboard::Player_Keyboard(const bool(&KEY_MAP)[1024]) : key_map(KEY_MAP) {

}

void Player_Keyboard::update(GameObject& g) {
	float deltaSpeed = speed; //  *delta;
	if(key_map[GLFW_KEY_LEFT_SHIFT]) { deltaSpeed *= 2; }
	if(key_map[GLFW_KEY_LEFT_ALT]) { deltaSpeed /= 2; }
	if(key_map[GLFW_KEY_W]) { g.set_position(g.get_position() + g.front * deltaSpeed); }
	if(key_map[GLFW_KEY_S]) { g.set_position(g.get_position() - g.front * deltaSpeed); }
	if(key_map[GLFW_KEY_A]) { g.set_position(g.get_position() - g.right * deltaSpeed); }
	if(key_map[GLFW_KEY_D]) { g.set_position(g.get_position() + g.right * deltaSpeed); }
	if(key_map[GLFW_KEY_SPACE]) { g.set_position(g.get_position() + g.up * deltaSpeed); }
	if(key_map[GLFW_KEY_LEFT_CONTROL]) { g.set_position(g.get_position() - g.up * deltaSpeed); }

	if(key_map[GLFW_KEY_M]) { std::cout << "Position: (" << g.get_position().x << "," << g.get_position().y << "," << g.get_position().z << ")" << std::endl; }
}

void Player_Keyboard::receive(int msg) {
	// TODO: incorporate some form of message system
}

void Player_Keyboard::activate() {

}

void Player_Keyboard::deactivate() {

}