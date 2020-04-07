#include "Player_Keyboard.h"
#include <glfw3.h>

Player_Keyboard::Player_Keyboard(const bool(&KEY_MAP)[1024]) : key_map(KEY_MAP) {

}

void Player_Keyboard::update(GameObject& g) {
	float deltaSpeed = speed * g.delta_time;
	if(key_map[GLFW_KEY_LEFT_SHIFT]) { deltaSpeed *= modifier; }
	if(key_map[GLFW_KEY_LEFT_ALT]) { deltaSpeed /= modifier; }
	if(key_map[GLFW_KEY_W]) { g.set_position(g.get_position() + g.flat_front * deltaSpeed); }
	if(key_map[GLFW_KEY_S]) { g.set_position(g.get_position() - g.flat_front * deltaSpeed); }
	if(key_map[GLFW_KEY_A]) { g.set_position(g.get_position() - g.right * deltaSpeed); }
	if(key_map[GLFW_KEY_D]) { g.set_position(g.get_position() + g.right * deltaSpeed); }
	if(key_map[GLFW_KEY_SPACE]) { g.set_position(g.get_position() + g.world_up * deltaSpeed); }
	if(key_map[GLFW_KEY_LEFT_CONTROL]) { g.set_position(g.get_position() - g.world_up * deltaSpeed); }

	//if(key_map[GLFW_KEY_W]) { g.velocity += g.flat_front * deltaSpeed; }
	//if(key_map[GLFW_KEY_S]) { g.velocity -= g.flat_front * deltaSpeed; }
	//if(key_map[GLFW_KEY_A]) { g.velocity -= g.right * deltaSpeed; }
	//if(key_map[GLFW_KEY_D]) { g.velocity += g.right * deltaSpeed; }
	//if(key_map[GLFW_KEY_SPACE]) { g.velocity += g.world_up * deltaSpeed; }
	//if(key_map[GLFW_KEY_LEFT_CONTROL]) { g.velocity -= g.world_up * deltaSpeed; }

	float limit = 0.5f;
	while(glm::length(glm::vec3(g.velocity.x, 0, g.velocity.z)) >= limit) {
		g.velocity = glm::vec3(g.velocity.x * limit, g.velocity.y, g.velocity.z * limit);
	}

	if(key_map[GLFW_KEY_M]) { std::cout << "Position: (" << g.get_position().x << "," << g.get_position().y << "," << g.get_position().z << ")" << std::endl; }
}

void Player_Keyboard::receive(std::string component, std::string action) {
	// TODO: incorporate some form of message system
}

void Player_Keyboard::activate() {

}

void Player_Keyboard::deactivate() {

}