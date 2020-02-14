#include "Player_Camera.h"

Player_Camera::Player_Camera(const std::pair<float, float>& offset) : mouse_offset(&offset) {

}

void Player_Camera::update(GameObject& g) {
	// TODO: add in some checking code to only update front, right, up when required

	if(!has_target) {
		std::cout << "now has a target" << std::endl;
		has_target = true;
		g.front = glm::normalize(g.get_position() - glm::vec3(g.get_position().x, g.get_position().y, g.get_position().z - 1));
		g.right = glm::normalize(glm::cross(g.world_up, g.front));
		g.up = glm::normalize(glm::cross(g.front, g.right));
		g.front = glm::normalize(-g.front);
	}

	float sensitivity = 0.025f;
	yaw += mouse_offset->first * sensitivity;
	pitch += mouse_offset->second * sensitivity;
	if(pitch > 89.0f) { pitch = 89.0f; }
	if(pitch < -89.0f) { pitch = -89.0f; }

	g.front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	g.front.y = sin(glm::radians(pitch));
	g.front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	g.front = glm::normalize(g.front);

	g.right = glm::normalize(glm::cross(g.world_up, g.front));
	g.up = glm::normalize(glm::cross(g.right, g.front));

	g.view = glm::lookAt(g.get_position(), g.get_position() + g.front, g.up);
}

void Player_Camera::receive(int message) {

}

void Player_Camera::activate() {

}
void Player_Camera::deactivate() {

}