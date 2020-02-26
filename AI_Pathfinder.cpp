#include "AI_Pathfinder.h"

AI_Pathfinder::AI_Pathfinder(World* world, glm::vec3 target, float speed) : world_(world), target_(target), speed_(speed) {

}

void AI_Pathfinder::update(GameObject& g) {
	if(!path_found || path_complete) {
		generate_path(g);
	}



}

void AI_Pathfinder::generate_path(GameObject& g) {
	path->search(*world_, g.get_position(), target_);
}

void AI_Pathfinder::receive(int msg) {

}
void AI_Pathfinder::activate() {

}
void AI_Pathfinder::deactivate() {

}