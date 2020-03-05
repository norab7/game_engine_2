#include "AI_Waypoint.h"

AI_Waypoint::AI_Waypoint(std::vector<glm::vec3>& waypoints) : WAYPOINTS_(waypoints) {
}

void AI_Waypoint::update(GameObject& g) {
	if(glm::length(WAYPOINTS_[INDEX_] - g.get_position()) <= TOLERANCE_) {
		INDEX_ = ++INDEX_ % WAYPOINTS_.size();
	}

	// 600 is 10 times the 1/60 ms_update
	float speed = glm::length(WAYPOINTS_[INDEX_] - g.get_position()) / (g.delta_time * 600);
	glm::vec3 direction = glm::normalize(WAYPOINTS_[INDEX_] - g.get_position());

	g.velocity += (direction * speed);
}

void AI_Waypoint::receive(std::string component, std::string action) {

}
void AI_Waypoint::activate() {

}
void AI_Waypoint::deactivate() {

}