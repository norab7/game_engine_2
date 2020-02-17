#include "GameObject.h"

/* Component Includes */
#include "I_Graphics.h"
#include "I_Input.h"
#include "I_Camera.h"
#include "I_Physics.h"
#include "I_Emitter.h"

// TODO: Find method of dynamically assigning and replacing components without mentioning via named parent class
GameObject::GameObject(I_Graphics* graphics, I_Input* input, I_Camera* camera, I_Physics* physics, I_Emitter* emitter)
	: graphics_(graphics), input_(input), camera_(camera), physics_(physics), emitter_(emitter) {

	// Linking Interfaces
	if(graphics != nullptr) { components.push_back(graphics); }
	if(input != nullptr) { components.push_back(input); }
	if(camera != nullptr) { components.push_back(camera); }
	if(physics != nullptr) { components.push_back(physics); }
}

void GameObject::update(UPDATE_TYPE update) {
	// TODO: update to switch / nested-ifs for compiler and run-time optimizations
	if(graphics_ != nullptr && (update == UPDATE_TYPE::ALL || update == UPDATE_TYPE::GRAPHICS)) { graphics_->update(*this); }
	if(input_ != nullptr && (update == UPDATE_TYPE::ALL || update == UPDATE_TYPE::INPUT)) { input_->update(*this); }
	if(camera_ != nullptr && (update == UPDATE_TYPE::ALL || update == UPDATE_TYPE::CAMERA)) { camera_->update(*this); }
	if(physics_ != nullptr && (update == UPDATE_TYPE::ALL || update == UPDATE_TYPE::PHYSICS)) { physics_->update(*this, -1); }
	if(emitter_ != nullptr && (update == UPDATE_TYPE::ALL || update == UPDATE_TYPE::EMITTER)) { emitter_->update(*this); }
}

void GameObject::set_velocity(glm::vec3 v) {
	this->velocity = v;
}
void GameObject::set_velocity(float x, float y, float z) {
	this->set_velocity(glm::vec3(x, y, z));
}

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