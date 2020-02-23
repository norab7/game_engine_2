#include "GameObject.h"

/* Component Includes */
#include "I_Graphics.h"
#include "I_Input.h"
#include "I_Camera.h"
#include "I_Physics.h"
#include "I_Emitter.h"
#include "I_AI.h"

// TODO: Find method of dynamically assigning and replacing components without mentioning via named parent class
GameObject::GameObject(glm::vec3 position, I_Graphics* graphics, I_Input* input, I_Camera* camera, I_Physics* physics, I_Emitter* emitter, I_AI* ai)
	: graphics_(graphics), input_(input), camera_(camera), physics_(physics), emitter_(emitter), ai_(ai) {

	// Linking Interfaces
	set_position(position);
	if(graphics != nullptr) { components.push_back(graphics); }
	if(input != nullptr) { components.push_back(input); }
	if(camera != nullptr) { components.push_back(camera); }
	if(physics != nullptr) { components.push_back(physics); }
	if(emitter != nullptr) { components.push_back(emitter); }
	if(ai != nullptr) { components.push_back(ai); }
}

void GameObject::update(UPDATE_TYPE update) {
	// TODO: update to switch / nested-ifs for compiler and run-time optimizations
	if(graphics_ != nullptr && (update == UPDATE_TYPE::ALL || update == UPDATE_TYPE::GRAPHICS)) { graphics_->update(*this); }
	if(input_ != nullptr && (update == UPDATE_TYPE::ALL || update == UPDATE_TYPE::INPUT)) { input_->update(*this); }
	if(camera_ != nullptr && (update == UPDATE_TYPE::ALL || update == UPDATE_TYPE::CAMERA)) { camera_->update(*this); }
	if(physics_ != nullptr && (update == UPDATE_TYPE::ALL || update == UPDATE_TYPE::PHYSICS)) { physics_->update(*this, -1); }
	if(emitter_ != nullptr && (update == UPDATE_TYPE::ALL || update == UPDATE_TYPE::EMITTER)) { emitter_->update(*this); }
	if(ai_ != nullptr && (update == UPDATE_TYPE::ALL || update == UPDATE_TYPE::AI)) { ai_->update(*this); }

	if(glm::length(velocity) > 0) { at_rest = false; }

	if(!at_rest || glm::length(velocity) == 0) {
		glm::vec3 pos(get_position());
		float delta = 0.0025f;

		pos.x += velocity.x * delta;
		pos.y += velocity.y * delta;
		pos.z += velocity.z * delta;

		float stoppage = 0.0005f;
		if(!falling) {
			pos.x = (glm::length(pos.x - get_position().x) <= stoppage) ? get_position().x : pos.x;
			pos.y = (glm::length(pos.y - get_position().y) <= stoppage) ? get_position().y : pos.y;
			pos.z = (glm::length(pos.z - get_position().z) <= stoppage) ? get_position().z : pos.z;
		}

		if(pos.y <= 0) {
			pos.y = 0;
			falling = false;
		} else {
			falling = true;
		}

		set_position(pos);
	}
}

void GameObject::set_velocity(glm::vec3 v) {
	this->velocity = v;
}
void GameObject::set_velocity(float x, float y, float z) {
	this->set_velocity(glm::vec3(x, y, z));
}

// TODO: update to allow sending messages to game objects, may require giving them an id to distinguish them
void GameObject::send(int msg) {
	for(unsigned i = 0; i < components.size(); i++) {
		components[i]->receive(msg);
	}
}

glm::mat4 GameObject::get_matrix() {
	return this->matrix;
}

const glm::vec3 GameObject::get_position() const {
	return glm::vec3(matrix[3][0], matrix[3][1], matrix[3][2]);
}

void GameObject::set_position(glm::vec3 pos) {
	matrix[3][0] = pos.x;
	matrix[3][1] = pos.y;
	matrix[3][2] = pos.z;
}

void GameObject::transform(glm::mat4 trans) {
	matrix *= trans;
}

void GameObject::translate(glm::vec3 trans) {
	matrix = glm::translate(matrix, trans);
}

void GameObject::rotate(float angle, glm::vec3 axis, bool radians) {
	matrix = glm::rotate(matrix, (radians) ? angle : glm::radians(angle), axis);
}

void GameObject::scale(float scale) {
	matrix = glm::scale(matrix, glm::vec3(scale));
}

void GameObject::scale(glm::vec3 scale) {
	matrix = glm::scale(matrix, scale);
}